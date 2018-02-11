#pragma once
#include "G_Renderable.h"
#include "G_BitmapFont.h"
#include <string>
class G_Text : public G_Renderable
{
public:
	G_Text();
	G_Text(std::string, G_BitmapFont*);
	G_Text(std::string, int x, int y,G_BitmapFont*);
	G_Text(std::string, int x, int y, float scale, G_BitmapFont*);
	~G_Text();

	G_BitmapFont*  font;
	std::string text;
	float scale;

	void render(SDL_Renderer* renderer);
};

