/** \brief  Implementation of Background Generator Class
 *  \author Henry J Schmale
 *  \date   March 20, 2015
 *  \file   BGGen.cpp
 */

#include "../include/BGGen.h"
#include <cstdlib>

#include "../Gradient.h"
#include "../Hjs_StdLib.h"

// ***********************************************
// *          FILE PRIVATE FUNCTIONS             *
// ***********************************************
inline float lerp(float a0, float a1, float w){
    return (1.0 - w) * a0 + w * a1;
}

// ***********************************************
// *            BGGEN IMPLEMENTATION             *
// ***********************************************

bggen::bggen(uint32_t w, uint32_t h)
    : m_thread(&bggen::threadEntryPoint, this),
      m_width(w), m_height(h){
    hjs::logToConsole("Initialized the Background Generator Class");
    m_img.create(m_width, m_height);
    m_seed    = rand() * rand();
    m_genDone = true;
    this->startGenerationProcess();
}

bggen::~bggen(){

}

int bggen::startGenerationProcess(){
    if(m_genDone == true){
        hjs::logToConsole("Started Generation Process");
        m_thread.launch();
        m_genDone = false; // Set False as now generating new image
    }
    return 0;
}

bool bggen::getGenerationStatus(){
    return m_genDone;
}

const uint8_t* bggen::getNewBackground(){
    if(m_genDone == true){
        return m_img.getPixelsPtr();
    }else{
        return NULL;
    }
}

const sf::Image& bggen::getNewBgImage()
{
    return m_img;
}

// ***********************************************
// *          CLASS PRIVATE FUNCTIONS            *
// ***********************************************

void bggen::threadEntryPoint(){
    // clear image
    hjs::logToConsole("Starting Next Iteration of Background Generation");
    this->clearImage(); // This might not really be neccessary
    this->drawClouds();
    hjs::logToConsole("Finished Generation of New Background");
    m_genDone = true;
    m_img.saveToFile("test.png");
}

void bggen::clearImage(){
    for(uint32_t x = 0; x < m_width; x++){
        for(uint32_t y = 0; y < m_height; y++){
            m_img.setPixel(x, y, sf::Color::Black);
        }
    }
}

void bggen::drawPlanet(uint32_t x, uint32_t y){

}

void bggen::drawStars(){

}

void bggen::drawClouds(){
    sf::Color col;
    double p;
    for(uint32_t x = 0; x < m_width; x++){
        for(uint32_t y = 0; y < m_height; y++){
            p = this->perlin(x, y); // holds computed perlin value
            col.r = (uint8_t)(p * 255.0) % 256;
            col.g = (uint8_t)(p * 255.0) % 256;
            col.b = (uint8_t)(p * 255.0) % 256;
            m_img.setPixel(x, y, col);
        }
    }
}

float bggen::dotGridGradient(int ix, int iy, float x, float y){
    float dx = x - (double)(ix);
    float dy = y - (double)(iy);

    return (dx*Gradient[iy][ix][0] + dy*Gradient[iy][ix][1]);
}

float bggen::perlin(float x, float y){
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
