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
		
		int getVelocityX() { return _velocityX; }
		int getVelocityY() { return _velocityY; }
		
		void setVelocityX(int value) { _velocityX = value; }
		void setVelocityY(int value) { _velocityY = value; }
		
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
		
		bool getIsStationary() { return _isStationary; }
		void setIsStationary(bool value) { _isStationary = value; }

		bool getIsComponent() { return _isComponent; }
		void setIsComponent(bool value) { _isComponent = value; }
		
		Mob * getParent() { return _parent; }
		void setParent(Mob * value) { _parent = value; }
		
		unsigned int getShotCooldown_ms() {return _shotCooldown_ms;}
		void setShotCooldown_ms(unsigned int value) { _shotCooldown_ms = value; }

		unsigned int getLastShotTick() { return _lastShotTick; }
		void setLastShotTick(unsigned int value) { _lastShotTick = value; }
		
		unsigned int getLastUpdateTick() { return _lastUpdateTick; }
		void setLastUpdateTick(unsigned int value) { _lastUpdateTick = value; }
		
		bool createProjectile();

		//	Components are no longer used.  Leaving these here until we know
		//	we have all the features converted over.
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
		
		short _velocityX = 0;
		short _velocityY = 0;

		unsigned int _lastUpdateTick = 0;
		unsigned int _shotCooldown_ms = 1000;
		unsigned int _lastShotTick = 0;

		list<MobComponent *> _components;
		
		bool _isStationary = false;
		bool _isComponent = false;
		Mob * _parent;
};
