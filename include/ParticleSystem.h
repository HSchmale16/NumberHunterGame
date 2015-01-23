#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

/** A Simple Particle System
 * @author Henry J Schmale
 * @date January 22, 2015
 */

#include <SFML/Graphics.hpp>


class ParticleSystem: sf::Drawable
{
	public:
		ParticleSystem();
		virtual ~ParticleSystem();

		void update();
	protected:
	private:
};

#endif // PARTICLESYSTEM_H
