/** TSA GAME 2015 Entry Point
 * @author Henry Schmale
 * @date Oct 3, 2014
 * @file main.cpp
 *
 * \mainpage Number Hunter Game
 * 
 * \section intro_sec Introduction
 * This is a game about collecting numbers that meet a certain
 * condition. Additionally, this game is designed to be easily
 * expandable and to have features added to it very easily.
 *
 * \section install_sec Installation
 * You don't. You simply run the program from the working directory
 * making sure that you have all of the required files in the
 * resources folder.
 */

#include <iostream>	            // for cout
#include <SFML/System.hpp>      // for threading
#include <SFML/Graphics.hpp>    // for windowing
#include "Hjs_StdLib.h"         // My STD LIB
#include "version.h"            // for versioning information
#include "config.h"             // for game configuration
#include "include/Player.h"
#include "include/Salvage.h"
#include "include/UI.h"
#include "include/Background.h"
#include "include/LaserHandler.h"
#include "include/Asteroids.h"
#include "include/LevelHandler.h"
#include "include/GameMenu.h"

// Declare Global Variables
bool bGameIsPaused = false;		// Is the game paused?

// scoring globals, these are set in InitGameObjects, but they are used in
// 'LaserHandler.cpp'
// loading these in main makes it easier to handle scoring
int PTS_GOOD_SALVAGE;               //!< pts given for collecting good salvage
int PTS_BAD_SALVAGE;                //!< pts lost for collecting bad salvage
int PTS_DESTROY_SALVAGE;            //!< pts lost for destroying salvage(any)
int PTS_HIT_ASTEROID;               //!< pts lost for hitting an asteroid
int PTS_DESTROY_ASTEROID;           //!< pts gained for destroying an asteroid by shooting it
GameDifficulty DIFFICULTY;          //!< Difficulty of the game

// Declare Global Objects
sf::RenderWindow window;

// dynamically allocate the following objects
Player *player;
Salvage *salv;
UI *myUI;
Background *bg;
LaserHandler *lHandler;
Asteroids *asteroid;
GameMenu *gmMenu;
LevelHandler *levels;
MenuRetType *menuRet;

// Declare Threads and Entry Points
void render()	// rendering thread entry point
{
    hjs::logToConsole("Rendering Thread Created");
    while((window.isOpen() && (hjs::gameIsActive())))
    {
        window.clear(sf::Color::Black);
        window.draw(*bg);
        window.draw(*salv);
        window.draw(*asteroid);
        window.draw(*player);
        window.draw(*lHandler);
        window.draw(*myUI);
        window.draw(*levels);
        window.display();
    }
    hjs::logToConsole("Rendering Thread Terminated");
}

void handleObjectEvents()	// object event thread entry point
{
    hjs::logToConsole("Object Event Handler Thread Created");
    while(window.isOpen())
    {
        if((!bGameIsPaused) && (levels->getLevelInProgress()) && (hjs::gameIsActive()))	// check if NOT paused
        {
            levels->checkLevelStatus();	// this can change game active status to make this thread safe, it needs to be checked after calling
            if(!hjs::gameIsActive())
            {
                hjs::endGame();
                break;
            }
            player->Move();
            salv->Move();
            asteroid->Move();
            int Points = lHandler->handleEvents(player, salv, asteroid);// laser hit test
            // update level handler on killed asteroids
            levels->addKilledAsteroids(lHandler->getAsteroidsDestroyedThisIter());
            // salvage hit test
            for(int i = 0; i < salv->getCount(); i++)		// Perform hitTests after moving
            {
                bool hit = salv->hitTest(i, *player);
                if(hit)
                {
                    int nSalvVal = salv->getValue(i);
                    if(myUI->isSalvValGood(nSalvVal))	// check if val is good
                    {
                        Points += PTS_GOOD_SALVAGE;
                        levels->addCollectedSalvage(1);
                        /// @todo animation for collection of salvage
                        /// call a func of salvgage class with index
                    }
                    else	// the salvage doesn't meet the specified condition so you lose points
                    {
                        /// @todo add a boom sound
                        Points += PTS_BAD_SALVAGE;
                        myUI->updateHealth(-1);
                    }
                    salv->ReInit(i);
                    myUI->setNewCondition();
                    hjs::logTimeToConsole();
                    std::cout << "Salvage(" << i << ") has hit player" << std::endl;
                }
            }
            // asteroid hittest
            for(int i = 0; i < asteroid->getCount(); i++)
            {
                bool hit = asteroid->hitTestPlayer(i, *player);
                if(hit)
                {
                    Points += PTS_HIT_ASTEROID;			// lose points for hitting an asteroid
                    myUI->updateHealth(-5);
                    levels->addKilledAsteroids(1);
                    asteroid->ReInit(i);
                    hjs::logTimeToConsole();
                    std::cout << "Asteroid(" << i << ") has hit player" << std::endl;
                }
            }
            // add points
            if(Points != 0)
            {
                myUI->addPoints(Points);
                levels->updateScore(myUI->getScore());
            }
        }
        sf::sleep(sf::milliseconds(10));
    }
    hjs::logToConsole("Object Event Handler Thread Terminated");
}

// thread declarations
sf::Thread renderingThread(&render);
sf::Thread objectEventThread(&handleObjectEvents);

// fwd declaration for set-up of game objects based on difficulty
void gameDifficultyInit(MenuRetType mrt);

int main()
{
    // output versioning information
    std::cout << "TSA GAME 2015" << std::endl;
    std::cout << "Version: " << AutoVersion::FULLVERSION_STRING << std::endl;
    std::cout << "Built on: " << AutoVersion::MONTH << " / " << AutoVersion::DATE
              << " / " << AutoVersion::YEAR << std::endl;
    std::cout << "Build Number: " << AutoVersion::BUILDS_COUNT << std::endl;
    std::cout << std::endl;

    hjs::init_Hjs_StdLib();			// init my lib

    // before init launch the menu
    gmMenu = new GameMenu;
    menuRet = new MenuRetType;
    *menuRet = gmMenu->getSelection();
    hjs::logToConsole("An Option has been Selected on the menu.");
    if(menuRet->select == EXIT_GAME)
        return 0;

    // All systems are go Init the game objects
    window.create(sf::VideoMode(config.GetInteger("window", "width", 375), config.GetInteger("window", "height", 650)), config.Get("Window", "Title", "Game"), sf::Style::Close);
    gameDifficultyInit(*menuRet);
    DIFFICULTY = menuRet->diff;

    delete gmMenu;		// free memory from GameMenu
    hjs::logToConsole("Menu Clean Up Finished");


    // init Graphics
    window.setFramerateLimit(30);		// limit fps
    window.setPosition(sf::Vector2i(500, 10));
    sf::Image myIcon;	// load an icon
    if(!myIcon.loadFromFile(ICON))
        return -123;
    window.setIcon(32, 32, myIcon.getPixelsPtr());
    hjs::logToConsole("Window Created");
    window.setActive(false);		// allow rendering thread to activate window context
    renderingThread.launch();		// launch rendering thread

    // init Objects
    objectEventThread.launch();

    // handle window until it closes
    while ((window.isOpen() && (hjs::gameIsActive())))
    {
        sf::Event event;
        //handle Window Events
        while (window.pollEvent(event))
        {
            // handle window close
            if (event.type == sf::Event::Closed)
                window.close();

            // Focus Change Pauses
            if (event.type == sf::Event::GainedFocus)
            {
                bGameIsPaused = false;
                levels->unPause();
            }
            if (event.type == sf::Event::LostFocus)
            {
                levels->pauseGame();
                bGameIsPaused = true;
            }

            // Pause on key press
            if(event.type == sf::Event::KeyPressed)
            {
                if(event.key.code == sf::Keyboard::Escape)
                {
                    if(bGameIsPaused)
                    {
                        bGameIsPaused = false;
                        levels->unPause();
                    }
                    else
                    {
                        bGameIsPaused = true;
                        levels->pauseGame();
                    }
                }
            }
        }
    }
    hjs::endGame();							// End threads of other objects
    hjs::logToConsole("Window Closed");
    // clean up
    delete player;
    delete salv;
    delete myUI;
    delete bg;
    delete lHandler;
    delete levels;
    delete menuRet;
    hjs::logToConsole("Finished Clean up in main thread");
    return 0;
}

// Init the game objects and variables based on the selected difficulty
void gameDifficultyInit(MenuRetType mrt)
{
    // init objects that doesn't depend on difficulty
    levels = new LevelHandler(gmMenu->getPlayerName());
    myUI = new UI;
    bg = new Background;
    lHandler = new LaserHandler;
    player = new Player;

    // init the rest of the objects that depend
    switch(mrt.diff)
    {
    case EASY:
        salv = new Salvage(config.GetInteger("easy_diff", "salvage_count", 4));
        asteroid = new Asteroids(config.GetInteger("easy_diff", "asteroid_count", 2),
                                 config.GetReal("easy_diff", "trajectory_deviation", .05));
        // set vars
        PTS_GOOD_SALVAGE = config.GetInteger("easy_diff", "pts_good_salvage", 5);
        PTS_BAD_SALVAGE = config.GetInteger("easy_diff", "pts_bad_salvage", -1);
        PTS_DESTROY_SALVAGE = config.GetInteger("easy_diff", "pts_destroy_salvage", 0);
        PTS_HIT_ASTEROID = config.GetInteger("easy_diff", "pts_hit_asteroid", -7);
        PTS_DESTROY_ASTEROID = config.GetInteger("easy_diff", "pts_shoot_asteroid", 2);
        hjs::logToConsole("Init game for easy diff");
        break;
    case MEDIMUM:
        salv = new Salvage(config.GetInteger("medium_diff", "salvage_count", 3));
        asteroid = new Asteroids(config.GetInteger("medium_diff", "asteroid_count", 4),
                                 config.GetReal("medium_diff", "trajectory_deviation", .15));
        PTS_GOOD_SALVAGE = config.GetInteger("medium_diff", "pts_good_salvage", 5);
        PTS_BAD_SALVAGE = config.GetInteger("medium_diff", "pts_bad_salvage", -1);
        PTS_DESTROY_SALVAGE = config.GetInteger("medium_diff", "pts_destroy_salvage", 0);
        PTS_HIT_ASTEROID = config.GetInteger("medium_diff", "pts_hit_asteroid", -7);
        PTS_DESTROY_ASTEROID = config.GetInteger("medium_diff", "pts_shoot_asteroid", 2);
        hjs::logToConsole("Init game for medium diff");
        break;
    case HARD:
        salv = new Salvage(config.GetInteger("hard_diff", "salvage_count", 3));
        asteroid = new Asteroids(config.GetInteger("hard_diff", "asteroid_count", 6),
                                 config.GetReal("hard_diff", "trajectory_deviation", .25));
        PTS_GOOD_SALVAGE = config.GetInteger("hard_diff", "pts_good_salvage", 5);
        PTS_BAD_SALVAGE = config.GetInteger("hard_diff", "pts_bad_salvage", -1);
        PTS_DESTROY_SALVAGE = config.GetInteger("hard_diff", "pts_destroy_salvage", 0);
        PTS_HIT_ASTEROID = config.GetInteger("hard_diff", "pts_hit_asteroid", -7);
        PTS_DESTROY_ASTEROID = config.GetInteger("hard_diff", "pts_shoot_asteroid", 2);
        hjs::logToConsole("Init game for hard diff");
        break;
    }
}



