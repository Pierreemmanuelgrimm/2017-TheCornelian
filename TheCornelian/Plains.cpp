#include "Plains.h"



Plains::Plains() : Location(3)
{
}


Plains::~Plains()
{
}
std::string Plains::getString() {
	return "Plains";
}
int Plains::getHandle(int& id) {
	int rnd = rand() % 100;
	if(rnd <= 34){
		return 0x10000010; // 35%
	}else if(rnd <= 44){
		return 0x10000012; // 10%
	}else if(rnd <= 49){
		return 0x10000013; // 5%
	}else if(rnd <= 50){
		return 0x10000014; // 1%
	}else if(rnd <= 65){
		return 0x10000015; // 15%
	}else if(rnd <= 75){
		return 0x10000016; // 10%
	}else if(rnd <= 76){
		return 0x11010001; // 1%
	}else if(rnd <= 86){
		return 0x11010003; // 10%
	}else if(rnd <= 96){
		return 0x11020001; // 10%
	}else if(rnd <= 99){
		return 0x11020002; // 3%
	}
	return 0x10000010; //Default
}