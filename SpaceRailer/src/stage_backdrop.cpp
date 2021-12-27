#include "graphics.h"
#include "particle.h"
#include "particleemitter.h"
#include "config.h"
#include "stage_backdrop.h"
#include "stage.h"


extern short windowWidth;
extern short windowHeight;

extern Stage * currentStage;
extern unsigned int gameTickCount;

bool StageBackdrop::process()
{
	return true;
}

bool StageBackdrop::render()
{
	SDL_Rect box;
	box.w = getWidth();
	box.h = getHeight();

	box.x = (getRenderWidth() * currentStage->getMapX() / (currentStage->getStageWidth() + windowWidth)) * -1;
	box.y = getRenderHeight() * currentStage->getMapY() / currentStage->getStageHeight();
	
	//box.x = getX() - currentStage->getMapX();
	//box.y = getY() - currentStage->getMapY();
	SDL_RenderCopy(getSDLRenderer(), sprites.front(), NULL, &box);
	
	return true;
}

bool StageBackdrop::initialize(string backdropName, int width, int height)
{
	_backdropName = backdropName;
	setWidth(width);
	setHeight(height);
	setRenderWidth(width);
	setRenderHeight(height);
	
	return loadSprite();
}

bool StageBackdrop::initialize(string backdropName)
{
	return initialize(backdropName, windowWidth, windowHeight);
}

bool StageBackdrop::initialize()
{
	return false;
}

bool StageBackdrop::loadSprite() {
	sprites.push_back(
		Graphics::loadTexture(Path_Tools::getGameDataPath() + "resources/backdrops/" + getBackdropName() + ".png")
	);
	return true;
}
