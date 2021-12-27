#include "graphics.h"
#include "particle.h"
#include "particleemitter.h"


extern unsigned int gameTickCount;

bool ParticleEmitter::process()
{
	//	We don't want to process physics on every chance (maybe).  That could
	//	make this slow af
	if(gameTickCount - getLastUpdateTick() < 50) { return true; }
	
	bool foundActive = false;
	
	for(int epart = 0; epart < ((int)sizeof(_particles) / (int)sizeof(_particles[0])); epart++)
	{
		if(_particles[epart].getActive())
		{
			foundActive = true;
			
			_particles[epart].process();
			
			//	Check if this particle has lived it's life and shoudl be destroyed
			if(gameTickCount - _particles[epart].getCreatedTick() > _particles[epart].getLifeTickCount())
			{
				//	Check if we should still be generating new particles.  It
				//	may have been too long at this point and this should stop!
				if(gameTickCount - getCreatedTick() < getLifeTickCount())
				{
					_initializeParticle(&_particles[epart], epart);
				}
				else
				{
					_particles[epart].setActive(false);
				}
			}
		}
	}
	
	setLastUpdateTick(gameTickCount);
	
	if(!foundActive) { setActive(false); }
	
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
	setCreatedTick(gameTickCount);
	
	for(int epart = 0; epart < ((int)sizeof(_particles) / (int)sizeof(_particles[0])); epart++)
	{
		_initializeParticle(&_particles[epart], epart);
	}
	
	return true;
}

bool ParticleEmitter::_initializeParticle(Particle * particle, int particleno)
{
	particle->setTexture(_texture);
	particle->setLastUpdateTick(gameTickCount);
	particle->setCreatedTick(gameTickCount);
	particle->setLifeTickCount(rand() % 1000);
	
	particle->setVelocityX(250 - (rand() % 500));
	particle->setVelocityY(250 - (rand() % 500));
	
	particle->setX((double)getX());
	particle->setY((double)getY());
	
	int texX, texY;
	texX = particleno % 16;
	texY = particleno / 16;
	
	SDL_Point texSize;
	SDL_QueryTexture(_texture, NULL, NULL, &texSize.x, &texSize.y);
	
	particle->setTextureCoords(
		(texSize.x / 16) * texX,
		(texSize.y / 16) * texY,
		(texSize.x / 16) * texX + (texSize.x / 16),
		(texSize.y / 16) * texY + (texSize.y / 16)
	);
	
	particle->setActive(true);
	
	return true;
}
