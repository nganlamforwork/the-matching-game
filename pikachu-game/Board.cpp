﻿#include "Board.h"
#include "Node.h"
#include "Common.h"


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
}

Board::~Board()
{
    for (int i = 0; i < _size; i++)
        delete[] _dataBoard[i];
    delete[] _dataBoard,
        _dataBoard = nullptr;

	delete[] _pos;
}

int Board::getSize()
{
	return _size;
}

int Board::getLeftCoor()
{
	return _left;
}

int Board::getTopCoor()
{
	return _top;
}

////////////////////////////////////////////////////////////////////////////

void Board::generateBoardData()
{
    srand(time(NULL));

    bool* checkDuplicate = new bool[_size * _size];
    _pos = new int[_size * _size];

    //Build random character pair
	for (int i = 0; i < _size * _size; i += 2) {
		if (i / 2 > 25)
			_pairCharacter[i] = _pairCharacter[i + 1] = /*rand() % 26 + 'A'*/ rand() % 1 + 'A';
		else
			_pairCharacter[i] = _pairCharacter[i + 1] = /*i / 2 + 'A'*/ rand() % 1 + 'A';
	}

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
	for (int i = 1; i < _size * CELL_LENGTH; i++){
		//Sleep(2);
		if (i % CELL_LENGTH == 0)
			putchar(205);
		else
			putchar(205);
	}
	putchar(187);


	//Vẽ biên phải
	for (int i = 1; i < _size * CELL_HEIGHT; i++){
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
	for (int i = 1; i < _size * CELL_LENGTH; i++){
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
	for (int i = 1; i < _size * CELL_HEIGHT; i++){
		//Sleep(5);
		Common::gotoXY(_left + 1, _size * CELL_HEIGHT + _top - i);
		if (i % CELL_HEIGHT == 0)
			putchar(186);
		else
			putchar(186);
	}

	//Vẽ đường dọc
	for (int i = 1; i < _size * CELL_HEIGHT; i++){
		for (int j = CELL_LENGTH; j < _size * CELL_LENGTH; j += CELL_LENGTH){
			if (i % CELL_HEIGHT != 0){
				Common::gotoXY(j + _left + 1, i + _top);
				putchar(179);
			}
		}
		//Sleep(5);
	}

	//Vẽ đường ngang
	for (int i = 1; i < _size * CELL_LENGTH; i++){
		for (int j = CELL_HEIGHT; j < _size * CELL_HEIGHT; j += CELL_HEIGHT){
			Common::gotoXY(i + _left + 1, j + _top);
			if (i % CELL_LENGTH == 0)
				putchar(32);
			else
				putchar(196);
		}
		//Sleep(2);
	}

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
	for (int i = 1; i < CELL_HEIGHT * 4; i++)
	{
		Common::gotoXY(CELL_LENGTH * (_size + 4) + _left, i + _top);
		putchar(186);
		//Sleep(5);
	}
	Common::gotoXY(CELL_LENGTH * (_size + 4) + _left, CELL_HEIGHT * 4 + _top);
	putchar(188);

	//Vẽ biên dưới
	for (int i = 1; i < CELL_LENGTH * 3; i++)
	{
		Common::gotoXY(CELL_LENGTH * (_size + 4) - i + _left, CELL_HEIGHT * 4 + _top);
		putchar(205);
		//Sleep(5);
	}
	Common::gotoXY(CELL_LENGTH * (_size + 4) - CELL_LENGTH * 3 + _left, CELL_HEIGHT * 4 + _top);
	putchar(200);

	//Vẽ biên trái
	for (int i = CELL_HEIGHT * 4 - 1; i >= 1; i--)
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

void Board::drawEndgame(int score)
{
	int left = 0, top = 0;
	Common::clearConsole();
	ifstream endgame("GameOver.txt");
	string s;
	int i = 0;
	while (!endgame.eof())
	{
		Common::gotoXY(left + 20, top + i);
		getline(endgame, s);
		cout << s;
		i++;
	}
	endgame.close();

	Common::gotoXY(left + 55, top + 11);
	cout << "Your score is: " << score << "!!!";
}

//https://patorjk.com/software/taag/#p=testall&f=Blocks&t=The%20Matching%20Game%0A

void Board::drawEnterName()
{
	int left = 0, top = 0;
	ifstream inName("EnterName.txt");
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	string s;
	int i = 0;
	while (!inName.eof())
	{
		Common::gotoXY(left + 20, top + 2 + i);
		getline(inName, s);
		cout << s << endl;
		i++;
	}
	inName.close();
}

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

void Board::drawLeaderBoard()
{
	Common::clearConsole();
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	int left = 50, top = 10;//left và top của leaderboard
	int height = 15, width = 30;

	ifstream boardtitle("Leaderboard.txt");
	string s;
	int i = 0;
	while (getline(boardtitle, s))
	{
		Common::gotoXY(left - 40, top - 10 + i);
		cout << s;
		i++;
	}
	boardtitle.close();

	vector<Players> playerList;
	Players().readPlayersFile(playerList);

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
	return _dataBoard[r][c].getStatus();
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
			putchar(' ');
		}

	//Delete left border
	if (c > 0 && getStatus(r, c - 1) == DELETED)
		for (int i = y - 1; i <= y + 1; i++) {
			Common::gotoXY(x - 4, i);
			putchar(' ');
		}
	//Delete right border
	if (c < _size - 1 && getStatus(r, c + 1 ) == DELETED)
		for (int i = y - 1; i <= y + 1; i++) {
			Common::gotoXY(x + 4, i);
			putchar(' ');
		}
	//Delete top border
	if (r > 0 && getStatus(r - 1, c) == DELETED)
		for (int i = x - 3; i <= x + 3; i++) {
			Common::gotoXY(i, y - 2);
			putchar(' ');
		}
	//Delete bottom border
	if (r < _size - 1 && getStatus(r + 1, c) == DELETED)
		for (int i = x - 3; i <= x + 3; i++) {
			Common::gotoXY(i, y + 2);
			putchar(' ');
		}

	//Go back to center
	Common::gotoXY(x, y);
}

////////////////////////////////////////////////////////////////////////////

bool Board::outputMatchI()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "I-Matched!! :D" << endl;
	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	Sleep(WAIT_TIME);
	cout << "             " << endl;*/
	return 1;
}

bool Board::outputMatchU()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "U-Matched!! :D" << endl;
	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	Sleep(WAIT_TIME);
	cout << "             " << endl;*/
	return 1;
}

bool Board::outputMatchL()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "L-Matched!! :D" << endl;
	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	Sleep(WAIT_TIME);
	cout << "             " << endl;*/
	return 1;
}

bool Board::outputMatchZ()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "Z-Matched!! :D" << endl;
	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	Sleep(WAIT_TIME);
	cout << "             " << endl;*/
	return 1;
}

bool Board::outputNoMatch()
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	cout << "Not a match :(" << endl;
	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
	Sleep(WAIT_TIME + 100);
	cout << "              " << endl;*/
	return 0;
}