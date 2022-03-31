#include "BoardLinkedList.h"

BoardLL::BoardLL(int size, int left, int top)
{
	_size = size;
	_left = left;
	_top = top;
	_remainCouple = _size * _size / 2;

	//Board
	_dataColumn = new LinkedList [_size];

	//Image board
	_imageBoard = new string[_size * 10];
}

BoardLL::~BoardLL()
{
	delete[] _dataColumn,
		_dataColumn = nullptr;
	delete[] _imageBoard,
		_imageBoard = nullptr;
}

////////////////////////////////////////////////////////////////////////////

int BoardLL::getXCoor(const int& c)
{
	return _left + 5 + CELL_LENGTH * c;
}

int BoardLL::getYCoor(const int& r)
{
	return _top + 2 + CELL_HEIGHT * r;
}

int BoardLL::getCCoor(const int& x)
{
	return (x - _left - 5) / CELL_LENGTH;
}

int BoardLL::getRCoor(const int& y)
{
	return (y - _top - 2) / CELL_HEIGHT;
}

int BoardLL::getStatus(const int& r, const int& c)
{
	return _dataColumn[c].getPos(_size - r - 1)->_status;
}

void BoardLL::setStatus(const int& r, const int& c, const int& status)
{
	_dataColumn[c].getPos(_size - r - 1)->_status = status;
}

////////////////////////////////////////////////////////////////////////////

void BoardLL::generateBoardData()
{
	srand(time(NULL));


	for (int i = 0; i < _size * _size; i += 2) {
		char tmp = rand() % 26 + 'A';
		
		for (int j = 0; j < 2; j++) {
			int tmpRand = 0;
			do {
				tmpRand = rand() % _size;
			} while (_dataColumn[tmpRand]._size >= _size);

			int r = _dataColumn[tmpRand]._size;
			int c = tmpRand;

			NodeLL* tmpNodeLL = new NodeLL(tmp, NORMAL, getXCoor(c), getYCoor(r), r, c);

			_dataColumn[tmpRand].addHead(tmpNodeLL);

			delete tmpNodeLL;
		}
	}
}

void BoardLL::drawBoard()
{
	Common::clearConsole();

	Common::gotoXY(120, 28);
	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	cout << "H: MOVE SUGGESTION";
	Common::gotoXY(120, 30);
	Common::setConsoleColor(BRIGHT_WHITE, YELLOW);
	cout << "ESC: EXIT";

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	//Vẽ biên trên
	Common::gotoXY(_left + 1, _top);
	putchar(201);
	for (int i = 1; i < _size * CELL_LENGTH; i++) {
		//Sleep(2);
		if (i % CELL_LENGTH == 0)
			putchar(205);
		else
			putchar(205);
	}
	putchar(187);


	//Vẽ biên phải
	for (int i = 1; i < _size * CELL_HEIGHT; i++) {
		//Sleep(5);
		Common::gotoXY(_size * CELL_LENGTH + _left + 1, i + _top);
		if (i % CELL_HEIGHT == 0)
			putchar(186);
		else
			putchar(186);
	}
	Common::gotoXY(_size * CELL_LENGTH + _left + 1, _size * CELL_HEIGHT + _top);
	putchar(188);


	//Ve biên dưới
	for (int i = 1; i < _size * CELL_LENGTH; i++) {
		Common::gotoXY(_size * CELL_LENGTH + _left - i + 1, _size * CELL_HEIGHT + _top);
		//Sleep(2);
		if (i % CELL_LENGTH == 0)
			putchar(205);
		else
			putchar(205);
	}
	Common::gotoXY(_left + 1, _size * CELL_HEIGHT + _top);
	putchar(200);

	//Ve biên trái
	for (int i = 1; i < _size * CELL_HEIGHT; i++) {
		//Sleep(5);
		Common::gotoXY(_left + 1, _size * CELL_HEIGHT + _top - i);
		if (i % CELL_HEIGHT == 0)
			putchar(186);
		else
			putchar(186);
	}

	//Vẽ đường dọc
	for (int i = 1; i < _size * CELL_HEIGHT; i++) {
		for (int j = CELL_LENGTH; j < _size * CELL_LENGTH; j += CELL_LENGTH) {
			if (i % CELL_HEIGHT != 0) {
				Common::gotoXY(j + _left + 1, i + _top);
				putchar(179);
			}
		}
		//Sleep(5);
	}

	//Vẽ đường ngang
	for (int i = 1; i < _size * CELL_LENGTH; i++) {
		for (int j = CELL_HEIGHT; j < _size * CELL_HEIGHT; j += CELL_HEIGHT) {
			Common::gotoXY(i + _left + 1, j + _top);
			if (i % CELL_LENGTH == 0)
				putchar(32);
			else
				putchar(196);
		}
		//Sleep(2);
	}

}

void BoardLL::renderBoardData()
{
	for (int j = 0; j < _size; j++) {	//Column
		NodeLL* tmp = _dataColumn[j]._head;
		for (int i = 0; i < _dataColumn[j]._size; i++) {
			Common::gotoXY(tmp->_x, tmp->_y);
			putchar(tmp->_charHolder);
			tmp = tmp->_next;
		}
	}
}

void BoardLL::initBoardBackground()
{
	std::ifstream bg;
	if (_size == 4) bg.open("images\\plane.txt");
	else if (_size == 6) bg.open("images\\house.txt");

	int i = 0;
	while (!bg.eof()) {
		getline(bg, _imageBoard[i]);
		int tmp = _imageBoard[i].size();
		i++;
	}
	bg.close();
}

////////////////////////////////////////////////////////////////////////////

void BoardLL::drawDuck()
{
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 8 + _left, 10 + _top);
	cout << "  __";
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 8 + _left, 11 + _top);
	cout << "<(o )___";
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 8 + _left, 12 + _top);
	cout << " ( ._> /";
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 8 + _left, 13 + _top);
	cout << "  `---' ";
}

void BoardLL::drawCat()
{
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 10 + _left, 10 + _top);
	cout << "___/|";
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 10 + _left, 11 + _top);
	cout << "\\o.O|";
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 10 + _left, 12 + _top);
	cout << "(___)";
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 10 + _left, 13 + _top);
	cout << "  U";
}

void BoardLL::drawScoreBoard()
{
	//Vẽ biên trên
	for (int i = 1; i < CELL_LENGTH * 3; i++){
		Common::gotoXY(CELL_LENGTH * (_size + 1) + i + _left, 0 + _top);
		putchar(205);
		//Sleep(5);
	}
	putchar(187);

	//Vẽ biên phải
	for (int i = 1; i < CELL_HEIGHT * 4; i++){
		Common::gotoXY(CELL_LENGTH * (_size + 4) + _left, i + _top);
		putchar(186);
		//Sleep(5);
	}
	Common::gotoXY(CELL_LENGTH * (_size + 4) + _left, CELL_HEIGHT * 4 + _top);
	putchar(188);

	//Vẽ biên dưới
	for (int i = 1; i < CELL_LENGTH * 3; i++){
		Common::gotoXY(CELL_LENGTH * (_size + 4) - i + _left, CELL_HEIGHT * 4 + _top);
		putchar(205);
		//Sleep(5);
	}
	Common::gotoXY(CELL_LENGTH * (_size + 4) - CELL_LENGTH * 3 + _left, CELL_HEIGHT * 4 + _top);
	putchar(200);

	//Vẽ biên trái
	for (int i = CELL_HEIGHT * 4 - 1; i >= 1; i--){
		Common::gotoXY(CELL_LENGTH * (_size + 1) + _left, i + _top);
		putchar(186);
		//Sleep(5);
	}
	Common::gotoXY(CELL_LENGTH * (_size + 1) + _left, 0 + _top);
	putchar(201);

	drawDuck();
	//drawCat();

}

////////////////////////////////////////////////////////////////////////////
//https://patorjk.com/software/taag/#p=testall&f=Blocks&t=The%20Matching%20Game%0A

void BoardLL::drawEnterName()
{
	int left = 0, top = 0;
	ifstream inName("EnterName.txt");
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	string s;
	int i = 0;
	while (!inName.eof()){
		Common::gotoXY(left + 20, top + 2 + i);
		getline(inName, s);
		cout << s << endl;
		i++;
	}
	inName.close();
}

void BoardLL::drawEndgame(int score)
{
	int left = 0, top = 0;
	Common::clearConsole();
	ifstream endgame("GameOver.txt");
	string s;
	int i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	while (!endgame.eof()) {
		Common::gotoXY(left + 20, top + 5 + i);
		getline(endgame, s);
		cout << s;
		i++;
	}
	endgame.close();

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(left + 55, top + 5 + 11);
	cout << "Your score is: " << score << " !!!";
}

void BoardLL::drawLeaderBoard()
{
	Common::clearConsole();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 50, top = 14;						//left và top của leaderboard
	int height = 15, width = 30;

	ifstream boardtitle("Leaderboard.txt");
	string s;
	int i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	while (getline(boardtitle, s)) {
		Common::gotoXY(left - 40, top - 12 + i);
		cout << s;
		i++;
	}
	boardtitle.close();

	vector<Players> playerList;
	Players().readPlayersFile(playerList);

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	//Vẽ biên trên
	for (int i = 1; i < width; i++)
	{
		Common::gotoXY(left + i, top);
		putchar(205);
	}
	putchar(187);

	//Vẽ biên phải
	for (int i = 1; i < height; i++)
	{
		Common::gotoXY(left + width, i + top);
		putchar(186);
	}
	Common::gotoXY(left + width, top + height);
	putchar(188);

	//Vẽ biên dưới
	for (int i = width - 1; i >= 1; i--)
	{
		Common::gotoXY(i + left, top + height);
		putchar(205);
	}
	Common::gotoXY(left, top + height);
	putchar(200);

	//Vẽ biên trái
	for (int i = height - 1; i >= 1; i--)
	{
		Common::gotoXY(left, top + i);
		putchar(186);
	}
	Common::gotoXY(left, top);
	putchar(201);

	//chia cột 1
	Common::gotoXY(left + 16, top);
	putchar(203);
	for (int i = 1; i < height; i++)
	{
		Common::gotoXY(left + 16, top + i);
		putchar(186);
	}
	Common::gotoXY(left + 16, top + height);
	putchar(202);

	//chia cột 2
	Common::gotoXY(left + 22, top);
	putchar(203);
	for (int i = 1; i < height; i++)
	{
		Common::gotoXY(left + 22, top + i);
		putchar(186);
	}
	Common::gotoXY(left + 22, top + height);
	putchar(202);

	//chia hàng ngang
	Common::gotoXY(left, top + 2);
	putchar(204);
	for (int i = 1; i < width; i++)
	{
		Common::gotoXY(left + i, top + 2);
		putchar(205);
	}
	Common::gotoXY(left + width, top + 2);
	putchar(185);
	Common::gotoXY(left + 16, top + 2);
	putchar(206);
	Common::gotoXY(left + 22, top + 2);
	putchar(206);

	Common::gotoXY(left + 1, top + 1);
	std::cout << "Player name";
	Common::gotoXY(left + 17, top + 1);
	std::cout << "Score";
	Common::gotoXY(left + 24, top + 1);
	std::cout << "Time";

	int n = 10;
	if (playerList.size() < n) n = playerList.size();
	for (int i = 0; i < n; i++)
	{
		Common::gotoXY(left + 1, top + 3 + i);
		cout << playerList[i]._name;
		Common::gotoXY(left + 18, top + 3 + i);
		cout << playerList[i]._score;
		Common::gotoXY(left + 24, top + 3 + i);
		cout << playerList[i]._display_time << 's';
	}

}

////////////////////////////////////////////////////////////////////////////

void BoardLL::repaintColumn(const int& c)
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	NodeLL* tmp = _dataColumn[c]._head;
	for (int i = 0; i < _dataColumn[c]._size; i++) {
		tmp->_r = _size - i - 1;
		tmp->_y = getYCoor(tmp->_r);

		int x = tmp->_x, y = tmp->_y;
		Common::gotoXY(x,y);

		for (int i = y - 1; i <= y + 1; i++)
			for (int j = x - 3; j <= x + 3; j++) {
				Common::gotoXY(j, i);
				if (j == x && i == y) putchar(tmp->_charHolder);
				else putchar(' ');
			}
		
		tmp = tmp->_next;
	}
	for (int i = _size - _dataColumn[c]._size - 1; i >= 0; i--) {
		int x = getXCoor(c), y = getYCoor(i);

		Common::gotoXY(x, y);

		for (int i = y - 1; i <= y + 1; i++)
			for (int j = x - 3; j <= x + 3; j++) {
				Common::gotoXY(j, i);
				putchar(_imageBoard[i - _top][j - _left]);
			}
	}
}

void BoardLL::lockCell(const int& r, const int& c)
{
	setStatus(r, c, LOCK);
}

void BoardLL::unlockCell(const int& r, const int& c)
{
	setStatus(r, c, NORMAL);
	char charHolder = _dataColumn[c].getPos(_size - r - 1)->_charHolder;

	int x = getXCoor(c), y = getYCoor(r);

	Common::gotoXY(x, y);
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = y - 1; i <= y + 1; i++)
		for (int j = x - 3; j <= x + 3; j++) {
			Common::gotoXY(j, i);
			if (j == x && i == y) putchar(charHolder);
			else putchar(' ');
		}
	Common::gotoXY(x, y);
}

void BoardLL::deleteCell(const int& r, const int& c)
{
	_dataColumn[c].removePos(_size - r - 1);
	repaintColumn(c);
	//setStatus(r, c, DELETED);

	int x = getXCoor(c), y = getYCoor(r);

	Common::gotoXY(x, y);
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	//Go back to original
	Common::gotoXY(x, y);
}

////////////////////////////////////////////////////////////////////////////

bool BoardLL::outputMatchI()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "I-Matched!! :D" << endl;
	return 1;
}

bool BoardLL::outputMatchU()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "U-Matched!! :D" << endl;
	return 1;
}

bool BoardLL::outputMatchL()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "L-Matched!! :D" << endl;
	return 1;
}

bool BoardLL::outputMatchZ()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "Z-Matched!! :D" << endl;
	return 1;
}

bool BoardLL::outputNoMatch()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "Not a match :(" << endl;
	return 0;
}