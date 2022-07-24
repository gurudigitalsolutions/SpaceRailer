#include <string>
#include <filesystem>
#include "stage_map_tile.h"


using namespace std;

class StageMapLayer
{
	public:
		StageMapTile * getTile(unsigned short x, unsigned short y);
	
		unsigned short getWidth() { return _width; }
		unsigned short getHeight() { return _height; }
		
		unsigned short getCurrentViewX() { return _currentViewX; }
		void setCurrentViewX(unsigned short value) { _currentViewX = value; }
		
		unsigned short getCurrentViewY() { return _currentViewY; }
		void setCurrentViewY(unsigned short value) { _currentViewY = value; }
		
		unsigned short getCurrentViewXOffset() { return _currentViewXOffset; }
		void setCurrentViewXOffset(unsigned short value) { _currentViewXOffset = value; }
		
		unsigned short getCurrentViewYOffset() { return _currentViewYOffset; }
		void setCurrentViewYOffset(unsigned short value) { _currentViewYOffset = value; }
		
		
		bool initialize(unsigned short width, unsigned short height, unsigned char * mapData);
	
	private:
		void _setTile(unsigned short x, unsigned short y, StageMapTile * smt);
	
		unsigned short _width = 1024;
		unsigned short _height = 1024;
		
		unsigned short _currentViewX = 32;
		unsigned short _currentViewY = 32;
		unsigned short _currentViewXOffset = 0;
		unsigned short _currentViewYOffset = 0;
		
		StageMapTile ** _map;
};
