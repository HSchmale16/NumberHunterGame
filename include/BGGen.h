/**\brief  A procedural background generator for space themed games
 * \file   bggen.h
 * \author Henry J Schmale
 * \date   March 18, 2015
 * \copyright This code is exclusive property of Henry J Schmale.
 *            It may not be used for commercial purposes without
 *            his express authorization, however it is free for
 *            personal and educational use.
 *
 * Additionally this procedural generation system has global variables that
 * can control the process of generation.
 */

#ifndef BGGEN_H
#define BGGEN_H

#include <cstdint>          // Fixed Width Integers
#include <SFML/System.hpp>  // Threading on windoze
#include <SFML/Graphics/Image.hpp>

/**\brief a struct that can contains an RGBA Image
 */
struct ImgRGBA_t {
    uint64_t m_length;  //!< Length of the data array
    uint32_t m_width;   //!< Width of the image
    uint32_t m_height;  //!< Height of the image
    uint8_t* m_data;    //!< The data buffer to hold the pixel values

    /**\brief Primary Ctor
     * \param w width
     * \param h height
     */
    ImgRGBA_t(uint32_t w, uint32_t h)
        : m_width(w), m_height(h) {
        m_length = m_width * m_height * 4;
        m_data   = new uint8_t[m_length];
        // Init Img to 0 or nothing
        for(uint64_t i = 0; i < m_length; i++) {
            m_data[i] = 0;
        }
    }

    /** \brief Destructor
     */
    ~ImgRGBA_t() {
        delete[] m_data;
    }

    /**\brief direct access of data array operator
     */
    uint8_t& operator[](uint64_t i) {
        return m_data[i];
    }

    /**\brief Coordinate Color Value Access Operator
     */
    uint8_t& operator()(uint32_t x, uint32_t y, uint8_t c){
        return m_data[y * m_width + x];
    }
};


/**\brief A background generator class
 */
class bggen {
public:
    /**\brief Primary Ctor
     * \param w width
     * \param h height
     */
    bggen(uint32_t w, uint32_t h);

    /** \brief The Destructor
     */
    ~bggen();

    /**\brief Starts up the background generation process in the background
     *         running in a seperate thread.
     * \return 0 on successful startup of the background process, any other
     * value returns to false.
     */
    int startGenerationProcess();

    /**\brief Is the generation of the next background complete?
     * \return The status on generation of the new background.
     *         Returns true when complete, otherwise false.
     */
    bool getGenerationStatus();

    /**\brief Returns a constant pointer containing a set of RGBA Pixels
     *        that can be used in an sf::Texture or sf::Image instance.
     * \return A pointer to a set of RGBA Pixels
     */
    const uint8_t* getNewBackground();

    /**\brief Fetches the new background as an sf::Image
     */
    const sf::Image& getNewBgImage();
private:
    sf::Thread m_thread;   //!< Thread that will run the generation system
    sf::Image  m_img;
    uint64_t   m_seed;     //!< Seed used for background generation
    uint32_t   m_width;
    uint32_t   m_height;
    bool       m_genDone;  //!< Generation of new background is complete

    /**\brief Entry Point for procedural generatoion
     */
    void threadEntryPoint();

    /**\brief clears the image to black
     */
    void clearImage();

    /**\brief Draws a randomly generated planet at the specified coords.
     * \param x x-axis positions of planet, top-left corner
     * \param y y-axis positions of planet, top-left corner
     *
     * This is a specialized implementation of the midpoint-circle
     * algorithm for drawing planets that are reminiscent of a
     * gas giant.
     */
    void drawPlanet(uint32_t x, uint32_t y);

    /**\brief Draws stars at random positions and of varying intensity
     */
    void drawStars();

    /**\brief Draws the clouds on to image
     *
     * Runs through the various parts of the perlin algorithim on this object's
     * internal image buffer
     */
    void drawClouds();

    float dotGridGradient(int ix, int iy, float x, float y);

    /**\brief calculates perlin noise vector at given coords
     */
    float perlin(float x, float y);
};

#endif // BGGEN_H
