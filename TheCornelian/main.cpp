#include <Windows.h>
#include "MainGame.h"

int main(int argc, char** argv) {
	// ---  RUN GAME -----------------
	MainGame mainGame;
	mainGame.run();
	mainGame.~MainGame();
	return 0;
}
