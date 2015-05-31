/** LaserHandler Class
 * Handles the laser bolts and reInits them on keypress
 * @author Henry Schmale
 * @date October 14,2014
 * @file LaserHandler.h
 */

#ifndef LASERHANDLER_H
#define LASERHANDLER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Laser.h"
#include "Player.h"
#include "Salvage.h"
#include "Asteroids.h"
#include "Enemy.h"

class LaserHandler: public sf::Drawable
{
public:
    /**\brief Default Constructor */
    LaserHandler();

    /**\brief Destructor */
    virtual ~LaserHandler();

    // Handles Laser Object Events
    // Returns how many points have been gained by lasers
    int handleEvents(Player *p, Salvage *s, Asteroids *a, Enemy *e);

    int getSalvageDestroyedThisIter();		// gets the count of salvage destroyed during the current iteration
    int getAsteroidsDestroyedThisIter();	// gets the number of asteroids destroyed during the current iteration
protected:
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
    // vector for laser beams
    std::vector<Laser*> m_vecLaser;
    int m_MaxLasers;
    int m_LaserLimiter;				// limits how many lasers can be shot per second

    int m_salvageDest;
    int m_asteroidDest;

    // Sound Data
    sf::SoundBuffer  m_sLaserSndBuff;
    sf::Sound       *m_LaserSnds;
    sf::Sound        m_blewUpSalv;   //!< Blew up salvage with laser
    sf::Sound        m_blewUpAster;  //!< Blew up laser with salvage
};

#endif // LASERHANDLER_H
