#include "Beach.h"



Beach::Beach() : Location(2)
{
}


Beach::~Beach()
{
}
std::string Beach::getString() {
	return "Beach";
}
int Beach::getHandle(int& id) {
	int rnd = rand() % 100;
	if (rnd <= 2) {
		return 0x10000006; // 3%
	}
	else if (rnd <= 9) {
		return 0x10000007; // 7%
	}
	else if (rnd <= 24) {
		return 0x10000008; // 15%
	}
	else if (rnd <= 89) {
		return 0x10000010; // 65%
	}
	else if (rnd <= 99) {
		return 0x11020002; // 10%
	}
	return 0x10000010; //Default
}
