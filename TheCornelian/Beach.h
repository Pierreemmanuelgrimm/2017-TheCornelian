#pragma once
#include "Location.h"
class Beach : public Location
{
public:
	Beach();
	~Beach();

	std::string getString();
	int getHandle(int&);
};

