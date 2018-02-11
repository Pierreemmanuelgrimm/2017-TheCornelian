#include "Mountain.h"



Mountain::Mountain() : Location(5)
{
}


Mountain::~Mountain()
{
}
std::string Mountain::getString() {
	return "Mountain";
}
int Mountain::getHandle(int& id) {
	int rnd = rand() % 100;
	if (rnd <= 9) {
		return 0x10000010; // 10%
	}
	else if (rnd <= 29) {
		return 0x10000014; // 20%
	}
	else if (rnd <= 34) {
		return 0x10000015; // 5%
	}
	else if (rnd <= 54) {
		return 0x10000016; // 20%
	}
	else if (rnd <= 64) {
		return 0x11010001; // 10%
	}
	else if (rnd <= 94) {
		return 0x11010002; // 30%
	}
	else if (rnd <= 99) {
		return 0x11020001; // 5%
	}
	return 0x10000010; //Default
}
