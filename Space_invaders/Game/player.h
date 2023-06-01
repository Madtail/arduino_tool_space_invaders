#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "graphics.h"

class Player
{
public:
	
	Player();
	~Player();

	void move();

	void handleEvent(SDL_Event& e);

	const int PLAYER_VEL = 3;

	int getXPos();
	int getYPos();

	typedef struct {
		int x;
		int y;
	} Mouse;

	Mouse mouse;

	// Player collision box
	SDL_Rect playerCollider;

	bool isDestroyed;

	int velX, velY;

private:
	// Position
	int xpos, ypos;
	



};


#endif // PLAYER_H