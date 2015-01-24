#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "23";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.01";
	
	//Software Status
	static const char STATUS[] =  "";
	static const char STATUS_SHORT[] =  "";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 0;
	static const long BUILD  = 999;
	static const long REVISION  = 9298;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 2067;
	#define RC_FILEVERSION 0,0,999,9298
	#define RC_FILEVERSION_STRING "0, 0, 999, 9298\0"
	static const char FULLVERSION_STRING [] = "0.0.999.9298";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 999;
	

}
#endif //VERSION_H
