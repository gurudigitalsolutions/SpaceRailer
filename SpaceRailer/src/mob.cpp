#include <string>
#include <filesystem>

#ifdef _WIN32
	#include <direct.h>
	#define getcwd _getcwd
#else
	#include <unistd.h>
#endif

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifdef _WIN32
	#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
#else
	#include <SDL2/SDL.h>
#endif
//#include <dirent.h>
#include "particle.h"
#include "particleemitter.h"
#include "config.h"
#include "stage_backdrop.h"
#include "stage.h"
#include "mob.h"

extern short windowWidth;
extern short windowHeight;

extern Stage * currentStage;
extern unsigned int gameTickCount;


using namespace std;


//	Called each game tick to process mob stuff.  This includes physics and
//	scripting.
bool Mob::process()
{
	//	Check if there are any queued events before processing physics
	//	for this mob.  This will start with registered collisions.
	while(!_collisionQueue.empty())
	{
		Mob * target = _collisionQueue.front();
		
		//	Am I a projectile?
		if(getIsProjectile())
		{
			//	Ok, deal projectile damage to the target
			target->setMarkForDestroy(true);
			
			//	Honestly, until this is more advanced I should die too
			setMarkForDestroy(true);
		}
		
		//	Is the target a projectile?
		if(target->getIsProjectile())
		{
			//	I must take projectile damage
			setMarkForDestroy(true);
			
			//	The projectile should also be disappeared
			target->setMarkForDestroy(true);
		}
		
		_collisionQueue.pop();
	}
	
	//	Check if I'm supposed to die after the collision detection.
	if(getMarkForDestroy()) { return true; }
	
	if(!_processVelocity())
	{
		//	Velocity processing failed
	}
	
	return true;
}

//	Process velocity/movement for this mob.
bool Mob::_processVelocity()
{
	if(abs(getVelocityX()) > 0)
	{
		unsigned int timesincelastupdate = gameTickCount - getLastUpdateTick();
		
		if(timesincelastupdate > 25)
		{
			double tdistance = getVelocityX() / 1000.0f;
			tdistance = tdistance * timesincelastupdate;
			setX(getX() + ceil(tdistance));
			
			setLastUpdateTick(gameTickCount);
		}
	}
	
	if(abs(getVelocityY()) > 0)
	{
		unsigned int timesincelastupdate = gameTickCount - getLastUpdateTick();
		
		if(timesincelastupdate > 25)
		{
			double tdistance = getVelocityY() / 1000.0f;
			tdistance = tdistance * timesincelastupdate;
			setX(getY() + ceil(tdistance));
			
			setLastUpdateTick(gameTickCount);
		}
	}
	
	return true;
}

//	This needs to handle rendering the mob itself and any associate components
bool Mob::render() {

	if (sprites.size() == 0) { return false; }

	SDL_Rect box;
	box.w = getWidth();
	box.h = getHeight();
	
	if(!getIsComponent())
	{
		box.x = getX() - currentStage->getMapX();
		box.y = getY() - currentStage->getMapY();
	}
	else
	{
		box.x = _parent->getX() + getX() - currentStage->getMapX();
		box.y = _parent->getY() + getY() - currentStage->getMapY();
	}
	
	//SDL_RenderCopy(getSDLRenderer(), sprites.front(), NULL, &box);
	SDL_RenderCopyEx(getSDLRenderer(), sprites.front(), NULL, &box, _renderAngle, NULL, SDL_FLIP_NONE);
	
	
	return true;
}


bool Mob::initialize(string mobname) {
	printf("MobName (Mob::initialize): %s\n", mobname.c_str());
	this->mobName = mobname;
	return Mob::initialize();
}

bool Mob::initialize()
{
	sprites.push_back(
		Graphics::loadTexture(Path_Tools::getGameDataPath() + "resources/mobs/" + mobName + "/sprites/mob0.png")
	);

	return true;
}

bool Mob::loadSprites()
{
	//	Check game data path for additional sprites to load for this mob
	// loops through available sprites
	return true;
}

bool Mob::loadSprite(string spriteName)
{
	return true;
}



bool Mob::checkCollision(int x, int y, int width, int height)
{
	if(getY() + getHeight() < y) { return false; }
	if(getY() > y + height) { return false; }
	if(getX() + getWidth() < x) { return false; }
	if(getX() > x + width) { return false; }
	
	return true;
}

//	Add a collision event to the collision queue.  This will be processed on
//	the next process() call.
bool Mob::registerCollision(Mob * target)
{
	_collisionQueue.push(target);
	return true;
}

bool Mob::createProjectile()
{
	Projectile * newProjectile = new Projectile();
	newProjectile->setX(getX() + getWidth() + 1);
	newProjectile->setY(getY() + (getHeight() / 2));
	newProjectile->setHeight(16);
	newProjectile->setWidth(16);
	
	newProjectile->setVelocityX(750);
	newProjectile->setVelocityY(10 - rand() % 20);
	newProjectile->setShotCooldown_ms(500);
	
	newProjectile->initialize("bullet1");
	newProjectile->setLastUpdateTick(gameTickCount);
	newProjectile->setIsProjectile(true);
	newProjectile->setTracer(5);
	newProjectile->setParent(this);
	currentStage->addMob(newProjectile);
	
	
	
	return true;
}
