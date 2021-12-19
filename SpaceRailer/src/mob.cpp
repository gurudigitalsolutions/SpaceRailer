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
	

	return true;
}

bool Mob::render() {

	SDL_Rect box;
	box.w = getWidth();
	box.h = getHeight();
	box.x = getX() - currentStage->getMapX();
	box.y = getY() - currentStage->getMapY();
	SDL_RenderCopy(getSDLRenderer(), sprites.front(), NULL, &box);
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
