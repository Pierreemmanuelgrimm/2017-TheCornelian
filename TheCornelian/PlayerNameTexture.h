#pragma once
#include "TextTexture.h"
#include "Mob.h"
class PlayerNameTexture : public TextTexture
{
public:
	//Default Constructor
	PlayerNameTexture();

	PlayerNameTexture(int x, int y, int width, int height, Mob* player, SDL_Color color, TTF_Font* nfont);

	//Default Desctructor
	~PlayerNameTexture();

	//Accessor functions
	std::string getString();
private:
	Mob* player;
	std::string stat;
};

