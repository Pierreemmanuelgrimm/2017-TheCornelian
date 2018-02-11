#pragma once
#include "G_Renderable.h"
#include <string>
class G_Image : public G_Renderable
{
public:
	G_Image();
	G_Image(SDL_Texture* text);
	~G_Image();
	void render(SDL_Renderer*);

	SDL_Texture* texture; // Texture source
	SDL_Rect* clip; // Sub-section of texture to draw
	SDL_RendererFlip flip;
};

