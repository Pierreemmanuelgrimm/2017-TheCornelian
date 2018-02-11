#include "PirateBase.h"



PirateBase::PirateBase() : Location(8)
{
}


PirateBase::~PirateBase()
{
}
std::string PirateBase::getString() {
	return "Pirate base";
}
int PirateBase::getHandle(int& id) {
	return 0x10000005;
}