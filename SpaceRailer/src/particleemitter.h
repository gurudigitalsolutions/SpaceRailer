#ifdef _WIN32
	#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

using namespace std;

class ParticleEmitter
{
	public:
		virtual unsigned int getLastUpdateTick() { return _lastUpdateTick; }
		virtual void setLastUpdateTick(unsigned int value) { _lastUpdateTick = value; }
		
		virtual unsigned int getCreatedTick() { return _createdTick; }
		virtual void setCreatedTick(unsigned int value) { _createdTick = value; }
		
		virtual unsigned int getLifeTickCount() { return _lifeTickCount; }
		virtual void setLifeTickCount(unsigned int value) { _lifeTickCount = value;  }
		
		virtual int getX() { return _x; }
		virtual void setX(int value) { _x = value; }
		
		virtual int getY() { return _y; }
		virtual void setY(int value) { _y = value; }
		
		virtual SDL_Texture * getTexture() { return _texture; }
		virtual void setTexture(SDL_Texture * value);
		
		virtual bool getActive() { return _active; }
		virtual void setActive(bool value) { _active = value; }
		
		virtual unsigned int getRespawnLoopSetPoint() { return _respawnLoopSetPoint; }
		virtual void setRespawnLoopSetPoint(unsigned int value) { _respawnLoopSetPoint = value; }
		
		virtual unsigned int getRespawnLoopCount() { return _respawnLoopCount; }
		virtual void setRespawnLoopCount(unsigned int value) { _respawnLoopCount = value; }
		
		virtual bool process();
		virtual bool render();
		virtual bool initialize();
	
	private:
		unsigned int _lastUpdateTick = 0;
		unsigned int _createdTick = 0;
		unsigned int _lifeTickCount = 10000;
		
		unsigned int _respawnLoopSetPoint = 10;
		unsigned int _respawnLoopCount = 0;
		
		bool _active = true;
		
		int _x = 0;
		int _y = 0;
		
		
	protected:
		Particle _particles[256];
		
		SDL_Texture * _texture;
		
		virtual bool _initializeParticle(Particle * particle, int particleno);
};
