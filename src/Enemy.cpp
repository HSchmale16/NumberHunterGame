/**\file   Enemy.cpp
 * \author Henry J Schmale
 * \date   May 29, 2015
 * \brief  The Enemy Class Implementation File
 */

#include "Enemy.h"
#include "../config.h"
#include "../Hjs_StdLib.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>

Enemy::Enemy() {
    //ctor
    m_enemyCount = config.GetInteger("enemies", "count", 3);
    m_laserCount = m_enemyCount * config.GetInteger("enemies", "lasers", 5);
    m_width      = new float[m_enemyCount];
    m_height     = new float[m_enemyCount];
    m_xPos       = new float[m_enemyCount];
    m_yPos       = new float[m_enemyCount];
    m_active     = new bool[m_enemyCount];
    m_lua        = new lua_State*[m_enemyCount];
    m_shape      = new sf::RectangleShape[m_enemyCount];

    if(!m_texture.loadFromFile("resources/img/Enemy.png")){
        //!< \todo Screw up logic for file load fail
    }

    for(uint64_t i  = 0; i < m_enemyCount; i++) {
        // Init the Lua VM
        m_lua[i] = luaL_newstate();
        luaL_openlibs(m_lua[i]);
        if(luaL_loadfile(m_lua[i],
                         config.Get("enemies", "script1", "resources/enemy1.lua").c_str())
                || lua_pcall(m_lua[i], 0, 0, 0)) {
            fprintf(stderr, "Lua Error = %s", lua_tostring(m_lua[i], -1));
        }
        lua_getglobal(m_lua[i], "init");
        if(!lua_isfunction(m_lua[i], -1)) {
            lua_pop(m_lua[i], 1);
            hjs::logToConsole("init is not a function. This is really bad.");
            exit(0);
        }
        if(lua_pcall(m_lua[i], 0, 0, 0) != 0) {
            hjs::logTimeToConsole();
            fprintf(stderr, "Err: Returning 'init': %s\n", lua_tostring(m_lua[i], -1));
            exit(0);
        }
        // Set default Values
        lua_getglobal(m_lua[i], "xPos");
        m_xPos[i] = (float)lua_tonumber(m_lua[i], -1);
        lua_getglobal(m_lua[i], "yPos");
        m_yPos[i] = (float)lua_tonumber(m_lua[i], -1);
        lua_pop(m_lua[i], 2);
        // Init the other values
        m_width[i] = 30;
        m_height[i] = 30;
        m_active[i] = true;
        // Init the shape
        m_shape[i].setSize(sf::Vector2f(m_width[i], m_height[i]));
        m_shape[i].setFillColor(sf::Color::Green);
        m_shape[i].setPosition(m_xPos[i], m_yPos[i]);
        m_shape[i].setTexture(&m_texture);
        hjs::logToConsole("Enemy Created");
    }
}

Enemy::~Enemy() {
    //dtor
    delete[] m_width;
    delete[] m_height;
    delete[] m_xPos;
    delete[] m_yPos;
    delete[] m_shape;
    delete[] m_active;
    for(uint64_t i = 0; i < m_enemyCount; i++) {
        lua_close(m_lua[i]);
    }
}

void Enemy::ReInit(uint64_t index) {
    m_active[index] = true;
    lua_getglobal(m_lua[index], "init");
    if(lua_pcall(m_lua[index], 0, 0, 0) != 0) {
        hjs::logTimeToConsole();
        fprintf(stderr, "Err: Returning 'init': %s\n", lua_tostring(m_lua[index], -1));
        exit(0);
    }
    lua_getglobal(m_lua[index], "xPos");
    m_xPos[index] = (float)lua_tonumber(m_lua[index], -1);
    lua_getglobal(m_lua[index], "yPos");
    m_yPos[index] = (float)lua_tonumber(m_lua[index], -1);
    lua_pop(m_lua[index], 2);
    m_shape[index].setPosition(m_xPos[index], m_yPos[index]);
}

void Enemy::Move() {
    for(uint64_t i = 0; i < m_enemyCount; i++) {
        if(m_active[i] != true) {
            continue;
        }
        // run the lua virtual machine for this iteration
        lua_getglobal(m_lua[i], "moveEnemy");
        if(lua_pcall(m_lua[i], 0, 0, 0) != 0) {
            //!\todo Handle Error
        }
        lua_getglobal(m_lua[i], "xPos");
        m_xPos[i] = (float)lua_tonumber(m_lua[i], -1) - m_width[i] / 2.0;
        lua_getglobal(m_lua[i], "yPos");
        m_yPos[i] = (float)lua_tonumber(m_lua[i], -1) - m_height[i] / 2.0;
        // check if it can shoot
        lua_getglobal(m_lua[i], "shoot");
        if(lua_pcall(m_lua[i], 0, 1, 0) != 0) {
            //!< \todo handle error
        }
        bool shoot = lua_toboolean(m_lua[i], -1);
        if(shoot) {
            this->initLaser(i);
        }
        // Clean up and update position
        lua_pop(m_lua[i], 2); // Free the some memory
        m_shape[i].setPosition(m_xPos[i], m_yPos[i]);
    }
    for(uint64_t i = 0; i < m_lasers.size(); i++) {
        m_lasers[i]->Move();
        if(!m_lasers[i]->getActive()) {
            m_lasers.erase(m_lasers.begin() + i);
            i--;
        }
    }
}

// Drawing Function for the enemy itself
void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states)const {
    for(uint64_t i = 0; i < m_lasers.size(); i++) {
        target.draw(*(m_lasers[i]), states);
    }
    for(uint64_t i = 0; i < m_enemyCount; i++) {
        if(m_active[i]) {
            target.draw(m_shape[i], states);
        }
    }
}

void Enemy::initLaser(uint64_t index) {
    if(index > m_enemyCount || index < 0) {
        return;
    }
    lua_getglobal(m_lua[index], "bullet_dx");
    float bdx = (float)lua_tonumber(m_lua[index], -1);
    lua_pop(m_lua[index], 1);
    lua_getglobal(m_lua[index], "bullet_dy");
    float bdy = (float)lua_tonumber(m_lua[index], -1);
    lua_pop(m_lua[index], 1);
    //!<\todo Create a new EnemyLaser instance in the m_lasers vector
    m_lasers.push_back(new EnemyLaser(m_xPos[index], m_yPos[index], bdx, bdy));
    hjs::logTimeToConsole();
    std::cerr << m_lasers.size() << "\t"
              << m_xPos[index] << "\t" << m_yPos[index] << "\t" << bdx << "\t" << bdy
              << std::endl;
    return; // init only ONE laser
}

bool Enemy::hitTestLaser(uint64_t index, Laser &l) {
    // verify index is within bounds
    if((index > m_enemyCount) || (index < 0))
        return false;

    // algorithm taken from: http://en.wikipedia.org/wiki/Hit-testing on Oct 5
    // modified by H. Schmale for use in this game
    return (
               (( m_xPos[index] + m_width[index] >= l.getX()) &&
                (m_xPos[index] <= l.getX()))
               &&
               (( m_yPos[index] + m_height[index] >= l.getY()) &&
                (m_yPos[index] <= l.getY()))
           );
}

bool Enemy::hitTestPlayer(uint64_t index, Player &p) {
    // default case if the index is not valid
    if((index > m_enemyCount) || (index < 0))
        return false;

    lua_pushnumber(m_lua[index], p.getXCoord());
    lua_setglobal(m_lua[index], "player_x");
    lua_pushnumber(m_lua[index], p.getYCoord());
    lua_setglobal(m_lua[index], "player_y");

    // algorithm taken from: http://en.wikipedia.org/wiki/Hit-testing on Oct 5
    // modified by HSchmale for use in this game
    return (
               (( m_xPos[index] + m_width[index] >= p.getXCoord()) &&
                (m_xPos[index] <= p.getXCoord() + p.getSideLength()))
               &&
               (( m_yPos[index] + m_height[index] >= p.getYCoord()) &&
                (m_yPos[index] <= p.getYCoord() + p.getSideLength()))
           );
}

// Getter Methods
uint64_t Enemy::getEnemyCount() {
    return m_enemyCount;
}
uint64_t Enemy::getLaserCount() {
    return m_lasers.size();
}

EnemyLaser* Enemy::getLaser(uint64_t i) {
    return m_lasers[i];
}

// ==============================================
// Implementation of Enemy::EnemyLaser Below
// ==============================================
EnemyLaser::EnemyLaser() {
    m_active = false;
}

EnemyLaser::EnemyLaser(float x, float y, float dx, float dy){
    m_active = true;
    m_xPos   = x;
    m_xSpeed = dx;
    m_yPos   = y;
    m_ySpeed = dy;
    m_shape.setRadius(5);
    m_shape.setFillColor(sf::Color::Red);
    //hjs::logTimeToConsole();
    //std::cerr << m_xPos << "\t" << m_yPos << "\t" << m_xSpeed << "\t" << m_ySpeed
    //          << std::endl;
}

EnemyLaser::~EnemyLaser() {

}

void EnemyLaser::Move() {
    if(!m_active) {
        return;
    }
    m_xPos += m_xSpeed;
    m_yPos += m_ySpeed;
    if((m_xPos < 0) || (m_xPos > 375) || (m_yPos < 0) || (m_yPos > 650)) {
        m_active = false;
    }
    m_shape.setPosition(m_xPos, m_yPos);
}

bool EnemyLaser::getActive() {
    return m_active;
}

bool EnemyLaser::hitTestPlayer(Player& p) {
    bool hit = (
               (( m_xPos >= p.getXCoord()) &&
                (m_xPos <= p.getXCoord() + p.getSideLength()))
               &&
               (( m_yPos >= p.getYCoord()) &&
                (m_yPos <= p.getYCoord() + p.getSideLength()))
           );
    if(hit){
        m_active = false; // deactivate so that Enemy class can gc this
    }
    return hit;
}

// Drawing Function for the enemy laser
void EnemyLaser::draw(sf::RenderTarget &target, sf::RenderStates states)const {
    if(m_active) {
        target.draw(m_shape, states);
    }
}
