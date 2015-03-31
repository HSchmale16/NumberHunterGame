#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "31";
	static const char MONTH[] = "03";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.03";
	
	//Software Status
	static const char STATUS[] =  "";
	static const char STATUS_SHORT[] =  "";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 1;
	static const long BUILD  = 1269;
	static const long REVISION  = 2850;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 2604;
	#define RC_FILEVERSION 0,1,1269,2850
	#define RC_FILEVERSION_STRING "0, 1, 1269, 2850\0"
	static const char FULLVERSION_STRING [] = "0.1.1269.2850";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 269;
	

}
#endif //VERSION_H
