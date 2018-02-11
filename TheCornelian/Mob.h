// Header == > Function Declarations

#ifndef MOB_H
#define MOB_H

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Item.h"
using namespace std;

class Mob {
public:
	//Default Constructor
	Mob();

	//Overload Constructor
	Mob(bool);
	Mob(string, int, int, int, bool,bool, int);

	//Destructor 
	~Mob();

	//Accesor Functions
	string getName() const;
	int getLevel() const;
	int getExperience() const;
	int getXpReward() const;

	int getHealth() const;
	int getMaxHealth() const;

	int getEnergy() const;
	int getMaxEnergy() const;

	int getStrength() const;
	int getPerception() const;
	int getDexterity() const;
	int getArmor() const;

	bool getIsExhausted() const;
	bool getIsDead() const;
	bool getIsInvincible() const;
	int getTeam() const;

	int xpForLevel() const;
	//getTeam - Returns team of Mob
	Mob* getTarget(vector<Mob*>) const;
	//getTarget - Returns the target's attack

	//Mutator Functions
	void setName(string);
	void setLevel(int);
	void addLevel();
	void addExperience(int);
	void setExperience(int);

	void setHealth(int);
	void addHealth(int);
	void setVitality(int);
	void addVitality(int);

	void setEnergy(int);
	void addEnergy(int);
	void setEndurance(int);
	void addEndurance(int);

	void setStrength(int);
	void addStrength(int);
	void setPerception(int);
	void addPerception(int);
	void setDexterity(int);
	void addDexterity(int);
	void setArmor(int);
	void addArmor(int);

	void setIsExhausted(bool);
	void setIsDead(bool);
	void setIsInvincible(bool);

	void setTeam(int);
	void kill();	
private:
	//Member Variables
	string _name;
	int _health;
	int _energy;

	int _level;
	int _experience;

	int _vitality;
	int _endurance;
	
	int _strength;
	int _perception;
	int _dexterity;
	int _armor;

	bool _isExhausted;
	bool _isDead;
	bool _isInvincible; 
	vector<Item> _inventory;

	int _team;

};
#endif