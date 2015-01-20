/** Game Menu Class Declaration
*	Creates a window with a menu and waits for input blocking the main thread until input is received.
*	This object is pretty much a launcher in of itself, but for full cross-platform compatibility it is
*	integrated directly into the program. It will then return the selected option for the main thread to
*	take action on.
*	@note Requires the menu button class to work
*	@note Instances of this class should Dynamically allocated for memory management purposes
*	@author Henry Schmale
*	@date October 10, 2014
*/

#ifndef GAMEMENU_H
#define GAMEMENU_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "MenuButton.h"
#include "../FilePaths.h"
#include "../Hjs_StdLib.h"

// Possible Options for what happens on the menu
enum MenuOptions
{
	PLAY_GAME,
	EXIT_GAME
};

enum GameDifficulty
{
	EASY = 0,
	MEDIMUM = 1,
	HARD = 2
};


struct MenuRetType{
    MenuOptions select;
    GameDifficulty diff;
};

class GameMenu
{
public:
	GameMenu();
	virtual ~GameMenu();

	// Enters the event loop of this object
	// Create a window for the menu and will take care of the menu
	// it will only return if the EXIT_GAME or PLAY_GAME button is
	// pressed
	MenuRetType getSelection();
    std::string getPlayerName();
protected:
private:
	sf::RenderWindow menuWindow;
	sf::RectangleShape m_RsBg;			// background sprite
	std::string m_pname;

	sf::Font font;						// font used for text

	// Texture Assets
	sf::Texture m_texBG;				// texture for menu background
	sf::Texture m_texPlay;				// texture for play button

	// buttons
	MenuButton *m_mbPlay;		// play button
	MenuButton *m_mbCredits;	// Credits Button
	MenuButton *m_mbExit;		// exit button
	MenuButton *m_mbDifficulty;	// Difficulty Selection Button
	MenuButton *m_mbBack;		// back button to exit from credits screen and return to main menu;
	MenuButton *m_mbHighScores;	// button to go to highscores page in browser

	// Text Objects
	sf::Text m_creditText;	// text to hold credits
	sf::Text m_versionText;	// text to hold version information on main screen
	sf::Text m_playerName;	// text that holds player name

  // Menu Music
  sf::Music m_menuMusic;

	// return type
	MenuRetType m_mrt;

	// private member functions
	void incrementDifficulty();	// increments the selected difficulty on m_mrt struct and updates the difficulty selection button
	void enterName();			// prompts the player for their name
};

#endif // GAMEMENU_H
