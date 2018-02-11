#pragma once
#include "Location.h"
class DeepJungle : public Location
{
public:
	DeepJungle();
	~DeepJungle();

	std::string getString();
	int getHandle(int&);
};

