#pragma once
#include "Location.h"
class Mountain : public Location
{
public:
	Mountain();
	~Mountain();

	std::string getString();
	int getHandle(int&);
};

