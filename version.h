#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.03";
	
	//Software Status
	static const char STATUS[] =  "";
	static const char STATUS_SHORT[] =  "";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 1;
	static const long BUILD  = 1110;
	static const long REVISION  = 4752;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 2314;
	#define RC_FILEVERSION 0,1,1110,4752
	#define RC_FILEVERSION_STRING "0, 1, 1110, 4752\0"
	static const char FULLVERSION_STRING [] = "0.1.1110.4752";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 110;
	

}
#endif //VERSION_H
