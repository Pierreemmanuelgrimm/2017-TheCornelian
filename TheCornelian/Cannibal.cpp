#include "Cannibal.h"



Cannibal::Cannibal()
{
}
Cannibal::Cannibal(int ind, int level) {
	setName("Cannibal " + to_string(ind + 1));
	if (level == 0) level = (rand() % 4) + 1;
	setLevel(level);
	setExperience(0);

	setVitality(150 + (level - 1) * 50 * ((rand() % 3) + 1));
	setHealth(getMaxHealth());

	setEndurance(2000 + (level - 1) *  (rand() % 500));
	setEnergy(getMaxEnergy());

	setStrength(10 + level *  rand() % 4);
	setPerception(15 + level *  rand() % 5);
	setDexterity(15 + level *  rand() % 5);
	setArmor(5 + level *  rand() % 3);
	setTeam(2);
	setIsExhausted(0);
	setIsDead(0);
	setIsInvincible(0);
}


Cannibal::~Cannibal()
{
}
