#include "G_Image.h"



G_Image::G_Image(){
	texture = nullptr;
	dst = { 0,0,0,0 };
	flip = SDL_FLIP_NONE;
}
G_Image::G_Image(SDL_Texture* text) {
	texture = text;
	SDL_QueryTexture(texture, NULL, NULL, &dst.w, &dst.h);
	flip = SDL_FLIP_NONE;
}

G_Image::~G_Image(){
}
void G_Image::render(SDL_Renderer* rend) {
	SDL_RenderCopyEx(rend, texture, clip, &dst, 0, NULL, flip);
}
