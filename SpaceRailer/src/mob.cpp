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
#include "mob.h"

using namespace std;

//	Called each game tick to process mob stuff.  This includes physics and
//	scripting.
bool Mob::process()
{
	return true;
}

bool Mob::render() {

	SDL_Rect box;
	box.w = 30;
	box.h = 30;
	box.x = 50;
	box.y = 50;

	//	Set draw color to green
	SDL_SetRenderDrawColor(getSDLRenderer(), 0x00, 0xff, 0x00, 0xff);
	SDL_RenderFillRect(getSDLRenderer(), &box);
	SDL_RenderPresent(getSDLRenderer());
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

	return true;
}
