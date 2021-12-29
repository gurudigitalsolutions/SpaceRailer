#include "graphics.h"
#include "particle.h"
#include "particleemitter.h"
#include "config.h"
#include "stage_backdrop.h"
#include "stage.h"


extern Stage * currentStage;
extern unsigned int gameTickCount;

bool Particle::process()
{
	unsigned int ts = gameTickCount - getLastUpdateTick();
	setLastUpdateTick(gameTickCount);
	
	double tdistance = getVelocityX() / 1000.0f;
	tdistance = tdistance * ts;
	setX(getX() + ceil(tdistance));
	
	tdistance = getVelocityY() / 1000.0f;
	tdistance = tdistance * ts;
	setY(getY() + ceil(tdistance));
	
	/*setX((float)((getX() + (getVelocityX() * ts)) ));
	setY((float)((getY() + (getVelocityY() * ts)) ));
	setZ((float)((getZ() + (getVelocityZ() * ts)) ));*/
	
	return true;
}

bool Particle::render()
{
	SDL_Rect box;
	box.w = getWidth();
	box.h = getHeight();
	
	box.x = ((int)getX() - currentStage->getMapX());
	box.y = ((int)getY() - currentStage->getMapY());
	
	SDL_Rect clipBox;
	clipBox.x = _textureX1;
	clipBox.y = _textureY1;
	clipBox.w = _textureX2 - _textureX1;
	clipBox.h = _textureY2 - _textureY1;
	
	//printf("Particle render alpha %d\n", getAlpha());
	SDL_SetTextureAlphaMod(
		_texture, 
		getAlpha()
	);
	
	//printf("Rendering particle x,y %d, %d   %f, %f\n", box.x, box.y, getX(), getY());
	//SDL_RenderCopy(getSDLRenderer(), sprites.front(), NULL, &box);
	SDL_RenderCopyEx(
		getSDLRenderer(), 
		_texture, 
		(_textureX1 == -1 ? NULL : &clipBox),				//	Clip box 
		&box, 
		0.0, 				//	Render angle
		NULL, 
		SDL_FLIP_NONE
	);
	
	SDL_SetTextureAlphaMod(_texture, 255);
	
	return true;
}

void Particle::setTextureCoords(int x1, int x2, int y1, int y2)
{
	_textureX1 = x1;
	_textureX2 = x2;
	_textureY1 = y1;
	_textureY2 = y2;
}
