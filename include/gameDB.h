/** Game Database
 * \author Henry J Schmale
 * \date November 4, 2014
 * \file include/gameDB.h
 */
#ifndef GAMEDB_H
#define GAMEDB_H

#include <string>
#include <vector>
//#include <sqlite3.h>
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

    /**\brief  adds a score record to the selected level table
     * \param  player        name of player
     * \param  score         score gotten on level
     * \param  salvageCount  good salvage collected
     * \param  asteroidCount asteroids destroyed
     * \param  level         the level the values are good for.
     * \return nothing
     * \note   Can be blocking due to network latency and socket timeouts, because it
     *         makes an HTTP request to a web server.
     */
    void addScoreRecord(std::string name, int score, int salvageCount, int asteroidCount,
                        int level);

    /**\brief  gets limit high scores sorted descending for the selected level
     * \param  level the level to get scores for
     * \param  limit number of scores to get
     * \return a vector of strings with appropriate headers. Element 0 of the vector
     *         contains the names of players. Element 1 contains the scores. Each string
     *         has the values delimited by newlines.
     * \note   This function makes a network request for the scores and it can be
     *         blocking depending on socket timeouts on the client system.
     */
    std::vector<std::string> getHighScoreString(int level, int limit);
protected:
private:
    // Submit to server
    bool pingServer(); // returns true on successful connection to server
    void addScoreNetwork(std::string name, int score, int salvageCount, int asteroidCount, int level);
    std::vector<std::string> getHS_Network(int level, int limit);

    // Use local db
    void addScoreLocal(std::string name, int score, int salvageCount, int asteroidCount, int level);
    std::vector<std::string> getHS_Local(int level, int limit);

    // private objects
    bool m_NetworkIsAvailable;
};

#endif // GAMEDB_H
