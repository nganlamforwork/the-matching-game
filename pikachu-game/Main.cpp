//21127334 - Le Vu Ngan Lam
// Pham Tien Duc

#include <iostream>
#include "Common.h"
#include "Board.h"
#include "Game.h"

#define EASY_ 4
#define MEDIUM_ 6
#define HARD_ 8

int main()
{
	Common::setUpConsole();

	Game testingGame(EASY_);
	testingGame.startGame();

	Sleep(5000);

	Common::clearConsole();
}
