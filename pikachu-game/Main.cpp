//21127334 - Le Vu Ngan Lam
//21127598 - Pham Tien Duc

#include <iostream>
#include "Common.h"
#include "Board.h"
#include "Game.h"
#include "Menu.h"

int main()
{
	Common::setUpConsole(18);

	/*Game testingGame(EASY);
	testingGame.startGame();*/
	Menu testingMenu;
	testingMenu.renderMainScreen();

	Sleep(50000000);

	Common::clearConsole();
}
