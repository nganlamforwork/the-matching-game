//21127334 - Le Vu Ngan Lam
// Pham Tien Duc

#include <iostream>
#include "Common.h"
#include "Board.h"
#include "Game.h"
#include "Menu.h"

int main()
{
	Common::setUpConsole();

	/*Game testingGame(EASY);
	testingGame.startGame();*/
	Menu testingMenu;
	testingMenu.renderMainScreen();

	Sleep(5000);

	Common::clearConsole();
}
