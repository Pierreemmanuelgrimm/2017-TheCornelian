#pragma once
#include "Texture.h"
class ImageTexture : public Texture
{
public:
	//Constructor
	ImageTexture();
	ImageTexture(int x, int y, int width, int height, SDL_Surface* nsurface);

	//Destructor
	~ImageTexture();

	//Access methods
	void render(SDL_Renderer* renderer);

private:
	SDL_Surface* surface;
};

