/** Background Class Declaration
 * @author Henry Schmale
 * @date October 7, 2014
 * @file include\Background.h
 */

#ifndef BACKGROUND_H
#define BACKGROUND_H

#ifdef LINUX_BUILD
#include <atomic>
#include <future>
#include <thread>
#endif // LINUX_BUILD

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
    ~Background();
protected:
private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

    // Main Background Image
    sf::RectangleShape m_sfRS;
    sf::Texture m_texBG;

    // Stars
#ifndef LINUX_BUILD
    sf::Thread starMove;                            //!< Thread to handle moving the stars
#else
    std::thread starMove;
#endif //LINUX_BUILD
    void moveStars();                               //!< Entry Point to starMove
    std::vector<sf::CircleShape> m_vecStars;
    std::vector<int> m_vecStarX;
    std::vector<int> m_vecStarY;

    static const unsigned int STAR_COUNT = 100;     //!< Stars on Screen
    // Background Music
    sf::Music m_bgMusic;
};

#endif // BACKGROUND_H
