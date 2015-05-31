/** Implementation of Asteroid Class
 * @author Henry Schmale
 * @date October 14, 2014
 * @file src/Asteroids.cpp
 */

#include "../include/Asteroids.h"   //!< Class Header
#include <math.h>
#include "../FilePaths.h"
#include "../Hjs_StdLib.h"

/** \brief a quick and dirty floating point modular division algorithm with a
 * floating point return
 * \param val The value to mod
 * \param r the value to mod with
 */

static inline float floatMod(float val, int r)
{
    if(val < r)
    {
        return val; // the remainder is itself
    }
    return (val - float((int(val) / r) * r));
}

Asteroids::Asteroids(int nCount, float trajDeviation)
{

    m_nCount = nCount;
    // allocate memory
    m_shape = new sf::RectangleShape[m_nCount];
    m_tex = new sf::Texture[m_nCount];
    m_xCoord = new float[m_nCount];
    m_yCoord = new float[m_nCount];
    m_width = new float[m_nCount];
    m_height = new float[m_nCount];
    m_xspeed = new float[m_nCount];
    m_yspeed = new float[m_nCount];
    m_angle = new float[m_nCount];
    m_rotRate = new float[m_nCount];

    // set non declared constant
    m_MAX_DEVIAT = trajDeviation;

    // populate value arrays
    for(int i = 0; i < nCount; i++)
    {
        // set vars
        if(!m_tex[i].loadFromFile(ASTEROID_TEX))
        {
            hjs::logToConsole("Couldn't Load Asteroid Texture");
            exit(2);
        }

        m_xCoord[i] = rand() % 375;
        m_yCoord[i] = rand() % 300;
        m_width[i] = 20 + (rand() % 20);
        m_height[i] = m_width[i];          // Just make it a square the math is easier
        m_yspeed[i] = float(rand() % 1001 / 1000.0f ) * 2 + .05;// somewhere between [0.02, 2.02]
        m_angle[i] = rand() % 360;
        m_rotRate[i] = (rand() % 500) / 1000.0f;
        // randomize left or right deviation
        if(int(m_xCoord[i]) % 2)
        {
            m_xspeed[i] = (m_yspeed[i] * (m_MAX_DEVIAT/2));
        }
        else
        {
            m_xspeed[i] = (m_yspeed[i] * -(m_MAX_DEVIAT/2));
        }


        // setup graphics
        //m_s[i].setOutlineColor(sf::Color::Magenta);
        //m_s[i].setOutlineThickness(2.0);
        m_shape[i].setOrigin(m_width[i] / 2.0f, m_height[i] / 2.0);
        m_shape[i].setTexture(&m_tex[i]);
        m_shape[i].setSize(sf::Vector2f(m_width[i], m_height[i]));
        // m_s[i].setFillColor(sf::Color::Cyan);
        m_shape[i].setPosition(m_xCoord[i], m_yCoord[i]);
        m_shape[i].setRotation(m_angle[i]);
    }
}

Asteroids::~Asteroids()
{
    //dtor
    // deallocate memory for member variables
    delete[] m_shape;
    delete[] m_xCoord;
    delete[] m_yCoord;
    delete[] m_width;
    delete[] m_height;
    delete[] m_xspeed;
    delete[] m_yspeed;
    delete[] m_rotRate;
    delete[] m_angle;
    delete[] m_tex;
}

// Public Member Functions
void Asteroids::Move()
{
    // move each instance
    for(int i = 0; i < m_nCount; i++)
    {
        m_xCoord[i] += m_xspeed[i];
        m_yCoord[i] += m_yspeed[i];
        m_angle[i] = floatMod((m_angle[i] + m_rotRate[i]), 360);
        m_shape[i].setPosition(m_xCoord[i] + (m_width[i] / 2.0f),
                           m_yCoord[i] + (m_height[i] / 2.0f));
        m_shape[i].setRotation(m_angle[i]);

        // reInit the selected index because that index is off screen
        if((m_yCoord[i] > 650) || (m_xCoord[i] < -50) || (m_xCoord[i] > 400))
        {
            this->ReInit(i);
        }
    }
}

void Asteroids::ReInit(int i)
{
    // Out of bounds, auto return
    if(i >= m_nCount)
    {
        hjs::logToConsole("Something tried to reinit a non existent asteroid instance");
        return;
    }
    m_xCoord[i] = rand() % 375;
    m_yCoord[i] = -50;
    m_width[i] = 20 + (rand() % 20);
    m_height[i] = m_width[i];
    m_yspeed[i] = float(rand() % 1001 / 1000.0f) * 2;
    m_angle[i] = rand() % 360;
    m_rotRate[i] = (rand() % 500) / 1000.0f;

    // randomization of left or right trajectory
    if(int(m_xCoord[i]) % 2)
        m_xspeed[i] = (m_yspeed[i] * (m_MAX_DEVIAT/2));
    else
        m_xspeed[i] = (m_yspeed[i] * -(m_MAX_DEVIAT/2));

    m_shape[i].setOrigin(0, 0);
    m_shape[i].setSize(sf::Vector2f(m_width[i], m_height[i]));
    m_shape[i].setPosition(m_xCoord[i], m_yCoord[i]);
    m_shape[i].setOrigin(m_width[i] / 2.0f, m_height[i] / 2.0f);
    m_shape[i].setRotation(m_angle[i]);
}

bool Asteroids::hitTestPlayer(int index, Player &p)
{
    // default case if the index is not valid
    if((index > m_nCount) || (index < 0))
        return false;

    // algorithm taken from: http://en.wikipedia.org/wiki/Hit-testing on Oct 5
    // modified by HSchmale for use in this game
    return (
               (( m_xCoord[index] + m_width[index] >= p.getXCoord()) && (m_xCoord[index] <= p.getXCoord() + p.getSideLength()))
               &&
               (( m_yCoord[index] + m_height[index] >= p.getYCoord()) && (m_yCoord[index] <= p.getYCoord() + p.getSideLength()))
           );
}

bool Asteroids::hitTestLaser(int index, Laser &l)
{
    // verify index is within bounds
    if((index > m_nCount) || (index < 0))
        return false;

    // algorithm taken from: http://en.wikipedia.org/wiki/Hit-testing on Oct 5
    // modified by HSchmale for use in this game
    return (
               (( m_xCoord[index] + m_width[index] >= l.getX()) && (m_xCoord[index] <= l.getX()))
               &&
               (( m_yCoord[index] + m_height[index] >= l.getY()) && (m_yCoord[index] <= l.getY()))
           );
}

// Getters
int Asteroids::getCount()
{
    return m_nCount;
}

// Window Draw Function
void Asteroids::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    for(int i = 0; i < m_nCount; i++)
        target.draw(m_shape[i], states);
}

