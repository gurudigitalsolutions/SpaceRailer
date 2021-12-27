#include "graphics.h"

using namespace std;

class Particle
{
	public:
		float getX() { return _x; }
		void setX(float value) { _x = value; }
		float getY() { return _y; }
		void setY(float value) { _y = value; }
		float getZ() { return _z; }
		void setZ(float value) { _z = value; }
		
		int getWidth() { return _width; }
		int getHeight() { return _height; }
		void setWidth(int value) { _width = value; }
		void setHeight(int value) { _height = value; }
		
		float getVelocityX() { return _velocityX; }
		float getVelocityY() { return _velocityY; }
		float getVelocityZ() { return _velocityZ; }
		void setVelocityX(float value) { _velocityX = value; }
		void setVelocityY(float value) { _velocityY = value; }
		void setVelocityZ(float value) { _velocityZ = value; }
		
		void setTexture(SDL_Texture * value) { _texture = value; }
		void setTextureCoords(int x1, int x2, int y1, int y2);
		
		bool getActive() { return _active; }
		void setActive(bool value) { _active = value; }
		
		unsigned int getLastUpdateTick() { return _lastUpdateTick; }
		void setLastUpdateTick(unsigned int value) { _lastUpdateTick = value; }
		
		unsigned int getCreatedTick() { return _createdTick; }
		void setCreatedTick(unsigned int value) { _createdTick = value; }
		
		unsigned int getLifeTickCount() { return _lifeTickCount; }
		void setLifeTickCount(unsigned int value) { _lifeTickCount = value; }
		
		bool process();
		bool render();
	
	private:
		bool _active = false;
		unsigned int _lastUpdateTick = 0;
		unsigned int _createdTick = 0;
		unsigned int _lifeTickCount = 500;
		
		float _x = 0.0;
		float _y = 0.0;
		float _z = 0.0;
		
		int _width = 16;
		int _height = 16;
		
		float _velocityX = 0.0;
		float _velocityY = 0.0;
		float _velocityZ = 0.0;
		
		SDL_Texture * _texture;
		int _textureX1 = 0;
		int _textureX2 = 0;
		int _textureY1 = 0;
		int _textureY2 = 0;
};
