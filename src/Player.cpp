#include "Player.h"
#include "../INIReader.h"
#include "../FilePaths.h"

INIReader pr(CONFIG_FILE);

Player::Player()
{
	//ctor
	// load texture
	if(!m_texture.loadFromFile(pr.Get("player", "t", "resources/img/player.png")))
		exit(2);

	// init member vars
	m_fXSpeed = 2;
	m_fXCoord = pr.GetInteger("player", "start_x", 200);
	m_fYSpeed = 1;
	m_fYCoord = pr.GetInteger("player", "start_y", 400);
	m_fSideLength = 60;

	// init RectangleShape
	s.setSize(sf::Vector2f(m_fSideLength, m_fSideLength));
	s.setPosition(20, 20);
	s.setTexture(&m_texture);

	// init particle system
  m_ps = new ParticleSystem(100);
}

Player::~Player()
{
	//dtor
	delete m_ps;
}

void Player::Move()
{
	// check movement keys
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (m_fXCoord > -(m_fSideLength / 2)))
	{
		m_fXCoord -= m_fXSpeed;
	}
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (m_fXCoord < 355))
	{
		m_fXCoord += m_fXSpeed;
	}
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) && (m_fYCoord > 0))
	{
		m_fYCoord -= m_fYSpeed;
	}
	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (m_fYCoord < 630))
	{
		m_fYCoord += m_fYSpeed;
	}
	s.setPosition(m_fXCoord, m_fYCoord);	// update position
	m_ps->setEmitter(sf::Vector2f(m_fXCoord + (m_fSideLength / 2), m_fYCoord + m_fSideLength));
	m_ps->update(m_clock.restart());
}

void Player::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(s, states);
	target.draw(*m_ps, states);
}


/// GETTERS
float Player::getSideLength()
{
	return m_fSideLength;
}
float Player::getXCoord()
{
	return m_fXCoord;
}
float Player::getYCoord()
{
	return m_fYCoord;
}
