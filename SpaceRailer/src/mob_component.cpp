#ifdef _WIN32
	#include "C:\vclib\SDL2-2.0.18\include\SDL.h"
#else
	#include <SDL2/SDL.h>
#endif
#include "config.h"
#include "stage.h"
#include "mob_componet.h"

extern Stage * currentStage;

bool MobComponent::process() {
	return false;
}
bool MobComponent::render() {
	
	SDL_Rect box;
	box.w = getWidth();
	box.h = getHeight();
	box.x = getParentX() + getX() - currentStage->getMapX();
	box.y = getParentY() + getY() - currentStage->getMapY();
	SDL_RenderCopy(getSDLRenderer(), sprites.front(), NULL, &box);
	
	return true;
}
bool MobComponent::initialize(string componentName, string parentName) {
	this->componentName = componentName;
	this->parentName = parentName;
	
	if(!loadSprite()) { return false; }
	
	return true;
}
bool MobComponent::initialize() {
	return true;
}
bool MobComponent::loadSprites() {
	//	Check game data path for additional sprites to load for this mob
	// loops through available sprites
	return true;
}
bool MobComponent::loadSprite() {
	sprites.push_back(
		Graphics::loadTexture(Path_Tools::getGameDataPath() + "resources/mobs/" + parentName + "/sprites/mob_" + componentName + ".png")
	);
	return true;
}

