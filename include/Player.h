#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player: public sf::Drawable
{
public:
	Player();
	virtual ~Player();
	void Move();

	// getters
	float getXCoord();		// gets x coord - top left corner
	float getYCoord();		// gets y coord - top left
	float getSideLength();	// gets the side length
protected:
private:
	// funcs
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

	// Vars
	float m_fXSpeed;
	float m_fYSpeed;
	float m_fXCoord;
	float m_fYCoord;
	float m_fSideLength;

	// objects
	sf::RectangleShape s;
	sf::Texture m_texture;

};

#endif // PLAYER_H
