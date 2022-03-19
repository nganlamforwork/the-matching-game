//21127334 - Le Vu Ngan Lam
// Pham Tien Duc

#include <iostream>
#include "Common.h"

void GenerateMatrix(const int n);
void PrintRectangle(int left, int top, int width, int height);
void PrintOptionsBoard();
void DrawBoard(const int left, const int top, const int size);

int main()
{
	Common::setUpConsole();
	PrintRectangle(0, 0, 10, 10);
	PrintOptionsBoard();
	DrawBoard(0,0,6);
	/*int n = 4;
	GenerateMatrix(n);*/
	Sleep(5000);

	Common::clearConsole();
}
