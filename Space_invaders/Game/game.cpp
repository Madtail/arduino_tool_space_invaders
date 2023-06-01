#include "game.h"

static std::vector<Bullet> bullets;
static std::vector<Alien> aliens1;
static std::vector<Alien> aliens2;
static std::vector<Alien> aliens3;
static std::vector<Alien> aliens4;
static std::vector<Alien> aliens5;
static std::vector<Alien> aliens6;
static std::vector<Alien> aliens7;
static std::vector<Alien> aliens8;
std::vector<int> aliensXpos = { 250, 280, 310, 340, 370, 400, 430, 460, 490, 520, 550 };
int aliens1Ypos = 20;
int aliens2Ypos = 70;
int aliens3Ypos = 120;
int aliens4Ypos = 170;
int aliens5Ypos = 220;
int aliens6Ypos = 270;
int aliens7Ypos = 320;
int aliens8Ypos = 370;

Uint32 tempAlienTime = -1000;

Uint32 bulletStartTime = -1000;

Uint32 scoreTime = -1000;

SDL_Event Game::event;

Graphics graphics;
Player player;



//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string Game::GetLastErrorAsString()
{
	//Get the error message ID, if any.
	DWORD errorMessageID = ::GetLastError();
	if (errorMessageID == 0) {
		return std::string(); //No error message has been recorded
	}

	LPSTR messageBuffer = nullptr;

	//Ask Win32 to give us the string version of that message ID.
	//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

	//Copy the error message into a std::string.
	std::string message(messageBuffer, size);

	//Free the Win32's string's buffer.
	LocalFree(messageBuffer);

	return message;
}

Game::Game()
{
	restart = false;
	left = false;
	right = false;
	shoot = false;

	_running = true;

	

	if (SDL_Init(SDL_INIT_EVERYTHING && TTF_Init()) == 0)
	{
		std::cout << "Subsystems Initialized...\n";
	}
	else {
		std::cout << GetLastErrorAsString() << std::endl;
	}

	victory = false;

	score = 0;
	highestHighScore = 1000;
	highScoreMessageRect.x = 0;
	highScoreMessageRect.y = 0;
	highScoreMessageRect.w = 200;
	highScoreMessageRect.h = 200;

	gameOverMessageRect.x = 220;
	gameOverMessageRect.y = 200;
	gameOverMessageRect.w = 400;
	gameOverMessageRect.h = 400;
	font = TTF_OpenFont("C64_Pro-STYLE.ttf", 50);
	white = { 255,255,255 };
	surfaceGameOverMessage = TTF_RenderUTF8_Blended(font, "GAME OVER", white);
	gameOverMessage = SDL_CreateTextureFromSurface(graphics.getRenderer(), surfaceGameOverMessage);

	surfaceVictoryMessage = TTF_RenderUTF8_Blended(font, "VICTORY", white);
	victoryMessage = SDL_CreateTextureFromSurface(graphics.getRenderer(), surfaceVictoryMessage);
}

SDL_Texture* playerTexture = graphics.loadMedia("../media/player.png");
SDL_Texture* bulletTexture = graphics.loadMedia("../media/bullet2.png");
SDL_Texture* alienTexture1 = graphics.loadMedia("../media/alien1.png");
SDL_Texture* alienTexture2 = graphics.loadMedia("../media/alien2.png");

void Game::restartGame()
{
	aliens1.clear();
	aliens2.clear();
	aliens3.clear();
	aliens4.clear();
	aliens5.clear();
	aliens6.clear();
	aliens7.clear();
	aliens8.clear();

	score = 0;
	player.isDestroyed = false;

	initializeAliens();
}

void Game::initializeAliens()
{
	// First line of aliens
	for (int i = 0; i < 11; i++)
	{
		aliens1.push_back(Alien());
		aliens1[i].alienXPos = aliensXpos[i];
		aliens1[i].alienYPos = aliens1Ypos;
		
		aliens2.push_back(Alien());
		aliens2[i].alienXPos = aliensXpos[i];
		aliens2[i].alienYPos = aliens2Ypos;

		aliens3.push_back(Alien());
		aliens3[i].alienXPos = aliensXpos[i];
		aliens3[i].alienYPos = aliens3Ypos;

		aliens4.push_back(Alien());
		aliens4[i].alienXPos = aliensXpos[i];
		aliens4[i].alienYPos = aliens4Ypos;

		aliens5.push_back(Alien());
		aliens5[i].alienXPos = aliensXpos[i];
		aliens5[i].alienYPos = aliens5Ypos;

		aliens6.push_back(Alien());
		aliens6[i].alienXPos = aliensXpos[i];
		aliens6[i].alienYPos = aliens6Ypos;

		aliens7.push_back(Alien());
		aliens7[i].alienXPos = aliensXpos[i];
		aliens7[i].alienYPos = aliens7Ypos;

		aliens8.push_back(Alien());
		aliens8[i].alienXPos = aliensXpos[i];
		aliens8[i].alienYPos = aliens8Ypos;
	}
}

void Game::handleEvents(std::string message, int randomNumber, int randomAlien1, int randomAlien2, int randomAlien3, int randomAlien4, int randomAlien5, int randomAlien6, int randomAlien7, int randomAlien8)
{	
	std::cout << "Message: " << message << std::endl;

	if (message == "RESTART\n") {
		restart = true;
		message = "";
	}

	if (message == "LEFT\n") {
		left = true;
		player.velX -= player.PLAYER_VEL;
		player.move();
		message = "";
	}
	if (message == "RIGHT\n") {
		right = true;
		player.velX += player.PLAYER_VEL;
		player.move();
		message = "";
	}
	if (message == "SHOOT\n") {
		shoot = true;
		if ((SDL_GetTicks() - bulletStartTime) >= 500 && player.isDestroyed != true) {
			bulletStartTime = SDL_GetTicks();
			bullets.push_back(Bullet());
			bullets.back().bulletXpos = player.getXPos() + 8;
			bullets.back().bulletYpos = player.getYPos() - 16;
		}
		message = "";
	}

	while (SDL_PollEvent(&event))
	{
		

		switch (event.type)
		{
		case SDL_QUIT:
			_running = false;
			break;

		default:
			break;
		}

		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
			case SDLK_z:
				if ((SDL_GetTicks() - bulletStartTime) >= 500 && player.isDestroyed != true) {
					bulletStartTime = SDL_GetTicks();
					bullets.push_back(Bullet());
					bullets.back().bulletXpos = player.getXPos() + 8;
					bullets.back().bulletYpos = player.getYPos() - 16;
				}	
				break;
			case SDLK_r:
				restart = true;
				break;
			}

		}
	
		player.handleEvent(event);

		if ((SDL_GetTicks() - scoreTime >= 2000) && player.isDestroyed != true && victory != true)
		{
			scoreTime = SDL_GetTicks();
			score++;
		}

		if (randomAlien1 >= aliens1.size())
		{
			randomAlien1 = aliens1.size() - 1;
		}

		if (aliens1.size() != 0)
		{
			if (((SDL_GetTicks() - tempAlienTime) >= 3000) && (randomNumber == 45 || randomNumber == 10 || (5 < randomNumber && randomNumber < 15))) {
				tempAlienTime = SDL_GetTicks();
				bullets.push_back(Bullet());
				bullets.back().bulletXpos = aliens1[randomAlien1].alienXPos;
				bullets.back().bulletYpos = aliens1[randomAlien1].alienYPos + 20;
				bullets.back().bulletVelY = -bullets.back().bulletVelY;
			}
		}

		if (randomAlien2 >= aliens2.size())
		{
			randomAlien2 = aliens2.size() - 1;
		}

		if (aliens2.size() != 0)
		{
			if (((SDL_GetTicks() - tempAlienTime) >= 3000) && (randomNumber == 35 || randomNumber == 2 || (1 < randomNumber && randomNumber < 12))) {
				tempAlienTime = SDL_GetTicks();
				bullets.push_back(Bullet());
				bullets.back().bulletXpos = aliens2[randomAlien2].alienXPos;
				bullets.back().bulletYpos = aliens2[randomAlien2].alienYPos + 20;
				bullets.back().bulletVelY = -bullets.back().bulletVelY;
			}
		}

		if (randomAlien3 >= aliens3.size())
		{
			randomAlien3 = aliens3.size() - 1;
		}

		if (aliens3.size() != 0)
		{
			if (((SDL_GetTicks() - tempAlienTime) >= 3000) && (randomNumber == 55 || randomNumber == 3 || (4 < randomNumber && randomNumber < 7))) {
				tempAlienTime = SDL_GetTicks();
				bullets.push_back(Bullet());
				bullets.back().bulletXpos = aliens3[randomAlien3].alienXPos;
				bullets.back().bulletYpos = aliens3[randomAlien3].alienYPos + 20;
				bullets.back().bulletVelY = -bullets.back().bulletVelY;
			}
		}

		if (randomAlien4 >= aliens4.size())
		{
			randomAlien4 = aliens4.size() - 1;
		}

		if (aliens4.size() != 0)
		{
			if (((SDL_GetTicks() - tempAlienTime) >= 3000) && (randomNumber == 65 || randomNumber == 4 || (6 < randomNumber && randomNumber < 9))) {
				tempAlienTime = SDL_GetTicks();
				bullets.push_back(Bullet());
				bullets.back().bulletXpos = aliens4[randomAlien4].alienXPos;
				bullets.back().bulletYpos = aliens4[randomAlien4].alienYPos + 20;
				bullets.back().bulletVelY = -bullets.back().bulletVelY;
			}
		}

		if (randomAlien5 >= aliens5.size())
		{
			randomAlien5 = aliens5.size() - 1;
		}

		if (aliens5.size() != 0)
		{
			if (((SDL_GetTicks() - tempAlienTime) >= 3000) && (randomNumber == 75 || randomNumber == 5 || (9 < randomNumber && randomNumber < 12))) {
				tempAlienTime = SDL_GetTicks();
				bullets.push_back(Bullet());
				bullets.back().bulletXpos = aliens5[randomAlien5].alienXPos;
				bullets.back().bulletYpos = aliens5[randomAlien5].alienYPos + 20;
				bullets.back().bulletVelY = -bullets.back().bulletVelY;
			}
		}

		if (randomAlien6 >= aliens6.size())
		{
			randomAlien6 = aliens6.size() - 1;
		}

		if (aliens6.size() != 0)
		{
			if (((SDL_GetTicks() - tempAlienTime) >= 3000) && (randomNumber == 85 || randomNumber == 6 || (11 < randomNumber && randomNumber < 14))) {
				tempAlienTime = SDL_GetTicks();
				bullets.push_back(Bullet());
				bullets.back().bulletXpos = aliens6[randomAlien6].alienXPos;
				bullets.back().bulletYpos = aliens6[randomAlien6].alienYPos + 20;
				bullets.back().bulletVelY = -bullets.back().bulletVelY;
			}
		}

		if (randomAlien7 >= aliens7.size())
		{
			randomAlien7 = aliens7.size() - 1;
		}

		if (aliens7.size() != 0)
		{
			if (((SDL_GetTicks() - tempAlienTime) >= 3000) && (randomNumber == 95 || randomNumber == 7 || (14 < randomNumber && randomNumber < 17))) {
				tempAlienTime = SDL_GetTicks();
				bullets.push_back(Bullet());
				bullets.back().bulletXpos = aliens7[randomAlien7].alienXPos;
				bullets.back().bulletYpos = aliens7[randomAlien7].alienYPos + 20;
				bullets.back().bulletVelY = -bullets.back().bulletVelY;
			}
		}

		if (randomAlien8 >= aliens8.size())
		{
			randomAlien8 = aliens8.size() - 1;
		}

		if (aliens8.size() != 0)
		{
			if (((SDL_GetTicks() - tempAlienTime) >= 3000) && (randomNumber == 105 || randomNumber == 8 || (15 < randomNumber && randomNumber < 18))) {
				tempAlienTime = SDL_GetTicks();
				bullets.push_back(Bullet());
				bullets.back().bulletXpos = aliens8[randomAlien8].alienXPos;
				bullets.back().bulletYpos = aliens8[randomAlien8].alienYPos + 20;
				bullets.back().bulletVelY = -bullets.back().bulletVelY;
			}
		}

		
	}

}
//TODO: Alien problem with vector, out of range
// Movement, check collisions and the state of everything
void Game::update()
{

	// Update player position
	player.move();

	// Check collisions between aliens1 and bullets
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i].bulletCollider.x = bullets[i].bulletXpos;
		bullets[i].bulletCollider.y = bullets[i].bulletYpos;
		for (int j = 0; j < aliens1.size(); j++)
		{
			aliens1[j].alienCollisionBox.x = aliens1[j].alienXPos;
			aliens1[j].alienCollisionBox.y = aliens1[j].alienYPos;
			// Collision
			if (checkCollison(aliens1[j].alienCollisionBox, bullets[i].bulletCollider) && bullets[i].bulletVelY != -bullets[i].BULLET_VEL)
			{
				aliens1[j].isDestroyed = true;
				bullets[i].isDestroyed = true;
			}
			if (checkCollison(aliens1[j].alienCollisionBox, player.playerCollider))
			{
				aliens1[j].isDestroyed = true;
				player.isDestroyed = true;
			}
		}
		//aliens2
		for (int j = 0; j < aliens2.size(); j++)
		{
			aliens2[j].alienCollisionBox.x = aliens2[j].alienXPos;
			aliens2[j].alienCollisionBox.y = aliens2[j].alienYPos;
			// Collision
			if (checkCollison(aliens2[j].alienCollisionBox, bullets[i].bulletCollider) && bullets[i].bulletVelY != -bullets[i].BULLET_VEL)
			{
				aliens2[j].isDestroyed = true;
				bullets[i].isDestroyed = true;
			}
			if (checkCollison(aliens2[j].alienCollisionBox, player.playerCollider))
			{
				aliens2[j].isDestroyed = true;
				player.isDestroyed = true;
			}
		}

		//aliens3
		for (int j = 0; j < aliens3.size(); j++)
		{
			aliens3[j].alienCollisionBox.x = aliens3[j].alienXPos;
			aliens3[j].alienCollisionBox.y = aliens3[j].alienYPos;
			// Collision
			if (checkCollison(aliens3[j].alienCollisionBox, bullets[i].bulletCollider) && bullets[i].bulletVelY != -bullets[i].BULLET_VEL)
			{
				aliens3[j].isDestroyed = true;
				bullets[i].isDestroyed = true;
			}
			if (checkCollison(aliens3[j].alienCollisionBox, player.playerCollider))
			{
				aliens3[j].isDestroyed = true;
				player.isDestroyed = true;
			}
		}


		//aliens4
		for (int j = 0; j < aliens4.size(); j++)
		{
			aliens4[j].alienCollisionBox.x = aliens4[j].alienXPos;
			aliens4[j].alienCollisionBox.y = aliens4[j].alienYPos;
			// Collision
			if (checkCollison(aliens4[j].alienCollisionBox, bullets[i].bulletCollider) && bullets[i].bulletVelY != -bullets[i].BULLET_VEL)
			{
				aliens4[j].isDestroyed = true;
				bullets[i].isDestroyed = true;
			}
			if (checkCollison(aliens4[j].alienCollisionBox, player.playerCollider))
			{
				aliens4[j].isDestroyed = true;
				player.isDestroyed = true;
			}
		}
		//aliens5
		for (int j = 0; j < aliens5.size(); j++)
		{
			aliens5[j].alienCollisionBox.x = aliens5[j].alienXPos;
			aliens5[j].alienCollisionBox.y = aliens5[j].alienYPos;
			// Collision
			if (checkCollison(aliens5[j].alienCollisionBox, bullets[i].bulletCollider) && bullets[i].bulletVelY != -bullets[i].BULLET_VEL)
			{
				aliens5[j].isDestroyed = true;
				bullets[i].isDestroyed = true;
			}
			if (checkCollison(aliens5[j].alienCollisionBox, player.playerCollider))
			{
				aliens5[j].isDestroyed = true;
				player.isDestroyed = true;
			}
		}
		//aliens6
		for (int j = 0; j < aliens6.size(); j++)
		{
			aliens6[j].alienCollisionBox.x = aliens6[j].alienXPos;
			aliens6[j].alienCollisionBox.y = aliens6[j].alienYPos;
			// Collision
			if (checkCollison(aliens6[j].alienCollisionBox, bullets[i].bulletCollider) && bullets[i].bulletVelY != -bullets[i].BULLET_VEL)
			{
				aliens6[j].isDestroyed = true;
				bullets[i].isDestroyed = true;
			}
			if (checkCollison(aliens6[j].alienCollisionBox, player.playerCollider))
			{
				aliens6[j].isDestroyed = true;
				player.isDestroyed = true;
			}
		}
		//aliens7
		for (int j = 0; j < aliens7.size(); j++)
		{
			aliens7[j].alienCollisionBox.x = aliens7[j].alienXPos;
			aliens7[j].alienCollisionBox.y = aliens7[j].alienYPos;
			// Collision
			if (checkCollison(aliens7[j].alienCollisionBox, bullets[i].bulletCollider) && bullets[i].bulletVelY != -bullets[i].BULLET_VEL)
			{
				aliens7[j].isDestroyed = true;
				bullets[i].isDestroyed = true;
			}
			if (checkCollison(aliens7[j].alienCollisionBox, player.playerCollider))
			{
				aliens7[j].isDestroyed = true;
				player.isDestroyed = true;
			}
		}
		//aliens8
		for (int j = 0; j < aliens8.size(); j++)
		{
			aliens8[j].alienCollisionBox.x = aliens8[j].alienXPos;
			aliens8[j].alienCollisionBox.y = aliens8[j].alienYPos;
			// Collision
			if (checkCollison(aliens8[j].alienCollisionBox, bullets[i].bulletCollider) && bullets[i].bulletVelY != -bullets[i].BULLET_VEL)
			{
				aliens8[j].isDestroyed = true;
				bullets[i].isDestroyed = true;
			}
			if (checkCollison(aliens8[j].alienCollisionBox, player.playerCollider))
			{
				aliens8[j].isDestroyed = true;
				player.isDestroyed = true;
			}
		}

		//Player collision with bullet
		player.playerCollider.x = player.getXPos();
		player.playerCollider.y = player.getYPos();
		if (checkCollison(player.playerCollider, bullets[i].bulletCollider))
		{
			bullets[i].isDestroyed = true;
			player.isDestroyed = true;
		}

	}


	// Update bullet position and delete
	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end();)
	{
		it->fire();

		if (it->isDestroyed) {
			it = bullets.erase(it);
		}
		else {
			++it;
		}
	}

	// Update positions of aliens1, fire bullets and delete
	for (std::vector<Alien>::iterator it = aliens1.begin(); it != aliens1.end();)
	{
		it->alienMove();

		if ((SDL_GetTicks() - it->alienMoveTimeY) >= 5000)
		{
			it->alienMoveTimeY = SDL_GetTicks();
			it->alienYPos += 10;
		}

		if (it->isDestroyed)
		{
			it = aliens1.erase(it);
		}
		else {
			++it;
		} 
	}

	//aliens2
	for (std::vector<Alien>::iterator it = aliens2.begin(); it != aliens2.end();)
	{
		it->alienMove();

		if ((SDL_GetTicks() - it->alienMoveTimeY) >= 5000)
		{
			it->alienMoveTimeY = SDL_GetTicks();
			it->alienYPos += 10;
		}

		if (it->isDestroyed)
		{
			it = aliens2.erase(it);
		}
		else {
			++it;
		}
	}
	//aliens3
	for (std::vector<Alien>::iterator it = aliens3.begin(); it != aliens3.end();)
	{
		it->alienMove();

		if ((SDL_GetTicks() - it->alienMoveTimeY) >= 5000)
		{
			it->alienMoveTimeY = SDL_GetTicks();
			it->alienYPos += 10;
		}

		if (it->isDestroyed)
		{
			it = aliens3.erase(it);
		}
		else {
			++it;
		}
	}
	//aliens4
	for (std::vector<Alien>::iterator it = aliens4.begin(); it != aliens4.end();)
	{
		it->alienMove();
		
		if ((SDL_GetTicks() - it->alienMoveTimeY) >= 5000)
		{
			it->alienMoveTimeY = SDL_GetTicks();
			it->alienYPos += 10;
		}

		if (it->isDestroyed)
		{
			it = aliens4.erase(it);
		}
		else {
			++it;
		}
	}
	//aliens5
	for (std::vector<Alien>::iterator it = aliens5.begin(); it != aliens5.end();)
	{
		it->alienMove();

		if ((SDL_GetTicks() - it->alienMoveTimeY) >= 5000)
		{
			it->alienMoveTimeY = SDL_GetTicks();
			it->alienYPos += 10;
		}

		if (it->isDestroyed)
		{
			it = aliens5.erase(it);
		}
		else {
			++it;
		}
	}

	//aliens6
	for (std::vector<Alien>::iterator it = aliens6.begin(); it != aliens6.end();)
	{
		it->alienMove();

		if ((SDL_GetTicks() - it->alienMoveTimeY) >= 5000)
		{
			it->alienMoveTimeY = SDL_GetTicks();
			it->alienYPos += 10;
		}

		if (it->isDestroyed)
		{
			it = aliens6.erase(it);
		}
		else {
			++it;
		}
	}
	//aliens7
	for (std::vector<Alien>::iterator it = aliens7.begin(); it != aliens7.end();)
	{
		it->alienMove();

		if ((SDL_GetTicks() - it->alienMoveTimeY) >= 5000)
		{
			it->alienMoveTimeY = SDL_GetTicks();
			it->alienYPos += 10;
		}

		if (it->isDestroyed)
		{
			it = aliens7.erase(it);
		}
		else {
			++it;
		}
	}

	//aliens8
	for (std::vector<Alien>::iterator it = aliens8.begin(); it != aliens8.end();)
	{
		it->alienMove();

		if ((SDL_GetTicks() - it->alienMoveTimeY) >= 5000)
		{
			it->alienMoveTimeY = SDL_GetTicks();
			it->alienYPos += 10;
		}

		if (it->isDestroyed)
		{
			it = aliens8.erase(it);
		}
		else {
			++it;
		}
	}
}

void Game::render()
{
	SDL_RenderClear(graphics.getRenderer());

	// Draw here
	// draw player
	if (player.isDestroyed != true)
	{
		graphics.render(playerTexture, player.getXPos(), player.getYPos());
	}
	else
	{
		// Game over
		graphics.render(gameOverMessage, gameOverMessageRect.x, gameOverMessageRect.y);
	}



	if ((SDL_GetTicks() > 0) && ((aliens1.size() + aliens2.size() + aliens3.size() + aliens4.size() + aliens5.size() + aliens6.size() + aliens7.size() + aliens8.size()) == 0))
	{
		graphics.render(victoryMessage, gameOverMessageRect.x, gameOverMessageRect.y);
		victory = true;
		if (score < highestHighScore) {
			highestHighScore = score;
		}
	}

	highScoreString = std::to_string(score);
	char const* pchar = highScoreString.c_str();
	surfacehighScoreMessage = TTF_RenderUTF8_Blended(font, pchar, white);
	highScoreMessage = SDL_CreateTextureFromSurface(graphics.getRenderer(), surfacehighScoreMessage);
	graphics.render(highScoreMessage, highScoreMessageRect.x, highScoreMessageRect.y);

	for (std::vector<Bullet>::iterator it = bullets.begin(); it != bullets.end(); ++it)
	{
		graphics.render(bulletTexture, it->bulletXpos, it->bulletYpos);
	}
	// Aliens1
	for (std::vector<Alien>::iterator it = aliens1.begin(); it != aliens1.end(); ++it)
	{
		graphics.render(alienTexture1, it->alienXPos, it->alienYPos);
	}
	// Aliens2
	for (std::vector<Alien>::iterator it = aliens2.begin(); it != aliens2.end(); ++it)
	{
		graphics.render(alienTexture1, it->alienXPos, it->alienYPos);
	}
	// Aliens3
	for (std::vector<Alien>::iterator it = aliens3.begin(); it != aliens3.end(); ++it)
	{
		graphics.render(alienTexture1, it->alienXPos, it->alienYPos);
	}
	// Aliens4
	for (std::vector<Alien>::iterator it = aliens4.begin(); it != aliens4.end(); ++it)
	{
		graphics.render(alienTexture2, it->alienXPos, it->alienYPos);
	}
	// Aliens5
	for (std::vector<Alien>::iterator it = aliens5.begin(); it != aliens5.end(); ++it)
	{
		graphics.render(alienTexture2, it->alienXPos, it->alienYPos);
	}
	// Aliens6
	for (std::vector<Alien>::iterator it = aliens6.begin(); it != aliens6.end(); ++it)
	{
		graphics.render(alienTexture2, it->alienXPos, it->alienYPos);
	}
	// Aliens7
	for (std::vector<Alien>::iterator it = aliens7.begin(); it != aliens7.end(); ++it)
	{
		graphics.render(alienTexture2, it->alienXPos, it->alienYPos);
	}
	// Aliens8
	for (std::vector<Alien>::iterator it = aliens8.begin(); it != aliens8.end(); ++it)
	{
		graphics.render(alienTexture2, it->alienXPos, it->alienYPos);
	}

	SDL_RenderPresent(graphics.getRenderer());
}

void Game::clean()
{
	SDL_DestroyWindow(graphics.getWindow());
	SDL_DestroyRenderer(graphics.getRenderer());
	SDL_Quit();

	std::cout << "Bullet vector size: \n" << bullets.size() << std::endl;
	std::cout << "Aliens1 vector size: \n" << aliens1.size() << std::endl;
	std::cout << "Game Cleaned!\n";
}

bool Game::checkCollison(SDL_Rect a, SDL_Rect b)
{
	// Get left and right sides
	int leftA = a.x;
	int rightA = a.x + a.w;
	int leftB = b.x;
	int rightB = b.x + b.w;

	// Get top and bottom sides
	int topA = a.y;
	int bottomA = a.y + a.h;
	int topB = b.y;
	int bottomB = b.y + b.h;

	if (bottomA <= topB)
	{
		return false;
	}
	
	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	// if all tests were false
	return true;
}

