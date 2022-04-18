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

int BoardLL::getTopRow(const int& c)
{
	return _size - _dataColumn[c]._size;
}

////////////////////////////////////////////////////////////////////////////

void BoardLL::generateBoardData()
{
	srand(time(NULL));

	char* pairCharacter = new char[_size * _size];
	bool* pos = new bool[_size * _size];

	for (int i = 0; i < _size * _size; i += 2) 
		pairCharacter[i] = pairCharacter[i + 1] = rand() % 26 + 'A';

	for (int i = 0; i < _size * _size; i++)
		pos[i] = 0;

	for (int i = 0; i < _size * _size; i ++) {
		int tmp;
		do {
			tmp = rand() % (_size * _size);
		} while (pos[tmp] == 1);
		pos[tmp] = 1;

		int c = i % _size;
		int r = _dataColumn[c]._size;

		NodeLL* tmpNodeLL = new NodeLL(pairCharacter[tmp], NORMAL, getXCoor(c), getYCoor(r), r, c);

		_dataColumn[c].addHead(tmpNodeLL);
	}
	delete[] pairCharacter;
	delete[] pos;
}

void BoardLL::drawBoard()
{
	Common::clearConsole();

	Common::gotoXY(_left + 1, _size * CELL_HEIGHT + _top + 2);
	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	cout << "H: MOVE SUGGESTION     ";
	Common::setConsoleColor(BRIGHT_WHITE, YELLOW);
	cout << "ESC: EXIT";

	Common::setConsoleColor(BRIGHT_WHITE, GRAY);
	for (int i = 0; i< _size; i++) {	
		Common::gotoXY(getXCoor(i),_top-1);
		putchar(i+'1');
	}
	for (int i = 0; i < _size; i++) {
		Common::gotoXY(_left - 1, getYCoor(i));
		putchar(i + 'A');
	}

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
	for (int i = 1; i < CELL_HEIGHT * _size; i++){
		Common::gotoXY(CELL_LENGTH * (_size + 4) + _left, i + _top);
		putchar(186);
		//Sleep(5);
	}
	Common::gotoXY(CELL_LENGTH * (_size + 4) + _left, CELL_HEIGHT * _size + _top);
	putchar(188);

	//Vẽ biên dưới
	for (int i = 1; i < CELL_LENGTH * 3; i++){
		Common::gotoXY(CELL_LENGTH * (_size + 4) - i + _left, CELL_HEIGHT * _size + _top);
		putchar(205);
		//Sleep(5);
	}
	Common::gotoXY(CELL_LENGTH * (_size + 4) - CELL_LENGTH * 3 + _left, CELL_HEIGHT * _size + _top);
	putchar(200);

	//Vẽ biên trái
	for (int i = CELL_HEIGHT * _size - 1; i >= 1; i--){
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
	ifstream inName("titles\\EnterName.txt");
	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	string s;
	int i = 0;
	while (!inName.eof()){
		Common::gotoXY(left + 20, top + 2 + i);
		getline(inName, s);
		cout << s << endl;
		i++;
	}
	inName.close();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
}

void BoardLL::drawEndgame(int score)
{
	int left = 0, top = 0;
	Common::clearConsole();
	ifstream endgame("titles\\GameOver.txt");
	string s;
	int i = 0;

	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	while (!endgame.eof()) {
		Common::gotoXY(left + 24, top + 5 + i);
		getline(endgame, s);
		cout << s;
		i++;
	}
	endgame.close();

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(left + 55, top + 5 + 11);
	cout << "Your score is: " << score << " !!!";

	ifstream bht;
	bht.open("Haha\\bht.txt");

	i = 0;
	left = 25;
	top = 20;
	while (!bht.eof()) {
		getline(bht, s);
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	bht.close();

	if (score < 100) {
		Common::gotoXY(left + 2, top - 2);
		cout << "Choi j ki` z";
	}
	else if (score < 400) {
		Common::gotoXY(left + 5, top - 2);
		cout << "J thap the";
	}
	else if (score < 600) {
		Common::gotoXY(left + 5, top - 2);
		cout << "Dam ba cai game";
	}
	else if (score < 900) {
		Common::gotoXY(left + 5, top - 2);
		cout << "D1nk k0ut z";
	}
	else {
		Common::gotoXY(left + 5, top - 2);
		cout << "Tu3yt v0i 0ng m4t tr0i";
	}
}

void BoardLL::drawLeaderBoard()
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
	Players().readPlayersFile(playerList, "PlayersListLL.txt");

	left = 40;
	top = 10;							//left and top of the board
	int height = 15, width = 50;		//board size
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
	Common::gotoXY(left + 27, top);
	putchar(203);
	for (int i = 1; i < height; i++)
	{
		Common::gotoXY(left + 27, top + i);
		putchar(186);
	}
	Common::gotoXY(left + 27, top + height);
	putchar(202);

	//chia cột 3
	Common::gotoXY(left + 40, top);
	putchar(203);
	for (int i = 1; i < height; i++)
	{
		Common::gotoXY(left + 40, top + i);
		putchar(186);
	}
	Common::gotoXY(left + 40, top + height);
	putchar(202);

	//chia hàng ngang
	Common::gotoXY(left, top + 2);
	putchar(204);
	for (int i = 1; i < width; i++)
	{
		Common::gotoXY(left + i, top + 2);
		putchar(205);
	}
	//Dấu cộng ở giữa hàng và cột
	Common::gotoXY(left + width, top + 2);
	putchar(185);
	Common::gotoXY(left + 16, top + 2);
	putchar(206);
	Common::gotoXY(left + 27, top + 2);
	putchar(206);
	Common::gotoXY(left + 40, top + 2);
	putchar(206);

	Common::gotoXY(left + 3, top + 1);
	std::cout << "Player name";
	Common::gotoXY(left + 20, top + 1);
	std::cout << "Time";
	Common::gotoXY(left + 32, top + 1);
	std::cout << "Mode";
	Common::gotoXY(left + 43, top + 1);
	std::cout << "Score";

	string mode1 = "Easy";
	string mode2 = "Medium";
	int n = 17;
	if (playerList.size() < n) n = playerList.size();
	for (int i = 0; i < n; i++)
	{
		Common::gotoXY(left + 8 - playerList[i]._name.length() / 2, top + 3 + i);
		cout << playerList[i]._name;
		Common::gotoXY(left + 22 - (playerList[i]._display_time.length() + 1) / 2, top + 3 + i);
		cout << playerList[i]._display_time << 's';
		switch (playerList[i]._mode)
		{
		case 4:
			Common::gotoXY(left + 28 + 6 - mode1.length() / 2, top + 3 + i);
			cout << mode1;
			break;
		case 6:
			Common::gotoXY(left + 28 + 6 - mode2.length() / 2, top + 3 + i);
			cout << mode2;
			break;
		}
		stringstream ss;
		ss << playerList[i]._score;
		string str = ss.str();
		Common::gotoXY(left + 41 + 4 - str.length() / 2, top + 3 + i);
		cout << playerList[i]._score;
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

		//Delete top border
		if (i != 0)
			for (int i = x - 3; i <= x + 3; i++) {
				Common::gotoXY(i, y - 2);
				putchar(_imageBoard[y - 2 - _top][i - _left]);
			}
		//Delete right border
		if (c != _size - 1 && _size - _dataColumn[c+1]._size > i) 
			for (int i = y - 1; i <= y + 1; i++) {
				Common::gotoXY(x + 4, i);
				putchar(_imageBoard[i - _top][x + 4 - _left]);
			}
		//Delete left border
		if (c != 0 && _size - _dataColumn[c - 1]._size > i)
			for (int i = y - 1; i <= y + 1; i++) {
				Common::gotoXY(x - 4, i);
				putchar(_imageBoard[i - _top][x - 4 - _left]);
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
	cout << "I-Matched!!! :D" << endl;
	return 1;
}

bool BoardLL::outputMatchU()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "U-Matched!!! :D" << endl;
	return 1;
}

bool BoardLL::outputMatchL()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "L-Matched!!! :D" << endl;
	return 1;
}

bool BoardLL::outputMatchZ()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "Z-Matched!!! :D" << endl;
	return 1;
}

bool BoardLL::outputNoMatch()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "Not a match :((" << endl;
	return 0;
}