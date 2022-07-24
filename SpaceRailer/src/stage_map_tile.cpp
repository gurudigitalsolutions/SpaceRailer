#include <string>
#include <filesystem>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>
#include <fstream>
#include <string>
#include <math.h>

#ifdef _WIN32
	#include <Windows.h>
#define sleep Sleep
#else
	#include <unistd.h>
	#include <dirent.h>
#endif

#include "stage_map_tile.h"


bool StageMapTile::getIsSolid()
{
	if(_spriteID == 0) { return false; }
	return _isSolid;
}

void StageMapTile::_initialize(unsigned short spriteID)
{
	_spriteID = spriteID;
}
