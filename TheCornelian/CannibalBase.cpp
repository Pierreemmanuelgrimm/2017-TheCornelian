#include "CannibalBase.h"



CannibalBase::CannibalBase() : Location(7)
{
}


CannibalBase::~CannibalBase()
{
}
std::string CannibalBase::getString() {
	return "Cannibal base";
}
int CannibalBase::getHandle(int& id) {
	return 0x10000009;
}