/**\brief  A procedural background generator for space themed games
 * \file   bggen.h
 * \author Henry J Schmale
 * \date   March 18, 2015
 * \copyright This code is exclusive property of Henry J Schmale.
 *            It may not be used for commercial purposes without
 *            his express authorization, however it is free for
 *            personal and educational use.
 */

#ifndef BGGEN_H
#define BGGEN_H

#include <cstdint>

/** \brief A color channel enumeration for ImgRGBA_t defined below
 */
enum COLOR_CHAN{
    RED   = 0,  //!< Starting Index of the Red Channel
    GREEN = 1,  //!< Starting Index of the Green Channel
    BLUE  = 2,  //!< Starting Index of the Blue Channel
    ALPHA = 3,  //!< Starting Index of the Alpha Channel
};

/**\brief a struct that can contains an RGBA Image
 */
struct ImgRGBA_t{
    uint32_t m_width;   //!< Width of the image
    uint32_t m_height;  //!< Height of the image
    uint8_t* m_data;    //!< The data buffer to hold the pixel values

    /**\brief Primary Ctor
     * \param w width
     * \param h height
     */
    ImgRGBA_t(uint32_t w, uint32_t h)
      : m_width(w), m_height(h){
        m_data = new uint8_t[m_width * m_height * 4];
    }

    /** \brief Destructor
     */
    ~ImgRGBA_t(){
        delete[] m_data; 
    }

    /** \brief Element Access Operator
     */
    uint8_t& operator()(uint32_t x, uint32_t y, COLOR_CHAN c){
        
    }
};


/**\brief A background generator class
 */
class bggen{
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

    /**\brief Returns a constant pointer containing a set of RGBA Pixels
     *        that can be used in an sf::Texture or sf::Image instance.
     * \return A pointer to a set of RGBA Pixels
     */
    const uint8_t* getNewBackground();
private:
    ImgRGBA_t* m_img;     //!< Image buffer of the background generator
    uint64_t   m_seed;    //!< Seed used for background generation
    bool       m_genDone; //!< Generation of new background is complete


};

#endif // BGGEN_H
