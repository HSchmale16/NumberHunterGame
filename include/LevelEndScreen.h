/** LevelEndScreen Class Declaration
*	Screen shown at end of level
*	@author Henry Schmale
*	@date November 18, 2014
*/

#ifndef LEVELENDSCREEN_H
#define LEVELENDSCREEN_H

#include <SFML/Graphics.hpp>    // for drawing this to screen
#include "MenuButton.h"
#include "../LevelDatTypes.h"

enum LvlEndScreenSelection
{
    NO_SELECTION,
    NEXT_LEVEL,
    START_FROM_BEGINING,
    QUIT
};

class LevelEndScreen: public sf::Drawable
{
public:
    LevelEndScreen();
    virtual ~LevelEndScreen();

    LvlEndScreenSelection menuIdle();

    // setters
    void updateLevelData(const LevelStats* stats,
                         const LevelSettings *settings,
                         int currentLvl);

    void updateHighScoreTable(std::vector<std::string> vecStrHS);

    void setVisible(bool b);
protected:
private:
    // private functions
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states)const;
    void updateStrings();

    // private vars
    bool m_visible;
    bool m_lvlPassed;
    int m_lvlNum;
    LevelStats* m_lvlStats;
    sf::Font m_font;

    // drawables
    MenuButton *m_mbNextLevel;
    MenuButton *m_mbQuitGame;
    MenuButton *m_mbStartOver;

    // stat texts
    sf::Text m_tMenuHeading;

    // high score table texts
    sf::Text m_tNames;
    sf::Text m_tScores;
    sf::Text m_tScoreTbHeading;
};

#endif // LEVELENDSCREEN_H
