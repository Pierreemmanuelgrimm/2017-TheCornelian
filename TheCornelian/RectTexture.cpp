#include "RectTexture.h"

RectTexture::RectTexture() : Texture(){
}
RectTexture::RectTexture(int x, int y, int nwidth, int nheight, SDL_Color color) : Texture(x, y, nwidth, nheight, color) {
}

RectTexture::~RectTexture(){
}

void RectTexture::render(SDL_Renderer* renderer) {
	if (!getVisible()) return;
	SDL_SetRenderDrawColor(renderer, getR(), getG(), getB(), getA());
	SDL_Rect rect = { getX(), getY(), getWidth(), getHeight() };
	SDL_RenderFillRect(renderer, &rect);
}
