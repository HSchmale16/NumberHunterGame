/** \brief Game Menu Class Declaration
 *
 *	Creates a window with a menu and waits for input blocking the main thread until input is received.
 *	This object is pretty much a launcher in of itself, but for full cross-platform compatibility it is
 *	integrated directly into the program. It will then return the selected option for the main thread to
 *	take action on.
 *
 *	\note Requires the MenuButton class to work
 *	\note Instances of this class should Dynamically allocated for memory management purposes
 *	\author Henry Schmale
 *	\date October 10, 2014
 */

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "MenuButton.h"
#include "../FilePaths.h"
#include "../Hjs_StdLib.h"

/**\brief Possible options that could be returned from the game menu
 */
enum MenuOptions
{
    PLAY_GAME, //!< Play Button Selected
    EXIT_GAME  //!< Exit Button Selected or Menu Window was closed
};

/**\brief Game play Difficulty Levels
 */
enum GameDifficulty
{
    EASY = 0,    //!< Easy Mode
    MEDIMUM = 1, //!< Medium Mode
    HARD = 2     //!< Hard Mode
};

/**\brief A struct that contains the selected menu options
 */
struct MenuRetType
{
    MenuOptions select;  //!< Which option was selected from the menu
    GameDifficulty diff; //!< Selected Difficulty
};

/**\brief The Launcher - shows a menu to start the game and displays various information
 *        about the game.
 */
class GameMenu
{
public:
    /**\brief Default CTOR */
    GameMenu();

    /**\brief Destructor */
    virtual ~GameMenu();

    /**\brief Enters the event loop of this object
     * \return a MenuRetType struct containing the selected options on the menu
     *
     * Create a window for the menu and will take care of the menu
     * it will only return if the EXIT_GAME or PLAY_GAME button is
     * pressed
     */
    MenuRetType getSelection();
    std::string getPlayerName();
protected:
private:
    sf::RenderWindow menuWindow;        //!< Window menu is displayed in
    sf::RectangleShape m_RsBg;			//!< background sprite
    sf::RectangleShape m_HowToImg;      //!< The How to sprite, shows how to play
    std::string m_pname;                //!< Player Name

    sf::Font font;						//!< font used for text

    // Texture Assets
    sf::Texture m_texBG;                //!< texture for menu background
    sf::Texture m_texPlay;              //!< texture for play button4
    sf::Texture m_texEasy;              //!< Texture for easy diff button
    sf::Texture m_texMed;               //!< Texture for medium diff button
    sf::Texture m_texHard;              //!< Texture for hard diff button
    sf::Texture m_texHowTo;             //!< The How To Texture

    // buttons
    MenuButton *m_mbPlay;               //!< play button
    MenuButton *m_mbCredits;            //!< Credits Button
    MenuButton *m_mbExit;               //!< exit button
    MenuButton *m_mbDifficulty;        	//!< Difficulty Selection Button
    MenuButton *m_mbBack;               //!< back button to exit from credits screen and return to main menu;
    MenuButton *m_mbHighScores;	        //!< button to go to highscores page in browser

    // Text Objects
    sf::Text m_creditText;	            //!< text to hold credits
    sf::Text m_versionText;	            //!< text to hold version information on main screen
    sf::Text m_playerName;	            //!< text that holds player name
    sf::Text m_how2Play;                //!< Text containing instructions to play

    // Menu Music
    sf::Music m_menuMusic;              //!< The music played on the menu

    // return type
    MenuRetType m_mrt;

    // private member functions
    void incrementDifficulty();	       //!< increments the selected difficulty on m_mrt and updates the difficulty selection button
    void enterName();                  //!< prompts the player for their name
};

#endif // GAMEMENU_H
