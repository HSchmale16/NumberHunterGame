/** \brief  Implementation of Background Generator Class
 *  \author Henry J Schmale
 *  \date   March 20, 2015
 *  \file   BGGen.cpp
 */

#include "../include/BGGen.h"
#include <cstdlib>
#include <cmath>

#include "../Gradient.h"
#include "../Hjs_StdLib.h"

// ***********************************************
// *      FILE PRIVATE FUNCTIONS & DATA          *
// ***********************************************

#define PI 3.14159265
#define CLOUDS_IMG "resources/Clouds.png"
/** \brief Linerally Intepolartes some numbers
 */
inline float lerp(float a0, float a1, float w) {
    return (1.0 - w) * a0 + w * a1;
}

/** \brief Maps one value that is in-between 2 limits to some value between
 *         2 differint limits.
 *  \return       The value mapped
 *  \param x      The value to be mapped
 *  \param inMin  The minimum value that can be input
 *  \param inMax  The maximum value that can be input
 *  \param outMin The minimum value that can be output
 *  \param outMax The maximum value that can be output
 *  \note There is no input verifcation provided on the input values.
 */
template<typename TYP>
inline TYP map(TYP x, TYP inMin, TYP inMax, TYP outMin, TYP outMax) {
    return (x - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}
/** \brief clamps some value between 2 other values */template<typename TYP>inline TYP clamp(TYP x, TYP Min, TYP Max){    if((x <= Max) && (x >= Min)){        return x;    }else if(x < Min){        return Min;    }else if(x > Max){        return Max;    }    return Min;}/** \return a random value between 2 limits */template<typename TYP>inline TYP randClamped(TYP L, TYP U){    return (rand() % abs(U - L)) + L;}
// ***********************************************
// *            BGGEN IMPLEMENTATION             *
// ***********************************************

bggen::bggen(uint32_t w, uint32_t h)
    : m_thread(&bggen::threadEntryPoint, this),
      m_width(w), m_height(h) {
    hjs::logToConsole("Initialized the Background Generator Class");
    m_img.create(m_width, m_height);
    m_seed    = rand() * rand();
    m_genDone = true;
    this->startGenerationProcess();
}

bggen::~bggen() {

}

int bggen::startGenerationProcess() {
    if(m_genDone == true) {
        hjs::logToConsole("Started Generation Process");
        m_thread.launch();
        m_genDone = false; // Set False as now generating new image
    }
    return 0;
}

bool bggen::getGenerationStatus() {
    return m_genDone;
}

const uint8_t* bggen::getNewBackground() {
    if(m_genDone == true) {
        return m_img.getPixelsPtr();
    } else {
        return NULL;
    }
}

const sf::Image& bggen::getNewBgImage() {
    return m_img;
}

// ***********************************************
// *          CLASS PRIVATE FUNCTIONS            *
// ***********************************************

void bggen::threadEntryPoint() {
    // clear image
    hjs::logToConsole("Starting Next Iteration of Background Generation");
    this->clearImage(); // This might not really be neccessary    this->drawStars();
    this->drawClouds();    this->drawStars();
    hjs::logToConsole("Finished Generation of New Background");
    m_genDone = true;
    m_img.saveToFile("test.png");
}

void bggen::clearImage() {
    for(uint32_t x = 0; x < m_width; x++) {
        for(uint32_t y = 0; y < m_height; y++) {
            m_img.setPixel(x, y, sf::Color::Black);
        }
    }
}

void bggen::drawPlanet(uint32_t x, uint32_t y) {
    int r  = (rand() % 50) / 2;
    int x0 = rand() % m_width;
    int y0 = rand() % m_height;
    int x  = r;
    int y  = 0;
    int rE = 1 - x;
    // A variant of the midpoint circle algorithm
    while(x >= y){
        // Draw the Planet's Colors using a random stripe algorithim
        // DrawStripe(x + x0, y + y0, -x + y0,  y + y0);
        // DrawStripe(x + x0, y - y0, -x + y0, -y + y0);
        // DrawStripe(y + x0, x + y0, -y + y0,  x + y0);
        // DrawStripe(y + x0, x - y0, -y + y0, -x + x0);
        y++;
        if(rE < 0){
            rE += 2*y+1;
        }else{
            x--;
            rE += 2*(y - x) + 1;
        }
    }
}

void bggen::drawStars() {
    uint16_t stars = rand() % 100 + 50;    for(uint16_t i = 0; i < stars; i++){        uint8_t intensity = (rand() % 64) + 192;        uint32_t x = rand() % m_width,                 y = rand() % m_height;        sf::Color c = m_img.getPixel(x, y);        sf::Color n(intensity, intensity, intensity, 255);        sf::Color m = c + n;        m_img.setPixel(x, y, m);        m_img.setPixel(x, y + 1, m);        m_img.setPixel(x, y - 1, m);        m_img.setPixel(x + 1, y, m);        m_img.setPixel(x - 1, y, m);        n = sf::Color(intensity * .25, intensity * .25, intensity *.25, intensity * .25);        m = c + n;        m_img.setPixel(x + 1, y + 1, m);        m_img.setPixel(x + 1, y - 1, m);        m_img.setPixel(x - 1, y + 1, m);        m_img.setPixel(x - 1, y - 1, m);    }
}

void bggen::drawClouds() {
    sf::Color col;#ifdef USE_PROCEDURAL_GEN
    double p,           minThresh = randClamped(0, 32),           maxThresh = randClamped(32, 192),           dThresh   = randClamped(minThresh, maxThresh);
    for(uint32_t x = 0.0; x < m_width; x++) {
        for(uint32_t y = 0.0; y < m_height; y++) {
            col =  m_img.getPixel(round(x), round(y));
            p = this->perlin(map((double)x, 0.0, (double)m_width, -2.0 * PI, 2.0 * PI),
                             map((double)y, 0.0, (double)m_height, PI, 9.0 * PI));
            p = clamp(p * 255.0, minThresh, maxThresh);
            if(p > dThresh){
                col += sf::Color(p*sin(map((double)x, 0.0, (double)m_width, 0.0, PI/2.0)),
                                 p*cos(map((double)y, 0.0, (double)m_height,0.0, PI/2.0)),
                                 p*sin(map((double)y+x, 0.0,
                                           (double)(m_width * m_height), 0.0, PI/2.0)),
                                 p*cos(map((double)x-y, 0.0,                                           double(m_width + m_height), 0.0, PI/2.0)));
            }
            m_img.setPixel(round(x), round(y), col);        }
    }#else    sf::Image tile;    if(!tile.loadFromFile(CLOUDS_IMG)){        hjs::logToConsole("Failed to load Clouds Tile");        return;    }else{        hjs::logToConsole("Loaded the clouds tile");    }    // rotate the image, but not really as it is a flip    if(rand() % 2 == 0){        tile.flipHorizontally();    }    if(rand() % 2 == 0){        tile.flipVertically();    }    for(uint32_t x = 0; x < m_width; x += tile.getSize().x){        for(uint32_t y = 0; y < m_height; y += tile.getSize().y){            m_img.copy(tile, x, y, sf::IntRect(), true);        }    }#endif // USE_PROCEDURAL_GEN
}

float bggen::dotGridGradient(int ix, int iy, float x, float y) {
    float dx = x - (double)(ix);
    float dy = y - (double)(iy);

    return (dx*Gradient[iy][ix][0] + dy*Gradient[iy][ix][1]);
}

float bggen::perlin(float x, float y) {
    int x0   = (x > 0.0 ? (int)x : (int)x-1);
    int x1   = x0 + 1;
    int y0   = (y > 0.0 ? (int)y : (int)y-1);
    int y1   = y0 + 1;

    float sx = x - (double)x0;
    float sy = y - (double)y0;

    float n0, n1, ix0, ix1, value;
    n0       = dotGridGradient(x0, y0, x, y);
    n1       = dotGridGradient(x1, y0, x, y);
    ix0      = lerp(n0, n1, sx);
    n0       = dotGridGradient(x0, y1, x, y);
    n1       = dotGridGradient(x1, y1, x, y);
    ix1      = lerp(n0, n1, sx);
    value    = lerp(ix0, ix1, sy);
    return value;
}
