#ifndef GAME_H
#define GAME_H


#include "SDL.h"
#include <stdio.h>
#include <ctime>
#include <SDL_ttf.h>
#include <string>
#include "serialport.h"
#include "graphics.h"
#include "bullet.h"
#include "alien.h"

class Game
{
public:

	Game();

	// Global event
	static SDL_Event event;

	bool Running()
	{
		return _running;
	}

	void handleEvents(int randomNumber, int randomAlien1, int randomAlien2, int randomAlien3, int randomAlien4, int randomAlien5, int randomAlien6, int randomAlien7, int randomAlien8);
	void update();
	void render();
	void clean();
	
	
	bool restart;

	void restartGame();

	void initializeAliens();

	std::string GetLastErrorAsString();
	

	TTF_Font* font;
	SDL_Color white;
	SDL_Surface* surfaceGameOverMessage;
	SDL_Texture* gameOverMessage;
	SDL_Rect gameOverMessageRect;

	int highScore;
	std::string highScoreString;
	SDL_Surface* surfacehighScoreMessage;
	SDL_Texture* highScoreMessage;
	SDL_Rect highScoreMessageRect;

	SDL_Surface* surfaceVictoryMessage;
	SDL_Texture* victoryMessage;

	bool victory;

	// Check collision between two objects
	bool checkCollison(SDL_Rect a, SDL_Rect b);

private:
	bool _running;

};

#endif // GAME_H