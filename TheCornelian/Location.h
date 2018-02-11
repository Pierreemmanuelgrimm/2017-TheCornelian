#pragma once
#include <string>
class Location
{
public:
	Location();
	Location(int);
	~Location();

	//Accessor functions
	virtual std::string getString();
	virtual int getHandle(int&);
	void setID(int);
	int getID();


private:
	int id;
};

