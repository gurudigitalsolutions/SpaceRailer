#include "../graphics.h"
#include "../particles/particle.h"
#include "../particles/particleemitter.h"
#include "../config.h"
#include "../stage_backdrop.h"
#include "../stage.h"

extern short windowWidth;
extern short windowHeight;

extern Stage * currentStage;

bool Player::initialize()
{
	printf("In player initilize\n");
	return Mob::initialize("playership");
}

bool Player::process()
{
	/*if(getX() < 0) { setX(0); }
	if(getY() < 0) { setY(0); }
	
	if(getX() > currentStage->getMapX() + windowWidth - getWidth()) { setX(currentStage->getMapX() + windowWidth - getWidth()); }
	if(getY() > currentStage->getMapY() + windowHeight - getHeight()) { setY(currentStage->getMapY() + windowHeight - getHeight()); }
	*/
	//if(getX() > windowWidth - 1 - getWidth()) { setX(windowWidth - 1 - getWidth()); }
	//if(getY() > windowHeight - 1 - getHeight()) { setY(windowHeight - 1 - getHeight()); }
	
	/*if(getX() < currentStage->getMapX()) { setX(currentStage->getMapX() + 1); }*/
	
	//	Apply friction to slow ship
	if(getVelocityX() != 0)
	{
		if(getVelocityX() > 0) { setVelocityX(getVelocityX() - 5); }
		else { setVelocityX(getVelocityX() + 5); }
	}
	
	if(getVelocityY() != 0)
	{
		if(getVelocityY() > 0) { setVelocityY(getVelocityY() - 5); }
		else { setVelocityY(getVelocityY() + 5); }
	}
	
	if(getVelocityX() > 500) { setVelocityX(500); }
	if(getVelocityX() < -500) { setVelocityX(-500); }
	if(getVelocityY() > 500) { setVelocityY(500); }
	if(getVelocityY() < -500) { setVelocityY(-500); }
	
	return Mob::process();
}
