#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "08";
	static const char MONTH[] = "06";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.06";
	
	//Software Status
	static const char STATUS[] =  "";
	static const char STATUS_SHORT[] =  "";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 1;
	static const long BUILD  = 1525;
	static const long REVISION  = 5641;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 3230;
	#define RC_FILEVERSION 0,1,1525,5641
	#define RC_FILEVERSION_STRING "0, 1, 1525, 5641\0"
	static const char FULLVERSION_STRING [] = "0.1.1525.5641";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 525;
	

}
#endif //VERSION_H
