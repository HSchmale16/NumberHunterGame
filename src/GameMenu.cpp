/**\brief Game Menu Class Implementation
 * \author Henry Schmale
 * \date October 10, 2014
 * \file src/GameMenu.cpp
 *
 * This is the menu that appears before the game starts, this is shown in a seperate
 * window from the game and is closed when either the play or quit option is selected.
 * This class handles every thing before the game starts.
 */

#include <string>
#include "../include/GameMenu.h"
#include "../Hjs_StdLib.h"
#include "../FilePaths.h"
#include "../INIReader.h"
#include "../version.h"

// is the windows platform targeted this part of the code is windows only
#ifdef WINDOWS_PLATFORM_TARGETED
#include <windows.h>
static LPCSTR HighscoresURL = "http://numberhuntergame.com/highscores.php?Level=1&diff=0";	// URL to goto for website
#endif // WINDOWS_PLATFORM_TARGETED

// Menu configuration object
INIReader gmR(MENU_CONFIG_FILE);

static const char HOW_TO_PLAY_STR[] =
    "Instructions\n\n"
    "Arrow Keys or WASD to Move\n"
    "Space Bar shoots Lasers\n\n"
    "Shoot the asteroids\n"
    "Collect the salvage that meets\n"
    "condition at the bottom of the screen\n"
    "by running into it. Don't hit the salvage\n"
    "that fails to meet the condition.\n\n"
    "Click to Continue";

// ctor
GameMenu::GameMenu() {
    //ctor
    // load Assets
    if(!font.loadFromFile(MAIN_FONT)){
        hjs::logToConsole("Failed to load: " MAIN_FONT);
        exit(2);
    }
    if(!m_texPlay.loadFromFile(gmR.Get("play_button", "texture", "PlayButton"))){
        hjs::logToConsole("Failed to load: Play Button Texture");
        exit(2);
    }
    if(!m_texBG.loadFromFile(gmR.Get("menu_window", "background", "BG_TEX"))){
        hjs::logToConsole("Failed to load: Menu Background");
        exit(2);
    }
    if(!m_texEasy.loadFromFile(gmR.Get("difficulty_button", "easyTexture", "Easy_tex"))){
        hjs::logToConsole("Failed to load: Easy Difficulty Button Texture");
        exit(2);
    }
    if(!m_texMed.loadFromFile(gmR.Get("difficulty_button", "medTexture", "MED_TEX"))){
        hjs::logToConsole("Failed to load: Medium Difficulty Button Texture");
        exit(2);
    }
    if(!m_texHard.loadFromFile(gmR.Get("difficulty_button", "hardTexture", "Hard_Tex"))){
        hjs::logToConsole("Failed to load: Hard Difficulty Button Texture");
        exit(2);
    }
    // This is a really quick thing just to get the game ready for TSA States
    // so I'm just using the ICON
    if(!m_texLogo.loadFromFile(ICON)){
        hjs::logToConsole("Failed to load: " ICON);
    }

    // Open Menu Music file and play
    if(m_menuMusic.openFromFile(MENU_MUSIC)) {
        m_menuMusic.setLoop(true);
        m_menuMusic.play();
    }else{
        hjs::logToConsole("Failed to load: Menu Music - This is not a big deal. DON'T PANIC!");
    }
    // create buttons
    m_mbPlay = new MenuButton(gmR.GetInteger("play_button", "xpos", 100),
                              gmR.GetInteger("play_button", "ypos", 100),
                              gmR.GetInteger("play_button", "width", 100),
                              gmR.GetInteger("play_button", "height", 25),
                              gmR.Get("play_button", "text", "PLAY GAME"),
                              &m_texPlay,
                              sf::Color::Black,
                              font);
    m_mbCredits = new MenuButton(gmR.GetInteger("credits_button", "xpos", 100),
                                 gmR.GetInteger("credits_button", "ypos", 100),
                                 gmR.GetInteger("credits_button", "width", 100),
                                 gmR.GetInteger("credits_button", "height", 25),
                                 gmR.Get("credits_button", "text", "CREDITS"),
                                 sf::Color::Blue,
                                 sf::Color::Black,
                                 font);
    m_mbExit = new MenuButton(gmR.GetInteger("exit_button", "xpos", 100),
                              gmR.GetInteger("exit_button", "ypos", 100),
                              gmR.GetInteger("exit_button", "width", 100),
                              gmR.GetInteger("exit_button", "height", 25),
                              gmR.Get("exit_button", "text", "EXIT"),
                              sf::Color::Green,
                              sf::Color::Black,
                              font);
    m_mbBack = new MenuButton(gmR.GetInteger("back_button", "xpos", 100),
                              gmR.GetInteger("back_button", "ypos", 100),
                              gmR.GetInteger("back_button", "width", 100),
                              gmR.GetInteger("back_button", "height", 25),
                              gmR.Get("back_button", "text", "BACK"),
                              sf::Color::White,
                              sf::Color::Black,
                              font);
    m_mbDifficulty = new MenuButton(gmR.GetInteger("difficulty_button", "xpos", 100),
                                    gmR.GetInteger("difficulty_button", "ypos", 100),
                                    gmR.GetInteger("difficulty_button", "width", 100),
                                    gmR.GetInteger("difficulty_button", "height", 25),
                                    gmR.Get("difficulty_button", "easyText", "EASY"),
                                    &m_texEasy,
                                    sf::Color::Black,
                                    font);
    m_mbHighScores = new MenuButton(gmR.GetInteger("highscores_button", "xpos", 100),
                                    gmR.GetInteger("highscores_button", "ypos", 100),
                                    gmR.GetInteger("highscores_button", "width", 100),
                                    gmR.GetInteger("highscores_button", "height", 25),
                                    gmR.Get("highscores_button", "text", "High Scores"),
                                    sf::Color::White,
                                    sf::Color::Black,
                                    font);
    // init credit screen text
    m_creditText.setPosition(sf::Vector2f(gmR.GetInteger("credits_text", "xpos", 25), gmR.GetInteger("credits_text", "ypos", 20)));
    m_creditText.setCharacterSize(12);
    m_creditText.setColor(sf::Color::White);
    m_creditText.setFont(font);
#ifdef TSA_BUILD
    m_creditText.setString("CREDITS\nThis is the TSA Build of the\n"
                           "game and is not meant for\npublic distribution"
                           "\n\nFont by Severin Meyer\n\nLibrary Credits:\n"
                           "INIH by benh...@gmail.com\nSFML by Laurent Gomez");
#else
    m_creditText.setString("Credits\nProgrammed By: Henry Schmale\n"
                           "Artwork by: Matt Krammer\n\n"
                           "Font by Severin Meyer\n\nLibrary Credits:\n"
                           "INIH by benh...@gmail.com\nSFML by Laurent Gomez");
#endif // TSA_BUILD

    // init version text
    m_versionText.setPosition(sf::Vector2f(gmR.GetInteger("version_text", "xpos", 10),
                                           gmR.GetInteger("version_text", "ypos", 320)));
    m_versionText.setCharacterSize(gmR.GetInteger("version_text", "font_size", 10));
    m_versionText.setColor(sf::Color::White);
    m_versionText.setFont(font);
    std::string versionStr;			// used to set the version string because the str is complex concoction
    versionStr += "Version: ";
    versionStr += AutoVersion::FULLVERSION_STRING;
    m_versionText.setString(versionStr);

    // init player name text
    m_playerName.setCharacterSize(gmR.GetInteger("player_text", "fontSz", 10));
    m_playerName.setPosition(sf::Vector2f(gmR.GetInteger("player_text", "xpos", 10), gmR.GetInteger("player_text", "ypos", 300)));
    m_playerName.setFont(font);
    m_playerName.setColor(sf::Color::White);

    // init how2play text
    m_how2Play.setCharacterSize(14);
    m_how2Play.setPosition(10, 10);
    m_how2Play.setFont(font);
    m_how2Play.setColor(sf::Color::White);
    m_how2Play.setString(HOW_TO_PLAY_STR);

    // init menu background
    m_RsBg.setTexture(&m_texBG);
    m_RsBg.setSize(sf::Vector2f(gmR.GetInteger("menu_window", "width", 300),
                                gmR.GetInteger("menu_window", "height", 300)));
    m_RsBg.setPosition(0, 0);

    // Logo Setup
    m_logoShape.setSize(sf::Vector2f(60, 60));
    m_logoShape.setPosition(30, 20);
    m_logoShape.setTexture(&m_texLogo);

    // init vars
    m_mrt.select = EXIT_GAME;	// q`uit by default
    m_mrt.diff = EASY;

    // Finished
    hjs::logToConsole("Created Game Menu");
} // End Ctor


GameMenu::~GameMenu() {
    //dtor
    hjs::logToConsole("Dtor of GameMenu Called");
    m_menuMusic.stop();
    delete m_mbBack;
    delete m_mbCredits;
    delete m_mbDifficulty;
    delete m_mbExit;
    delete m_mbPlay;
}

static const int MAIN_SCR_ID     = 0; //!< Main Menu Screen Id
static const int CREDITS_SCR_ID  = 1; //!< Credit Screen Id
static const int HOW2PLAY_SCR_ID = 2; //!< How to play screen Id

MenuRetType GameMenu::getSelection() {
    int  screenNum     = 0;
    menuWindow.create(sf::VideoMode(gmR.GetInteger("menu_window", "width", 300),
                                    gmR.GetInteger("menu_window", "height", 300)),
                      "TSA Game 2015 Starter",
                      sf::Style::Close);
    sf::Image m_icon;	// load an icon
    if(!m_icon.loadFromFile(ICON)){
        hjs::logToConsole("Failed to load Window Icon");
    }else{
        menuWindow.setIcon(32, 32, m_icon.getPixelsPtr());
    }
    // get player name first
    enterName();
    m_playerName.setString("Logged in as: " + getPlayerName());
    while(menuWindow.isOpen()){
        // Handle Events
        sf::Event event;
        while(menuWindow.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                menuWindow.close();
                m_mrt.select = EXIT_GAME;
            }

            // mouse hover checks
            sf::Vector2i mouselocalPosition = sf::Mouse::getPosition(menuWindow);
            // only test for these if the credits screen is not shown
            if(screenNum == MAIN_SCR_ID) {
                // play button
                if((m_mbPlay->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                    screenNum    = HOW2PLAY_SCR_ID;
                    m_mrt.select = PLAY_GAME;
                }
                // credits button
                if((m_mbCredits->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                    screenNum = CREDITS_SCR_ID;
                }
                // exit button
                if((m_mbExit->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                    menuWindow.close();
                    m_mrt.select = EXIT_GAME;
                }
                // difficulty selection button
                if((m_mbDifficulty->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                    this->incrementDifficulty();
                }
                // open highscores in browser, windows only
                if((m_mbHighScores->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                    #ifdef WINDOWS_PLATFORM_TARGETED
                    // windows only way to open browser
                    ShellExecute(NULL, "open", HighscoresURL, NULL, NULL, SW_SHOWNORMAL);
                    #endif // WINDOWS_PLATFORM_TARGETED
                }
            } else if(screenNum == CREDITS_SCR_ID){	// handle stuff on credits screen
                // back button
                if((m_mbBack->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left))) {
                    screenNum = MAIN_SCR_ID;
                }
            } else if(screenNum == HOW2PLAY_SCR_ID){
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                    menuWindow.close();
                }
            }
        } // End of event processing

        // Render
        menuWindow.clear(sf::Color::Black);
        menuWindow.draw(m_RsBg);

        switch(screenNum){ // Change the things drawn based on the screen id
        case MAIN_SCR_ID:
            menuWindow.draw(m_logoShape);
            menuWindow.draw(*m_mbPlay);
            menuWindow.draw(*m_mbCredits);
            menuWindow.draw(*m_mbExit);
            menuWindow.draw(*m_mbDifficulty);
            menuWindow.draw(m_versionText);
            menuWindow.draw((m_playerName));
            menuWindow.draw(*m_mbHighScores);
            break;
        case CREDITS_SCR_ID:
            menuWindow.draw(*m_mbBack);
            menuWindow.draw(m_creditText);
            break;
        case HOW2PLAY_SCR_ID:
            menuWindow.draw(m_how2Play);
            break;
        }
        menuWindow.display();
    } // Window is not open anymore
    for(int i = 100; i > 10; i -= 10) {
        // fade the menu music out
        m_menuMusic.setVolume(i);
        sf::sleep(sf::milliseconds(i));
    }
    return m_mrt;
}

std::string GameMenu::getPlayerName() {
    if(!m_pname.empty())
        return m_pname;
    else
        return gmR.Get("default_options", "default_name", "Player");
}

// private functions
// increment the returned difficulty and updates the menu button
void GameMenu::incrementDifficulty() {
    switch(m_mrt.diff) {
    case EASY:
        m_mrt.diff = MEDIMUM;
        m_mbDifficulty->setText(gmR.Get("difficulty_button", "medText", "MEDIMUM"));
        m_mbDifficulty->setTexture(&m_texMed);
        break;
    case MEDIMUM:
        m_mrt.diff = HARD;
        m_mbDifficulty->setText(gmR.Get("difficulty_button", "hardText", "HARD"));
        m_mbDifficulty->setTexture(&m_texHard);
        break;
    case HARD:
        m_mrt.diff = EASY;
        m_mbDifficulty->setText(gmR.Get("difficulty_button", "easyText", "EASY"));
        m_mbDifficulty->setTexture(&m_texEasy);
        break;
    }
}

void GameMenu::enterName() {
    // set up text box that displays name entered
    std::string str = gmR.Get("default_options", "default_name", "Player");
    sf::Text name;
    name.setCharacterSize(14);
    name.setFont(font);
    name.setColor(sf::Color::White);
    name.setString(str);
    sf::FloatRect rectBounds = m_RsBg.getGlobalBounds();
    sf::FloatRect textBounds = name.getGlobalBounds();
    name.setPosition(
        rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
        rectBounds.top + (rectBounds.height / 2) - (textBounds.height / 2)
    );

    // set up instructions text
    sf::Text instruct;
    instruct.setCharacterSize(12);
    instruct.setFont(font);
    instruct.setColor(sf::Color::White);
    instruct.setString("Enter your name and Press Enter to Continue..."
                       "\n(if you enter nothing your name will be \nset to \'" +
                       gmR.Get("default_options", "default_name", "Player") +
                       "\'. Used for recording high scores");
    rectBounds = m_RsBg.getGlobalBounds();
    textBounds = instruct.getGlobalBounds();
    instruct.setPosition(
        rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2), 120);

    while(menuWindow.isOpen()) {
        sf::Event event;
        while(menuWindow.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                menuWindow.close();
                m_mrt.select = EXIT_GAME;
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    str.push_back(static_cast<char>(event.text.unicode));
                    if((event.text.unicode == 8) && (str.size() > 1)) {	// backspace
                        str = str.substr(0, str.length() - 2);
                    } else if((event.text.unicode == 8) && (str.size() <= 1)) {
                        str = std::string();
                    }

                    if(event.text.unicode == 13) { // return
                        str = str.substr(0, str.length() - 1);
                        m_pname = str;
                        return;
                    }
                    if(event.text.unicode == 32) { // NO SPACES ALLOWED
                        str = str.substr(0, str.length() - 1);
                        std::cout << "\a";
                    }
                    name.setString(str);
                    rectBounds = m_RsBg.getGlobalBounds();
                    textBounds = name.getGlobalBounds();
                    name.setPosition(
                        rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
                        rectBounds.top + (rectBounds.height / 2) - (textBounds.height / 2)
                    );
                }
            }// text event catch
        }

        // Render
        menuWindow.clear(sf::Color::Black);
        menuWindow.draw(m_RsBg);
        menuWindow.draw(instruct);
        menuWindow.draw(name);
        menuWindow.display();
    }
}
