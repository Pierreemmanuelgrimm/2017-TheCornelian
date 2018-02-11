#include "Pirate.h"



Pirate::Pirate()
{
}
Pirate::Pirate(int level){
	setName(createName());
	if (level == 0) level = (rand() % 4) + 1;
	setLevel(level);
	setExperience(0);

	setVitality(200 + (level - 1) * 50 * ((rand() % 3) + 1));
	setHealth(getMaxHealth());

	setEndurance(1000 + (level - 1) *  (rand() % 250));
	setEnergy(getMaxEnergy());

	setStrength(15 + level *  rand() % 5);
	setPerception(5 + level *  rand() % 3);
	setDexterity(10 + level *  rand() % 4);
	setArmor(15 + level *  rand() % 5);
	setTeam(1);
	setIsExhausted(0);
	setIsDead(0);
	setIsInvincible(0);
}

Pirate::~Pirate()
{
}
std::string Pirate::createName() {
	std::string name;
	int a = rand() % 19;
	switch (a) {
	case 0:
		name += "Ol' ";
		break;
	case 1:
		name += "Stinky ";
		break;
	case 2:
		name += "Creeps ";
		break;
	case 3:
		name += "One Eye ";
		break;
	case 4:
		name += "Captain ";
		break;
	case 5:
		name += "Fishy ";
		break;
	case 6:
		name += "Rogue ";
		break;
	case 7:
		name += "Sharkbait ";
		break;
	case 8:
		name += "Red ";
		break;
	case 9:
		name += "Sticky ";
		break;
	case 10:
		name += "Ghost ";
		break;
	case 11:
		name += "Whale ";
		break;
	case 12:
		name += "Flying ";
		break;
	case 13:
		name += "Cutlass ";
		break;
	case 14:
		name += "King ";
		break;
	case 15:
		name += "Ironhook ";
		break;
	case 16:
		name += "Mad ";
		break;
	case 17:
		name += "Ruthless ";
		break;
	case 18:
		name += "Jean ";
		break;
	}
	int b = rand() % 19;
	switch (b) {
	case 0:
		name += "Lagoon ";
		break;
	case 1:
		name += "Barnacle ";
		break;
	case 2:
		name += "Creepy ";
		break;
	case 3:
		name += "Plank ";
		break;
	case 4:
		name += "Slappy ";
		break;
	case 5:
		name += "Beard ";
		break;
	case 6:
		name += "Hook ";
		break;
	case 7:
		name += "Crabbe ";
		break;
	case 8:
		name += "Blubber ";
		break;
	case 9:
		name += "Broom ";
		break;
	case 10:
		name += "Treasure ";
		break;
	case 11:
		name += "One-Ear ";
		break;
	case 12:
		name += "Claw ";
		break;
	case 13:
		name += "Parrot ";
		break;
	case 14:
		name += "Flag ";
		break;
	case 15:
		name += "Stubbs ";
		break;
	case 16:
		name += "Gutt ";
		break;
	case 17:
		name += "Von ";
		break;
	case 18:
		name += "Swamp ";
		break;
	}
	int c = rand() % 19;
	switch (c) {
	case 0:
		name += "Sea ";
		break;
	case 1:
		name += "Joe ";
		break;
	case 2:
		name += "Pants ";
		break;
	case 3:
		name += "Swashbuckler ";
		break;
	case 4:
		name += "McGee ";
		break;
	case 5:
		name += "Legs ";
		break;
	case 6:
		name += "Smuggler ";
		break;
	case 7:
		name += "Fishhawk ";
		break;
	case 8:
		name += "Jack ";
		break;
	case 9:
		name += "Moonscar ";
		break;
	case 10:
		name += "Feathersword ";
		break;
	case 11:
		name += "Rat Breath ";
		break;
	case 12:
		name += "Skurvy ";
		break;
	case 13:
		name += "Sea Rat ";
		break;
	case 14:
		name += "Silver ";
		break;
	case 15:
		name += "Slag ";
		break;
	case 16:
		name += "Turner ";
		break;
	case 17:
		name += "of the Sea ";
		break;
	case 18:
		name += "Jambe de Bois ";
		break;
	}
	return name;
}
