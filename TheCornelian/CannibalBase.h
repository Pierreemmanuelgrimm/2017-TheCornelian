#pragma once
#include "Location.h"
class CannibalBase : public Location
{
public:
	CannibalBase();
	~CannibalBase();

	std::string getString();
	bool isAccessible();
	int getHandle(int&);
};

