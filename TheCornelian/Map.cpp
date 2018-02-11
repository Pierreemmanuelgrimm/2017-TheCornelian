#include "Map.h"



Map::Map()
{
}


Map::~Map()
{
}
Location* Map::getLocation(int x, int y) {
	return map[y][x];
}
void Map::setStartingLocation(int& mx, int& my) {
	for (unsigned int j = 0; j < map.size(); j++) {
		for (unsigned int i = 0; i < map[0].size(); i++) {
			if ((*map[j][i]).getID() == 9) {
				mx = i;
				my = j;
				return;
			}
		}
	}
}
void Map::init() {
	int mapGrid[10][10] = 
	{
		{ 0,0,0,0,0,0,0,0,0,0 },
		{ 0,0,1,1,1,2,2,2,8,0 },
		{ 0,1,6,6,7,6,4,3,2,0 },
		{ 0,2,4,6,6,6,5,5,2,0 },
		{ 0,2,3,4,4,4,5,5,1,0 },
		{ 0,2,3,3,3,4,4,4,2,0 },
		{ 0,1,3,3,3,4,4,9,2,0 },
		{ 0,0,1,2,2,1,1,2,2,0 },
		{ 0,0,0,0,0,0,0,0,0,0 }
	};
	Ocean* ocean = new Ocean(); //0
	Cliff* cliff = new Cliff(); // 1
	Beach* beach = new Beach(); // 2
	Plains* plains = new Plains(); // 3
	Jungle* jungle = new Jungle(); // 4
	Mountain* mountain = new Mountain(); // 5
	DeepJungle* deepjungle = new DeepJungle(); // 6
	CannibalBase* cannicalbase = new CannibalBase(); //7
	PirateBase* piratebase = new PirateBase(); // 8
	PlayerBase* playerbase = new PlayerBase(); // 9

	std::vector<Location*> t;
	for (int i = 0; i < 10; i++) {
		t.clear();
		for (int j = 0; j < 10; j++) {
			switch(mapGrid[i][j]) {
			case 0:
				t.push_back(ocean);
				break;
			case 1:
				t.push_back(cliff);
				break;
			case 2:
				t.push_back(beach);
				break;
			case 3:
				t.push_back(plains);
				break;
			case 4:
				t.push_back(jungle);
				break;
			case 5:
				t.push_back(mountain);
				break;
			case 6:
				t.push_back(deepjungle);
				break;
			case 7:
				t.push_back(cannicalbase);
				break;
			case 8:
				t.push_back(piratebase);
				break;
			case 9:
				t.push_back(playerbase);
				break;
			}

		}
		map.push_back(t);
	}
}
int Map::getLocationHandle(int x, int y, int& id) {
	return map[y][x]->getHandle(id);
}