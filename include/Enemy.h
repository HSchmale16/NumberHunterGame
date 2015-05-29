/**\file   Enemy.h
 * \author Henry J Schmale
 * \date   May 29, 2015
 * \brief  The Enemy Class Declaration File
 */
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <cstdint>
#include "Player.h"
#include "Laser.h"

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

/**\brief The Enemy(Space Pirates) manager class
 *
 * This class manages the enemies displayed on screen. It also manages their lasers
 * and attacks.
 */
class Enemy: public sf::Drawable {
public:
    Enemy();
    virtual ~Enemy();

    uint16_t getLaserCount();
    uint16_t getEnemyCount();
    bool     hitTestPlayer(Player *p);
protected:
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states)const;

    /* Data Members */
    uint64_t            m_enemyCount;
    uint64_t            m_laserCount;
    float*              m_width;
    float*              m_height;
    float*              m_xPos;
    float*              m_yPos;
    sf::RectangleShape* m_rect;
    lua_State**         m_lua;

    class EnemyLaser: public sf::Drawable {
    public:
        EnemyLaser();
        ~EnemyLaser();
        void move();
        void init(float x, float y);
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states)const;
        sf::RectangleShape m_shape;
        float              m_xPos;
        float              m_yPos;
        float              m_ySpeed;
        bool               m_active;
    }* m_lasers;
};

#endif // ENEMY_H
