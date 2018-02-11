#include "PlayerHealthText.h"

PlayerHealthText::PlayerHealthText():TextTexture(){
}
PlayerHealthText::PlayerHealthText(int x, int y, int width, int height, Mob* nplayer, SDL_Color color, TTF_Font* nfont, std::string nstat) : TextTexture(x, y, width, height, "def", color, nfont){
	player = nplayer;
	stat = nstat;
}


PlayerHealthText::~PlayerHealthText(){
}
std::string PlayerHealthText::getString() {
	std::string c = "";
	if (stat == "health") {
		std::string a = to_string((*player).getHealth());
		std::string b = to_string((*player).getMaxHealth());
		c =  "HP: " + a + "/" + b;
	}
	else if (stat == "energy") {
		std::string a = to_string((*player).getEnergy());
		std::string b = to_string((*player).getMaxEnergy());
		c =  "E: " + a + "/" + b;
	}
	else if (stat == "level") {
		c = "Level: " + to_string(player->getLevel());
	}
	else if (stat == "experience") {
		c = "XP: " + to_string(player->getExperience()) + "/" + to_string(player->xpForLevel());
	}
	else if (stat == "strength") {
		c = "STR: " + to_string(player->getStrength());
	}
	else if (stat == "perception") {
		c = "PER: " + to_string(player->getPerception());
	}
	else if (stat == "dexterity") {
		c = "DEX: " + to_string(player->getDexterity());
	}
	else if (stat == "armor") {
		c = "AR: " + to_string(player->getArmor());
	}
	return c;
}
