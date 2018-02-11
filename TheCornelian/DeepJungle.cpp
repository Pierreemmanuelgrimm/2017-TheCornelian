#include "DeepJungle.h"



DeepJungle::DeepJungle() : Location(6)
{
}


DeepJungle::~DeepJungle()
{
}
std::string DeepJungle::getString() {
	return "Deep Jungle";
}
int DeepJungle::getHandle(int& id) {
	int rnd = rand() % 100;
	if (rnd <= 19) {
		return 0x10000011; // 20%
	}
	else if (rnd <= 44) {
		return 0x10000013; // 25%
	}
	else if (rnd <= 49) {
		return 0x10000014; // 5%
	}
	else if (rnd <= 54) {
		return 0x10000016; // 5%
	}
	else if (rnd <= 64) {
		return 0x11010001; // 10%
	}
	else if (rnd <= 84) {
		return 0x11010003; // 20%
	}
	else if (rnd <= 99) {
		return 0x11010004; // 15%
	}
	return 0x10000010; //Default
}
