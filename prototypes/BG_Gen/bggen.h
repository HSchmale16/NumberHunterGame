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
    uint8_t* m_data     //!< The data buffer to hold the pixel values

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


private:
    ImgRGBA_t* m_img;


};

#endif // BGGEN_H
