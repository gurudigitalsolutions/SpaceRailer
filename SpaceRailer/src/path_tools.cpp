#include <string>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
	#include <direct.h>
	#define getcwd _getcwd
#elif
	#include <inistd.h>
#endif

#include "path_tools.h"


using namespace std;

string Path_Tools::_gameDataPath  = "";

// gets the game data path, sets value if empty
string Path_Tools::getGameDataPath() {
	if (_gameDataPath=="")
	{
		_gameDataPath = pathsExist(_getSystemDataPaths());
	}
	return _gameDataPath;
}



// Gets the array of paths to check for game's data
// Returns OS specific array of paths to check
string* Path_Tools::_getSystemDataPaths() {
	#ifdef _WIN32
		string appdata = (string)getenv("APPDATA") + "/SpaceRailer/";
		string progdata = (string)getenv("PROGRAMDATA") + "/SpaceRailer/";
		// TODO: this will need to be tweaked to the actual installation path
		char install[256];
		getcwd(install, 256);
		//cout << appdata << "\n" << (string)install << "\n" << progdata << "\n";
		return new string[3]{ appdata,install,progdata };
	#elif

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
		cout << "Stage directory not found.\n";
		return false;    // this is not a directory!

	// Unix systems
	#elif
		DIR* dp = opendir(stageDir.c_str());
		if (dp == NULL)
		{
			cout << "Stage directory not found.\n";
			return false;
		}
		closedir(dp);
	#endif
}


// Checks array of directories returning first valid path
// paths_to_check should be in order of preference
string Path_Tools::pathsExist(string paths_to_check[]) {

	for (int i = 0; i < 3; i++)
	{
		cout << "Checking path: " << paths_to_check[i] << "\n";
		if (pathExists(paths_to_check[i])) {
			return paths_to_check[i];
		}
	}
	return "";
}