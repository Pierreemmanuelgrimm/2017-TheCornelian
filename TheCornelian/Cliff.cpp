#include "Cliff.h"



Cliff::Cliff() : Location(1)
{
}


Cliff::~Cliff()
{
}
std::string Cliff::getString() {
	return "Cliff";
}
int Cliff::getHandle(int& id) {
	return 0x10000010;
}
