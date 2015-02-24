/** Laser Class
*	Instances of this object are created by the Laser Handler  object and are moved by the player object
*	Instances should be hitTest against salvage object
*	@author Henry Schmale
*	@date October 11, 2014
*/

#ifndef LASER_H
#define LASER_H

#include <SFML/Graphics.hpp>

class Laser: public sf::Drawable
{
public:
    Laser();
    virtual ~Laser();

    void Move();							// move this object
    void Activate(int xPos, int yPos);		// reset
    void DeActivate();						// Deactivate and move out of view

    // getters
    float getX();
    float getY();
    float getWidth();
    float getHeight();
    bool getActive();
protected:
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

    sf::RectangleShape m_beam;		// visible body of this
    float m_xCoord;								// X Position on screen
    float m_yCoord;								// Y Position on screen
    float m_speed;								// px per iteration

    bool m_bActive;								// is this instance active

    // declare constant
    const float RADIUS = 3.0;
};

#endif // LASER_H
