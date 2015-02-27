/** Game Menu Class Implementation
 * @author Henry Schmale
 * @date October 10, 2014
 * @file src/GameMenu.cpp
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
// if the build platform is
#endif // WINDOWS_PLATFORM_TARGETED

// Menu configuration object
INIReader gmR(MENU_CONFIG_FILE);

// ctor
GameMenu::GameMenu()
{
    //ctor
    // load Assets
    if(!font.loadFromFile(MAIN_FONT))
        exit(2);
    if(!m_texPlay.loadFromFile(gmR.Get("play_button", "texture", "PlayButton")))
        exit(2);
    if(!m_texBG.loadFromFile(gmR.Get("menu_window", "background", "BG_TEX")))
        exit(2);
    if(!m_texEasy.loadFromFile(gmR.Get("difficulty_button", "easyTexture", "Easy_tex")))
        exit(2);
    if(!m_texMed.loadFromFile(gmR.Get("difficulty_button", "medTexture", "MED_TEX")))
        exit(2);
    if(!m_texHard.loadFromFile(gmR.Get("difficulty_button", "hardTexture", "Hard_Tex")))
        exit(2);

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
    m_creditText.setCharacterSize(14);
    m_creditText.setColor(sf::Color::White);
    m_creditText.setFont(font);
#ifdef TSA_BUILD
    m_creditText.setString("CREDITS\nThis is the TSA Build of the\ngame and is not meant for\npublic distribution\n\nFont by: Severin Meyer\n\nLibrary Credits:\nINIH by benh...@gmail.com\nSFML by Laurent Gomez");
#else
    m_creditText.setString("Credits\nProgrammed By: Henry Schmale\nArtwork by: <PARTNER NAME>\n\nFont by: Severin Meyer\n\nLibrary Credits:\nINIH by benh...@gmail.com\nSFML by Laurent Gomez");
#endif

    // init version text
    m_versionText.setPosition(sf::Vector2f(gmR.GetInteger("version_text", "xpos", 10), gmR.GetInteger("version_text", "ypos", 320)));
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

    // init menu background
    m_RsBg.setTexture(&m_texBG);
    m_RsBg.setSize(sf::Vector2f(gmR.GetInteger("menu_window", "width", 300),
                                gmR.GetInteger("menu_window", "height", 300)));
    m_RsBg.setPosition(0, 0);

    // init vars
    m_mrt.select = EXIT_GAME;	// quit by default
    m_mrt.diff = EASY;

    // Open Menu Music file and play
    if(m_menuMusic.openFromFile(MENU_MUSIC))
    {
        m_menuMusic.setLoop(true);
        m_menuMusic.play();
    }

    // Finished
    hjs::logToConsole("Created Game Menu");
} // End Ctor


GameMenu::~GameMenu()
{
    //dtor
    delete m_mbBack;
    delete m_mbCredits;
    delete m_mbDifficulty;
    delete m_mbExit;
    delete m_mbPlay;
}

MenuRetType GameMenu::getSelection()
{
    bool bShowCreditScreen = false;
    menuWindow.create(sf::VideoMode(gmR.GetInteger("menu_window", "width", 300),
                                    gmR.GetInteger("menu_window", "height", 300)),
                      "TSA Game 2015 Starter",
                      sf::Style::Close);
    // get player name first
    enterName();
    m_playerName.setString("Logged in as: " + getPlayerName());
    while(menuWindow.isOpen())
    {
        // Handle Events
        sf::Event event;
        while(menuWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                menuWindow.close();
                m_mrt.select = EXIT_GAME;
            }

            // mouse hover checks
            sf::Vector2i mouselocalPosition = sf::Mouse::getPosition(menuWindow);
            // only test for these if the credits screen is not shown
            if(!bShowCreditScreen)
            {
                // play button
                if((m_mbPlay->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                {
                    menuWindow.close();
                    m_mrt.select = PLAY_GAME;
                }
                // credits button
                if((m_mbCredits->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                {
                    bShowCreditScreen = true;
                }
                // exit button
                if((m_mbExit->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                {
                    menuWindow.close();
                    m_mrt.select = EXIT_GAME;
                }
                // difficulty selection button
                if((m_mbDifficulty->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                {
                    this->incrementDifficulty();
                }
                // open highscores in browser, windows only
                if((m_mbHighScores->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                {
#ifdef WINDOWS_PLATFORM_TARGETED
                    // windows only way to open browser
                    ShellExecute(NULL, "open", HighscoresURL, NULL, NULL, SW_SHOWNORMAL);
#endif // WINDOWS_PLATFORM_TARGETED
                }
            }
            else	// handle stuff on credits screen
            {
                // back button
                if((m_mbBack->mouseHoverCheck(mouselocalPosition.x, mouselocalPosition.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
                {
                    bShowCreditScreen = false;
                }
            }
        }

        // Render
        menuWindow.clear(sf::Color::Black);
        menuWindow.draw(m_RsBg);
        if(!bShowCreditScreen)
        {
            menuWindow.draw(*m_mbPlay);
            menuWindow.draw(*m_mbCredits);
            menuWindow.draw(*m_mbExit);
            menuWindow.draw(*m_mbDifficulty);
            menuWindow.draw(m_versionText);
            menuWindow.draw((m_playerName));
            menuWindow.draw(*m_mbHighScores);
        }
        else
        {
            menuWindow.draw(*m_mbBack);
            menuWindow.draw(m_creditText);
        }
        menuWindow.display();
    }
    for(int i = 100; i > 10; i -= 10)
    {
        m_menuMusic.setVolume(i);
        sf::sleep(sf::milliseconds(i));
    }
    return m_mrt;
}

std::string GameMenu::getPlayerName()
{
    if(!m_pname.empty())
        return m_pname;
    else
        return gmR.Get("default_options", "default_name", "Player");
}

// private functions
// increment the returned difficulty and updates the menu button
void GameMenu::incrementDifficulty()
{
    switch(m_mrt.diff)
    {
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

void GameMenu::enterName()
{
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

    while(menuWindow.isOpen())
    {
        sf::Event event;
        while(menuWindow.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                menuWindow.close();
                m_mrt.select = EXIT_GAME;
            }
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    str.push_back(static_cast<char>(event.text.unicode));
                    if((event.text.unicode == 8) && (str.size() > 1))	// backspace
                    {
                        str = str.substr(0, str.length() - 2);
                    }
                    else if((event.text.unicode == 8) && (str.size() <= 1))
                    {
                        str = std::string();
                    }

                    if(event.text.unicode == 13) // return
                    {
                        str = str.substr(0, str.length() - 1);
                        m_pname = str;
                        return;
                    }
                    if(event.text.unicode == 32)// NO SPACES ALLOWED
                    {
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
