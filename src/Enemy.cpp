/**\file   Enemy.cpp
 * \author Henry J Schmale
 * \date   May 29, 2015
 * \brief  The Enemy Class Implementation File
 */

#include "Enemy.h"
#include "../config.h"

Enemy::Enemy() {
    //ctor
}

Enemy::~Enemy() {
    //dtor
    delete[] m_width;
    delete[] m_height;
    delete[] m_xPos;
    delete[] m_yPos;
    delete[] m_lasers;
}

// Drawing Function for the enemy itself
void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states)const {

}

// Drawing Function for the enemy laser
void Enemy::EnemyLaser::draw(sf::RenderTarget &target, sf::RenderStates states)const {

}
