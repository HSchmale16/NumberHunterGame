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

Enemy::Enemy() {
    //ctor
    m_enemyCount = 1;
    m_laserCount = m_enemyCount * config.GetInteger("enemies", "lasers", 5);
    m_lasers     = new Enemy::EnemyLaser[m_laserCount];
    m_shape      = new sf::RectangleShape[m_enemyCount];
    m_width      = new float[m_enemyCount];
    m_height     = new float[m_enemyCount];
    m_xPos       = new float[m_enemyCount];
    m_yPos       = new float[m_enemyCount];
    m_lua        = new lua_State*[m_enemyCount];

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
        if(!lua_isfunction(m_lua[i], -1)){
            lua_pop(m_lua[i], 1);
            hjs::logToConsole("init is not a function. This is really bad.");
            exit(0);
        }
        if(lua_pcall(m_lua[i], 0, 1, 0) != 0){
            hjs::logTimeToConsole();
            fprintf(stderr, "Err: Returning 'init': %s\n", lua_tostring(m_lua[i], -1));
            exit(0);
        }
        // Set default Values
        lua_getglobal(m_lua[i], "xPos");
        m_xPos[i] = lua_tonumber(m_lua[i], -1);
        lua_getglobal(m_lua[i], "yPos");
        m_yPos[i] = lua_tonumber(m_lua[i], -1);
        // Init the shape
        m_shape[i].setSize(sf::Vector2f(rand() % 40 + 20, 20));
        m_shape[i].setFillColor(sf::Color::Green);
        m_shape[i].setPosition(m_xPos[i], m_yPos[i]);
        hjs::logToConsole("Enemy Created");
    }
}

Enemy::~Enemy() {
    //dtor
    delete[] m_width;
    delete[] m_height;
    delete[] m_xPos;
    delete[] m_yPos;
    delete[] m_lasers;
    for(uint64_t i = 0; i < m_enemyCount; i++) {
        lua_close(m_lua[i]);
    }
}

void Enemy::Move(){
    for(uint64_t i = 0; i < m_enemyCount; i++){
        lua_getglobal(m_lua[i], "moveEnemy");
        if(lua_pcall(m_lua[i], 0, 1, 0) != 0){
            //!\todo Handle Error
        }
        lua_getglobal(m_lua[i], "xPos");
        m_xPos[i] = lua_tonumber(m_lua[i], -1);
        lua_getglobal(m_lua[i], "yPos");
        m_yPos[i] = lua_tonumber(m_lua[i], -1);
        m_shape[i].setPosition(m_xPos[i], m_yPos[i]);
    }
}

// Drawing Function for the enemy itself
void Enemy::draw(sf::RenderTarget &target, sf::RenderStates states)const {
    for(uint64_t i = 0; i < m_enemyCount; i++){
        target.draw(m_shape[i]);
    }
}

// Implementation of Enemy::EnemyLaser Below
Enemy::EnemyLaser::EnemyLaser()
:m_xPos(0), m_yPos(0), m_xSpeed(0), m_ySpeed(0), m_active(false){
    m_shape.setRadius(2.5);
    m_shape.setFillColor(sf::Color::Blue);
}

Enemy::EnemyLaser::~EnemyLaser() {

}

void Enemy::EnemyLaser::Move(){

}

void Enemy::EnemyLaser::init(float x, float y, float dx, float dy){

}

bool Enemy::EnemyLaser::getActive(){return m_active;}

// Drawing Function for the enemy laser
void Enemy::EnemyLaser::draw(sf::RenderTarget &target, sf::RenderStates states)const {
    target.draw(m_shape);
}
