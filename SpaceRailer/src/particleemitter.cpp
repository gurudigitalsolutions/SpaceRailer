#include "graphics.h"
#include "particle.h"
#include "particleemitter.h"


extern unsigned int gameTickCount;

bool ParticleEmitter::process()
{
	//	We don't want to process physics on every chance (maybe).  That could
	//	make this slow af
	if(gameTickCount - getLastUpdateTick() < 50) { return true; }
	setLastUpdateTick(gameTickCount);
	
	for(int epart = 0; epart < ((int)sizeof(_particles) / (int)sizeof(_particles[0])); epart++)
	{
		if(_particles[epart].getActive())
		{
			_particles[epart].process();
		}
	}
	
	return true;
}

bool ParticleEmitter::render()
{
	for(int epart = 0; epart < ((int)sizeof(_particles) / (int)sizeof(_particles[0])); epart++)
	{
		if(_particles[epart].getActive())
		{
			_particles[epart].render();
		}
	}
	
	return true;
}


void ParticleEmitter::setTexture(SDL_Texture * value)
{
	_texture = value;
	
	for(int epart = 0; epart < ((int)sizeof(_particles) / (int)sizeof(_particles[0])); epart++)
	{
		_particles[epart].setTexture(_texture);
	}
}

bool ParticleEmitter::initialize()
{
	setLastUpdateTick(gameTickCount);
	
	for(int epart = 0; epart < ((int)sizeof(_particles) / (int)sizeof(_particles[0])); epart++)
	{
		_particles[epart].setTexture(_texture);
		_particles[epart].setLastUpdateTick(gameTickCount);
		
		_particles[epart].setVelocityX(250 - (rand() % 500));
		_particles[epart].setVelocityY(250 - (rand() % 500));
		
		_particles[epart].setX((double)getX());
		_particles[epart].setY((double)getY());
		
		printf("Particle at %f, %f\n", _particles[epart].getX(), _particles[epart].getY());
		
		_particles[epart].setActive(true);
	}
	
	return true;
}
