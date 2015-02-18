/** Implementation of Laser Class
*	@author Henry Schmale
*	@date October 11, 2014
*/

#include "../include/Laser.h"
#include "../INIReader.h"
#include "../FilePaths.h"
#include "../Hjs_StdLib.h"

// config helper
INIReader lr(CONFIG_FILE);

Laser::Laser()
{
    //ctor
    m_beam.setFillColor(sf::Color::Red);
    m_beam.setSize(sf::Vector2f(RADIUS, RADIUS * 4));


    m_speed = lr.GetReal("player", "laser_shot_speed", 5.0);
    m_bActive = false;
    hjs::logToConsole("Laser Created");
}

Laser::~Laser()
{
    //dtor
    hjs::logToConsole("Laser Destroyed");
}

void Laser::Move()
{
    if((m_yCoord < -100) && (m_bActive == true))
    {
        m_bActive = false;
    }
    else if(m_bActive == true)
    {
        m_yCoord -= m_speed;
        m_beam.move(0, -m_speed);
    }
}

void Laser::Activate(int xPos, int yPos)
{
    m_xCoord = xPos - RADIUS;
    m_yCoord = yPos - RADIUS;
    m_bActive = true;

    m_beam.setPosition(m_xCoord, m_yCoord);

    hjs::logTimeToConsole();
    std::cout << "Laser Created at " << xPos << " , " << yPos << std::endl;
}

void Laser::DeActivate()
{
    m_bActive = false;
    m_yCoord = 2000;
    m_beam.setPosition(m_xCoord, m_yCoord);
    //hjs::logTimeToConsole();
    //std::cout << "Laser Deactivated at " << m_xCoord << " , " << m_yCoord << std::endl;
}

void Laser::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    if(m_bActive)
        target.draw(m_beam, states);
}

// Getters
float Laser::getX()
{
    return m_xCoord;
}
float Laser::getY()
{
    return m_yCoord;
}
bool Laser::getActive()
{
    return m_bActive;
}
