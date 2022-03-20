//21127334 - Le Vu Ngan Lam
// Pham Tien Duc

#include <iostream>
#include "Common.h"
#include "Board.h"

int main()
{
	Common::setUpConsole();

	Board testingBoard(6);
	testingBoard.drawBoard();
	testingBoard.generateBoardData();
	testingBoard.renderBoardData();

	Sleep(5000);

	Common::clearConsole();
}
