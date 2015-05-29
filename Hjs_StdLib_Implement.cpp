/** @brief  Implementation of my StdLib
 *  @author Henry J Schmale
 *  @date   Sept 25, 2014
 *  @file   Hjs_StdLib_Implement.cpp
 *
 *  This has no class implementation just the implementation of functions
 *  defined in `Hjs_StdLib.h`. These are mostly general functions for
 *  checking various things, and logging. The logging functionallity is
 *  removed if `DEBUG_BUILD` is not defined, as it speeds up execution of
 *  the program, because `cout`/`cerr` is extremely slow on MS Windows.
 */

#include "Hjs_StdLib.h"
#include <cmath>
#include <cstdio>

/// Variables that are for internal use by Hjs_StdLib
time_t startTime;                 // time in program execution lib was init'd
bool   bLibIsInit = false;        // Is the lib init'd
bool   bMainThreadActive = true;  // Is the main thread still active

/// Initiates my library
void hjs::init_Hjs_StdLib()
{
    // check if lib is not init'd, because this should only be called once
    if(!bLibIsInit)
    {
        bLibIsInit = true;
        startTime = clock();
#ifdef DEBUG_BUILD
        hjs::logToConsole("HjsStdLib Initiated");
#endif // DEBUG_BUILD
    }
}

void hjs::logTimeToConsole()
{
    // time output
#ifdef DEBUG_BUILD
    time_t t = clock();     // Get the Time
    float elaps = (float(t) - startTime) / CLOCKS_PER_SEC;
    std::cerr << "[" << elaps << "] \t";
#endif // DEBUG_BUILD
}

/// Logs a message to stdOutput with the time since execution begin
void hjs::logToConsole(const char * ch)
{
#ifdef DEBUG_BUILD
    // output time
    logTimeToConsole();
    fprintf(stderr, "%s\n", ch);
#endif // DEBUG_BUILD
}

/// Allows the any thread to end the whole program by calling this function
void hjs::endGame()
{
    hjs::logToConsole("GAME OVER!");
    bMainThreadActive = false;
}

/// All subthreads should be in while loop testing for this to turn false
bool hjs::gameIsActive()
{
    return bMainThreadActive;
}
