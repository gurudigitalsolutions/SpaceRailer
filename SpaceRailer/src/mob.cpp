#include <string>
#include <filesystem>

#ifdef _WIN32
	#include <direct.h>
	#define getcwd _getcwd
#else
	#include <unistd.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
	#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
#else
	#include <SDL2/SDL.h>
#endif
//#include <dirent.h>

#include "config.h"
#include "mob.h"

using namespace std;

//	Called each game tick to process mob stuff.  This includes physics and
//	scripting.
bool Mob::process()
{
	return true;
}

bool Mob::render() {
	return false;
}


bool Mob::initialize(string mobName) {
	this->mobName = mobName;
	return initialize();
}

