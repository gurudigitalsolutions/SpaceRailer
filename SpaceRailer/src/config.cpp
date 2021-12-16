#include <string>
#include <filesystem>
#include <iostream>

#ifdef _WIN32
	#include <Windows.h>
	#define getcwd _getcwd
#else
	#include <unistd.h>
#endif

#include "config.h"
#include "path_tools.h"


using namespace std;


string Config::getConfigDir()
{
	return Path_Tools::getGameDataPath() + "/config/";
}


//	This will need to be updated to look into the install location.  For now,
//	this just uses the current working directory.
string Config::getStageDir()
{
	return Path_Tools::getGameDataPath() + "/data/stages/";
}



