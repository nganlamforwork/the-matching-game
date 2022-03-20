#include "Common.h"

HWND Common::consoleWindow = GetConsoleWindow();
HANDLE Common::consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

void Common::setUpConsole()
{
	setFontInfo();
	setAndCenterWindow();
	disableMaximize();
	setConsoleTitle();
	hideScrollBars();
	showCursor(false);
	disableMouseInput();
}

void Common::gotoXY(int pX, int pY)
{
	SetConsoleCursorPosition(consoleOutput, COORD{ (short)pX, (short)pY });
}

void Common::setAndCenterWindow()
{
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int width = 960;
	int height = 540;
	int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
		posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
	MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
}

void Common::setConsoleColor(int background, int text)
{
	SetConsoleTextAttribute(consoleOutput, background * 16 + text);
}

void Common::hideScrollBars()
{
	ShowScrollBar(consoleWindow, SB_BOTH, 0);
}

void Common::setConsoleTitle()
{
	SetConsoleTitle(L"PIKACHU GAME");
}

void Common::disableMaximize()
{
	SetWindowLong(consoleWindow, GWL_STYLE,
		GetWindowLong(consoleWindow, GWL_STYLE) & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME));
}

void Common::showCursor(bool show)
{
	CONSOLE_CURSOR_INFO info = { 1, show };
	SetConsoleCursorInfo(consoleOutput, &info);
}

void Common::setFontInfo()
{
	CONSOLE_FONT_INFOEX info;
	info.cbSize = sizeof(info);
	GetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
	info.dwFontSize.X = 12;
	info.dwFontSize.Y = 24;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(consoleOutput, FALSE, &info);
}

void Common::clearConsole()
{
	system("cls");
}

void Common::disableMouseInput()
{
	DWORD prev_mode;
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}

int Common::getConsoleInput()
{
	int c = _getch();
	if (c == 0 || c == 224)
	{
		switch (_getch())
		{
		case 72:				//lên
			return 2;
		case 75:				//trái
			return 3;
		case 77:				//phải
			return 4;
		case 80:				//xuống
			return 5;
		default:				//nút khác
			return 0;
		}
	}
	else
	{
		if (c == 27)                  //esc
			return 1;
		else if (c == 87 || c == 119) //W, w
			return 2;
		else if (c == 65 || c == 97)  //A, a
			return 3;
		else if (c == 68 || c == 100) //D, d
			return 4;
		else if (c == 83 || c == 115) //S, s
			return 5;
		else if (c == 13)             //Enter
			return 6;
		else if (c == 72 || c == 104) //H, h
			return 7;
		else
			return 0;                 //nút khác
	}
}


void Common::playSound(int i)
{
	static vector<const wchar_t*> soundFile{ L"win.wav", L"lose.wav",
		L"move.wav", L"enter.wav", L"error.wav",  L"background.wav", L"effect.wav" };
	PlaySound(soundFile[i], NULL, SND_FILENAME | SND_ASYNC);
}


int getRandomInt(int begin, int end)
{
	static random_device rd;
	static mt19937 mt(rd());
	uniform_int_distribution<int> dist(0, end);
	return dist(mt);
}