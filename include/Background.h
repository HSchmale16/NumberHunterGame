/** Background Class Declaration
 * @author Henry Schmale
 * @date October 7, 2014
 * @file Background.h
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
    /**\brief Default CTOR
     */
     Background();

    /** Default destructor */
    ~Background();
protected:
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

    // Main Background Image
    sf::RectangleShape m_sfRS;
    sf::Texture        m_texBG;

    // Stars
    sf::Thread starMove;                            //!< Thread to handle moving the stars
    void moveStars();                               //!< Entry Point to starMove Thread
    std::vector<sf::CircleShape> m_vecStars;
    std::vector<int> m_vecStarX;
    std::vector<int> m_vecStarY;

    const unsigned int STAR_COUNT;     //!< Stars on Screen
    // Background Music
    sf::Music m_bgMusic;
};

#endif // BACKGROUND_H
