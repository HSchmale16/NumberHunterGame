#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "31";
	static const char MONTH[] = "05";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.05";
	
	//Software Status
	static const char STATUS[] =  "";
	static const char STATUS_SHORT[] =  "";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 1;
	static const long BUILD  = 1470;
	static const long REVISION  = 2792;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3114;
	#define RC_FILEVERSION 0,1,1470,2792
	#define RC_FILEVERSION_STRING "0, 1, 1470, 2792\0"
	static const char FULLVERSION_STRING [] = "0.1.1470.2792";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 470;
	

}
#endif //VERSION_H
