/** LevelDatTypes.h
* Contains the various datatypes used for handling levels
* @author Henry Schmale
* @date November 18, 2014
*/
#ifndef LEVELDATTYPES_H_INCLUDED
#define LEVELDATTYPES_H_INCLUDED

#include <stdint.h>

// Enumeration of possible level types
enum LevelType
{
	SURVIVAL,					// Survive for set amount of time
	SCORE_TARGET,				// Get a minimum number of points in a set time
	SALVAGE_COLLECTION_TARGET,	// Collect n salvage in x seconds that are correct
	CLEAR_ASTEROIDS				// Blow up asteroids
};

// struct of current level target variables
struct LevelSettings
{
	LevelType type;			// level type
	uint16_t timeLimit;		// seconds to complete goal
	uint16_t maxFails;		// how many times you can fail before game over
	uint16_t salvCollect;	// Salvage to be collected
	uint16_t asteClearGoal;	// asteroids that must be cleared when that game type is active to win level
	unsigned int minScore;
};

// struct for current holding current data on what player has right now
struct LevelStats
{
	int score;
	int salvageCollected;
	int asteroidsKilled;
};


#endif // LEVELDATTYPES_H_INCLUDED
