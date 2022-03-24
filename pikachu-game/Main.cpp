//21127334 - Le Vu Ngan Lam
//21127598 - Pham Tien Duc

#include <iostream>
#include "Common.h"
#include "Menu.h"
#include "Game.h"
#include "Node.h"

int main()
{
	Common::setUpConsole(18);

	/*Game testingGame(EASY);
	testingGame.startGame();*/
	Menu testingMenu;
	testingMenu.renderMainScreen();

	Sleep(5000);

	Common::clearConsole();
}
