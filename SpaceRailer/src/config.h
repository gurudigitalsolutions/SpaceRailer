#include <string>
#include <filesystem>
#include <iostream>

#ifdef _WIN32
	#include <Windows.h>
	#define getcwd _getcwd
#elif
	#include <inistd.h>
#endif


using namespace std;

class Config
{
	private:
	
	public:
		string getConfigDir();
		string getStageDir();
};
