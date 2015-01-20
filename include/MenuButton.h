/** MenuButton Class Declaration
*   Controls the menu and has a function that will return true if that instance was clicked
*	@author Henry Schmale
*	@date October 10, 2014
*/

#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <string>
#include <SFML/Graphics.hpp>

class MenuButton: public sf::Drawable
{
public:
	MenuButton();

	// texture fill
	MenuButton(int x, int y, int width, int height, std::string text,
			   const sf::Texture *tex, sf::Color textC, const sf::Font &font);

	// color fill
	MenuButton(int x, int y, int width, int height, std::string text,
			   sf::Color fillC, sf::Color textC, const sf::Font &font);

	virtual ~MenuButton();

	// ---->  PUBLIC MEMBER FUNCTIONS  <----
	// create the button after creating an instance of this object
	void create(int x, int y, int width, int height, std::string text);

	// set the graphics of this object
	// must be called right after creation of this object+
	void setGraphics(sf::Color bgFill, sf::Color borderColor, sf::Color texColor);

	// checks if this button was pressed
	bool checkIfPressed();

	// checks if the mouse is hovering over this button and if so an outline is set around the button
	bool mouseHoverCheck(int mX, int mY);

	// update what the button says
	void setText(std::string str);
protected:
private:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;

	// graphics
	sf::RectangleShape m_RsBG;	// Button background
	sf::Text m_text;			// text field
	int m_xPos;
	int m_yPos;
	int m_width;
	int m_height;
};

#endif // MENUBUTTON_H
