/**\file   Enemy.cpp
 * \author Henry J Schmale
 * \date   May 29, 2015
 * \brief  The Enemy Class Implementation File
 */

#include "Enemy.h"
#include "../config.h"

Enemy::Enemy() {
    //ctor
    m_enemyCount = config.GetInteger("enemies", "count", 3);
    m_laserCount = m_enemyCount * config.GetInteger("enemies", "lasers", 5);
    m_lasers     = new Enemy::EnemyLaser[m_laserCount];
    m_rect       = new sf::RectangleShape[m_enemyCount];
    m_width      = new float[m_enemyCount];
    m_height     = new float[m_enemyCount];
    m_xPos       = new float[m_enemyCount];
    m_yPos       = new float[m_enemyCount];
    m_lua        = new lua_State*[m_enemyCount];

    for(uint64_t i  = 0; i < m_enemyCount; i++){
        m_lua[i] = luaL_newstate();
        luaL_openlibs(m_lua[i]);
    }
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

Enemy::EnemyLaser::EnemyLaser(){

}

Enemy::EnemyLaser::~EnemyLaser(){

}

// Drawing Function for the enemy laser
void Enemy::EnemyLaser::draw(sf::RenderTarget &target, sf::RenderStates states)const {

}
