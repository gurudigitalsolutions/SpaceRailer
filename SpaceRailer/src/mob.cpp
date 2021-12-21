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
#include "config.h"
#include "stage_backdrop.h"
#include "stage.h"
#include "mob.h"

extern Stage * currentStage;


using namespace std;

//	Called each game tick to process mob stuff.  This includes physics and
//	scripting.
bool Mob::process()
{
	//setX(getX() + 1);
	//setY(getY() - 1);
	
	//	Do all processing for this mob's components
	//	PROBABLY DELETE THIS!!!!11!!
	/*for(list<MobComponent *>::iterator emc = _components.begin(); emc != _components.end(); emc++)
	{
		(*emc)->setParentX(getX());
		(*emc)->setParentY(getY());
		(*emc)->process();
	}*/
	
	

	return true;
}

//	This needs to handle rendering the mob itself and any associate components
bool Mob::render() {

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
	
	SDL_RenderCopy(getSDLRenderer(), sprites.front(), NULL, &box);
	
	/*for(list<MobComponent *>::iterator emc = _components.begin(); emc != _components.end(); emc++)
	{
		(*emc)->render();
	}*/
	
	return true;
}


bool Mob::initialize(string mobName) {
	this->mobName = mobName;
	return initialize();
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

//	Add a pre-defined component to this mob.
bool Mob::addComponent(MobComponent * nComponent)
{
	_components.push_back(nComponent);
	return true;
}

bool Mob::addComponent(string component, int offsetx, int offsety, int width, int height)
{
	MobComponent * tComponent = new MobComponent();
	tComponent->setX(offsetx);
	tComponent->setY(offsety);
	tComponent->setWidth(width);
	tComponent->setHeight(height);
	
	if(!tComponent->initialize(component, mobName))
	{
		cout << "Failed to load component: " + component + " " + mobName + "\n";
		return false;
	}
	
	return addComponent(tComponent);
}

bool Mob::addComponent(
	string component, int offsetx, int offsety, int width, int height, 
	componentAttachMode attachmode, unsigned char maxdistancex, unsigned char maxdistancey)
{
	MobComponent * tComponent = new MobComponent();
	tComponent->setX(offsetx);
	tComponent->setY(offsety);
	tComponent->setWidth(width);
	tComponent->setHeight(height);
	
	if(!tComponent->initialize(component, mobName))
	{
		cout << "Failed to load component: " + component + " " + mobName + "\n";
		return false;
	}
	
	tComponent->setAttachMode(attachmode);
	tComponent->setAttachMaxDistanceX(maxdistancex);
	tComponent->setAttachMaxDistanceY(maxdistancey);
	
	return addComponent(tComponent);
}
