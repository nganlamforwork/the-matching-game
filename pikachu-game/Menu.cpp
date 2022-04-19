#include "Menu.h"

Menu::Menu()
{
	_curOption = 0	;
	_optionsSize = 7;
	_xMenu = 50;
	_yMenu = 15;
}
Menu::~Menu()
{
}

////////////////////////////////////////////////////////////////////////////
void Menu::startApp()
{
	renderLoadingScreen();
	renderMainScreen();
}

void Menu::renderLoadingScreen()
{
	Common::playSound(BACKGROUND_SOUND);
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::clearConsole();

	renderGameTitle();

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);

	std::ifstream bg;
	bg.open("images\\flowers.txt");

	int i = 0;
	std::string line;
	while (!bg.eof()) {
		Common::gotoXY(18, 24+i);
		getline(bg, line);
		cout << line << '\n';
		i++;
	}
	bg.close();

	Common::setConsoleColor(BRIGHT_WHITE, GRAY);
	Common::gotoXY(40, 19);
	cout << "LOADING...";

	int level = 13;

	//2 horizontal lines
	for (int x = 55; x < 85; x++) { 
		Common::gotoXY(x, 18);
		cout << char(205);
		Common::gotoXY(x, 20);
		cout << char(205);
	}

	//2 vertical lines
	for (int y = 19; y < 20; y++) { //2 vertical lines
		Common::gotoXY(55, y);
		cout << char(186);
		Common::gotoXY(85, y);
		cout << char(186);
	}

	//top left
	Common::gotoXY(55, 18);
	cout << (char)201;
	//top right
	Common::gotoXY(85, 18);
	cout << (char)187;
	//bottom left
	Common::gotoXY(55, 20);
	cout << (char)200;
	//bottom right
	Common::gotoXY(85, 20);
	cout << (char)188;

	//bar internal content
	for (int load = 56; load <= 84; load++) {
		Common::gotoXY(load, 19);
		cout << char(178);
		Sleep(100);

		level += 3;
		Common::gotoXY(88, 19);
		cout << level << "%";
	}
	
	Sleep(300);
}

void Menu::renderMainScreen()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::clearConsole();
	renderGameTitle();
	renderFlowers();
	renderOptionsMenu();
	renderOptionsText();

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
			switch (_curOption) {
			case 0: 
				playEasy();
				break;
			case 1:
				playMedium();
				break;
			case 2:
				playEasyDifficult();
				break;
			case 3:
				playMediumDifficult();
				break;
			case 4:
				showTutorial();
				break;
			case 5:
				showLeaderboard();
				break;
			case 6:
				exitGame();
				break;
			}
			break;
		default:
			Common::playSound(ERROR_SOUND);
		}
	}

}

void Menu::renderGameTitle()
{
	unsigned char M[] = {
						' ', '_', '_', ' ',' ', ' ',' ','_','_', ' ', ' ', ' ',
						'/', '\\',' ', '"','-', '.','/',' ',' ', '\\',' ', ' ',
						'\\',' ', '\\',' ','\\','-','.','/','\\',' ', '\\',' ',
						' ','\\',' ','\\','_','\\',' ','\\',' ','\\','_','\\',
						' ',' ','\\','/','_','/',' ',' ','\\','/','_','/'
	};
	unsigned char A[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','_','_',' ','\\',' ',' ',
						'\\',' ','\\',' ',' ','_','_',' ','\\',' ',
						' ','\\',' ','\\','_','\\',' ','\\','_','\\',
						' ',' ','\\','/','_','/','\\','/','_','/'
	};
	unsigned char T[] = {
						' ','_','_','_','_','_','_',' ',
						'/','\\','_','_',' ',' ','_','\\',
						'\\','/','_','/','\\',' ','\\','/',
						' ',' ',' ','\\',' ','\\','_','\\',
						' ',' ',' ',' ','\\','/','_','/'
	};
	unsigned char C[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','_','_','_','\\',' ',' ',
						'\\',' ','\\',' ','\\','_','_','_','_',' ',
						' ','\\',' ','\\','_','_','_','_','_','\\',
						' ',' ','\\','/','_','_','_','_','_','/',
	};
	unsigned char H[] = {
						' ','_','_',' ',' ','_','_',' ',' ',' ',
						'/','\\',' ','\\','_','\\',' ','\\',' ',' ',
						'\\',' ','\\',' ',' ','_','_',' ','\\',' ',
						' ','\\',' ','\\','_','\\',' ','\\','_','\\',
						' ',' ','\\','/','_','/','\\','/','_','/',
	};
	unsigned char I[] = {
						' ','_','_',' ',' ',' ',
						'/','\\',' ','\\',' ',' ',
						'\\',' ','\\',' ','\\',' ',
						' ','\\',' ','\\','_','\\',
						' ',' ','\\','/','_','/',
	};
	unsigned char N[] = {
						' ','_','_',' ',' ',' ','_','_',' ',' ',' ',
						'/','\\',' ','"','-','.','\\',' ','\\',' ',' ',
						'\\',' ','\\',' ','\\','-','.',' ',' ','\\',' ',
						' ','\\',' ','\\','_','\\','\\','"','\\','_','\\',
						' ',' ','\\','/','_','/',' ','\\','/','_','/',
	};
	unsigned char G[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','_','_','_','\\',' ',' ',
						'\\',' ','\\',' ','\\','_','_',' ','\\',' ',
						' ','\\',' ','\\','_','_','_','_','_','\\',
						' ',' ','\\','/','_','_','_','_','_','/',
	};
	unsigned char E[] = {
						' ','_','_','_','_','_','_',' ',' ',' ',
						'/','\\',' ',' ','_','_','_','\\',' ',' ',
						'\\',' ','\\',' ',' ','_','_','\\',' ',' ',
						' ','\\',' ','\\','_','_','_','_','_','\\',
						' ',' ','\\','/','_','_','_','_','_','/',
	};
	unsigned char space[] = {
						' ',' ',' ',' ',
						' ',' ',' ',' ',
						' ',' ',' ',' ',
						' ',' ',' ',' ',
						' ',' ',' ',' '
	};

	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	Common::gotoXY(42, 1);
	std::cout << "Pham Tien Duc - Le Vu Ngan Lam - 21CLC08 - HCMUS";

	unsigned char* word[] = { M, A, T, C, H, I, N, G, G, A, M, E };
	int sizeOfWord = (sizeof(word) / sizeof(word[0]));
	int wide[] = { 12, 10, 8, 10, 10, 6, 11, 10, 10, 10, 12, 10 };
	int color[] = { LIGHT_AQUA, AQUA, LIGHT_BLUE, BLUE, LIGHT_PURPLE, PURPLE };

	int loop = 1, colorCount = 0, left = 0;
	while (loop--) {
		Common::setConsoleColor(BRIGHT_WHITE, color[colorCount % 6]);

		left = 26;
		for (int i = 0; i < sizeOfWord; i++) {
			for (int j = 0; j < 5; j++) {
				if (i > 7) Common::gotoXY(left, 9 + j);
				else Common::gotoXY(left, 3 + j);

				for (int k = 0; k < wide[i]; k++)
					putchar(word[i][j * wide[i] + k]);
			}
			left += wide[i] + 1;
			if (i == 7 ) left = 45;
		}

		colorCount++;
	}
}

void Menu::renderOptionsMenu()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = _xMenu, top = _yMenu;
	int length = 35, height = _optionsSize*2;

	std::ifstream bg;
	bg.open("images\\borderMenu.txt");

	int i = 0;
	std::string line;
	while (!bg.eof()) {
		getline(bg, line);
		Common::gotoXY(left, top + i);
		cout << line << '\n';
		i++;
	}
	bg.close();

}

void Menu::renderOptionsText()
{
	int left = _xMenu + 9, top = _yMenu + 2;
	for (int i = 0; i < _optionsSize; i++) {
		Common::gotoXY(left, top + i*2 );
		cout << _options[i];
	}
	renderCurrentOption();
}

void Menu::renderCurrentOption()
{
	Common::playSound(MOVE_SOUND);
	int left = _xMenu + 9, top = _yMenu + 2;
	Common::setConsoleColor(BRIGHT_WHITE, RED);

	Common::gotoXY(left, top + _curOption * 2);
	cout << _options[_curOption];

	Common::gotoXY(left - 3, top + _curOption * 2);
	putchar(175);
	Common::gotoXY(left + 21, top + _curOption * 2);
	putchar(174);

}

void Menu::renderFlowers()
{
	std::ifstream bg;
	bg.open("images\\flower.txt");

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);

	int i = 0;
	std::string line;
	while (!bg.eof()) {
		getline(bg, line);

		Common::gotoXY(_xMenu - 38, _yMenu + 7 + i);
		cout << line << '\n';

		Common::gotoXY(_xMenu + 40, _yMenu + 7 + i);
		cout << line << '\n';

		i++;
	}
	bg.close();
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
	int left = _xMenu + 9, top = _yMenu + 2;
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	Common::gotoXY(left, top + _curOption * 2);
	cout << _options[_curOption];

	Common::gotoXY(left - 3, top + _curOption * 2);
	putchar(' ');
	Common::gotoXY(left + 21, top + _curOption * 2);
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

void Menu::showTutorial()
{
	Common::clearConsole();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 22, top = 2;						//Left and top of title
	int height = 15, width = 30;

	ifstream in;
	in.open("titles\\HowToPlay.txt");
	string s;
	int i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	while (getline(in, s)) {
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	in.close();

	left = 58, top = 12;

	in.open("titles\\tutorial.txt");
	i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	while (getline(in, s)) {
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	in.close();

	left = 3, top = 12;

	in.open("images\\tutorialMonster.txt");
	i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	while (getline(in, s)) {
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	in.close();

	while (true) {
		switch (Common::getConsoleInput()) {
		case 8:									
			renderMainScreen();
			break;
		default:
			Common::playSound(ERROR_SOUND);
		}
	}
}

void Menu::showLeaderboard()
{
	Common::clearConsole();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	ifstream boardtitle("titles\\Leaderboard.txt");
	string s;
	int i = 0;

	//Left and top of leaderboard title
	int left = 15, top = 2;
	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	while (getline(boardtitle, s)) {
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	boardtitle.close();

	vector<Players> playerList;
	Players().readPlayersFile(playerList, "PlayersList.txt");

	left = 60;
	top = 12;							//left and top of the board
	int height = 18, width = 65;		//board size

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	//Draw horizontal borders
	for (int i = 1; i < width; i++) {
		Common::gotoXY(left + i, top);
		putchar(205);
		Common::gotoXY(i + left, top + height);
		putchar(205);
	}
	Common::gotoXY(left + width, top);
	putchar(187);
	Common::gotoXY(left, top + height);
	putchar(200);

	//Draw vertical borders
	for (int i = 1; i < height; i++) {
		Common::gotoXY(left + width, i + top);
		putchar(186);
		Common::gotoXY(left, top + i);
		putchar(186);
	}
	Common::gotoXY(left + width, top + height);
	putchar(188);
	Common::gotoXY(left, top);
	putchar(201);

	//divide row
	Common::gotoXY(left, top + 2);
	putchar(204);
	for (int i = 1; i < width; i++) {
		Common::gotoXY(left + i, top + 2);
		putchar(205);
	}
	Common::gotoXY(left + width, top + 2);
	putchar(185);

	int posColumn[4] = { 16,27,40,53 };

	//divid columns
	for (int i = 0; i < 4; i++) {
		Common::gotoXY(left + posColumn[i], top);
		putchar(203);
		for (int j = 1; j < height; j++) {
			Common::gotoXY(left + posColumn[i], top + j);
			putchar(186);
		}
		Common::gotoXY(left + posColumn[i], top + height);
		putchar(202);

		//plus (+) symbol
		Common::gotoXY(left + posColumn[i], top + 2);
		putchar(206);
	}

	string headerNameColumn[5] = { "Player name", "Time", "Level", "Mode", "Score" };
	int headerPosNameColumn[5] = { 3, 20, 32, 45, 57 };

	Common::setConsoleColor(BRIGHT_WHITE, RED);
	for (int i = 0; i < 5; i++) {
		Common::gotoXY(left + headerPosNameColumn[i], top + 1);
		std::cout << headerNameColumn[i];
	}

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	string level1 = " Easy ";
	string level2 = "Medium";

	int n = 15;
	if (playerList.size() < n) n = playerList.size();
	for (int i = 0; i < n; i++) {
		Common::gotoXY(left + 8 - playerList[i]._name.length() / 2, top + 3 + i);
		cout << playerList[i]._name;

		Common::gotoXY(left + 22 - (playerList[i]._display_time.length() + 1) / 2, top + 3 + i);
		cout << playerList[i]._display_time << 's';

		Common::gotoXY(left + 31, top + 3 + i);
		if (playerList[i]._level == 4) cout << level1;
		else cout << level2;

		Common::gotoXY(left + 43, top + 3 + i);
		if (playerList[i]._mode == 1) cout << "Standard";
		else cout << "Difficult";

		stringstream ss;
		ss << playerList[i]._score;
		string str = ss.str();
		Common::gotoXY(left + 59 - str.length() / 2, top + 3 + i);
		cout << playerList[i]._score;
	}

	left = 3, top = 12;

	ifstream in;
	in.open("images\\tutorialMonster.txt");
	i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	while (getline(in, s)) {
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	in.close();

	bool loop = 1;
	while (loop) {
		switch (Common::getConsoleInput()) {
		case 8:
			loop = 0;
			break;
		default:
			Common::playSound(ERROR_SOUND);
		}
	}
}

void Menu::exitGame()
{
	Common::clearConsole();
	exit(0);
}