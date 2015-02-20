/** FilePaths.h
*   Contains #define'd relative file path strings to load resources for game
*	@note if you're using GCC use (/) to indicate path
*   @author Henry Schmale
*   @date 9/26/2014
*/

#ifndef FILEPATHS_H_INCLUDED
#define FILEPATHS_H_INCLUDED

/** Tell where the config files are located */
#define CONFIG_FILE "resources/TSA_GAME.ini"			// the main config for game options
#define MENU_CONFIG_FILE "resources/MenuConfig.INI"		// config file strictly for the menu
#define LEVEL_CONFIG_FILE "resources/LevelConfig.INI"	// config file for strictly levels

/** Tell where the window icon is located */
#define ICON "resources/img/Icon.png"

/** Define Textures used in game and their relative path from the working directory
 */
// BG Plasma Texture
#define BG_PLASMA_TEX "resources/img/BG_PlasmaClouds.PNG"

// Pause Screen Graphic
#define PAUSE_SCREEN_IMAGE "resources/img/PauseScreen.PNG"

// Salvage Textures
#define SALVAGE_TEX_1 "resources/img/SalvTex1.png"
#define SALVAGE_TEX_2
#define SALVAGE_TEX_3

/// Path to Asteroid Textures
#define ASTEROID_TEX "resources/img/Asteroid.png"

/** Define the path to fonts used in game
*/
// Main Font Used In Game
#define MAIN_FONT "resources/fonts/Xolonium-Regular.otf"			// Main Font used in game - under GPLv2

/** Define the path to other resources used in game
*/

// Laser Sound
#define LASER_SOUND "resources/sounds/Laser.wav"

// Game Music
#define GM_MUSIC "resources/sounds/Space_Fighter_Loop.ogg"
#define MENU_MUSIC "resources/sounds/Ready_Aim_Fire.ogg"

#endif // FILEPATHS_H_INCLUDED
