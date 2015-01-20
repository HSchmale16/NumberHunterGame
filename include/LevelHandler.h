/** LevelHandler Class
*	Handles the loading of levels from file
*	Also has a member function to handle the drawing of targets at top of screen.
*	Will also handle game pausing as well
*	Handles level ending as well
*	@author Henry Schmale
*	@date October 27, 2014
*/

#ifndef LEVELHANDLER_H
#define LEVELHANDLER_H

#include <SFML/Graphics.hpp>    // for drawing this to screen
#include <time.h>
#include <string>				// for selecting next section header
#include "gameDB.h"
#include "LevelEndScreen.h"
#include "../INIReader.h"
#include "../LevelDatTypes.h"

class LevelHandler: public sf::Drawable
{
public:
	LevelHandler();
	LevelHandler(std::string playerName);
	virtual ~LevelHandler();

	// dispatches to type handler
	void checkLevelStatus();			// checks the status for the current level and flips the levelInProgress if the requirements are met

	// Status Update Funcs for game stats
	void addCollectedSalvage(int n);	// adds n to the count of collected salvage
	void addKilledAsteroids(int n);		// adds n to the count of killed asteroids
	void updateScore(int n);			// updates the current score

	// Game pausing handlers
	void pauseGame();
	void unPause();

	// getters & setters
	bool getLevelInProgress();			// returns true if a level is currently in progress
protected:
private:
	// private functions
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	// Loads the parameters for the next level and starts the next levels
	void incrementLevel();

	// updates the GUI at the top
	void updateGUI();

	// Time Updater
    void updateTimer();

    // Level Ender
    void endLevel();

	// handlers for each of the level types
	// handler funcs are prefaced with an h_
	void h_kill();	// attack goal
	void h_score();
	void h_survive();
	void h_collect();

	// gets the level type to set the type of the enumeration
	LevelType parseType();

	// dynamically allocated items
	INIReader *m_reader;				// Ini parser to handle loading of levels
	LevelSettings *m_settings;			// settings to test for end of level
	LevelStats *m_currStats;			// player's current stats for the level
	gameDB *m_gDB;						// game database for scores and such

	// member data
	bool m_levelInProgress;				// is a level currently in progress
	bool m_timeLimitInLevel;			// does the level have a time limit
	int m_totalNumLevels;				// total number of levels in game
	int m_currentLevel;					// level currently active
	std::string m_LevelSectionHeader;	// the ini file header to access the data to create the current level
	std::string m_TargetStr;			// Visible string to target of level
	std::string m_PlayerName;			// Name of player to insert into db
    int m_TimeRemaining;				// how much time remains in the level
    float m_prevCompletionPercent;		// previous completion percentage
    float m_currCompletionPercent;		// current completion percentage

	// ui elements
	sf::Font m_font;
	sf::Text m_GoalText;				// tell what the goal of the level is
	sf::Text m_LevelText;				// tell what level the player is currently on
	sf::Text m_CountDownText;			// tells how much time remains in the lvl
	sf::RectangleShape m_ProgressMeter;	// Tells how close to completion the level is
	sf::RectangleShape m_RsBg;			// Main Background of level gui
	sf::RectangleShape m_PauseScreen;	// pausescreen drawn on top

	LevelEndScreen *m_lvlEndScreen;		// level end screen
};

#endif // LEVELHANDLER_H
