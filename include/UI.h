/** UI Class - handles the health bar and score as well as target salvage type
*	@author Henry Schmale
*	@date October 5, 2014
*/

#ifndef UI_H
#define UI_H

#include "../Hjs_StdLib.h"

// create an enum of possible conditions for salvage target
#define NUM_TYPES_SALVCONDITION 3		// total number of possible types in enum SalvCondition
enum SalvCondition
{
	ODD_NUM,
	EVEN_NUM,
	PRIME_NUM
};

// class declaration
class UI: public sf::Drawable
{
public:
	UI();
	virtual ~UI();

	void Reset();									/// Reset this object to defaults
	void setNewCondition();							/// Selects a new condition randomly
	void setCondition(SalvCondition condition); 	/// selects a certain type for target salvage
	void addPoints(int points);						/// adds @param points to m_nScore and updates ScoreText
	void updateHealth(int n);						/// updates the health of the player
	void resetHealth();								/// reset the health of the player

	bool isSalvValGood(int val);					/// checks if @param val meets current required condition
	int getScore();									/// gets the current score
protected:
private:
	// Private Updater
	void updateTarget();			// updates on screen prompts based on m_eTarget

	// rendering
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
	sf::RectangleShape m_BG;		// contains the background
	sf::RectangleShape m_HealthBox;	// Health box - tells how much fuel remains
	sf::RectangleShape m_HealthBar;	// bar that scales within the m_FuelBox

	// Text Outputs
	sf::Font font;
	sf::Text m_TargetText;		// What condition should the label on the salvage meet
	sf::Text m_ScoreText;		// How high your score is now

	// Variables
	int m_nScore;				// Score
	SalvCondition m_eTarget;	// Target Condition for player collected salvage

	int m_CurrentHealth;
	int m_MaxHealth;
};

#endif // UI_H
