/**\file   Enemy.h
 * \author Henry J Schmale
 * \date   May 29, 2015
 * \brief  The Enemy Class Declaration File
 */
#ifndef ENEMY_H
#define ENEMY_H

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <vector>
#include "Player.h"
#include "Laser.h"

/**\brief A class defining the Enemy's Lasers. They are how the enemies attack the
 * player, and the enemies only way can do so, other than ramming the player.
 */
class EnemyLaser: public sf::Drawable {
public:
    EnemyLaser();
    EnemyLaser(float x, float y, float dx, float dy);
    ~EnemyLaser();

    void Move();
    bool getActive();
    /**\brief Handles hit tests against a Player object and this object
     * \return true if it was hit, otherwise false
     * \param p Player object to hit test against
     * \note This function will cause the active state of this object to be set to false
     * on returning true.
     */
    bool hitTestPlayer(Player& p);
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states)const;

    sf::CircleShape m_shape;
    float           m_xPos;
    float           m_yPos;
    float           m_xSpeed;
    float           m_ySpeed;
    bool            m_active;
};

/**\brief The Enemy(Space Pirates) manager class
 *
 * This class manages the enemies displayed on screen. It also manages their lasers
 * and attacks.
 */
class Enemy: public sf::Drawable {
public:
    Enemy();
    virtual ~Enemy();

    void        ReInit(uint64_t index);
    uint64_t    getLaserCount();
    uint64_t    getEnemyCount();
    EnemyLaser* getLaser(uint64_t i);

    bool     hitTestPlayer(uint64_t index, Player& p);
    bool     hitTestLaser(uint64_t index, Laser& l);
    /**\brief Moves all objects that are managed by this class on screen.
     */
    void     Move();
protected:
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states)const;
    /**\brief Makes a laser at the center of the enemy
     * \param index The enemy index to create laser at
     */
    void initLaser(uint64_t index);

    /* Data Members */
    uint64_t                    m_enemyCount;
    uint64_t                    m_laserCount;
    float*                      m_width;
    float*                      m_height;
    float*                      m_xPos;
    float*                      m_yPos;
    bool*                       m_active;
    sf::RectangleShape*         m_shape;
    sf::Texture*                m_texture;
    lua_State**                 m_lua;
    std::vector<EnemyLaser*>    m_lasers;
};

#endif // ENEMY_H
