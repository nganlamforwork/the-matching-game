//21127334 - Le Vu Ngan Lam
//21127598 - Pham Tien Duc

#include <iostream>
#include "Common.h"
#include "Menu.h"
#include "Game.h"
#include "Node.h"
#include "LinkedList.h"

int main()
{
	Common::setUpConsole(18);


	/*Game testingGame(EASY);
	testingGame.startGame();*/
	Menu testingMenu;
	testingMenu.renderMainScreen();

	/*LinkedList testLink;
	Node* tmp = new Node('A', 0, 0, 0);
	testLink.addTail(tmp);
	delete tmp;
	tmp = new Node('B', 0, 0, 0);
	testLink.addTail(tmp);
	delete tmp;
	tmp = new Node('C', 0, 0, 0);
	testLink.addTail(tmp);
	delete tmp;
	tmp = new Node('D', 0, 0, 0);
	testLink.addTail(tmp);
	delete tmp;
	testLink.removePos(1);
	testLink.removePos(2);*/
	Sleep(5000);

	Common::clearConsole();
}
