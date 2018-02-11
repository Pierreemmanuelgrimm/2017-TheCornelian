#include "PlayerBase.h"



PlayerBase::PlayerBase() : Location(9)
{
}


PlayerBase::~PlayerBase()
{
}
std::string PlayerBase::getString() {
	return "Base";
}
int PlayerBase::getHandle(int& id) {
	return 0x10000010;
}
