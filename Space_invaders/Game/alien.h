#ifndef ALIEN_H
#define ALIEN_H
#include <SDL.h>
#include <vector>

class Alien 
{

public:

	static const int ALIEN_VEL = 1;

	Alien();
	~Alien();

	void alienMove();

	int alienXPos;
	int alienYPos;

	int alienVelX;
	int alienVelY;

	SDL_Rect alienCollisionBox;

	bool isDestroyed;

	Uint32 alienMoveTimeX;
	Uint32 alienMoveTimeY;

private:


};

#endif // ALIEN_H