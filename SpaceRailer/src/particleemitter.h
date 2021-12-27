#ifdef _WIN32
	#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

using namespace std;

class ParticleEmitter
{
	public:
		unsigned int getLastUpdateTick() { return _lastUpdateTick; }
		void setLastUpdateTick(unsigned int value) { _lastUpdateTick = value; }
		
		unsigned int getCreatedTick() { return _createdTick; }
		void setCreatedTick(unsigned int value) { _createdTick = value; }
		
		unsigned int getLifeTickCount() { return _lifeTickCount; }
		void setLifeTickCount(unsigned int value) { _lifeTickCount = value;  }
		
		int getX() { return _x; }
		void setX(int value) { _x = value; }
		
		int getY() { return _y; }
		void setY(int value) { _y = value; }
		
		SDL_Texture * getTexture() { return _texture; }
		void setTexture(SDL_Texture * value);
		
		bool getActive() { return _active; }
		void setActive(bool value) { _active = value; }
		
		bool process();
		bool render();
		bool initialize();
	
	private:
		unsigned int _lastUpdateTick = 0;
		unsigned int _createdTick = 0;
		unsigned int _lifeTickCount = 2500;
		
		bool _active = true;
		
		int _x = 0;
		int _y = 0;
		Particle _particles[256];
		
		SDL_Texture * _texture;
		
		bool _initializeParticle(Particle * particle);
};
