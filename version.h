#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "22";
	static const char MONTH[] = "01";
	static const char YEAR[] = "2015";
	static const char UBUNTU_VERSION_STYLE[] =  "15.01";
	
	//Software Status
	static const char STATUS[] =  "";
	static const char STATUS_SHORT[] =  "";
	
	//Standard Version Type
	static const long MAJOR  = 0;
	static const long MINOR  = 0;
	static const long BUILD  = 978;
	static const long REVISION  = 7906;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 2035;
	#define RC_FILEVERSION 0,0,978,7906
	#define RC_FILEVERSION_STRING "0, 0, 978, 7906\0"
	static const char FULLVERSION_STRING [] = "0.0.978.7906";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 978;
	

}
#endif //VERSION_H
