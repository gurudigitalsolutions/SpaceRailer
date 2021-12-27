#include "graphics.h"
#include "particle.h"

bool Particle::process()
{
	
	return true;
}

bool Particle::render()
{
	
	return true;
}

void Particle::setTextureCoords(int x1, int x2, int y1, int y2)
{
	_textureX1 = x1;
	_textureX2 = x2;
	_textureY1 = y1;
	_textureY2 = y2;
}
