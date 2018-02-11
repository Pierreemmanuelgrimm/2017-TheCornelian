#pragma once
#include "Location.h"
class Cliff : public Location
{
public:
	Cliff();
	~Cliff();

	std::string getString();
	int getHandle(int&);
};

