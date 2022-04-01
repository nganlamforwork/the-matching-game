﻿#include "Menu.h"

Menu::Menu()
{
	_curOption = 0	;
	_optionsSize = 6;
	_xMenu = 50;
	_yMenu = 17;
}
Menu::~Menu()
{
}

////////////////////////////////////////////////////////////////////////////

void Menu::renderMainScreen()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	Common::playSound(BACKGROUND_SOUND);
	renderGameTitle();
	renderOptionsMenu();
	renderOptionsText();


	std::unordered_map<std::string, void(*)()> function_map = {
		{_options[0], playEasy},
		{_options[1], playMedium},
		{_options[2], playEasyDifficult},
		{_options[3], playMediumDifficult},
		{_options[4], showLeaderboard},
		{_options[5], exitGame} };


	bool loadMenu = 1;
	while (true){
		if (!loadMenu) break;
		switch (Common::getConsoleInput()){
		case 2:									//Up
			changeOption(-1);
			break;
		case 5:									//Down
			changeOption(1);
			break;
		case 6:									//Enter
			loadMenu = 0;
			function_map[_options[_curOption]]();
			break;
		default:
			Common::playSound(ERROR_SOUND);
			loadMenu = 0;
		}
	}

}

void Menu::renderGameTitle()
{
	unsigned char M[] = {
						219,219,' ',' ',' ',219,219,
						219,219,219,' ',219,219,219,
						219,219,219,219,219,219,219,
						219,219,' ',219,' ',219,219,
						219,219,' ',' ',' ',219,219
	};
	unsigned char A[] = {
						' ',219,219,219,' ',
						219,219,' ',219,219,
						219,219,219,219,219,
						219,219,' ',219,219,
						219,219,' ',219,219,
	};
	unsigned char T[] = {
						219,219,219,219,219,219,
						' ',' ',219,219,' ',' ',
						' ',' ',219,219,' ',' ',
						' ',' ',219,219,' ',' ',
						' ',' ',219,219,' ',' '
	};
	unsigned char C[] = {
						219,219,219,219,219,
						219,219,' ',' ',' ',
						219,219,' ',' ',' ',
						219,219,' ',' ',' ',
						219,219,219,219,219
	};
	unsigned char H[] = {
						219,219,' ',' ',219,219,
						219,219,' ',' ',219,219,
						219,219,219,219,219,219,
						219,219,' ',' ',219,219,
						219,219,' ',' ',219,219
	};
	unsigned char I[] = {
						219,219,219,219,
						' ',219,219,' ',
						' ',219,219,' ',
						' ',219,219,' ',
						219,219,219,219
	};
	unsigned char N[] = {
						219,219,' ',' ',' ',219,219,
						219,219,219,' ',' ',219,219,
						219,219,219,219,' ',219,219,
						219,219,' ',219,219,219,219,
						219,219,' ',' ',219,219,219
	};
	unsigned char G[] = {
						219,219,219,219,219,219,
						219,219,' ',' ',' ',' ',
						219,219,' ',219,219,219,
						219,219,' ',' ',219,219,
						219,219,219,219,219,219
	};
	unsigned char E[] = {
						219,219,219,219,219,
						219,219,' ',' ',' ',
						219,219,219,219,219,
						219,219,' ',' ',' ',
						219,219,219,219,219
	};
	unsigned char space[] = {
						' ',' ',' ',' ',
						' ',' ',' ',' ',
						' ',' ',' ',' ',
						' ',' ',' ',' ',
						' ',' ',' ',' '
	};

	unsigned char* word[] = { M, A, T, C, H, I, N, G, space, G, A, M, E };
	int sizeOfWord = (sizeof(word) / sizeof(word[0]));
	int wide[] = { 7, 5, 6, 5, 6, 4, 7, 6, 4, 6, 5, 7, 5 };
	int color[] = { LIGHT_AQUA, AQUA, LIGHT_BLUE, BLUE, LIGHT_PURPLE, PURPLE };

	int symbol[] = { 177,178 };

	int loop = 12, colorCount = 0, left = 0;
	while (loop--) {
		Common::setConsoleColor(BRIGHT_WHITE, color[colorCount % 6]);

		////EFFECT DOT
		//for (int sym = 0; sym < 2; sym++) {
		//	left = 28;
		//	for (int i = 0; i < sizeOfWord; i++) {
		//		for (int j = 0; j < 5; j++) {
		//			Common::gotoXY(left, 4 + j);
		//			for (int k = 0; k < wide[i]; k++)
		//				if (word[i][j * wide[i] + k] != ' ')
		//					putchar(symbol[sym]);
		//				else putchar(' ');
		//		}
		//		left += wide[i] + 1;
		//		Sleep(20);
		//	}
		//}

		left = 28;
		for (int i = 0; i < sizeOfWord; i++) {
			for (int j = 0; j < 5; j++) {
				Common::gotoXY(left, 4 + j);
				for (int k = 0; k < wide[i]; k++)
					putchar(word[i][j * wide[i] + k]);
			}
			left += wide[i] + 1;
			//Sleep(20);
		}

		colorCount++;
	}
}

void Menu::renderOptionsMenu()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = _xMenu, top = _yMenu;
	int length = 35, height = _optionsSize*2;

	Common::gotoXY(left, top);
	putchar(201);
	for (int i = 1; i < length; i++)
		putchar(205);
	putchar(187);

	for (int i = 1; i < height; i++){
		Common::gotoXY(left, top + i);
		if (i % 2 != 0){
			putchar(186);
			Common::gotoXY(left + length, top + i);
			putchar(186);
		}
		else{
			putchar(199);
			for (int i = 1; i < length; i++)
				putchar(196);
			putchar(182);
		}
	}
	Common::gotoXY(left, top + height);
	putchar(200);
	for (int i = 1; i < length; i++){
		putchar(205);
	}
	putchar(188);
}

void Menu::renderOptionsText()
{
	int left = _xMenu + 8, top = _yMenu + 1;
	for (int i = 0; i < 6; i++) {
		Common::gotoXY(left, top + i*2 );
		cout << _options[i];
	}
	renderCurrentOption();
}

void Menu::renderCurrentOption()
{
	Common::playSound(MOVE_SOUND);
	int left = _xMenu + 8, top = _yMenu + 1;
	Common::setConsoleColor(BRIGHT_WHITE, RED);

	Common::gotoXY(left, top + _curOption * 2);
	cout << _options[_curOption];

	Common::gotoXY(left - 11, top + _curOption * 2);
	putchar(175);
	Common::gotoXY(left + 29, top + _curOption * 2);
	putchar(174);

}

////////////////////////////////////////////////////////////////////////////

int Menu::getCurrentOption()
{
	return _curOption;
}

void Menu::setCurrentOption(int opt)
{
	_curOption = opt;
}

void Menu::offCurrentOption()
{
	int left = _xMenu + 8, top = _yMenu + 1;
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	Common::gotoXY(left, top + _curOption * 2);
	cout << _options[_curOption];

	Common::gotoXY(left - 11, top + _curOption * 2);
	putchar(' ');
	Common::gotoXY(left + 29, top + _curOption * 2);
	putchar(' ');

}

void Menu::changeOption(int direction) //-1: Up - 1: Down
{
	int tmp = _curOption + direction;
	if (tmp < 0 || tmp >= _optionsSize) {
		Common::playSound(ERROR_SOUND);
		return;
	}
	offCurrentOption();
	_curOption = tmp;
	renderCurrentOption();

}

////////////////////////////////////////////////////////////////////////////

void Menu::playEasy()
{
	Common::clearConsole();
	Game game(EASY);
	game.startGame();
}

void Menu::playMedium()
{
	Common::clearConsole();
	Game game(MEDIUM);
	game.startGame();
}

void Menu::playEasyDifficult()
{
	Common::clearConsole();
	GameLL game(EASY);
	game.startGame();
}

void Menu::playMediumDifficult()
{
	Common::clearConsole();
	GameLL game(MEDIUM);
	game.startGame();
}

void Menu::aboutPage()
{
	
}

void Menu::showLeaderboard()
{
	Board::drawLeaderBoard();
}

void Menu::exitGame()
{
	Common::clearConsole();
	exit(0);
}