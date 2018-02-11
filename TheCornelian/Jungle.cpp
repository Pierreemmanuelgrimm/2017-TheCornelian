#include "Jungle.h"



Jungle::Jungle() : Location(4)
{
}


Jungle::~Jungle()
{
}
std::string Jungle::getString() {
	return "Jungle";
}
int Jungle::getHandle(int& id) {
	int rnd = rand() % 100;
	if (rnd <= 2) {
		return 0x10000006; // 3%
	}
	else if (rnd <= 4) {
		return 0x10000008; // 2%
	}
	else if (rnd <= 14) {
		return 0x10000010; // 10%
	}
	else if (rnd <= 25) {
		return 0x10000011; // 1%
	}
	else if (rnd <= 29) {
		return 0x10000012; // 5%
	}
	else if (rnd <= 54) {
		return 0x10000013; // 25%
	}
	else if (rnd <= 59) {
		return 0x10000014; // 5%
	}
	else if (rnd <= 64) {
		return 0x10000016; // 5%
	}
	else if (rnd <= 74) {
		return 0x11010001; // 10%
	}
	else if (rnd <= 89) {
		return 0x11010003; // 15%
	}
	else if (rnd <= 94) {
		return 0x11010004; // 5%
	}
	else if (rnd <= 98) {
		return 0x11020001; // 4%
	}
	else if (rnd <= 99) {
		return 0x11020002; // 1%
	}
	return 0x10000010; //Default
}