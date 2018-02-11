#include "Mob.h"

class Pirate : public Mob
{
public:
	Pirate();
	Pirate(int level);
	~Pirate();

	std::string createName();
};

