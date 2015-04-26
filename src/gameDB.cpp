/** Implementation of the Game Database Class
 * @author Henry J Schmale
 * @date November 4, 2014
 * @file src/gameDB.cpp
 */

#include "../include/gameDB.h"
#include <stdio.h>
#include <sstream>
#include <SFML/Network.hpp>
#include "../include/GameMenu.h"

const std::string HOST = "numberhuntergame.com";
const short PORT = 80;

extern GameDifficulty DIFFICULTY;

static std::vector<std::string> vecStrHS;
std::stringstream ss1;
std::stringstream ss2;

#ifdef SQLITE_DB_USED
static int retHighScores(void *data, int argc, char **argv, char **azColName)
{
    for(int i = 0; i < argc; i += 2)
    {
        ss1 << argv[i] << "\n";
        ss2 << argv[i + 1] << "\n";
    }
    return 0;
}
#endif // SQLITE_DB_USED

// ===========================================================================
// constructors & Destructors
gameDB::gameDB(int totalLvls)
{
    //ctor
    hjs::logToConsole("Instance of gameDB created");
}

gameDB::~gameDB()
{

}

/// public funcs
void gameDB::addScoreRecord(std::string name, int score, int salvageCount,
                            int asteroidCount, int level)
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
        std::cout << "request failed: " << response.getStatus() << "\tContent= "
                  << response.getBody() << std::endl;
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
            if(temp[i] == ' ') // found a delimiter
            {
                if(bWritingName)
                {
                    ss1 << std::endl;
                }
                else
                {
                    ss2 << std::endl;
                }
                bWritingName = !bWritingName; //if was writing a name, now writing a score
                continue; // skip as this will just write garbage into the string stream
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
        // Failed to get scores
        std::cout << "request failed: " << response.getStatus() << "\tContent= "
                  << response.getBody() << std::endl;
        for(int i = 0; i < 10; i++)
        {
            ss1 << "NULL" << std::endl;
            ss2 << "NULL" << std::endl;
        }
        vecStrHS[0] = ss1.str();
        vecStrHS[1] = ss2.str();
        return vecStrHS;
    }
}
