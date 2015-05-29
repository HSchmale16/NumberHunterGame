/**\file   Enemy.h
 * \author Henry J Schmale
 * \date   May 29, 2015
 * \brief  The Enemy Class Declaration File
 */
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy: public sf::Drawable {
public:
    Enemy(std::string actionFile);
    virtual ~Enemy();
protected:
private:
    void draw(sf::RenderTarget &target, sf::RenderStates states)const;

};

#endif // ENEMY_H
