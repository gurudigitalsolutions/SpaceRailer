#pragma once
#include <string>
#include "graphics.h"
#include <list>

#include "mob_componet.h"
#include "path_tools.h"

using namespace std;

class Mob
{
	public:
		unsigned int getHitPoints() { return _hitPoints; }
		void setHitPoints(unsigned int value) { _hitPoints = value; }
		
		unsigned int getMagicPoints() { return _magicPoints; }
		void setMagicPoints(unsigned int value) { _magicPoints = value; }
		
		int getX() { return _coordX; }
		int getY() { return _coordY; }

		void setX(int value) { _coordX = value; }
		void setY(int value) { _coordY = value; }

		int getWidth() { return _width; }
		int getHeight() { return _height; }

		void setWidth(int value) { _width = value; }
		void setHeight(int value) { _height = value; }
		
		double getRenderAngle() { return _renderAngle; }
		void setRenderAngle(double value) { _renderAngle = value; }
		
		list<SDL_Texture *> sprites;

		bool isFriendly;
		string mobName;

		bool process();

		bool render();
		bool initialize(string mobName);
		bool initialize();

		bool loadSprites();
		bool loadSprite(string spriteName);
		
		bool getIsComponent() { return _isComponent; }
		void setIsComponent(bool value) { _isComponent = value; }
		
		Mob * getParent() { return _parent; }
		void setParent(Mob * value) { _parent = value; }
		
		bool addComponent(MobComponent * nComponent);
		bool addComponent(string component, int offsetX, int offsety, int width, int height);
		bool addComponent(string component, int offsetX, int offsety, int width, int height, componentAttachMode attachmode, unsigned char maxdistancex, unsigned char maxdistancey);
	
	private:
		unsigned int _hitPoints = 100;
		unsigned int _magicPoints = 0;
		int _coordX = 0;
		int _coordY = 0;
		
		int _width = 0;
		int _height = 0;
		double _renderAngle = 0.0;

		short _accelerationX = 0;
		short _accelerationY = 0;
		short _accelerationMaxX = 40;
		short _accelerationMaxY = 40;

		list<MobComponent *> _components;
		
		bool _isComponent = false;
		Mob * _parent;
};
