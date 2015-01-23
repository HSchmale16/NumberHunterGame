#include "ParticleSystem.h"
#include <cstdlib>
#include <math.h>

ParticleSystem::ParticleSystem(int count)
{
	//ctor
	m_particlesCount = count;
	for(int i = 0; i < count; i++)
	{
		m_particles.push_back(Particle());
		resetParticle(i);
	}
}

ParticleSystem::~ParticleSystem()
{
	//dtor
}

void ParticleSystem::setEmitter(float x, float y)
{
	m_emiterLocal = sf::Vector2f();
}

void ParticleSystem::update()
{

}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states)
{

}

void ParticleSystem::resetParticle(int index)
{
	float angle = ((rand() % 60) + 240) * (3.14159 / 180.0);
	float speed = (2 * double(rand() % 65536));
	m_particles[index].m_veloc =
		sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
  m_particles[index].m_currLife = 0;
  m_particles[index].m_maxLife = rand() % 75;
}

