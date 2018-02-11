#pragma once
#include "TextTexture.h"
#include "Mob.h"
class PlayerHealthText : public TextTexture
{
public:
	//Constructor
	PlayerHealthText();
	PlayerHealthText(int, int, int, int, Mob*, SDL_Color, TTF_Font*, std::string nstat);
	//Destructor
	~PlayerHealthText();

	//Accessor functions
	std::string getString();

private:
	Mob* player;
	std::string stat;
};

