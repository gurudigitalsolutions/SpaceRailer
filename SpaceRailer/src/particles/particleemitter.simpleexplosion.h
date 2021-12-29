#ifdef _WIN32
	#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
#else
	#include <SDL2/SDL.h>
#endif

using namespace std;

class SimpleExplosion : public ParticleEmitter
{
	public:
		bool process() override;
		bool render() override;
		bool initialize() override;
	
	private:
		bool _initializeParticle(Particle * particle, int particleno) override;
};
