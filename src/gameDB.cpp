#include "gameDB.h"
#include <stdio.h>
#include <sstream>
#include <SFML/Network.hpp>
#include "GameMenu.h"

const std::string HOST = "numberhuntergame.com";
const short PORT = 80;

extern GameDifficulty DIFFICULTY;

/// define sql scripts used, these should be FILE GLOBALS
/// @note sql script strings have 'sql_' prefixed

// creates a table to hold high scores and who got thems
static const char sql_StatsTBCreateFSTR[] = "create table if not exists %s(ID INTEGER PRIMARY KEY AUTOINCREMENT,"
		"DATE TEXT NOT NULL,"
		"NAME TEXT NOT NULL,"
		"SCORE INTEGER NOT NULL,"
		"Salvage_Collected Integer,"
		"Asteroids_Destroyed Integer);";

/// adds a record to scores table, note this is a format string for snprintf
static const char sql_ScoreInsertFSTR[] = "Insert into %s(DATE, NAME, Score, Salvage_COLLECTED, Asteroids_Destroyed) Values(CURRENT_TIMESTAMP, '%s', %d, %d, %d);";

/// fetches a list of highscores with just names and score sorted so that highest is at the top
static const char sql_FetchHighScores[] = "Select name, score from %s where score > 0 order by score desc limit %d;";

// func needed for sqlite execution
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	return 0;
}

// sqlite callback for sql scores
static std::vector<std::string> vecStrHS;
std::stringstream ss1;
std::stringstream ss2;
static int retHighScores(void *data, int argc, char **argv, char **azColName)
{
	for(int i = 0; i < argc; i += 2)
	{
		ss1 << argv[i] << "\n";
		ss2 << argv[i + 1] << "\n";
	}
	return 0;
}

// ===========================================================================
// constructors & Destructors
gameDB::gameDB(int totalLvls)
{
	//ctor
	//char *zErrMsg = 0;
	int rc = sqlite3_open(DB_PATH, &m_db);
	if( rc )
	{
		hjs::logTimeToConsole();
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(m_db));
		exit(0);
	}
	else
	{
		hjs::logToConsole("Opened Database Success");
	}
	/*initStatsTable((char*)(TB_HIGHSCORES));
	for(int i = 1; i <= totalLvls; i++)
	{
		char buff[20];
		snprintf(buff, 20, TB_LVL_FSTR, i);
		initStatsTable(buff);
	}*/
}

gameDB::~gameDB()
{
	sqlite3_close(m_db);
}

/// public funcs
void gameDB::addScoreRecord(std::string name, int score, int salvageCount, int asteroidCount, int level)
{
	// limit the length of the name to the max that the server can handle
	if(name.length() > 28)
	{
		name = name.substr(0, 28);
	}

	// prepare the request
	sf::Http::Request request("/addScore.php", sf::Http::Request::Post);

	// encode the parameters in the request body
	std::ostringstream stream;
	stream << "name=" << name << "&score=" << score << "&level=" << level
		   << "&salvage=" << salvageCount << "&asteroids=" << asteroidCount
		   << "&diff=" << DIFFICULTY;
	request.setBody(stream.str());

	// send the request
	sf::Http http(HOST);
	sf::Http::Response response = http.sendRequest(request);

	// check the status
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		// check the contents of the response
		std::cout << response.getBody() << std::endl;
	}
	else
	{
		std::cout << "request failed: " << response.getStatus() << "\tContent= " << response.getBody() << std::endl;
	}
}

/// @todo parse the callback for sql
std::vector<std::string> gameDB::getHighScoreString(int level, int limit)
{
	// prepare the request
	sf::Http::Request request("/getHighScores.php", sf::Http::Request::Post);

	// encode the parameters in the request body
	std::ostringstream stream;
	stream << "Level=" << level << "&diff="
	<< DIFFICULTY;
	request.setBody(stream.str());

	// send the request
	sf::Http http(HOST);
	sf::Http::Response response = http.sendRequest(request);

	// get Highscores
	std::string temp;
	vecStrHS.clear();
	vecStrHS.push_back(std::string());
	vecStrHS.push_back(std::string());

	ss1.str(std::string());
	ss2.str(std::string());
	ss1 << "Player Name:\n";	// names
	ss2 << "Score:\n";			// scores
	if (response.getStatus() == sf::Http::Response::Ok)
	{
		// check the contents of the response
		temp = response.getBody();	// holds a list delimited by spaces
		std::cout << response.getBody();
		bool bWritingName = true;
		for(unsigned int i = 0; i < temp.length(); i++)
		{
			if(temp[i] == ' ')
			{
				if(bWritingName)
					ss1 << std::endl;
				else
					ss2 << std::endl;
				bWritingName = !bWritingName;
				continue;
			}
			if(bWritingName == true)
			{
				ss1 << temp[i];
			}
			else
			{
				ss2 << temp[i];
			}
		}
		vecStrHS[0] = ss1.str();
		vecStrHS[1] = ss2.str();
		return vecStrHS;
	}
	else
	{
		std::cout << "request failed: " << response.getStatus() << "\tContent= " << response.getBody() << std::endl;
		for(int i = 0; i < 10; i++){
			ss1 << "NULL"; ss2 << "NULL";
		}
		vecStrHS[0] = ss1.str();
		vecStrHS[1] = ss2.str();
		return vecStrHS;
	}
	/*ss1.str(std::string());
	ss2.str(std::string());
	ss1 << "Player Name:\n";
	ss2 << "Score:\n";
	vecStrHS.clear();
	vecStrHS.push_back(std::string());
	vecStrHS.push_back(std::string());
	// create insert statement using FSTR and Arguments
	char sql[512];
	snprintf(sql, 512, sql_FetchHighScores, tbName, limit);

	// perform sql querry
	char *zErrMsg = 0;
	int rc;
	rc = sqlite3_exec(m_db, sql, retHighScores, 0, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		hjs::logTimeToConsole();
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		hjs::logToConsole("Got highscore records");
	}
	vecStrHS[0] = ss1.str();
	vecStrHS[1] = ss2.str();
	return vecStrHS;*/
}

/// Private funcs
void gameDB::initStatsTable(char *tbname)
{
	// create insert statement using FSTR and Arguments
	char sql[512];
	snprintf(sql, 512, sql_StatsTBCreateFSTR, tbname);

	char *zErrMsg = 0;
	int  rc;
	// create highscores table
	rc = sqlite3_exec(m_db, sql, callback, 0, &zErrMsg);
	if( rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else
	{
		hjs::logTimeToConsole();
		fprintf(stdout, "%s Table created successfully\n", tbname);
	}
}

