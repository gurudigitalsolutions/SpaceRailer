#pragma once
#include <string>
#include "../graphics.h"
#include <list>
#include <queue>

#include "../path_tools.h"

using namespace std;

class Mob
{
	public:
		unsigned int getHitPoints() { return _hitPoints; }
		void setHitPoints(unsigned int value) { _hitPoints = value; }
		
		unsigned int getMagicPoints() { return _magicPoints; }
		void setMagicPoints(unsigned int value) { _magicPoints = value; }
		
		int getX() { return (getTileX() * 32) + getTileXOffset(); }
		int getY() { return (getTileY() * 32) + getTileYOffset(); }
		
		unsigned short getTileX();
		unsigned short getTileY();
		unsigned short getTileXOffset();
		unsigned short getTileYOffset();
		
		void setTileX(unsigned short value) { _tileX = value; }
		void setTileY(unsigned short value) { _tileY = value; }
		void setTileXOffset(unsigned short value) { _tileXOffset = value; }
		void setTileYOffset(unsigned short value) { _tileYOffset = value; }
		
		void changeTileXOffset(short amount);
		void changeTileYOffset(short amount);

		void setX(int value) { _coordX = value; }
		void setY(int value) { _coordY = value; }

		int getWidth() { return _width; }
		int getHeight() { return _height; }

		void setWidth(int value) { _width = value; }
		void setHeight(int value) { _height = value; }

		int getHitboxX() { return _hitboxX; }
		int getHitboxY() { return _hitboxY; }

		int getXWithHitbox() {
			if (getHitboxX() == -1) { return getX();  }
			return getX() + getHitboxX();
		}
		int getYWithHitbox() {
			if (getHitboxY() == -1) { return getY(); }
			return getY() + getHitboxY();
		}

		void setHitboxX(int value) { _hitboxX = value; }
		void setHitboxY(int value) { _hitboxY = value; }

		int getHitboxWidth() { 
			if (getHitboxX() == -1) { return getWidth(); }
			return _hitboxWidth;
		}
		int getHitboxHeight() { 
			if (getHitboxY() == -1) { return getHeight(); }
			return _hitboxHeight;
		}

		void setHitboxWidth(int value) { _hitboxWidth = value; }
		void seHitboxtHeight(int value) { _hitboxHeight = value; }
		
		int getVelocityX() { return _velocityX; }
		int getVelocityY() { return _velocityY; }
		
		void setVelocityX(int value) { _velocityX = value; }
		void setVelocityY(int value) { _velocityY = value; }
		
		double getRenderAngle() { return _renderAngle; }
		void setRenderAngle(double value) { _renderAngle = value; }
		
		list<SDL_Texture *> sprites;

		bool isFriendly;
		string mobName;

		virtual bool process();
		virtual bool render();
		virtual bool initialize(string mobName);
		virtual bool initialize();

		bool loadSprites();
		bool loadSprite(string spriteName);
		
		bool getIsStationary() { return _isStationary; }
		void setIsStationary(bool value) { _isStationary = value; }

		bool getIsComponent() { return _isComponent; }
		void setIsComponent(bool value) { _isComponent = value; }
		
		bool getIsProjectile() { return _isProjectile; }
		void setIsProjectile(bool value) { _isProjectile = value; }
		
		bool getMarkForDestroy() { return _markForDestroy; }
		void setMarkForDestroy(bool value) { _markForDestroy = value; }
		
		Mob * getParent() { return _parent; }
		void setParent(Mob * value) { _parent = value; }
		
		unsigned int getShotCooldown_ms() {return _shotCooldown_ms;}
		void setShotCooldown_ms(unsigned int value) { _shotCooldown_ms = value; }

		unsigned int getLastShotTick() { return _lastShotTick; }
		void setLastShotTick(unsigned int value) { _lastShotTick = value; }
		
		unsigned int getLastUpdateTick() { return _lastUpdateTick; }
		void setLastUpdateTick(unsigned int value) { _lastUpdateTick = value; }
		
		bool checkCollision(int x, int y, int width, int height);
		bool createProjectile();
		
		bool registerCollision(Mob * target);

	
	private:
		
		
		unsigned int _hitPoints = 100;
		unsigned int _magicPoints = 0;
		int _coordX = 0;
		int _coordY = 0;
		
		unsigned short _tileX = 0;
		unsigned short _tileY = 0;
		unsigned short _tileXOffset = 0;
		unsigned short _tileYOffset = 0;
		
		int _width = 0;
		int _height = 0;
		double _renderAngle = 0.0;

		int _hitboxX = -1;
		int _hitboxY = -1;
		int _hitboxWidth = -1;
		int _hitboxHeight = -1;

		short _accelerationX = 0;
		short _accelerationY = 0;
		short _accelerationMaxX = 40;
		short _accelerationMaxY = 40;
		
		short _velocityX = 0;
		short _velocityY = 0;
		
		bool _markForDestroy;

		unsigned int _lastUpdateTick = 0;
		unsigned int _shotCooldown_ms = 1000;
		unsigned int _lastShotTick = 0;

		
		bool _isStationary = false;
		bool _isComponent = false;
		bool _isProjectile = false;
		
		queue<Mob *> _collisionQueue;
		
	protected:
		bool _processVelocity();
		
		Mob * _parent;
};
