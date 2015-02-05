#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <cmath>

class ParticleSystem : public sf::Drawable, public sf::Transformable
{
public:

	ParticleSystem(unsigned int count) :
		m_particles(count),
		m_lifetime(sf::seconds(3)),
		m_emitter(0, 0)
	{
	}

	void setEmitter(sf::Vector2f position)
	{
		m_emitter = position;
	}

	void update(sf::Time elapsed)
	{
		for (std::size_t i = 0; i < m_particles.size(); ++i)
		{
			// update the particle lifetime
			Particle& p = m_particles[i];
			p.lifetime -= elapsed;

			// if the particle is dead, respawn it
			if (p.lifetime <= sf::Time::Zero)
				resetParticle(i);

			// update the position of the corresponding vertex
			m_particles[i].m_s.move(p.velocity * elapsed.asSeconds());

			// update the alpha (transparency) of the particle according to its lifetime
			float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();
      m_particles[i].m_color.a = static_cast<sf::Uint8>(ratio * 255);
      m_particles[i].m_s.setFillColor(m_particles[i].m_color);
		}
	}

private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for(unsigned int i = 0; i < m_particles.size(); i++)
		{
			target.draw(m_particles[i].m_s, states);
		}
	}

	struct Particle
	{
		sf::Vector2f velocity;
		sf::Time lifetime;
		sf::RectangleShape m_s;
		sf::Color m_color;
	};

	void resetParticle(std::size_t index)
	{
		// give a random velocity and lifetime to the particle
		float angle = (rand() % 120 + 30) * 3.14f / 180.f;
		float speed = (rand() % 50) + 50.f;
		m_particles[index].velocity = sf::Vector2f(cos(angle) * speed, sin(angle) * speed);
		m_particles[index].lifetime = sf::milliseconds((rand() % 1200) + 700);

		m_particles[index].m_s.setSize(sf::Vector2f(rand() % 7 + 2, rand() % 7 + 5));
		m_particles[index].m_s.setPosition(m_emitter);
		m_particles[index].m_color = sf::Color(rand() % 255,
									 rand() % 64,
									 rand() % 64);
		m_particles[index].m_s.setFillColor(m_particles[index].m_color);
	}

	std::vector<Particle> m_particles;
	sf::Time m_lifetime;
	sf::Vector2f m_emitter;
};

#endif // PARTICLESYSTEM_H
