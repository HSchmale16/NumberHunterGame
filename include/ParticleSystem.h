#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

/** A Simple Particle System
 * @author Henry J Schmale
 * @date January 22, 2015
 */

#include <SFML/Graphics.hpp>
#include <vector>

class ParticleSystem: sf::Drawable
{
	public:
		ParticleSystem(int count);
		virtual ~ParticleSystem();

		void update();
		void setEmitter(float x, float y);
	protected:
	private:
		struct Particle{
      sf::Vector2f m_veloc;
      int m_currLife;
      int m_maxLife;
		};

		virtual void draw(sf::RenderTarget &target, sf::RenderStates states);
		void resetParticle(int index);

		int m_particlesCount;								//!< Number of Particles
		std::vector<Particle> m_particles;	//!< Particles
		sf::VertexArray m_vertexArray;			//!< Vertexes
		sf::Vector2f m_emiterLocal;					//!< Location of Emitter
};

#endif // PARTICLESYSTEM_H
