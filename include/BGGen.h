#ifndef BGGEN_H
#define BGGEN_H

/**\brief Background Generator Class
 *
 * Generates a space themed background of specified dimensions using
 * various image transformation algorithms.
 */

#include <cstdint>

class BGGen
{
public:
    BGGen(uint32_t width, uint32_t height);
    ~BGGen();
protected:
private:
    uint8_t  *m_img;    //!< This things pixel buffer
    uint32_t  m_width;  //!< Width of pixel buffer
    uint32_t  m_height; //!< Height of the pixel buffer
    uint64_t  m_seed;   //!< Seed Value for Generating random noise
};

#endif // BGGEN_H
