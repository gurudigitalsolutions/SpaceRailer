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


#include "stage_map_layer.h"

//	Initialize this map layer.  Width and Height are the number of tiles that
//	make up this layer.  mapData is an unsigned char array filled with the
//	raw data from the map file.
bool StageMapLayer::initialize(unsigned short width, unsigned short height, unsigned char * mapData)
{
	//	We need to make sure that the width and height make some sort of sense
	if(width < 60
	|| height < 32)
	{
		cout << "Initialization of map failed.  Width and/or height are too small\n";
		return false;
	}
	
	_width = width;
	_height = height;
	
	//	Create a buffer to hold map data.  Each tile is represented by 4 bytes.
	//	This is:
	//
	//		0,1:	Tile/Sprite ID, little endian
	//		2,3:	Attributes, these are not currently defined
	
	unsigned char * buffer = new unsigned char[4];
	
	//	Allocate memory for the map
	_map = (StageMapTile **)malloc(sizeof(StageMapTile *) * getWidth() * getHeight());
	
	for(unsigned short ey = 0; ey < getWidth(); ey++)
	{
		for(unsigned short ex = 0; ex < getHeight(); ex++)
		{
			buffer = &mapData[(ey * (getWidth() * 4)) + ex];
			
			unsigned short spriteID = buffer[0] + (buffer[1] * 256);
			
			//	We need to read the attributes here, however since they are not
			//	currently defined, there isn't really anything to do with
			//	them.
			
			StageMapTile * tTile = new StageMapTile();
			tTile->_initialize(spriteID);
			
			_setTile(ex, ey, tTile);
		}
	}
	
	
	return true;
}

void StageMapLayer::_setTile(unsigned short x, unsigned short y, StageMapTile * smt)
{
	_map[(y * getWidth()) + x] = smt;
}

StageMapTile * StageMapLayer::getTile(unsigned short x, unsigned short y)
{
	return _map[(y * getWidth()) + x];
}
