#pragma once
#include "Location.h"
#include "Ocean.h"
#include "Cliff.h"
#include "Beach.h"
#include "Plains.h"
#include "Jungle.h"
#include "Mountain.h"
#include "DeepJungle.h"
#include "CannibalBase.h"
#include "PirateBase.h"
#include "PlayerBase.h"
#include <vector>
class Map
{
public:
	Map();
	
	~Map();
	void init();
	Location* getLocation(int, int);
	void setStartingLocation(int&, int&);

	int getLocationHandle(int, int, int&);
private:
	std::vector<std::vector<Location*> > map;
};

