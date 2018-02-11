#include "Animal.h"


Animal::Animal() {

}
Animal::Animal(int ind, int level)
{
	if (ind >= 0) {
		setName("Wild Beast " + to_string(ind + 1));
	}
	else {
		setName("Wild Beast");
	}
	if (level == 0) level = (rand() % 4) + 1;
	setLevel(level);
	setExperience(0);

	setVitality(50 + (level - 1) *  25 * ((rand() % 2) + 1));
	setHealth(getMaxHealth());

	setEndurance(2000 + (level - 1) *  (rand() % 500));
	setEnergy(getMaxEnergy());

	setStrength(7 + level *  rand() % 3);
	setPerception(7 + level *  rand() % 3);
	setDexterity(7 + level *  rand() % 3);
	setArmor(7 + level *  rand() % 3);
	setTeam(3);
	setIsExhausted(0);
	setIsDead(0);
	setIsInvincible(0);
}


Animal::~Animal()
{
}
