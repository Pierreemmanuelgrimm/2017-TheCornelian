#include "PlayerHealthBox.h"



PlayerHealthBox::PlayerHealthBox() : RectTexture()
{
}
PlayerHealthBox::PlayerHealthBox(int x, int y, int nwidth, int nheight, Mob* nplayer, SDL_Color color, std::string nstat) : RectTexture(x,y,nwidth,nheight,color) {
	player = nplayer;
	stat = nstat;
}


PlayerHealthBox::~PlayerHealthBox()
{
}
int PlayerHealthBox::getWidth() {
	int w = 0;
	if (stat == "health") {
		w = (Texture::getWidth()*(*player).getHealth()) / (*player).getMaxHealth();
	}
	if (stat == "energy") {
		w = (Texture::getWidth()*(*player).getEnergy()) / (*player).getMaxEnergy();
	}
	return w;
}
SDL_Color PlayerHealthBox::getColor() {
	if (stat == "health") {
		if (((*player).getMaxHealth() - (*player).getHealth()) > 0.70 * (*player).getMaxHealth()) {

			return{ 0xFF,0x00,0x00,0xFF };
		}
		else {
			return{ 0,170,0 };
		}
	}
	if (stat == "energy") {
		return{ 0x9C,0x9C,0x9C };
	}
	return { 0xFF,0x00,0x00,0xFF };
}
