// Header

#ifndef COMBAT_H
#define COMBAT_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include "Mob.h"
#include "TextTexture.h"
using namespace std;

class Combat {
public:
	//Default Constructor
	Combat();

	//Overload Constructor
	Combat(string, vector<Mob*>, vector<Mob*>, TextTexture*);

	//Destructor 
	~Combat();

	//Accesor Functions
	bool getIsVisible();
		//getIsVisible - Returns isVisible
	void fight();
		//fight - Opposes two teams
		//@param 
	
	bool getTeamStatus(const vector<Mob*>);
		//getTeamStatus - Gets the status of a team, if at least one is alive it will be alive
		//@param vector<Mob>& - A vector of mobs passed by reference
	void attack(Mob*, Mob*);
		//attack - Makes one Mob attack another Mob
		//@param Mob*,Mob* - Two pointers to Mobs
private:
	bool _isVisible;
	vector<Mob*> _mobs;
	TextTexture* out;
	unsigned int turn;
	unsigned int ind;
};
bool compareSpeeds(const Mob*, const Mob*);
//compareSpeeds - Compares the speeds of two Mobs
//@param Mob*, Mob* - Points to two Mobs
#endif
