//21127334 - Le Vu Ngan Lam
// Pham Tien Duc

#include <iostream>
#include "Common.h"
#include "Board.h"
#include "Game.h"

#define EASY 4
#define MEDIUM 6
#define HARD 8

int main()
{
	Common::setUpConsole();

	Game testingGame(EASY);
	testingGame.startGame();

	Sleep(5000);

	Common::clearConsole();
}
