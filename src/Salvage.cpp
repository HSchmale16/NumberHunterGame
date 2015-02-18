/** The implementation of the Salvage class
 * @author Henry J Schmale
 * @date October 2, 2014
 * @file src/Salvage.cpp
 */

#include "../include/Salvage.h"
#include "../FilePaths.h"
#include "../Hjs_StdLib.h"
#include <math.h>	// for rand
#include <stdio.h>	// for sprintf

#define TEXT_X_OFFSET 5
#define TEXT_Y_OFFSET 5

Salvage::Salvage(uint_fast8_t count)	// ctor
{
    SALVAGE_OBJECT_COUNT = count;
    // init variables
    srand(time(0));
    if(!font.loadFromFile(MAIN_FONT))
    {
        // Handle ERROR
        hjs::logToConsole("Could Not Load MAIN_FONT");
    }

    //dynamic allocation
    m_fXCoord = new float[SALVAGE_OBJECT_COUNT];
    m_fYCoord = new float[SALVAGE_OBJECT_COUNT];
    m_fSpeed = new float[SALVAGE_OBJECT_COUNT];
    m_Value = new uint_fast8_t[SALVAGE_OBJECT_COUNT];
    m_TextField = new sf::Text[SALVAGE_OBJECT_COUNT];
    s = new sf::RectangleShape[SALVAGE_OBJECT_COUNT];

    // begin assignment
    m_fSideLength = 30;
    for(int i = 0; i < SALVAGE_OBJECT_COUNT; i++)
    {
        m_fXCoord[i] = rand() % 325 + 25;
        m_fYCoord[i] = rand() % 400;
        m_fSpeed[i] = 2 * ((rand() % 1000 + 150) / 1000 + .15);
        m_Value[i] = rand() % 100;

        // setup text
        char numStr[2];
        sprintf(numStr, "%d", m_Value[i]);
        m_TextField[i].setFont(font);
        m_TextField[i].setCharacterSize(14);
        m_TextField[i].setColor(sf::Color::Black);
        m_TextField[i].setString(numStr);
        float x = m_fXCoord[i] + TEXT_X_OFFSET;
        float y = m_fYCoord[i] + TEXT_Y_OFFSET;
        m_TextField[i].setPosition(x, y);

        // set up graphics
        s[i].setSize(sf::Vector2f(m_fSideLength, m_fSideLength));
        s[i].setFillColor(sf::Color::White);
        s[i].setOutlineColor(sf::Color::Red);
        s[i].setOutlineThickness(2);
        s[i].setPosition(m_fXCoord[i], m_fYCoord[i]);
    }
}

Salvage::~Salvage()
{
    //dtor
    delete[] m_fXCoord;
    delete[] m_fYCoord;
    delete[] m_fSpeed;
    delete[] m_Value;
    delete[] s;
    delete[] m_TextField;
}

void Salvage::Move()
{
    for(int i = 0; i < SALVAGE_OBJECT_COUNT; i++)
    {
        m_fYCoord[i] += m_fSpeed[i];
        if(m_fYCoord[i] >  650)
        {
            ReInit(i);
        }
        m_TextField[i].move(0, m_fSpeed[i]);
        s[i].move(0, m_fSpeed[i]);
    }
}

void Salvage::ReInit(int i)
{
    // Position and movement
    m_fXCoord[i] = rand() % 325 + 25;
    m_fYCoord[i] = -20;
    m_fSpeed[i] = 2 * ((rand() % 1000 + 150) / 1000 + .15);
    // Salvage Value
    m_Value[i] = rand() % 100;
    char numStr[3];
    sprintf(numStr, "%d", m_Value[i]);
    m_TextField[i].setString(numStr);
    // reset pos
    float x = m_fXCoord[i] + TEXT_X_OFFSET;
    float y = m_fYCoord[i] + TEXT_Y_OFFSET;
    m_TextField[i].setPosition(x, y);
    s[i].setPosition(m_fXCoord[i], m_fYCoord[i]);
}

bool Salvage::hitTest(int index, Player& p)
{
    // verify index is within bounds
    if((index > SALVAGE_OBJECT_COUNT) | (index < 0))
        return false;

    // algorithm taken from: http://en.wikipedia.org/wiki/Hit-testing on Oct 5
    // modified by HSchmale for use in this game
    return (
               (( m_fXCoord[index] + m_fSideLength >= p.getXCoord()) && (m_fXCoord[index] <= p.getXCoord() + p.getSideLength()))
               &&
               (( m_fYCoord[index] + m_fSideLength >= p.getYCoord()) && (m_fYCoord[index] <= p.getYCoord() + p.getSideLength()))
           );
}

bool Salvage::hitTestShot(int index, Laser &l)
{
    // verify index is within bounds
    if((index > SALVAGE_OBJECT_COUNT) | (index < 0))
        return false;

    // algorithm taken from: http://en.wikipedia.org/wiki/Hit-testing on Oct 5
    // modified by HSchmale for use in this game
    return (
               (( m_fXCoord[index] + m_fSideLength >= l.getX()) && (m_fXCoord[index] <= l.getX()))
               &&
               (( m_fYCoord[index] + m_fSideLength >= l.getY()) && (m_fYCoord[index] <= l.getY()))
           );
}

void Salvage::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    // draw each index of salvage
    for(int i = 0; i < SALVAGE_OBJECT_COUNT; i++)
    {
        target.draw(s[i], states);
        target.draw(m_TextField[i], states);
    }
}

// getters
int Salvage::getValue(int index)
{
    return m_Value[index];
}
int Salvage::getCount()
{
    return SALVAGE_OBJECT_COUNT;
}
