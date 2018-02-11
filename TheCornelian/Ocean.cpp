#include "Ocean.h"



Ocean::Ocean() : Location(0)
{
}


Ocean::~Ocean()
{
}
std::string Ocean::getString() {
	return "Ocean";
}
int Ocean::getHandle(int& id) {
	return 0x10000010;
}