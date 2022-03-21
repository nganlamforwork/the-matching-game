#include "Menu.h"
#include "Common.h"

Menu::Menu()
{
	_x = 0;
}
Menu::~Menu()
{

}
void Menu::renderMainScreen()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	renderGameTitle();
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

	int loop = 6, colorCount = 0, left = 0;
	while (loop--) {
		Common::setConsoleColor(BRIGHT_WHITE, color[colorCount % 6]);

		//EFFECT DOT
		for (int sym = 0; sym < 2; sym++) {
			left = 28;
			for (int i = 0; i < sizeOfWord; i++) {
				for (int j = 0; j < 5; j++) {
					Common::gotoXY(left, 4 + j);
					for (int k = 0; k < wide[i]; k++)
						if (word[i][j * wide[i] + k] != ' ')
							putchar(symbol[sym]);
						else putchar(' ');
				}
				left += wide[i] + 1;
				Sleep(20);
			}
		}

		left = 28;
		for (int i = 0; i < sizeOfWord; i++) {
			for (int j = 0; j < 5; j++) {
				Common::gotoXY(left, 4 + j);
				for (int k = 0; k < wide[i]; k++)
					putchar(word[i][j * wide[i] + k]);
			}
			left += wide[i] + 1;
			Sleep(20);
		}

		colorCount++;
	}
}