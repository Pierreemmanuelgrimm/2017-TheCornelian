// Function Definitions

#include "Mob.h"

Mob::Mob() {
	_name = "Default Mob";
	_level = 1;
	_experience = 0;

	_vitality = 1;
	_health = 1;

	_endurance = 1;
	_energy = 1;

	_strength = 1;
	_perception = 1;
	_dexterity = 1;
	_armor = 1;

	_team = 0;
	_isExhausted = 0;
	_isDead = true;
	_isInvincible = true;

}
Mob::Mob(bool a) {
	_name = "Default Mob";
	_level = 1;
	_experience = 0;

	_vitality = (rand() % 50) + 100;
	if (!a) _vitality += 200;
	_health = _vitality;
	
	_endurance = (rand() % 250) + 1000;
	_energy = _endurance;

	_strength = (rand() % 13) + 7;
	_perception = (rand() % 13) + 7;
	_dexterity = (rand() % 13) + 7;
	_armor = (rand() % 13) + 7;

	_team = a;
	_isExhausted = 0;
	_isDead = false;
	_isInvincible = false;

}
Mob::Mob(string newName, int newHealth, int newEnergy, int newSpeed, bool newIsDead, bool newIsInvincible, int newTeam) {
	_name = newName;
	_health = newHealth;
	_vitality = newHealth;
	_level = 1;
	_experience = 0;
	_energy = newEnergy;
	_perception = newSpeed;
	_isDead = newIsDead;
	_isInvincible = newIsInvincible;
	_team = newTeam;

}
Mob::~Mob() {

}
string Mob::getName() const {
	return _name;
}
int Mob::getHealth() const {
	return _health;
}
int Mob::getMaxHealth() const {
	return _vitality;
}
int Mob::getLevel() const {
	return _level;
}
int Mob::getExperience() const{
	return _experience;
}
int Mob::getXpReward() const {
	return 50 + getMaxHealth() + getDexterity() + getStrength();
}
int Mob::getEnergy() const {
	return _energy;
}
int Mob::getMaxEnergy() const {
	return _endurance;
}
int Mob::getStrength() const {
	return _strength;
}
int Mob::getPerception() const {
	return _perception;
}
int Mob::getDexterity() const {
	return _dexterity;
}
int Mob::getArmor() const {
	return _armor;
}
bool Mob::getIsDead() const {
	return _isDead;
}
bool Mob::getIsExhausted() const {
	return _isExhausted;
}
bool Mob::getIsInvincible() const{
	return _isInvincible;
}
int Mob::getTeam() const {
	return _team;
}
Mob* Mob::getTarget(vector<Mob*> mobList) const{
	Mob* v = new Mob();
	bool assigned = 0;
	for (unsigned int x = 0; x < mobList.size(); x++) {
		if (mobList[x]->getTeam() != _team && !(mobList[x]->getIsDead())){
			if (assigned == 0) {
				v = mobList[x];
				assigned = 1;
			}
			else {
				if ((mobList[x]->getHealth()/ mobList[x]->getStrength()) < (v->getHealth() / v->getStrength())) {
				v = mobList[x];
				}
			}
		}
	}
	return v;
}
void Mob::setName(string newName) {
	_name = newName;
}
void Mob::setHealth(int newHealth) {
	_health = newHealth;
}
void Mob::addHealth(int d) {
	if (getIsInvincible() && d < 0) return; // If immortal and taking damage
	_health += d;
	if (_health <= 0) {
		kill();
	}
}
void Mob::setVitality(int newVitality) {
	_vitality = newVitality;
}
void Mob::addVitality(int d) {
	_vitality += d;
}
void Mob::setEnergy(int newEnergy) {
	_energy = newEnergy;
}
void Mob::addEnergy(int d) {
	_energy += d;
	if (_energy <= 0 && !_isExhausted) {
		_energy = 0;
		_isExhausted = 1;
	}
}
void Mob::setEndurance(int newEndurance) {
	_endurance = newEndurance;
}
void Mob::addEndurance(int d) {
	_endurance += d;
}

void Mob::setLevel(int newLevel) {
	_level = newLevel;
}
void Mob::addLevel() {
	_level++;
	_strength++;
	_perception++;
	_dexterity++;
	_armor++;
	_vitality += _vitality/10;
	_health = _vitality;
	_endurance += _endurance/10;
	_energy = _endurance;
}
int Mob::xpForLevel() const{
	int nxtLevel = _level *_level * 100;
	return nxtLevel;
}
void Mob::addExperience(int xp) {
	_experience += xp;
	int nxtLevel = xpForLevel();
	if (_experience >= nxtLevel) {
		addLevel();
		_experience -= nxtLevel;
	}
	
}
void Mob::setExperience(int xp) {
	_experience = xp;
}
void Mob::setStrength(int newStrength) {
	_strength = newStrength;
}
void Mob::addStrength(int d) {
	_strength += d;
}
void Mob::setPerception(int newSpeed) {
	_perception = newSpeed;
}
void Mob::addPerception(int d) {
	_perception += d;
}
void Mob::setDexterity(int newDex) {
	_dexterity = newDex;
}
void Mob::addDexterity(int d) {
	_dexterity += d;
}
void Mob::setArmor(int newArmor) {
	_armor = newArmor;
}
void Mob::addArmor(int d) {
	_armor += d;
}
void Mob::setIsExhausted(bool newIsExhausted) {
	_isExhausted = newIsExhausted;
}
void Mob::setIsDead(bool newIsDead) {
	_isDead = newIsDead;
}
void Mob::setIsInvincible(bool newIsInvincible) {
	_isInvincible = newIsInvincible;
}
void Mob::setTeam(int newTeam) {
	_team = newTeam;
}
void Mob::kill() {
	_health = 0;
	setIsDead(true);
	setIsInvincible(true);
}