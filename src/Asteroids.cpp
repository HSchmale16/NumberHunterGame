/** Implementation of Asteroid Class
 * @author Henry Schmale
 * @date October 14, 2014
 * @file src/Asteroids.cpp
 */

#include "../include/Asteroids.h"
#include <math.h>

Asteroids::Asteroids(int nCount, float trajDeviation)
{
    //ctor
    m_nCount = nCount;
    // allocate memory
    m_s = new sf::RectangleShape[m_nCount];
    m_xCoord = new float[m_nCount];
    m_yCoord = new float[m_nCount];
    m_width = new float[m_nCount];
    m_height = new float[m_nCount];
    m_xspeed = new float[m_nCount];
    m_yspeed = new float[m_nCount];

    // set non declared constant
    m_MAX_DEVIAT = trajDeviation;

    // populate value arrays
    for(int i = 0; i < nCount; i++)
    {
        // set vars
        m_xCoord[i] = rand() % 375;
        m_yCoord[i] = rand() % 600;
        m_width[i] = 20;
        m_height[i] = 20;
        m_yspeed[i] = float(rand() % 1001 / 1000.0f ) * 2 + .02; // somewhere between [0.02, 2.02]
        // randomize left or right deviation
        if(int(m_xCoord[i]) % 2)
            m_xspeed[i] = (m_yspeed[i] * (m_MAX_DEVIAT/2));
        else
            m_xspeed[i] = (m_yspeed[i] * -(m_MAX_DEVIAT/2));

        m_s[i].setSize(sf::Vector2f(m_width[i], m_height[i]));
        m_s[i].setFillColor(sf::Color::Cyan);
        m_s[i].setPosition(m_xCoord[i], m_yCoord[i]);
    }
}

Asteroids::~Asteroids()
{
    //dtor
    // deallocate memory for member variables
    delete[] m_s;
    delete[] m_xCoord;
    delete[] m_yCoord;
    delete[] m_width;
    delete[] m_height;
    delete[] m_xspeed;
    delete[] m_yspeed;
}

// Public Member Functions
void Asteroids::Move()
{
    // move each instance
    for(int i = 0; i < m_nCount; i++)
    {
        m_xCoord[i] += m_xspeed[i];
        m_yCoord[i] += m_yspeed[i];
        m_s[i].setPosition(m_xCoord[i], m_yCoord[i]);

        // reInit the selected index because that index is off screen
        if((m_yCoord[i] > 650) || (m_xCoord[i] < -50) || (m_xCoord[i] > 400))
        {
            this->ReInit(i);
        }
    }
}

void Asteroids::ReInit(int i)
{
    m_xCoord[i] = rand() % 375;
    m_yCoord[i] = -50;
    m_width[i] = 20;
    m_height[i] = 20;
    m_yspeed[i] = float(rand() % 1001 / 1000.0f) * 2;

    // randomization of left or right trajectory
    if(int(m_xCoord[i]) % 2)
        m_xspeed[i] = (m_yspeed[i] * (m_MAX_DEVIAT/2));
    else
        m_xspeed[i] = (m_yspeed[i] * -(m_MAX_DEVIAT/2));

    m_s[i].setPosition(m_xCoord[i], m_yCoord[i]);

}

bool Asteroids::hitTestPlayer(int index, Player &p)
{
    // default case if the index is not valid
    if((index > m_nCount) | (index < 0))
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
    if((index > m_nCount) | (index < 0))
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
        target.draw(m_s[i], states);
}

