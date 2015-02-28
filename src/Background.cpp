/** Implementation of Background Class
 * @author Henry Schmale
 * @date October 7, 2014
 * @file src/Background.cpp
 */

#include "../include/Background.h"

Background::Background()
#ifndef LINUX_BUILD
    : starMove(&Background::moveStars, this)		// Init the starMove Thread
#endif // LINUX_BUILD
{
    //ctor
    // Set up main bg
    if(!m_texBG.loadFromFile(BG_PLASMA_TEX))
    {
        hjs::logToConsole("FAILED TO LOAD BG_PLASMA_TEX");
        exit(2);
    }
    m_sfRS.setPosition(0, 0);
    m_sfRS.setSize(sf::Vector2f(375, 650));
    m_sfRS.setTexture(&m_texBG, false);



    // Set up stars
    for(unsigned int i = 0; i < STAR_COUNT; i++)
    {
        m_vecStarX.push_back(rand() % 375);
        m_vecStarY.push_back(rand() % 650);
        m_vecStars.push_back(sf::CircleShape());
        m_vecStars[i].setPosition(m_vecStarX[i], m_vecStarY[i]);
        m_vecStars[i].setFillColor(sf::Color::White);
        m_vecStars[i].setRadius((rand() % 15) / 10.0);
    }
#ifndef LINUX_BUILD
    starMove.launch(); // this is a method of sf::Thread
#endif // LINUX_BUILD


    // init music
    if(!m_bgMusic.openFromFile(GM_MUSIC))
    {
        hjs::logToConsole("Failed to Load Music");
    }
    else
    {
        m_bgMusic.setLoop(true);
        m_bgMusic.play();
    }
}

Background::~Background()
{
    //dtor
}

void Background::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
    target.draw(m_sfRS, states);	// draw main background image
    // draw the stars
    for(unsigned int i = 0; i < STAR_COUNT; i++)
    {
        target.draw(m_vecStars[i], states);
    }
}

void Background::moveStars()
{
    hjs::logToConsole("Background Star Move Thread Launched");
    while(hjs::gameIsActive())	// window is not accessible to this object, so use my library to check if window was called
    {
        for(unsigned int i = 0; i < STAR_COUNT; i++)
        {
            m_vecStarY[i] += 1;
            if(m_vecStarY[i] > 650)
            {
                m_vecStarY[i] = 0;
                m_vecStarX[i] = rand() % 375;
            }
            m_vecStars[i].setPosition(m_vecStarX[i], m_vecStarY[i]);
        }
        sf::sleep(sf::milliseconds(30));
    }
    hjs::logToConsole("Background Start Move Thread Terminating");
}
