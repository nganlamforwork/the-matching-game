#include "Board.h"
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

void Board::setSize(const int& size)
{
	_size = size;
}

void Board::setLeftCoor(const int& left)
{
	_left = left;
}

void Board::setTopCoor(const int& top)
{
	_top = top;
}

////////////////////////////////////////////////////////////////////////////

void Board::generateBoardData()
{
    srand(time(NULL));

    bool* checkDuplicate = new bool[_size * _size];
    int* pos = new int[_size * _size];

    //Build random character pair
    for (int i = 0; i < _size * _size; i += 2)
        if (i / 2 > 25)
            _pairCharacter[i] = _pairCharacter[i + 1] = rand() % 26 + 'A';
        else
            _pairCharacter[i] = _pairCharacter[i + 1] = i / 2 + 'A';

    //Build position array
    for (int i = 0; i < _size * _size; i++) checkDuplicate[i] = 0;
    for (int i = 0; i < _size * _size; i++) {
        int tmp = 0;

        do {
            tmp = rand() % (_size * _size);
        } while (checkDuplicate[tmp]);

        checkDuplicate[tmp] = 1;
        pos[i] = tmp;
    }


    //Build table
    for (int i = 0; i < _size * _size; i++) {
        int r = pos[i] / _size;
        int c = pos[i] % _size;
        _dataBoard[r][c].setCharHolder(_pairCharacter[i]);
    }

    delete[] pos;
    delete[] checkDuplicate;
}

void Board::drawBoard() 
{
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::clearConsole();

	//Vẽ biên trên
	Common::gotoXY(_left + 1, _top);
	putchar(201);
	for (int i = 1; i < _size * 4; i++)
	{
		Sleep(5);
		if (i % 4 == 0)
			putchar(209);
		else
			putchar(205);
	}
	putchar(187);


	//Vẽ biên phải
	for (int i = 1; i < _size * 2; i++)
	{
		Sleep(10);
		Common::gotoXY(_size * 4 + _left + 1, i + _top);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(182);
	}
	Common::gotoXY(_size * 4 + _left + 1, _size * 2 + _top);
	putchar(188);


	//Ve biên dưới
	for (int i = 1; i < _size * 4; i++)
	{
		Common::gotoXY(_size * 4 + _left - i + 1, _size * 2 + _top);
		Sleep(5);
		if (i % 4 == 0)
			putchar(207);
		else
			putchar(205);
	}
	Common::gotoXY(_left + 1, _size * 2 + _top);
	putchar(200);

	//Ve biên trái
	for (int i = 1; i < _size * 2; i++)
	{
		Sleep(10);
		Common::gotoXY(_left + 1, _size * 2 + _top - i);
		if (i % 2 != 0)
			putchar(186);
		else
			putchar(199);
	}

	//Vẽ đường dọc
	for (int i = 1; i < _size * 2; i++)
	{
		for (int j = 4; j < _size * 4; j += 4)
		{
			if (i % 2 != 0)
			{
				Common::gotoXY(j + _left + 1, i + _top);
				putchar(179);
			}
		}
		Sleep(10);
	}

	//Vẽ đường ngang
	for (int i = 1; i < _size * 4; i++)
	{
		for (int j = 2; j < _size * 2; j += 2)
		{
			Common::gotoXY(i + _left + 1, j + _top);
			if (i % 4 == 0)
				putchar(197);
			else
				putchar(196);
		}
		Sleep(5);
	}
}

void Board::renderBoardData()
{
	for (int i = 0; i < _size; i++)
		for (int j = 0; j < _size; j++) {
			Common::gotoXY(_left + 3 + 4 * j, _top + 1 + 2 * i);
			_dataBoard[i][j].setX(_left + 3 + 4 * j);
			_dataBoard[i][j].setY(_top + 1 + 2 * i);

			putchar(_dataBoard[i][j].getCharHolder());
		}
}

////////////////////////////////////////////////////////////////////////////

int Board::getXCoor(const int& c)
{
	return _left + 3 + 4 * c;
}

int Board::getYCoor(const int& r)
{
	return _top + 1 + 2 * r;
}

int Board::getCCoor(const int& x)
{
	return (x - _left - 3) / 4;
}

int Board::getRCoor(const int& y)
{
	return (y - _top - 1) / 24;
}

char Board::getCharRC(const int& r, const int& c)
{
	return _dataBoard[r][c].getCharHolder();
}

int Board::getStatus(const int& r, const int& c)
{
	return _dataBoard[r][c].getStatus();
}

////////////////////////////////////////////////////////////////////////////

void Board::lockCell(const int& r, const int& c)
{
	_dataBoard[r][c].setStatus(LOCK_);
}

void Board::unlockCell(const int& r, const int& c)
{
	_dataBoard[r][c].setStatus(NORMAL_);

	Common::gotoXY(getXCoor(c), getYCoor(r));
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	putchar(_dataBoard[r][c].getCharHolder());
}

void Board::deleteCell(const int& r, const int& c)
{
	_dataBoard[r][c].setStatus(DELETED_);
	_dataBoard[r][c].swapChar();

	Common::gotoXY(getXCoor(c),getYCoor(r));
	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	putchar(_dataBoard[r][c].getCharHolder());
}