#pragma once
#include "Location.h"
class PirateBase : public Location
{
public:
	PirateBase();
	~PirateBase();

	std::string getString();
	int getHandle(int&);
};

