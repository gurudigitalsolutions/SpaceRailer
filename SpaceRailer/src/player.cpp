#include "player.h"

extern short windowWidth;
extern short windowHeight;

bool Player::initialize()
{
	return Mob::initialize("playership");
}

bool Player::process()
{
	if(getX() < 0) { setX(0); }
	if(getY() < 0) { setY(0); }
	
	if(getX() > windowWidth - 1 - getWidth()) { setX(windowWidth - 1 - getWidth()); }
	if(getY() > windowHeight - 1 - getHeight()) { setY(windowHeight - 1 - getHeight()); }
	
	return Mob::process();
}
