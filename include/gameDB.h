#ifndef GAMEDB_H
#define GAMEDB_H

#include <string>
#include <vector>
#include <sqlite3.h>
#include "../Hjs_StdLib.h"

// defines for database paths
#ifdef TSA_BUILD
#define DB_PATH NULL // make the db for the TSA competition a temp in memory
#else
#define DB_PATH "NumberHunter.db" // for release builds use a persistant database file
#endif // TSA_BUILD

// defines for table names
#define TB_LVL_FSTR "Level%d_Scores"
#define TB_HIGHSCORES "HighScores"

class gameDB
{
public:
    gameDB(int totalLvls);
    ~gameDB();

    /// adds a score record to the selected tbName
    void addScoreRecord(std::string name, int score, int salvageCount, int asteroidCount, int level);

    /// gets the limit num of records sorted for a highscores table from tbName
    std::vector<std::string> getHighScoreString(int level, int limit);
protected:
private:
    // private funcs
    void initStatsTable(char *tbname);

    // Submit to server
    bool pingServer(); // returns true on successful connection to server
    void addScoreNetwork(std::string name, int score, int salvageCount, int asteroidCount, int level);
    std::vector<std::string> getHS_Network(int level, int limit);

    // Use local db
    void addScoreLocal(std::string name, int score, int salvageCount, int asteroidCount, int level);
    std::vector<std::string> getHS_Local(int level, int limit);

    // private objects
    sqlite3 *m_db;
    bool m_NetworkIsAvailable;
};

#endif // GAMEDB_H
