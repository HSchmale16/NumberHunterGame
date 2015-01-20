#ifndef SALVAGE_H
#define SALVAGE_H

#include <SFML/Graphics.hpp>
#include "../Hjs_StdLib.h"
#include "Player.h"			// for hitTest
#include "Laser.h"

class Salvage: public sf::Drawable
{
public:
	Salvage(uint_fast8_t count);
	virtual ~Salvage();

	bool hitTest(int index, Player& p);			// tests if the selected index is within the bounds of the player object
	bool hitTestShot(int index, Laser &l);		// tests if a laser(single coord is within the bounds of the selected index of salvage
	void Move();								// Moves this object

	// getters
	int getValue(int index);					// gets the value of salvage at index
	int getCount();								// gets how many are on screen

	// Reset
	void ReInit(int i);

protected:
private:
	// Variables
	uint_fast8_t SALVAGE_OBJECT_COUNT;
	float m_fSideLength;		// Length of sides
	float *m_fXCoord;			// Coords
	float *m_fYCoord;
	float *m_fSpeed;			// Speed of movement
	uint_fast8_t *m_Value;		// Collection Value of this

	// Graphics Handling
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	sf::RectangleShape *s;		// BG
	sf::Text *m_TextField;
	sf::Font font;
};

#endif // SALVAGE_H
