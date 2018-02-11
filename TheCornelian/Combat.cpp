#include "Combat.h"

Combat::Combat() {
	_isVisible = 0;
}
Combat::Combat(string newIsVisible, vector<Mob*> team_A, vector<Mob*> team_B, TextTexture* nout) {
	out = nout;
	turn = 0;
	ind = 0;
	if (newIsVisible == "hidden") {
		_isVisible = 0;
	}
	else if (newIsVisible == "visible") {
		_isVisible = 1;
	}
	else {
		_isVisible = 0;
	}

	for (unsigned int x = 0; x < team_A.size(); x++) {
		if(team_A[x]->getName() != "") _mobs.push_back(team_A[x]);
	}
	for (unsigned int x = 0; x < team_B.size(); x++) {
		if (team_B[x]->getName() != "") _mobs.push_back(team_B[x]);
	}
	std::sort(_mobs.begin(), _mobs.end(), compareSpeeds);
	out->addStringEnd("Fight initialized,");
	out->addStringEnd("Turn Order :");
	for (unsigned int x = 0; x < _mobs.size(); x++) {
		out->addStringEnd(std::to_string(x + 1) +  ") " + _mobs[x]->getName() + " [" + std::to_string(_mobs[x]->getPerception()) + "]");
	}
}
Combat::~Combat() {

}
void Combat::fight() {
		if (ind == _mobs.size() || ind == 0) {
			turn++;
			out->addStringEnd("----------------------------");
			out->addStringEnd("Turn " + std::to_string(turn));
			ind = 0;
		}
		if (!(_mobs[ind]->getIsDead())) {
			if (_mobs[ind]->getIsExhausted()) {
				out->addStringEnd(_mobs[ind]->getName() + " is too exhausted to attack.");
			}
			else{
			Mob* target;
			target = (*_mobs[ind]).getTarget(_mobs);
			attack(_mobs[ind], target);
			}
		}
		ind++;
}

//bool operator<(const Mob* mob_1, const Mob* mob_2) {
//	return (*mob_1).getSpeed() > (*mob_2).getSpeed();
//}
bool Combat::getIsVisible() {
	return _isVisible; 
}
bool compareSpeeds(const Mob* a, const Mob* b) { 
	return ((*a).getPerception() > (*b).getPerception());
}
bool Combat::getTeamStatus(const vector<Mob*> team) {
	for (unsigned int x = 0; x < team.size(); x++) {
		if (!(team[x]->getIsDead() || team[x]->getIsExhausted())) return 1;
	}
	return 0;
}
void Combat::attack(Mob* attacker, Mob* defender) {
	std::string o = (*attacker).getName() + " leaps at " + (*defender).getName() + ", ";
	int lost_energy = -1 * (15 + 1.5 * attacker->getArmor() - 1 * attacker->getDexterity());
	if (lost_energy > 0) lost_energy = 0;
	attacker->addEnergy(lost_energy);
	if (defender->getIsInvincible()) {
		o += " his invincibility protects him from damage.";
	}
	else if (((rand() % 5)*(defender->getDexterity()) - (defender->getArmor())) > ((rand() % 4 + 2) * (attacker->getDexterity())))
	{
		o += "who dodges";
	}
	else
	{
		int damage = 5 + (rand() % (attacker->getStrength()/2)) + attacker->getStrength() - defender->getArmor();
		if (damage <= 0) {
			o += "who takes no damage";
		}
		else{
			o += "who takes " + std::to_string(damage) + " damage";
			defender->addHealth(-1 * damage);
			if (defender->getIsDead() == 1) {
				o += " and dies.";
				attacker->addExperience(defender->getXpReward());
			}
			else
			{
				//o += " and is left with  " + std::to_string(defender->getHealth()) + " HP.";
			}
		}
	}
	out->addStringEnd(o);
}