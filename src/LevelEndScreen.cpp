/** LevelEndScreen Class Implementation
 * Screen shown at end of level
 * @author Henry Schmale
 * @date November 18, 2014
 * @file src/LevelEndScreen.cpp
 */

#include "../include/LevelEndScreen.h"
#include "../FilePaths.h"
#include "../Hjs_StdLib.h"
#include <sstream>

extern sf::RenderWindow window;

LevelEndScreen::LevelEndScreen()
{
    //ctor
    m_visible = false;
    if(!m_font.loadFromFile(MAIN_FONT))
    {
        // do something
    }
    m_lvlStats = new LevelStats;
    m_mbNextLevel = new MenuButton(225, 550, 100, 25,
                                   "Next Level", sf::Color::Red,
                                   sf::Color::Blue, m_font);
    m_mbQuitGame = new MenuButton(50, 550, 100, 25,
                                  "Quit Game", sf::Color::Blue,
                                  sf::Color::Red, m_font);
    m_mbStartOver = new MenuButton(225, 550, 100, 25,
                                   "Start Over", sf::Color::Green,
                                   sf::Color::Blue, m_font);
    m_tNames.setFont(m_font);
    m_tNames.setCharacterSize(12);
    m_tNames.setColor(sf::Color::White);
    m_tNames.setPosition(50, 150);

    m_tScores.setFont(m_font);
    m_tScores.setCharacterSize(12);
    m_tScores.setColor(sf::Color::White);
    m_tScores.setPosition(300, 150);

    m_tMenuHeading.setFont(m_font);
    m_tMenuHeading.setCharacterSize(16);
    m_tMenuHeading.setColor(sf::Color::White);
}

LevelEndScreen::~LevelEndScreen()
{
    //dtor
    delete m_mbNextLevel;
    delete m_mbQuitGame;
    delete m_mbStartOver;
}

// public functions
void LevelEndScreen::setVisible(bool b)
{
    m_visible = b;
}

void LevelEndScreen::updateHighScoreTable(std::vector<std::string> vecStrHS)
{
    m_tNames.setString(vecStrHS[0]);
    m_tScores.setString(vecStrHS[1]);
    //std::cout << vecStrHS[0] << std::endl << vecStrHS[1] << std::endl;
}

void LevelEndScreen::updateLevelData(const LevelStats *stats, const LevelSettings *settings, int currentLvl)
{
    *m_lvlStats = *stats;
    m_lvlPassed = false;
    m_lvlNum = currentLvl;
    switch(settings->type)
    {
    case SALVAGE_COLLECTION_TARGET:
        if(stats->salvageCollected >= settings->salvCollect)
        {
            m_lvlPassed = true;
        }
        break;
    case SCORE_TARGET:
        if(stats->score >= static_cast<int>(settings->minScore))
        {
            m_lvlPassed = true;
        }
        break;
    case SURVIVAL:
        // if you got to the lvlend screen without dying you passed
        m_lvlPassed = true;
        break;
    case CLEAR_ASTEROIDS:
        // No Action. This type is not fully implemented yet
        break;
    }
    updateStrings();
}

LvlEndScreenSelection LevelEndScreen::menuIdle()
{
    LvlEndScreenSelection s = NO_SELECTION;
    while(s == NO_SELECTION)
    {
        sf::Vector2i mlpos = sf::Mouse::getPosition(window);
        if(m_lvlPassed)
        {
            if((m_mbNextLevel->mouseHoverCheck(mlpos.x, mlpos.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
            {
                s = NEXT_LEVEL;
            }
        }
        else
        {
            if((m_mbStartOver->mouseHoverCheck(mlpos.x, mlpos.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
            {
                s = START_FROM_BEGINING;
            }
        }
        if((m_mbQuitGame->mouseHoverCheck(mlpos.x, mlpos.y)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)))
        {
            s = QUIT;
        }
        sf::sleep(sf::milliseconds(80));
    }
    return s;
}

// private functions
//! DRAWING FUNCTION !//
void LevelEndScreen::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    if(m_visible == true)
    {
        // draw menu
        target.draw(m_tMenuHeading, states);
        if(m_lvlPassed)
        {
            target.draw(*m_mbNextLevel, states);
        }
        else
        {
            // draw the start from beginning button
            target.draw(*m_mbStartOver, states);
        }
        target.draw(*m_mbQuitGame, states);
        target.draw(m_tNames, states);
        target.draw(m_tScores, states);
    }
}

void LevelEndScreen::updateStrings()
{
    // update string text
    std::stringstream ss;
    sf::FloatRect rectBounds = sf::FloatRect(0.0f, 0.0f, 375.0f, 650.0f);
    sf::FloatRect textBounds;

    // update menu heading
    ss << "Level " << m_lvlNum << " ";
    if(m_lvlPassed)
    {
        ss << "Passed!";
    }
    else
    {
        ss << "Failed!";
    }
    m_tMenuHeading.setString(ss.str());
    ss.str(std::string());
    textBounds = m_tMenuHeading.getGlobalBounds();
    m_tMenuHeading.setPosition(
        rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2), 10);
}
