/** UI Class Implementation
 * @author Henry Schmale
 * @date October 5, 2014
 * @file src/UI.cpp
 */

#include "../include/UI.h"
#include "../FilePaths.h"
#include "../config.h"
#include <stdio.h>    // for sprintf
#include <math.h>     // for sqrt

UI::UI()
{
    //ctor
    // load font and bind it to sf::Text Objects
    if(!font.loadFromFile(MAIN_FONT))
    {
        hjs::logToConsole("Failed to load MAIN_FONT in UI");
    }
    if(!m_texBG.loadFromFile(config.Get("ui_config", "ui_texture", "NULL")))
    {
        hjs::logToConsole("Failed to load ui texture");
        exit(2);
    }

    // setup Background
    m_BG.setSize(sf::Vector2f(375, 50));
    m_BG.setPosition(0, 600);
    m_BG.setFillColor(sf::Color::White);
    m_BG.setTexture(&m_texBG);

    // setup score
    m_nScore = 0;			//init to 0 points
    m_ScoreText.setFont(font);
    m_ScoreText.setCharacterSize(12);
    m_ScoreText.setPosition(5, 605);
    m_ScoreText.setColor(sf::Color::White);
    char numStr[20];
    sprintf(numStr, "Points: %d", m_nScore);	// convert m_nScore to char array
    m_ScoreText.setString(numStr);

    // set up target condition
    setCondition(EVEN_NUM);
    m_TargetText.setFont(font);
    m_TargetText.setCharacterSize(12);
    m_TargetText.setPosition(200, 605);
    m_TargetText.setColor(sf::Color::White);

    // setup health bar
    m_MaxHealth = 100;
    m_CurrentHealth = m_MaxHealth;

    m_HealthBox.setOutlineColor(sf::Color::Black);
    m_HealthBox.setOutlineThickness(1);
    m_HealthBox.setPosition(5, 630);
    m_HealthBox.setSize(sf::Vector2f(m_MaxHealth, 15));
    m_HealthBox.setFillColor(sf::Color::Transparent);

    m_HealthBar.setFillColor(sf::Color::Red);
    m_HealthBar.setSize(sf::Vector2f(m_MaxHealth, 15));
    m_HealthBar.setPosition(5, 630);
}

UI::~UI()
{
    //dtor
}

void UI::Reset()
{
    // reset score
    m_nScore = 0;
    char numStr[20];
    sprintf(numStr, "Points: %d", m_nScore);	// convert m_nScore to char array
    m_ScoreText.setString(numStr);
}

void UI::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    target.draw(m_BG, states);			// draw the bg
    target.draw(m_ScoreText, states);	// draw scoreText
    target.draw(m_TargetText, states);	// draw TargetText
    target.draw(m_HealthBar, states);
    target.draw(m_HealthBox, states);
}

void UI::addPoints(int points)
{
    m_nScore += points;
    char numStr[20];
    sprintf(numStr, "Points: %d", m_nScore);	// convert m_nScore to char array
    m_ScoreText.setString(numStr);
}

// Random Target Selection
void UI::setNewCondition()
{
    // perform a static cast to convert an int into a valid enumerated value
    m_eTarget = static_cast<SalvCondition>(rand() % NUM_TYPES_SALVCONDITION);
    updateTarget();		// update the target on UI bar
}

// set m_eTarget to specified condition
void UI::setCondition(SalvCondition condition)
{
    m_eTarget = condition;
    updateTarget();
}

// updates the prompt on screen for which type of salvage to collect
void UI::updateTarget()
{
    switch(m_eTarget)
    {
    case EVEN_NUM:
        m_TargetText.setString("Find an Even Number");
        break;
    case ODD_NUM:
        m_TargetText.setString("Find an Odd Number");
        break;
    case PRIME_NUM:
        m_TargetText.setString("Find a Prime Number");
        break;
    default:
        hjs::logToConsole("Invalid Value in UI SalvageValue Enumeration");
        exit(2);
    }
}

bool UI::isSalvValGood(int val)
{
    switch(m_eTarget)
    {
    case EVEN_NUM:
        /// @todo action on even
        if(val % 2 == 0)
            return true;
        else
            return false;
        break;
    case ODD_NUM:
        /// @todo action on odd
        if(val % 2 == 1)
            return true;
        else
            return false;
        break;
    case PRIME_NUM:
        // Basic Prime Number Test
        if(val <= 3)
        {
            return val > 1;
        }
        else if ((val % 2 ==  0) | (val % 3 == 0))
        {
            return false;
        }
        else
        {
            for(int i = 5; i < sqrt(val) + 1; i += 6)
            {
                if((val % i == 0) | (val % (i + 2) == 0))
                {
                    return false;
                }
            }
            return true;
        }
        break;
    default:
        /// something bad happened
        hjs::logToConsole("Invalid Value in UI SalvageValue Enumeration");
        exit(2);
    }
}

int UI::getScore()
{
    return m_nScore;
}

void UI::updateHealth(int n)
{
    m_CurrentHealth += n;
    m_HealthBar.setSize(sf::Vector2f(m_CurrentHealth, 15));
}

void UI::resetHealth()
{
    m_CurrentHealth = m_MaxHealth;
    m_HealthBar.setSize(sf::Vector2f(m_MaxHealth, 15));
}

