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
	
	//	Determine the coordinates for this component.  If the attachMode is set
	//	to sticky, then this is straighforward.  If it's loose, then we need
	//	to do some minimal math
	if(getAttachMode() == COMPONENT_ATTACH_STUCK)
	{
		setTempX(getX());
		setTempY(getY());
	}
	else
	{
		//	This math is totally not right
		//	I also think that because process is called so quickly that this
		//	is essentially unperceptable.
		//	You can see the jitter it causes though while stationary
		if(abs(getParentX() - getX()) > getTempX())
		{
			if(getX() > getTempX()) { setTempX(getTempX() + 1); }
			else { setTempX(getTempX() - 1); }
		}
		
		if(abs(getParentY() - getY()) > getTempY())
		{
			if(getY() > getTempY()) { setTempY(getTempY() + 1); }
			else { setTempY(getTempY() - 1); }
		}
	}
	
	
	return false;
}
bool MobComponent::render() {
	
	SDL_Rect box;
	box.w = getWidth();
	box.h = getHeight();
	box.x = getParentX() + getTempX() - currentStage->getMapX();
	box.y = getParentY() + getTempY() - currentStage->getMapY();
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

