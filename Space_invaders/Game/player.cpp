#include "player.h"

Player::Player()
{
	xpos = 400;
	ypos = 540;

	velX = 0;
	velY = 0;

	mouse = {0, 0};

	playerCollider.w = globals::PLAYER_WIDTH;
	playerCollider.h = globals::PLAYER_HEIGHT;

	isDestroyed = false;
}

Player::~Player() 
{}

int Player::getXPos()
{
	return xpos;
}

int Player::getYPos()
{
	return ypos;
}

void Player::move()
{
	//Add velocity
	xpos += velX;
	ypos += velY;
	playerCollider.x = xpos;
	playerCollider.y = ypos;


	if ( (xpos < 0) || (xpos + globals::PLAYER_WIDTH > globals::SCREEN_WIDTH) )
	{
		xpos -= velX;
	}
	if( (ypos < 0) || (ypos + globals::PLAYER_HEIGHT > globals::SCREEN_HEIGHT) )
	{
		ypos -= velY;
	}
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// Adjust velocity
		switch (e.key.keysym.sym)
		{
		//case SDLK_w: velY -= PLAYER_VEL; break;
		//case SDLK_s: velY += PLAYER_VEL; break;
		case SDLK_a: velX -= PLAYER_VEL; break;
		case SDLK_d: velX += PLAYER_VEL; break;

		//case SDLK_UP: velY -= PLAYER_VEL; break;
		//case SDLK_DOWN: velY += PLAYER_VEL; break;
		case SDLK_LEFT: velX -= PLAYER_VEL; break;
		case SDLK_RIGHT: velX += PLAYER_VEL; break;
		}
	}

	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		//case SDLK_w: velY += PLAYER_VEL; break;
		//case SDLK_s: velY -= PLAYER_VEL; break;
		case SDLK_a: velX += PLAYER_VEL; break;
		case SDLK_d: velX -= PLAYER_VEL; break;

		//case SDLK_UP: velY += PLAYER_VEL; break;
		//case SDLK_DOWN: velY -= PLAYER_VEL; break;
		case SDLK_LEFT: velX += PLAYER_VEL; break;
		case SDLK_RIGHT: velX -= PLAYER_VEL; break;
		}
	}
}