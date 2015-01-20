/** Config File for game contains a reader object and variables define the certain values
*	@author Henry Schmale
*	@date October 10, 2014
*/

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include "INIReader.h"		// For Parsing Config Files
#include "FilePaths.h"		// Tell where the config file is located

INIReader config(CONFIG_FILE);

#endif // CONFIG_H_INCLUDED
