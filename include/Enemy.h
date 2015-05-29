/**\file   Enemy.h
 * \author Henry J Schmale
 * \date   May 29, 2015
 * \brief  The Enemy Class Declaration File
 */
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <cstdint>

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
protected:
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states)const;

    /* Data Members */
    uint16_t            m_count;
    float*              m_width;
    float*              m_height;
    float*              m_xPos;
    float*              m_yPos;
    sf::RectangleShape* m_rect;

    class EnemyLaser: public sf::Drawable {
    public:
        EnemyLaser();
        ~EnemyLaser();
    private:
        void draw(sf::RenderTarget &target, sf::RenderStates states)const;
        float m_xPos;
        float m_yPos;
    }* m_lasers;
};

#endif // ENEMY_H
