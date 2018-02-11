#include "Location.h"

Location::Location()
{
}
Location::Location(int nid)
{
	id = nid;
}


Location::~Location()
{
}
void Location::setID(int x) {
	id = x;
}
int Location::getID() {
	return id;
}
std::string Location::getString() {
	return "";
}
int Location::getHandle(int& a) {
	return a;
}