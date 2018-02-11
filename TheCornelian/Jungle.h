#pragma once
#include "Location.h"
class Jungle : public Location
{
public:
	Jungle();
	~Jungle();

	std::string getString();
	int getHandle(int&);
};

