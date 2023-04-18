#include "graphics.h"
#include "SDL_image.h"


Graphics::Graphics()
{
		this->_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, 0);

		if (this->_window) {
			std::cout << "Window Created\n";
		}

		this->_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
		if (this->_renderer) {
			SDL_SetRenderDrawColor(this->_renderer, 0, 0, 0, 0);
			std::cout << "Renderer Created\n";
		}

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
	}

}

SDL_Texture* Graphics::loadMedia(std::string filepath)
{
	// Final texture
	SDL_Texture* newTexture = NULL;

	// Load surface
	SDL_Surface* loadedSurface = IMG_Load(filepath.c_str());
	
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", filepath.c_str(), IMG_GetError());
	}
	else
	{
		newTexture = SDL_CreateTextureFromSurface(this->_renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", filepath.c_str(), SDL_GetError());
		}
		// Delete surface
		SDL_FreeSurface(loadedSurface);
	}
	
	return newTexture;
}


void Graphics::blitTexture(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle)
{
	SDL_RenderCopy(this->_renderer, texture, sourceRectangle, destinationRectangle);
}

SDL_Rect Graphics::getSize(SDL_Texture* texture) {
	SDL_Rect size{};
	SDL_QueryTexture(texture, NULL, NULL, &size.w, &size.h);
	return size;
}

void Graphics::render(SDL_Texture* texture, int xpos, int ypos)
{
	SDL_Rect srcRect = getSize(texture);
	SDL_Rect destRect = srcRect;
	destRect.x = xpos;
	destRect.y = ypos;

	blitTexture(texture, &srcRect, &destRect);
}

SDL_Renderer* Graphics::getRenderer()
{
	return this->_renderer;
}

SDL_Window* Graphics::getWindow()
{
	return this->_window;
}