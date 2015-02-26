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

static inline float floatMod(float val, int r)
{
    if(val < r)
    {
        return val; // the remainder is itself
    }
    return (val - float((int(val) / r) * r));
}

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
    m_fSideLength = new float[SALVAGE_OBJECT_COUNT];
    m_fXCoord = new float[SALVAGE_OBJECT_COUNT];
    m_fYCoord = new float[SALVAGE_OBJECT_COUNT];
    m_fSpeed = new float[SALVAGE_OBJECT_COUNT];
    m_Value = new uint_fast8_t[SALVAGE_OBJECT_COUNT];
    m_TextField = new sf::Text[SALVAGE_OBJECT_COUNT];
    m_shape = new sf::RectangleShape[SALVAGE_OBJECT_COUNT];
    m_tex = new sf::Texture[SALVAGE_OBJECT_COUNT];
    // begin assignment

    for(int i = 0; i < SALVAGE_OBJECT_COUNT; i++)
    {
        m_fSideLength[i] = 30 + rand() % 20;
        if(!m_tex[i].loadFromFile(SALVAGE_TEXTURE))
        {
            hjs::logToConsole("Couldn't load salvage texture");
            exit(2);
        }
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

        sf::FloatRect rectBounds = m_shape[i].getGlobalBounds();
        sf::FloatRect textBounds = m_TextField[i].getGlobalBounds();
        m_TextField[i].setPosition(
            rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
            rectBounds.top + (rectBounds.height / 2) - (textBounds.height / 2)
        );

        // set up graphics
        m_shape[i].setSize(sf::Vector2f(m_fSideLength[i], m_fSideLength[i]));
        m_shape[i].setTexture(&m_tex[i]);
        m_shape[i].setPosition(m_fXCoord[i], m_fYCoord[i]);
    }
}

Salvage::~Salvage()
{
    //dtor
    delete[] m_fXCoord;
    delete[] m_fYCoord;
    delete[] m_fSpeed;
    delete[] m_Value;
    delete[] m_shape;
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
        m_shape[i].setPosition(m_fXCoord[i], m_fYCoord[i]);
        sf::FloatRect rectBounds = m_shape[i].getGlobalBounds();
        sf::FloatRect textBounds = m_TextField[i].getGlobalBounds();
        m_TextField[i].setPosition(
            rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
            rectBounds.top + (rectBounds.height / 2) - (textBounds.height / 2)
        );
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
    sf::FloatRect rectBounds = m_shape[i].getGlobalBounds();
    sf::FloatRect textBounds = m_TextField[i].getGlobalBounds();
    m_TextField[i].setPosition(
        rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
        rectBounds.top + (rectBounds.height / 2) - (textBounds.height / 2)
    );
    m_shape[i].setPosition(m_fXCoord[i], m_fYCoord[i]);
}

bool Salvage::hitTest(int index, Player& p)
{
    // verify index is within bounds
    if((index > SALVAGE_OBJECT_COUNT) | (index < 0))
        return false;

    // algorithm taken from: http://en.wikipedia.org/wiki/Hit-testing on Oct 5
    // modified by HSchmale for use in this game
    return (
               (( m_fXCoord[index] + m_fSideLength[index] >= p.getXCoord()) && (m_fXCoord[index] <= p.getXCoord() + p.getSideLength()))
               &&
               (( m_fYCoord[index] + m_fSideLength[index] >= p.getYCoord()) && (m_fYCoord[index] <= p.getYCoord() + p.getSideLength()))
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
               (( m_fXCoord[index] + m_fSideLength[index] >= l.getX()) && (m_fXCoord[index] <= l.getX()))
               &&
               (( m_fYCoord[index] + m_fSideLength[index] >= l.getY()) && (m_fYCoord[index] <= l.getY()))
           );
}

void Salvage::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    // draw each index of salvage
    for(int i = 0; i < SALVAGE_OBJECT_COUNT; i++)
    {
        target.draw(m_shape[i], states);
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
