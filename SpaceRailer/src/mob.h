#include <string>
#include "graphics.h"
#include "path_tools.h"
#include <list>

using namespace std;

class Mob
{
	public:
		unsigned int getHitPoints() { return _hitPoints; }
		void setHitPoints(unsigned int value) { _hitPoints = value; }
		
		unsigned int getMagicPoints() { return _magicPoints; }
		void setMagicPoints(unsigned int value) { _magicPoints = value; }
		
		int X() { return _coordX; }
		int Y() { return _coordY; }

		int Width() { return _width; }
		int Height() { return _height; }

		void setWidth(int value) { _width = value; }
		void setHeight(int value) { _height = value; }
		
		list<SDL_Texture *> sprites;

		bool isFriendly;
		string mobName;

		bool process();

		bool render();
		bool initialize(string mobName);
		bool initialize();

		bool loadSprites();
	
	private:
		unsigned int _hitPoints = 100;
		unsigned int _magicPoints = 0;
		int _coordX = 0;
		int _coordY = 0;
		int _width = 0;
		int _height = 0;
		short _accelerationX = 0;
		short _accelerationY = 0;
		short _accelerationMaxX = 40;
		short _accelerationMaxY = 40;

};
