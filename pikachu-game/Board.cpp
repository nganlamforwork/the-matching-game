#include "Board.h"

Board::Board(int size, int left, int top)
{
	_size = size;
	_left = left;
	_top = top;
	_remainCouple = _size * _size / 2;
    _pairCharacter = new int[_size * _size];

    //Board
    _dataBoard = new Node* [_size];
    for (int i = 0; i < _size; i++)
        _dataBoard[i] = new Node[_size];

	//Image board
	_imageBoard = new string[_size * 10];
}

Board::~Board()
{
    for (int i = 0; i < _size; i++)
        delete[] _dataBoard[i];
    delete[] _dataBoard,
        _dataBoard = nullptr;
	delete[] _imageBoard,
		_imageBoard = nullptr;

	delete[] _pos;
}

////////////////////////////////////////////////////////////////////////////

int Board::getXCoor(const int& c)
{
	return _left + 5 + CELL_LENGTH * c;
}

int Board::getYCoor(const int& r)
{
	return _top + 2 + CELL_HEIGHT * r;
}

int Board::getCCoor(const int& x)
{
	return (x - _left - 5) / CELL_LENGTH;
}

int Board::getRCoor(const int& y)
{
	return (y - _top - 2) / CELL_HEIGHT;
}

char Board::getCharRC(const int& r, const int& c)
{
	if (_dataBoard[r][c]._Status == DELETED) return ' ';
	return _dataBoard[r][c]._CharHolder;
}

int Board::getStatus(const int& r, const int& c)
{
	return _dataBoard[r][c]._Status;
}

////////////////////////////////////////////////////////////////////////////

void Board::generateBoardData()
{
    srand(time(NULL));

    bool* checkDuplicate = new bool[_size * _size];
    _pos = new int[_size * _size];

    //Build random character pair
	for (int i = 0; i < _size * _size; i += 2) 
			_pairCharacter[i] = _pairCharacter[i + 1] = rand() % 26 + 'A'/* rand() % 1 + 'A'*/;

    //Build position array
    for (int i = 0; i < _size * _size; i++) checkDuplicate[i] = 0;
    for (int i = 0; i < _size * _size; i++) {
        int tmp = 0;

        do {
            tmp = rand() % (_size * _size);
        } while (checkDuplicate[tmp]);

        checkDuplicate[tmp] = 1;
        _pos[i] = tmp;
    }


    //Build table
    for (int i = 0; i < _size * _size; i++) {
        int r = _pos[i] / _size;
        int c = _pos[i] % _size;
        _dataBoard[r][c].setCharHolder(_pairCharacter[i]);
    }

    delete[] checkDuplicate;
}

void Board::drawBoard()
{
	Common::clearConsole();

	Common::gotoXY(_left + 1, _size * CELL_HEIGHT + _top + 2);
	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	cout << "H: MOVE SUGGESTION     ";
	Common::setConsoleColor(BRIGHT_WHITE, YELLOW);
	cout << "ESC: EXIT";

	Common::setConsoleColor(BRIGHT_WHITE, GRAY);
	for (int i = 0; i < _size; i++) {
		Common::gotoXY(getXCoor(i), _top - 1);
		putchar(i + '1');
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

void Board::renderBoardData()
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++) {
			Common::gotoXY(_left + 5 + CELL_LENGTH * j, _top + 2 + CELL_HEIGHT * i);
			_dataBoard[i][j].setX(_left + 5 + CELL_LENGTH * j);
			_dataBoard[i][j].setY(_top + 2 + CELL_HEIGHT * i);
			_dataBoard[i][j].setR(i);
			_dataBoard[i][j].setC(j);

			putchar(_dataBoard[i][j].getCharHolder());
		}
}

void Board::initBoardBackground()
{
	std::ifstream bg;
	if (_size == 4) bg.open("images\\plane.txt");
	else if (_size == 6) bg.open("images\\house.txt");

	int i = 0;
	while (!bg.eof()){
		getline(bg, _imageBoard[i]);
		int tmp = _imageBoard[i].size();
		i++;
	}
	bg.close();
}

////////////////////////////////////////////////////////////////////////////

void Board::drawDuck()
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

void Board::drawCat()
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

void Board::drawScoreBoard()
{
	//Vẽ biên trên
	for (int i = 1; i < CELL_LENGTH * 3; i++)
	{
		Common::gotoXY(CELL_LENGTH * (_size + 1) + i + _left, 0 + _top);
		putchar(205);
		//Sleep(5);
	}
	putchar(187);

	//Vẽ biên phải
	for (int i = 1; i < CELL_HEIGHT * _size; i++)
	{
		Common::gotoXY(CELL_LENGTH * (_size + 4) + _left, i + _top);
		putchar(186);
		//Sleep(5);
	}
	Common::gotoXY(CELL_LENGTH * (_size + 4) + _left, CELL_HEIGHT * _size + _top);
	putchar(188);

	//Vẽ biên dưới
	for (int i = 1; i < CELL_LENGTH * 3; i++)
	{
		Common::gotoXY(CELL_LENGTH * (_size + 4) - i + _left, CELL_HEIGHT * _size + _top);
		putchar(205);
		//Sleep(5);
	}
	Common::gotoXY(CELL_LENGTH * (_size + 4) - CELL_LENGTH * 3 + _left, CELL_HEIGHT * _size + _top);
	putchar(200);

	//Vẽ biên trái
	for (int i = CELL_HEIGHT * _size - 1; i >= 1; i--)
	{
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

void Board::drawEnterName()
{
	int left = 0, top = 0;
	ifstream inName("titles\\EnterName.txt");
	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
	string s;
	int i = 0;
	while (!inName.eof())
	{
		Common::gotoXY(left + 25, top + 2 + i);
		getline(inName, s);
		cout << s << endl;
		i++;
	}
	inName.close();

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
}

void Board::drawEndgame(int score)
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
	bht.open("bht.txt");

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
		cout << "Game nay de~ ma?";
	}
	else if (score < 400) {
		Common::gotoXY(left + 5, top - 2);
		cout << "Cui pap z";
	}
	else if (score < 600) {
		Common::gotoXY(left + 5, top - 2);
		cout << "3 ngay la xong game nay roi";
	}
	else if (score < 900){
		Common::gotoXY(left + 5, top - 2);
		cout << "Gk3 v4y tr0i";
	}
	else {
		Common::gotoXY(left + 5, top - 2);
		cout << "Diem ao~ zay";
	}
}

void Board::drawLeaderBoard()//cần làm cho nó ra cả chế độ chơi là board nhỏ hay lớn và difficult hay normal
{
	Common::clearConsole();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	ifstream boardtitle("titles\\Leaderboard.txt");
	string s;
	int i = 0;

	//Left and top of leaderboard title
	int left = 15, top = 2;
	Common::setConsoleColor(BRIGHT_WHITE, GREEN);
	while (getline(boardtitle, s)){
		Common::gotoXY(left, top + i);
		cout << s;
		i++;
	}
	boardtitle.close();

	vector<Players> playerList;
	Players().readPlayersFile(playerList, "PlayersList.txt");

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
		Common::gotoXY(left + 8 - playerList[i]._name.length()/2, top + 3 + i);
		cout << playerList[i]._name;
		Common::gotoXY(left + 22 - (playerList[i]._display_time.length()+1)/2, top + 3 + i);
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
		Common::gotoXY(left + 41 + 4 - str.length()/2, top + 3 + i);
		cout << playerList[i]._score;
	}
}

////////////////////////////////////////////////////////////////////////////

void Board::lockCell(const int& r, const int& c)
{
	_dataBoard[r][c].setStatus(LOCK);
}

void Board::unlockCell(const int& r, const int& c)
{
	_dataBoard[r][c].setStatus(NORMAL);

	int x = getXCoor(c), y = getYCoor(r);

	Common::gotoXY(x,y);
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	for (int i = y - 1 ; i <= y + 1 ; i++)
		for (int j = x - 3; j <= x + 3; j++) {
			Common::gotoXY(j, i);
			if (j == x && i == y) putchar(getCharRC(r,c));
			else putchar(' ');
		}
	Common::gotoXY(x, y);
}

void Board::deleteCell(const int& r, const int& c)
{
	_dataBoard[r][c].setStatus(DELETED);

	int x = getXCoor(c), y = getYCoor(r);

	Common::gotoXY(x, y);
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);	
	putchar(getCharRC(r, c));						//In hình: image[r][c]???

	for (int i = y - 1; i <= y + 1; i++)
		for (int j = x - 3; j <= x + 3; j++) {
			Common::gotoXY(j, i);
			//putchar(' ');
			putchar(_imageBoard[i - _top][j - _left]);
		}

	//Delete left border
	if (c > 0 && getStatus(r, c - 1) == DELETED)
		for (int i = y - 1; i <= y + 1; i++) {
			Common::gotoXY(x - 4, i);
			//putchar(' ');
			putchar(_imageBoard[i - _top][x - 4 - _left]);
		}
	//Delete right border
	if (c < _size - 1 && getStatus(r, c + 1 ) == DELETED)
		for (int i = y - 1; i <= y + 1; i++) {
			Common::gotoXY(x + 4, i);
			//putchar(' ');
			putchar(_imageBoard[i - _top][x + 4 - _left]);
		}
	//Delete top border
	if (r > 0 && getStatus(r - 1, c) == DELETED)
		for (int i = x - 3; i <= x + 3; i++) {
			Common::gotoXY(i, y - 2);
			//putchar(' ');
			putchar(_imageBoard[y - 2 - _top][i - _left]);
		}
	//Delete bottom border
	if (r < _size - 1 && getStatus(r + 1, c) == DELETED)
		for (int i = x - 3; i <= x + 3; i++) {
			Common::gotoXY(i, y + 2);
			//putchar(' ');
			putchar(_imageBoard[y + 2 - _top][i - _left]);
		}

	//Go back to center
	Common::gotoXY(x, y);
}

////////////////////////////////////////////////////////////////////////////

bool Board::outputMatchI()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "I-Matched!!! :D" << endl;
	return 1;
}

bool Board::outputMatchU()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "U-Matched!!! :D" << endl;
	return 1;
}

bool Board::outputMatchL()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "L-Matched!!! :D" << endl;
	return 1;
}

bool Board::outputMatchZ()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "Z-Matched!!! :D" << endl;
	return 1;
}

bool Board::outputNoMatch()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "Not a match :((" << endl;
	return 0;
}