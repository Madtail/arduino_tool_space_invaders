#ifndef BULLET_H
#define BULLET_H

#include "SDL.h"
#include "globals.h"
#include "player.h"
#include "iostream"
#include <vector>

class Bullet 
{
public:

	Bullet();
	~Bullet();

	static const int BULLET_WIDTH = 16;
	static const int BULLET_HEIGHT = 16;
	static const int BULLET_VEL = 12;
	


	void fire();
	int getBulletXpos();
	int getBulletYpos();

	int bulletXpos;
	int bulletYpos;
	int bulletVelY;
	
	SDL_Rect bulletCollider;

	bool isDestroyed;

private:


};



#endif // !BULLET_H