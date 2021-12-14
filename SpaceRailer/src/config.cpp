#include <string>
#include <filesystem>

#ifdef _WIN32
	#include <direct.h>
	#define getcwd _getcwd
#elif
	#include <inistd.h>
#endif

#include "config.h"


using namespace std;


string Config::getConfigDir()
{
	return "";
}


//	This will need to be updated to look into the install location.  For now,
//	this just uses the current working directory.
string Config::getStageDir()
{
	char stagedir[256];
	getcwd(stagedir, 256);
	
	return (string)stagedir + "/data/stages/";
	
}
