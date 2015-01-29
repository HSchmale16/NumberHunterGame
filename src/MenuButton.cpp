/** MenuButton Implementation
*	@author Henry Schmale
*	@date October 22, 2014
*/

#include "../include/MenuButton.h"

MenuButton::MenuButton()
{
	//ctor
}

// Texture Fill
MenuButton::MenuButton(int x, int y, int width, int height, std::string text, const sf::Texture *tex, sf::Color textC, const sf::Font &font)
{
	m_xPos = x;
	m_yPos = y;
	m_width = width;
	m_height = height;

	m_RsBG.setPosition(sf::Vector2f(x, y));
	m_RsBG.setSize(sf::Vector2f(width, height));
	m_RsBG.setOutlineThickness(2.0f);
	m_RsBG.setOutlineColor(sf::Color::Transparent);
	m_RsBG.setTexture(tex);

	m_text.setString(text);
	m_text.setColor(textC);
	m_text.setFont(font);
	m_text.setCharacterSize(15);


	sf::FloatRect rectBounds = m_RsBG.getGlobalBounds();
	sf::FloatRect textBounds = m_text.getGlobalBounds();

	m_text.setPosition(
		rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
		rectBounds.top + (rectBounds.height / 2) - (textBounds.height / 2)
	);
}

// Color Fill
MenuButton::MenuButton(int x, int y, int width, int height, std::string text, sf::Color fillC, sf::Color textC, const sf::Font &font)
{
	m_xPos = x;
	m_yPos = y;
	m_width = width;
	m_height = height;

	m_RsBG.setPosition(sf::Vector2f(x, y));
	m_RsBG.setSize(sf::Vector2f(width, height));
	m_RsBG.setOutlineThickness(2.0f);
	m_RsBG.setOutlineColor(sf::Color::Transparent);
	m_RsBG.setFillColor(fillC);

	m_text.setString(text);
	m_text.setColor(textC);
	m_text.setFont(font);
	m_text.setCharacterSize(15);


	sf::FloatRect rectBounds = m_RsBG.getGlobalBounds();
	sf::FloatRect textBounds = m_text.getGlobalBounds();

	m_text.setPosition(
		rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
		rectBounds.top + (rectBounds.height / 2) - (textBounds.height / 2)
	);
}

MenuButton::~MenuButton()
{
	//dtor
}

bool MenuButton::mouseHoverCheck(int mX, int mY)
{
	if(((( m_xPos + m_width >= mX) && (m_xPos <= mX))
			&&
			(( m_yPos + m_height >= mY) && (m_yPos <= mY))
	   ))// close hitTest if block
	{
        m_RsBG.setOutlineColor(sf::Color::Cyan);
        return true;
	}
	else{
		m_RsBG.setOutlineColor(sf::Color::Transparent);
		return false;
	}
}

void MenuButton::setText(std::string str)
{
	m_text.setString(str);
	//center the text
	sf::FloatRect rectBounds = m_RsBG.getGlobalBounds();
	sf::FloatRect textBounds = m_text.getGlobalBounds();
	m_text.setPosition(
		rectBounds.left + (rectBounds.width / 2) - (textBounds.width / 2),
		rectBounds.top + (rectBounds.height / 2) - (textBounds.height / 2)
	);
}

// Private Drawing
void MenuButton::draw(sf::RenderTarget &target, sf::RenderStates states)const
{
	target.draw(m_RsBG, states);
	target.draw(m_text, states);
}
