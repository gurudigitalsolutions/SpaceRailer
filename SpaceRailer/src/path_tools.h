#include <string>
#include <iostream>

#ifdef _WIN32
#include <Windows.h>
#include <direct.h>
#define getcwd _getcwd
#elif
#include <inistd.h>
#endif

using namespace std;

class Path_Tools
{
private:
	static string _gameDataPath;
	static string * _getSystemDataPaths();
public:
	static bool pathExists(const string& dirName_in);
	static string pathsExist(string paths_to_check[]);
	static string getGameDataPath();
};
