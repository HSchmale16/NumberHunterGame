#include "bggen.h"
#include <cstdlib>

#include "../Gradient.h"

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
    : m_thread(&bggen::threadEntryPoint, this){
    m_img     = new ImgRGBA_t(w, h);
    m_seed    = rand() * rand();
    m_genDone = false;
}

bggen::~bggen(){
    delete m_img;
}

int bggen::startGenerationProcess(){

}

bool bggen::getGenerationStatus(){
    return m_genDone;
}

const uint8_t* bggen::getNewBackground(){
    return m_img->m_data;
}

void bggen::threadEntryPoint(){

}

void bggen::clearImage(){

}

void bggen::drawPlanet(uint32_t x, uint32_t y){

}

void bggen::drawStars(){

}

void bggen::drawClouds(){

}

float bggen::dotGridGradient(int ix, int iy, float x, float y){
    float dx = x - (double)(ix);
    float dy = y - (double)(iy);

    return (dx*Gradient[iy][ix][0] + dy*Gradient[iy][ix][1]);
}

float bggen::perlin(float x, float y){

}
