#pragma once
#include <string>
#include <iostream>

#ifdef _WIN32
	#include <Windows.h>
	#include <direct.h>
	#define getcwd _getcwd
#else
	#include <unistd.h>
#endif

using namespace std;

class Path_Tools
{
private:
	static string _gameDataPath;
	static void _getSystemDataPaths(string * dp1, string * dp2, string * dp3);
	
public:
	static bool pathExists(const string& dirName_in);
	static string pathsExist(string paths_to_check[]);
	static string getGameDataPath();
	static string getStageDataPath();
	static string getStageDataPath(string stagename);
	static string getMobsDataPath();
};
