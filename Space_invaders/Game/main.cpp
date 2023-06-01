#include "game.h"

Game* game = nullptr;


int main(int argc, char* argv[])
{

	// Open serial port object
	serialib serial;
	char buffer[15] = "test";
	char cleared = '0';

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->initializeAliens();
	SDL_ShowCursor(SDL_DISABLE);
	srand(time(NULL));

	// Connection to serial port
	char errorOpening = serial.openDevice("\\\\.\\COM3", 115200);

	if (errorOpening == 1) {
		std::cout << "Successfully opened device\n";
	}
	else {
		std::cout << game->GetLastErrorAsString() << std::endl;
	}
	
	//configureSerialPort(serial);

	// Game loop
	while (game->Running())
	{
		if (game->restart) {
			buffer[0] = cleared;
			game->restartGame();
			game->restart = false;
		}
		if (game->left) {
			buffer[0] = cleared;
			game->left = false;
		}
		if (game->right) {
			buffer[0] = cleared;
			game->right = false;
		}
		if (game->shoot) {
			buffer[0] = cleared;
			game->shoot = false;
		}
		
		// Check for restart
		if (serial.available() > 3) {
			serial.readString(buffer, '\n', 15, 0);
			std::cout << buffer << std::endl;
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
		game->handleEvents(buffer, randomNumber, randomAlien1, randomAlien2, randomAlien3, randomAlien4, randomAlien5, randomAlien6, randomAlien7, randomAlien8);
		game->update();
		game->render();
		
		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	serial.closeDevice();
	delete game;
	
	return 0;
}