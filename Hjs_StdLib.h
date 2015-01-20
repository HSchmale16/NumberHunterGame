#ifndef HJS_STDLIB_H_INCLUDED
#define HJS_STDLIB_H_INCLUDED

#include <iostream>     // For Logging to the console
#include <time.h>       // Also for logging

// Includes for game
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

// General Game Constants
#define GAME_WIDTH 400
#define GAME_HEIGHT 600

// My personal funcs
namespace hjs
{
/// Inits my library
void init_Hjs_StdLib();

/// Logs the time since execution begin to stdOut in brackets with a
/// tab following
void logTimeToConsole();

/// Logs @param ch to stdout with the time since execution start
void logToConsole(const char * ch);

/// Dirty Disqusting HACK!!! to control event threads
/// Returns if main thread is still running
bool gameIsActive();

/// called by any thread in the event of an unrecoverable error to shutdown all class event threads
/// dependent on gameIsActive()
void endGame();
}

#endif // HJS_STDLIB_H_INCLUDED
