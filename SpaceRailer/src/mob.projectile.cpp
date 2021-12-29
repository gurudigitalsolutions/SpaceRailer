#include <string>
#include "graphics.h"
#include "particles/particle.h"
#include "particles/particleemitter.h"
#include "config.h"
#include "stage_backdrop.h"
#include "stage.h"

using namespace std;

extern short windowWidth;
extern short windowHeight;

extern Stage * currentStage;

bool Projectile::initialize()
{
	
	return (mobName == "" ? initialize("bullet1") : initialize(mobName));
}

bool Projectile::initialize(string mobname)
{
	return Mob::initialize(mobname);
}

bool Projectile::process()
{
	_processVelocity();
	
	//	Manipulation for texture effects shoudl go right here
	
	//	Overriding the primary Mob::process for this
	//return Mob::process();
	
	return true;
}

//	Overriding render so that we can put effects on the projectile
bool Projectile::render()
{

	SDL_Rect box;
	box.w = getWidth();
	box.h = getHeight();
	
	uint8_t cAlpha = 255;
	
	for(int ep = 0; ep < (getTracer() + 1); ep++)
	{
		if(!getIsComponent())
		{
			box.x = getX() - (ep * 2) - currentStage->getMapX();
			box.y = getY() - currentStage->getMapY();
		}
		else
		{
			//	A projectile component :O !!!
			
			box.x = _parent->getX() + getX() - (ep * (getWidth() / 2)) - currentStage->getMapX();
			box.y = _parent->getY() + getY() - currentStage->getMapY();
		}
		
		SDL_SetTextureAlphaMod(sprites.front(), cAlpha);
		SDL_SetTextureColorMod(sprites.front(), 0, cAlpha, 0);
	
		SDL_RenderCopyEx(
			getSDLRenderer(), 
			sprites.front(), 
			NULL, 
			&box, 
			getRenderAngle(), 
			NULL, 
			SDL_FLIP_NONE
		);
		
		if(cAlpha >= 50) { cAlpha -= 50; }
	}
	
	SDL_SetTextureAlphaMod(sprites.front(), 255);
	SDL_SetTextureColorMod(sprites.front(), 255, 255, 255);
	
	
	return true;
	
}
