#pragma once
#include "Location.h"
class Plains : public Location
{
public:
	Plains();
	~Plains();

	std::string getString();
	int getHandle(int&);
};

