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
		
		int getX() { return _x; }
		void setX(int value) { _x = value; }
		
		int getY() { return _y; }
		void setY(int value) { _y = value; }
		
		SDL_Texture * getTexture() { return _texture; }
		void setTexture(SDL_Texture * value);
		
		bool process();
		bool render();
		bool initialize();
	
	private:
		unsigned int _lastUpdateTick = 0;
		int _x = 0;
		int _y = 0;
		Particle _particles[256];
		
		SDL_Texture * _texture;
};
