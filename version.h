#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "02";
	static const char MONTH[] = "04";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.04";
	
	//Software Status
	static const char STATUS[] =  "";
	static const char STATUS_SHORT[] =  "";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 1;
	static const long BUILD  = 1281;
	static const long REVISION  = 3455;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 2620;
	#define RC_FILEVERSION 0,1,1281,3455
	#define RC_FILEVERSION_STRING "0, 1, 1281, 3455\0"
	static const char FULLVERSION_STRING [] = "0.1.1281.3455";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 281;
	

}
#endif //VERSION_H
