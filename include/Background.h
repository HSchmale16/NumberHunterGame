/** Background Class Declaration
*	@author Henry Schmale
*	@date October 7, 2014
*/


#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <math.h>	// for rand
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Hjs_StdLib.h"
#include "../FilePaths.h"

class Background: public sf::Drawable
{
public:
	/** Default constructor */
	Background();
	/** Default destructor */
	virtual ~Background();
protected:
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

	// Main Background Image
	sf::RectangleShape sfRS;
	sf::Texture texBG;

	// Stars
	sf::Thread starMove;							// Thread to handle moving the stars
	void moveStars();								// Entry Point to starMove
	static const unsigned int STAR_COUNT = 100;		// Stars on Screen
	std::vector<sf::CircleShape> vecStars;
	std::vector<int> vecStarX;
	std::vector<int> vecStarY;

  // Background Music
  sf::Music m_bgMusic;
};

#endif // BACKGROUND_H
