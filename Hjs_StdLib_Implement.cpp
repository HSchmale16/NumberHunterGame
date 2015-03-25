/** Implementation of my StdLib
*   This has no class implementation just function implementation
*   @author Henry Schmale
*   @date Sept 25, 2014
*/

#include "Hjs_StdLib.h"
#include <math.h>

/// Variables that are for internal use by Hjs_StdLib
bool bLibIsInit = false;        // Is the lib init'd
time_t startTime;               // time in program execution lib was init'd
bool bMainThreadActive = true;  // Is the main thread still active

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
    std::cout << ch << std::endl;
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
