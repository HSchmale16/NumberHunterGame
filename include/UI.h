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
/**\todo Implement game over on run out of health
 * \note This class only handles the lower User Interface of the game.
 *
 */
class UI: public sf::Drawable
{
public:
    UI();
    virtual ~UI();

    /**\brief Reset this object back to default values
     */
    void Reset();

    /**\brief Selects a new **random** condition for good salvage
     */
    void setNewCondition();

    /**\brief Sets a random condition based on the SalvConditon passed
     * \param condition The Salvage Condition
     */
    void setCondition(SalvCondition condition);

    /**\brief Adds/Subtracts Points from the current score
     * \param points How many points to give or take.
     */
    void addPoints(int points);

    /**\brief Updates the points of player's health
     * \param n The delta in health between then and now
     */
    void updateHealth(int n);
    void resetHealth();								/// reset the health of the player

    /**\brief Checks if the value of a salvage object meets the condition
     * \param val the value of checked salvage object
     */
    bool isSalvValGood(int val);
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

    // Texture Objects
    sf::Texture m_texBG; 				//!< The background Texture
    sf::Texture m_texHealBar1;	//!< The texture of the health bar

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
