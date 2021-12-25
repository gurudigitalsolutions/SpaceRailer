#include <string>
#include <iostream>

#ifdef _WIN32
	#include <Windows.h>
	#include <direct.h>
	#define getcwd _getcwd
#else
	#include <unistd.h>
	#include <dirent.h>
#endif

#include "path_tools.h"


using namespace std;

string Path_Tools::_gameDataPath;

// gets the game data path, sets value if empty
string Path_Tools::getGameDataPath() {
	if (_gameDataPath.empty())
	{
		string systemdatapaths[3]; 
		_getSystemDataPaths(&systemdatapaths[0], &systemdatapaths[1], &systemdatapaths[2]);
		_gameDataPath = pathsExist((string *)&systemdatapaths);
	}
	return _gameDataPath;
}

string Path_Tools::getStageDataPath(string stagename) {
	return Path_Tools::getStageDataPath() + "/" + stagename;
}

string Path_Tools::getStageDataPath() {
	return Path_Tools::getGameDataPath() + "resources/stages";
	
	
}

// Gets the array of paths to check for game's data
// Returns OS specific array of paths to check
void Path_Tools::_getSystemDataPaths(string* dp1, string* dp2, string* dp3) {
	#ifdef _WIN32
		*dp1 = (string)getenv("APPDATA") + "/SpaceRailer/";
		*dp2 = (string)getenv("PROGRAMDATA") + "/SpaceRailer/";
		//char install[256];
		//getcwd(install, 256);
		//*dp3 = (string) install + "/";
		*dp3 = (string)"";
		//cout << appdata << "\n" << (string)install << "\n" << progdata << "\n";
	#else
		*dp1 = (string)getenv("HOME") + "/.config/spacerailer/";
		*dp2 = "/usr/share/spacerailer/";
		*dp3 = (string)"";
	#endif
}


// Checks that a directory path is valid
bool Path_Tools::pathExists(const string& path_to_check)
{
	// Windows systems
	#ifdef _WIN32
		DWORD ftyp = GetFileAttributesA(path_to_check.c_str());
		if (ftyp == INVALID_FILE_ATTRIBUTES) {
			//cout << "Stage directory not found.\n";
			return false;  // something is wrong with your path!
		}
		if (ftyp & FILE_ATTRIBUTE_DIRECTORY) {
			return true;   // this is a directory!
		}
		//cout << "Stage directory not found.\n";
		return false;    // this is not a directory!

	// Unix systems
	#else
		DIR * dp = opendir(path_to_check.c_str());
		if (dp == NULL)
		{
			//cout << "Stage directory not found.\n";
			//cout << path_to_check << "\n";
			return false;
		}
		closedir(dp);
		
		return true;
	#endif
	
	//	Shouldn't reach here
	return false;
}


// Checks array of directories returning first valid path
// paths_to_check should be in order of preference
string Path_Tools::pathsExist(string * paths_to_check) {

	for (int i = 0; i < 3; i++)
	{
		//cout << "Checking path: " << paths_to_check[i] << "\n";
		if (pathExists(paths_to_check[i])) {
			return paths_to_check[i];
		}
	}
	return "";
}
