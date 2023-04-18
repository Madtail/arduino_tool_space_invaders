#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include "globals.h"
#include <iostream>

class Graphics
{
public:
	Graphics();

	// Load image function
	SDL_Texture* loadMedia(std::string filepath);

	// Draw image on specified area of the screen
	void blitTexture(SDL_Texture* texture, SDL_Rect* sourceRectangle, SDL_Rect* destinationRectangle);

	// Get the width and height of a texture
	SDL_Rect getSize(SDL_Texture* texture);

	void render(SDL_Texture* texture, int xpos, int ypos);

	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;
};


#endif // GRAPHICS_H

