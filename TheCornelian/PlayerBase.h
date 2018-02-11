#pragma once
#include "Location.h"
class PlayerBase : public Location
{
public:
	PlayerBase();
	~PlayerBase();

	std::string getString();
	int getHandle(int&);
};

