#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <filesystem>
#include "Common.h"

void PrintRectangle(int left, int top, int width, int height)
{
	Common::gotoXY(left, top);
	putchar(218);
	for (int i = 0; i < width; i++)
		putchar(196);
	putchar(191);

	int i = 0;
	for (; i < height; i++)
	{
		Common::gotoXY(left, top + i + 1);
		putchar(179);
		Common::gotoXY(left + width + 1, top + i + 1);
		putchar(179);
	}

	Common::gotoXY(left, top + i);
	putchar(192);
	for (i = 0; i < width; i++)
		putchar(196);
	putchar(217);
}

void PrintOptionsBoard()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 48;
	int top = 20;
	Common::gotoXY(left, top);
	putchar(201);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(187);


	for (int i = 1; i < 8; i++)
	{
		Common::gotoXY(left, top + i);
		if (i % 2 != 0)
		{
			putchar(186);
			Common::gotoXY(left + 12, top + i);
			putchar(186);
		}
		else
		{
			putchar(199);
			for (int i = 1; i < 12; i++)
			{
				putchar(196);
			}
			putchar(182);
		}
	}
	Common::gotoXY(left, top + 8);
	putchar(200);
	for (int i = 1; i < 12; i++)
	{
		putchar(205);
	}
	putchar(188);
}

void DrawBoard(const int left, const int top, const int size)
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::clearConsole();

	Common::gotoXY(left + 3, top + 1);
	putchar('A');
	Common::gotoXY(left + 3 + 4, top + 1);
	putchar('B');

	//Vẽ biên trên
	Common::gotoXY(left + 1, top);
	putchar(201);
	for (int i = 1; i < size * 4; i++)
	{
		Sleep(5);
		if (i % 4 == 0)
			putchar(209);
		else
			putchar(205);
	}
	putchar(187);


	//Vẽ biên phải
	for (int i = 1; i < size * 2; i++)
	{
		Sleep(10);
		Common::gotoXY(size * 4 + left + 1, i + top);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(182);
	}
	Common::gotoXY(size * 4 + left + 1, size * 2 + top);
	putchar(188);


	//Ve biên dưới
	for (int i = 1; i < size * 4; i++)
	{
		Common::gotoXY(size * 4 + left - i + 1, size * 2 + top);
		Sleep(5);
		if (i % 4 == 0)
			putchar(207);
		else
			putchar(205);
	}
	Common::gotoXY(left + 1, size * 2 + top);
	putchar(200);

	//Ve biên trái
	for (int i = 1; i < size * 2; i++)
	{
		Sleep(10);
		Common::gotoXY(left + 1, size * 2 + top - i);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(199);
	}

	//Vẽ đường dọc
	for (int i = 1; i < size * 2; i++)
	{
		for (int j = 4; j < size * 4; j += 4)
		{
			if (i % 2 != 0)
			{
				Common::gotoXY(j + left + 1, i + top);
				putchar(179);
			}
		}
		Sleep(10);
	}

	//Vẽ đường ngang
	for (int i = 1; i < size * 4; i++)
	{
		for (int j = 2; j < size * 2; j += 2)
		{
			Common::gotoXY(i + left + 1, j + top);
			if (i % 4 == 0)
				putchar(197);
			else
				putchar(196);
		}
		Sleep(5);
	}
}