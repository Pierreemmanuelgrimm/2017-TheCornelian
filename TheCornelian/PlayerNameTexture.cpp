#include "PlayerNameTexture.h"



PlayerNameTexture::PlayerNameTexture():TextTexture(){
}
PlayerNameTexture::PlayerNameTexture(int x, int y, int width, int height, Mob* nplayer, SDL_Color color, TTF_Font* nfont):TextTexture(x, y, width, height, "def", color, nfont) {
	player = nplayer;
}

PlayerNameTexture::~PlayerNameTexture(){
}
std::string PlayerNameTexture::getString() {
	return ("Name: " + (*player).getName());
}
