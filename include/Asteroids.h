/** Declaration of Asteroid Class
*	@author Henry Schmale
*	@date October 14, 2014
*/

#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Laser.h"

class Asteroids: public sf::Drawable
{
public:
    Asteroids(int nCount, float trajDeviation);
    virtual ~Asteroids();

    void Move();
    void ReInit(int index);

    // hit test for player
    bool hitTestPlayer(int index, Player &p);

    // hit test for lasers
    bool hitTestLaser(int index, Laser &l);

    int getCount();
protected:
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states)const;

    // variables unique to each subinstance
    sf::RectangleShape *m_s;	//!< The Main Body
    float *m_xCoord;			//!< xPos on screen
    float *m_yCoord;			//!< yPos on Screen
    float *m_width;				//!< Width of this object
    float *m_height;			//!< y-axis length
    float *m_xspeed;            //!< Speed on x-axis in Px
    float *m_yspeed;            //!< Speed on the y-axis in Px
    float *m_angle;             //!< Current Angle in degrees
    float *m_rotRate;           //!< The rotation rate in degrees

    float m_MAX_DEVIAT;	// Maximum deviation from straight down

    // global for this object
    int m_nCount;				// how many exist total

    // Texture
    sf::Texture *m_tex;          //!< Texture used by the asteroid object
};

#endif // ASTEROIDS_H
