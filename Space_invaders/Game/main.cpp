#include "game.h"



Game* game = nullptr;


int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->initializeAliens();
	SDL_ShowCursor(SDL_DISABLE);
	srand(time(NULL));
	// Game loop
	while (game->Running())
	{
		if (game->restart) {
			game->restartGame();
			game->restart = false;
		}
		frameStart = SDL_GetTicks();
		int randomNumber = rand() % 50 + 1;
		int randomAlien1 = rand() % 10 + 0;
		int randomAlien2 = rand() % 10 + 0;
		int randomAlien3 = rand() % 10 + 0;
		int randomAlien4 = rand() % 10 + 0;
		int randomAlien5 = rand() % 10 + 0;
		int randomAlien6 = rand() % 10 + 0;
		int randomAlien7 = rand() % 10 + 0;
		int randomAlien8 = rand() % 10 + 0;
		game->handleEvents(randomNumber, randomAlien1, randomAlien2, randomAlien3, randomAlien4, randomAlien5, randomAlien6, randomAlien7, randomAlien8);
		game->update();
		game->render();
		
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;
	
	return 0;
}