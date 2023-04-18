#include "alien.h"

Alien::Alien()
{
	alienVelX = ALIEN_VEL;
	alienVelY = ALIEN_VEL;

	alienXPos = 0;
	alienYPos = 0;

	alienCollisionBox.w = 16;
	alienCollisionBox.h = 16;

	alienMoveTimeX = -2000;
	alienMoveTimeY = -6000;

	isDestroyed = false;
}

Alien::~Alien() {};

void Alien::alienMove() 
{
	if (alienXPos <= 50)
	{
		alienVelX = -ALIEN_VEL;
	}
	else if(alienXPos >= 750)
	{
		alienVelX = ALIEN_VEL;
	}

	alienXPos -= alienVelX;
	alienCollisionBox.x = alienXPos;
	alienCollisionBox.y = alienYPos;
}