#include "bggen.h"
#include <cstdlib>

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

}

void bggen::threadEntryPoint(){

}

void bggen::clearImage(){

}

void drawPlanet(uint32_t x, uint32_t y){

}

void drawStars(){

}

void drawClouds(){

}
