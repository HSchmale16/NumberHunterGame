#ifndef GRADIENT_H_INCLUDED
#define GRADIENT_H_INCLUDED

/**\brief defines gradient constants for 2d perlin noise
 * \file   Gradient.h
 * \author Henry J Schmale
 * \date   March 19, 2015
 */

#include <cstdint>

const uint32_t GRAD_X = 375; //!< Max X Dim of Gradient Array
const uint32_t GRAD_Y = 650; //!< Max Y Dim of Gradient Array

extern const float Gradient[GRAD_X][GRAD_Y][2]; //!< The Gradient Vectors Precomputed

#endif // GRADIENT_H_INCLUDED
