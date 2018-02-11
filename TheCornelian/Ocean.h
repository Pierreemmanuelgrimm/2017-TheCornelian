#pragma once
#include "Location.h"
class Ocean : public Location
{
public:
	Ocean();
	~Ocean();

	std::string getString();
	int getHandle(int&);
};