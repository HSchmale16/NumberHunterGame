/**\brief The file to hold the precomputed gradient vector for
 *        generating perlin noise.
 * \author Henry J Schmale
 * \date   March 19, 2015
 * \file   Gradient.cpp
 *
 * This file contains the precomputed computed gradient vectors.
 * Might as well just stick it into the binary, as it would be harder
 * to break it then.
 */

#include "Gradient.h"

const float Gradient[GRAD_Y][GRAD_X][2] =
