/** Implementation of Background Class
*	@author Henry Schmale
*	@date October 7, 2014
*/

#include "../include/Background.h"

Background::Background()
    : starMove(&Background::moveStars, this)		// Init the starMove Thread
{
    //ctor
    // Set up main bg
    if(!texBG.loadFromFile(BG_PLASMA_TEX))
    {
        hjs::logToConsole("FAILED TO LOAD BG_PLASMA_TEX");
        exit(2);
    }
    sfRS.setPosition(0, 0);
    sfRS.setSize(sf::Vector2f(375, 650));
    sfRS.setTexture(&texBG, false);

    // Set up stars
    for(unsigned int i = 0; i < STAR_COUNT; i++)
    {
        vecStarX.push_back(rand() % 375);
        vecStarY.push_back(rand() % 650);
        vecStars.push_back(sf::CircleShape());
        vecStars[i].setPosition(vecStarX[i], vecStarY[i]);
        vecStars[i].setFillColor(sf::Color::White);
        vecStars[i].setRadius((rand() % 15) / 10.0);
    }
    starMove.launch();

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
    target.draw(sfRS, states);	// draw main background image
    // draw the stars
    for(unsigned int i = 0; i < STAR_COUNT; i++)
    {
        target.draw(vecStars[i], states);
    }
}

void Background::moveStars()
{
    while(hjs::gameIsActive())	// window is not accessible to this object, so use my library to check if window was called
    {
        for(unsigned int i = 0; i < STAR_COUNT; i++)
        {
            vecStarY[i] += 1;
            if(vecStarY[i] > 650)
            {
                vecStarY[i] = 0;
                vecStarX[i] = rand() % 375;
            }
            vecStars[i].setPosition(vecStarX[i], vecStarY[i]);
        }
        sf::sleep(sf::milliseconds(30));
    }
}
