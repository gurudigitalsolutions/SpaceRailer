#include "graphics.h"
#include "particle.h"
#include "particleemitter.h"
#include "particleemitter.mobexplosion.h"
#include "particleemitter.simpleexplosion.h"


extern unsigned int gameTickCount;

bool SimpleExplosion::process()
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
			
			unsigned int ticksAlive = gameTickCount - _particles[epart].getCreatedTick();
			double prctLife = ticksAlive / (_particles[epart].getLifeTickCount() == 0 ? 1 : _particles[epart].getLifeTickCount());
			uint8_t alpha = 255;
			
			if(prctLife > .5) { alpha = 192; }
			if(prctLife > .6) { alpha = 160; }
			if(prctLife > .7) { alpha = 128; }
			if(prctLife > .8) { alpha = 96; }
			if(prctLife > .9) { alpha = 64; }
			
			//printf("prctlife %f   alpha %d\n", prctLife, alpha);
			_particles[epart].setAlpha(alpha);
			_particles[epart].process();
			
			//	Check if this particle has lived it's life and shoudl be destroyed
			if(gameTickCount - _particles[epart].getCreatedTick() > _particles[epart].getLifeTickCount())
			{
				_particles[epart].setRespawnCount(_particles[epart].getRespawnCount() + 1);
				
				//	Check if we should still be generating new particles.  It
				//	may have been too long at this point and this should stop!
				if(gameTickCount - getCreatedTick() < getLifeTickCount()
				&& _particles[epart].getRespawnCount() < getRespawnLoopSetPoint())
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

bool SimpleExplosion::render()
{
	SDL_SetTextureColorMod(getTexture(), 255, 128, 0);
	
	for(int epart = 0; epart < ((int)sizeof(_particles) / (int)sizeof(_particles[0])); epart++)
	{
		if(_particles[epart].getActive())
		{
			_particles[epart].render();
		}
	}
	
	SDL_SetTextureColorMod(getTexture(), 255, 255, 255);
	
	return true;
}



bool SimpleExplosion::initialize()
{
	setLastUpdateTick(gameTickCount);
	setCreatedTick(gameTickCount);
	
	setRespawnLoopSetPoint(2);
	setRespawnLoopCount(0);
	
	for(int epart = 0; epart < ((int)sizeof(_particles) / (int)sizeof(_particles[0])); epart++)
	{
		_initializeParticle(&_particles[epart], epart);
	}
	
	return true;
}

bool SimpleExplosion::_initializeParticle(Particle * particle, int particleno)
{
	particle->setTexture(_texture);
	particle->setLastUpdateTick(gameTickCount);
	particle->setCreatedTick(gameTickCount);
	particle->setLifeTickCount(1000);
	
	
	int texX, texY;
	texX = particleno % 16;
	texY = particleno / 16;
	
	SDL_Point texSize;
	SDL_QueryTexture(_texture, NULL, NULL, &texSize.x, &texSize.y);
	
	//	Setting TextureCoords x value to -1 will disable texture clipping.
	particle->setTextureCoords(
		-1,
		0,
		texSize.x,
		texSize.y
	);
	
	
	particle->setX(getX());
	particle->setY(getY());
	
	
	
	//	Calculate the angle that this particle should be emitted at.  This is
	//	some trig that I absolutely do not remember but found online :)
	//
	//	Since we are using a 16x16 grid for particles, the center is 8.0.  This
	//	is where we calculate the angle from
	float angle = atan2(
		8.0 - texY,
		8.0 - texX
	);
	
	//	angle is currently radians, calculate degrees
	angle = angle * 180 / M_PI;
	
	//	Now we can calculate x and y velocities based on the angle.  We first
	//	need to decided a total velocity
	int speed = rand() % 200;
	
	particle->setVelocityX(speed * cos(angle));
	particle->setVelocityY(speed * sin(angle));
		
	
	//particle->setVelocityX(100 - (rand() % 200));
	//particle->setVelocityY(100 - (rand() % 200));
	
	particle->setActive(true);
	
	particle->setRespawnCount(0);
	
	return true;
}
