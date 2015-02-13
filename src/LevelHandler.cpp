/** Implementation of LevelHandler Class
*	@author Henry Schmale
*	@date October 27, 2014
*/

#include <stdio.h>			// for snprintf
#include <stdlib.h>			// for exit
#include "../include/LevelHandler.h"
#include "../FilePaths.h"	// for loading level config
#include "../Hjs_StdLib.h"
#include "../include/UI.h"

extern UI *myUI;

static clock_t lastClock = clock();	// file scope global to set up timing

LevelHandler::LevelHandler()	// ctor
{
	// allocate objects
	m_reader = new INIReader(LEVEL_CONFIG_FILE);
	m_settings = new LevelSettings;
	m_currStats = new LevelStats;

	// set members
	m_levelInProgress = true;
	m_currentLevel = 0;	// must be 0, b/c increment level updates this to 1 at entry
	m_totalNumLevels = m_reader->GetInteger("MAIN_CONF", "level_count", 5);

	m_currStats->asteroidsKilled = 0;
	m_currStats->salvageCollected = 0;
	m_currStats->score = 0;

	// init gui
	if(!m_texBG.loadFromFile(config.Get("ui_config", "ui_texture", "NULL"))){
		hjs::logToConsole("Failed to load ui texture");
		exit(2);
	}
	if(!m_font.loadFromFile(MAIN_FONT))
	{
		hjs::logToConsole("Couldn't load Font: MAIN_FONT");
		exit(1);
	}
	m_GoalText.setCharacterSize(12);
	m_GoalText.setColor(sf::Color::White);
	m_GoalText.setFont(m_font);

	m_LevelText.setCharacterSize(12);
	m_LevelText.setColor(sf::Color::White);
	m_LevelText.setFont(m_font);
	m_LevelText.setString("Level 1");

	m_RsBg.setSize(sf::Vector2f(375, 60));
	m_RsBg.setPosition(0, 0);
	//m_RsBg.setFillColor(sf::Color::Blue );
  m_RsBg.setTexture(&m_texBG);

	m_ProgressMeter.setSize(sf::Vector2f(50, -50));
	m_ProgressMeter.setFillColor(sf::Color::Red);
	m_ProgressMeter.setPosition(250, 55);

	m_CountDownText.setCharacterSize(12);
	m_CountDownText.setColor(sf::Color::White);
	m_CountDownText.setFont(m_font);
	m_CountDownText.setString("60");

	m_PauseScreen.setPosition(0, 0);	// set up pause screen
	m_PauseScreen.setSize(sf::Vector2f(375, 650));
	m_PauseScreen.setFillColor(sf::Color(64, 64, 64));

	m_PlayerName = "Player";

	m_gDB = new gameDB(m_totalNumLevels);	// launch gameDB for highscore handling
	m_lvlEndScreen = new LevelEndScreen();

	// function calls
	incrementLevel();
	updateGUI();
}

LevelHandler::LevelHandler(std::string playerName)
{
	//ctor
	// allocate objects
	m_reader = new INIReader(LEVEL_CONFIG_FILE);
	m_settings = new LevelSettings;
	m_currStats = new LevelStats;

	// set members
	m_levelInProgress = true;
	m_currentLevel = 0;	// must be 0, b/c increment level updates this to 1 at entry
	m_totalNumLevels = m_reader->GetInteger("MAIN_CONF", "level_count", 5);

	m_currStats->asteroidsKilled = 0;
	m_currStats->salvageCollected = 0;
	m_currStats->score = 0;

	// init gui
	if(!m_texBG.loadFromFile(config.Get("ui_config", "ui_texture", "NULL"))){
		hjs::logToConsole("Failed to load ui texture");
		exit(2);
	}
	if(!m_font.loadFromFile(MAIN_FONT))
	{
		hjs::logToConsole("Couldn't load Font: MAIN_FONT");
		exit(1);
	}
	m_GoalText.setCharacterSize(12);
	m_GoalText.setColor(sf::Color::White);
	m_GoalText.setFont(m_font);

	m_LevelText.setCharacterSize(12);
	m_LevelText.setColor(sf::Color::White);
	m_LevelText.setFont(m_font);
	m_LevelText.setString("Level 1");

	m_RsBg.setSize(sf::Vector2f(375, 60));
	m_RsBg.setPosition(0, 0);
	m_RsBg.setFillColor(sf::Color::White);
	m_RsBg.setTexture(&m_texBG);

	m_ProgressMeter.setSize(sf::Vector2f(50, -50));
	m_ProgressMeter.setFillColor(sf::Color::Red);
	m_ProgressMeter.setPosition(250, 55);

	m_CountDownText.setCharacterSize(12);
	m_CountDownText.setColor(sf::Color::White);
	m_CountDownText.setFont(m_font);
	m_CountDownText.setString("60");

	m_PauseScreen.setPosition(0, 0);	// set up pause screen
	m_PauseScreen.setSize(sf::Vector2f(375, 600));
	m_PauseScreen.setFillColor(sf::Color(64, 64, 64, 200));

	m_PlayerName = playerName;

	m_gDB = new gameDB(m_totalNumLevels);	// launch gameDB for highscore handling
	m_lvlEndScreen = new LevelEndScreen();

	// function calls
	incrementLevel();
	updateGUI();
}

LevelHandler::~LevelHandler()	// dtor
{
	//dtor
	delete m_reader;
	delete m_settings;
	delete m_currStats;
	delete m_lvlEndScreen;
}

// public functions
void LevelHandler::addCollectedSalvage(int n)
{
	if(n != 0)
	{
		m_currStats->salvageCollected += n;
		// update the GUI
	}
}

void LevelHandler::addKilledAsteroids(int n)
{
	if(n != 0)
	{
		m_currStats->asteroidsKilled += n;
		// update the GUI
	}
}

// just updates the score of current stats, b/c it would be too complex just to add the score
void LevelHandler::updateScore(int n)
{
	int oldScore = m_currStats->score;
	m_currStats->score = n;
	if(oldScore != m_currStats->score)
	{
		// update the GUI
	}
}

void LevelHandler::checkLevelStatus()
{
	updateTimer();
	switch(m_settings->type)
	{
	case CLEAR_ASTEROIDS:
		h_kill();
		break;
	case SALVAGE_COLLECTION_TARGET:
		h_collect();
		break;
	case SCORE_TARGET:
		h_score();
		break;
	case SURVIVAL:
		h_survive();
		break;
	}
	updateGUI();
}

void LevelHandler::pauseGame()
{
	m_levelInProgress = false;
}

void LevelHandler::unPause()
{
	m_levelInProgress = true;
	lastClock = clock();
}

// returns true if a level is currently in progress
bool LevelHandler::getLevelInProgress()
{
	return m_levelInProgress;
}

/*! private funcs !*/
void LevelHandler::incrementLevel()
{
	hjs::logToConsole("Incrementing Level");
	m_levelInProgress = false;
	// add a record for the current level
	char buff2[30];
	snprintf(buff2, 30, TB_LVL_FSTR, m_currentLevel);
	m_gDB->addScoreRecord(m_PlayerName, m_currStats->score, m_currStats->salvageCollected, m_currStats->asteroidsKilled, m_currentLevel);

	if(m_currentLevel < m_totalNumLevels)
	{
		if(m_currentLevel != 0)
		{
			m_lvlEndScreen->setVisible(true);
			m_lvlEndScreen->updateLevelData(m_currStats, m_settings, m_currentLevel);
			m_lvlEndScreen->updateHighScoreTable(m_gDB->getHighScoreString(m_currentLevel, 10));
			LvlEndScreenSelection s = m_lvlEndScreen->menuIdle();	// get option selected by player on endscreen
			if(s == START_FROM_BEGINING) // continue option on fail
			{
				m_currentLevel = 0;
				m_currStats->asteroidsKilled = 0;
				m_currStats->salvageCollected = 0;
				m_currStats->score = 0;
				myUI->addPoints(-myUI->getScore());
				myUI->resetHealth();
			}
			if(s == QUIT) // quit game
			{
				hjs::endGame();
			}
			// anything else just continue to next level
			m_lvlEndScreen->setVisible(false);//*/
			m_currStats->asteroidsKilled = 0; // reset my stats
			m_currStats->salvageCollected = 0;
			m_currStats->score = 0;
			myUI->addPoints(-myUI->getScore());
			myUI->resetHealth();
		}

		m_currentLevel++;
		// update section header
		char buff[100];
		snprintf(buff, 100, "LEVEL_%d", m_currentLevel);
		m_LevelSectionHeader = buff;
		//m_LevelSectionHeader.shrink_to_fit();
		hjs::logToConsole(m_LevelSectionHeader.c_str());

		// set values of settings struct using data loaded from config and update various things
		m_settings->timeLimit = m_reader->GetInteger(m_LevelSectionHeader, "time_limit", 0);
		if(m_settings->timeLimit == 0)
		{
			m_timeLimitInLevel = false;
		}
		else
		{
			m_timeLimitInLevel = true;
			m_TimeRemaining = m_settings->timeLimit * CLOCKS_PER_SEC + (1.024 * CLOCKS_PER_SEC);
		}
		m_settings->salvCollect = m_reader->GetInteger(m_LevelSectionHeader, "salvage_collect", 0);
		m_settings->asteClearGoal = m_reader->GetInteger(m_LevelSectionHeader, "asteroid_destruct", 0);
		m_settings->minScore = m_reader->GetInteger(m_LevelSectionHeader, "min_score", 0);
		m_settings->type = parseType();

		snprintf(buff, 100, "Level %d", m_currentLevel);
		m_LevelText.setString(std::string(buff));

		unPause();
	}
	else
	{
		///@todo display game end screen
	}
}

/// Drawing Function IMPORTANT!!!
void LevelHandler::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(m_RsBg, states);
	target.draw(m_GoalText, states);
	target.draw(m_LevelText, states);
	///@note Swap m_RsBg and m_ProgressMeter drawing order after texturing m_RsBg
	target.draw(m_ProgressMeter, states);
	target.draw(m_CountDownText, states);
	if(!m_levelInProgress)
	{
		target.draw(m_PauseScreen);
	}
	target.draw(*m_lvlEndScreen);
}

// parses the level type in the ini file
LevelType LevelHandler::parseType()
{
	std::string str = m_reader->Get(m_LevelSectionHeader, "level_type", "SURVIVAL");
	hjs::logToConsole(str.c_str());
	char buff[100];
	if(str.compare("SURVIVAL") == 0)
	{
		snprintf(buff, 100, "Survive For %d Seconds", m_settings->timeLimit);
		m_TargetStr = buff;
		m_GoalText.setString(m_TargetStr);
		return SURVIVAL;
	}
	if(str.compare("MIN_SCORE") == 0)
	{
		snprintf(buff, 100, "Score %d pts in %d Seconds", m_settings->minScore, m_settings->timeLimit);
		m_TargetStr = buff;
		m_GoalText.setString(m_TargetStr);
		return SCORE_TARGET;
	}
	if(str.compare("COLLECT_SALVAGE") == 0)
	{
		snprintf(buff, 100, "Collect %d Salvage in %d Seconds", m_settings->salvCollect, m_settings->timeLimit);
		m_TargetStr = buff;
		m_GoalText.setString(m_TargetStr);
		return SALVAGE_COLLECTION_TARGET;
	}
	if(str.compare("CLEAR_ASTEROIDS"))
	{
		snprintf(buff, 100, "Destroy %d Asteroids in %d Seconds", m_settings->asteClearGoal, m_settings->timeLimit);
		m_TargetStr = buff;
		m_GoalText.setString(m_TargetStr);
		return CLEAR_ASTEROIDS;
	}
	// default is survival && remove warning for non-void func
	return SURVIVAL;
}

void LevelHandler::updateGUI()
{
	// update text centers
	sf::FloatRect textBounds = m_GoalText.getGlobalBounds();
	m_GoalText.setPosition(0 + (200 / 2) - (textBounds.width / 2), 0);

	sf::FloatRect textBounds2 = m_LevelText.getGlobalBounds();
	m_LevelText.setPosition(0 + (330) - (textBounds2.width / 2), 0);

	sf::FloatRect textBounds3 = m_CountDownText.getGlobalBounds();
	m_CountDownText.setPosition(0 + (275) - (textBounds3.width / 2), 23);

	// update the progress meter
	if(m_prevCompletionPercent != m_currCompletionPercent)
	{
		m_ProgressMeter.setSize(sf::Vector2f(50, m_currCompletionPercent * -50));
	}
	m_prevCompletionPercent = m_currCompletionPercent;
}

void LevelHandler::updateTimer()
{
	clock_t currClock = clock();
	int TDiff = currClock - lastClock;
	lastClock = currClock;
	m_TimeRemaining -= TDiff;
	char buff[100];	// put the number into the time remaining
	snprintf(buff, 100, "%d", int(m_TimeRemaining / CLOCKS_PER_SEC));
	m_CountDownText.setString(buff);
	if(m_TimeRemaining <= 0)
	{
		incrementLevel();
	}
}

// private handlers for each level type
void LevelHandler::h_collect()
{
	// collection handler
	m_currCompletionPercent = float(m_currStats->salvageCollected) / m_settings->salvCollect;
}

void LevelHandler::h_kill()
{
	// kill handler
	m_currCompletionPercent = float(m_currStats->asteroidsKilled) / m_settings->asteClearGoal;
}

void LevelHandler::h_score()
{
	// min_score handler
	m_currCompletionPercent = float(m_currStats->score) / m_settings->minScore;
	if(m_currCompletionPercent < 0)	//so that progress bar is never underfilled and starts overlapping the screen
	{
		m_currCompletionPercent = 0;
	}
}

void LevelHandler::h_survive()
{
	m_currCompletionPercent = float(m_settings->timeLimit - (m_TimeRemaining / CLOCKS_PER_SEC)) / m_settings->timeLimit;
}
