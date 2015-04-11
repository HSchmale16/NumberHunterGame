/** Declaration of Asteroid Class
*	@author Henry Schmale
*	@date October 14, 2014
*/

#ifndef ASTEROIDS_H
#define ASTEROIDS_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Laser.h"

/**\brief Manages the asteroids seen on screen
 */
class Asteroids: public sf::Drawable
{
public:
    /**\brief Ctor
     * \param nCount The number of asteroids on screen
     * \param trajDeviation The maximum percent deviation from straight down each instance
     *        can travel.
     */
    Asteroids(int nCount, float trajDeviation);

    /**\brief Destructor - Performs Clean-up */
    virtual ~Asteroids();

    /**\brief Update the current posisition of all asteroids
     */
    void Move();

    /**\brief reinitializes a specified instance
     * \param index the thing to refresh
     */
    void ReInit(int index);

    /**\brief  Hit test that index with a player instance
     * \param  index which asteroid index to test against
     * \param  p The player instance to test against
     * \return true if they are touching
     */
    bool hitTestPlayer(int index, Player &p);

    /**\brief  Hit test an index of an asteroid against a specified Laser instance
     * \param  index The asteroid to test
     * \param  l The laser instance to test
     * \return true if the specified objects are touching
     */
    bool hitTestLaser(int index, Laser &l);

    /**\brief  get number of asteroids this class is managing
     * \return the number of asteroids being managed by this instance of this class.
     */
    int getCount();
protected:
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states)const;

    // variables unique to each subinstance
    sf::RectangleShape *m_shape;//!< The Main Body
    float *m_xCoord;            //!< xPos on screen
    float *m_yCoord;            //!< yPos on Screen
    float *m_width;             //!< Width of this object
    float *m_height;            //!< y-axis length
    float *m_xspeed;            //!< Speed on x-axis in Px
    float *m_yspeed;            //!< Speed on the y-axis in Px
    float *m_angle;             //!< Current Angle in degrees
    float *m_rotRate;           //!< The rotation rate in degrees

    float m_MAX_DEVIAT;	        //!< Maximum deviation from straight down

    // global for this object
    int m_nCount;               //!< how many exist total

    // Texture
    sf::Texture *m_tex;         //!< Texture used by the asteroid object
};

#endif // ASTEROIDS_H
