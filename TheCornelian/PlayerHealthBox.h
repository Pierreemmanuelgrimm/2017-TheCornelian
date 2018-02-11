#pragma once
#include "RectTexture.h"
#include "Mob.h"
class PlayerHealthBox : public RectTexture
{
public:
	//Constructor
	PlayerHealthBox();
	PlayerHealthBox(int x, int y, int nwidth, int nheight, Mob* player, SDL_Color color, std::string nstat);
	//Destructor
	~PlayerHealthBox();

	int getWidth();
	SDL_Color getColor();
private:
	Mob* player;
	std::string stat;

};

