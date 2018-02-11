#include "ImageTexture.h"



ImageTexture::ImageTexture() : Texture()
{
}
ImageTexture::ImageTexture(int x, int y, int width, int height, SDL_Surface* nsurface) : Texture(x, y, width, height, { 0x00,0x00,0x00,0x00 })
{
	surface = nsurface;
}


ImageTexture::~ImageTexture()
{
}

void ImageTexture::render(SDL_Renderer* renderer) {
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	//SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xFF, 0x00, 0xFF));
	//SDL_Rect renderQuad = { getX(), getY(), getWidth(), getHeight() };
	SDL_Rect renderQuad;
	renderQuad.x = getX();
	renderQuad.y = getY();
	SDL_QueryTexture(texture, NULL, NULL, &renderQuad.w, &renderQuad.h);
	SDL_RenderCopyEx(renderer, texture, NULL, &renderQuad,NULL,NULL,SDL_FLIP_NONE);

	SDL_DestroyTexture(texture);
	texture = NULL;
}
