#include "Board.h"

Board::Board(int size)
{
	_size = size;
	_remainCouple = _size * _size / 2;
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
    int* pairCharacter = new int[_size * _size];

    //Build random character pair
    for (int i = 0; i < _size * _size; i += 2)
        if (i / 2 > 25)
            pairCharacter[i] = pairCharacter[i + 1] = rand() % 26 + 'A';
        else
            pairCharacter[i] = pairCharacter[i + 1] = i / 2 + 'A';

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

    //Initiallized
    char** dataTable = new char* [_size];
    for (int i = 0; i < _size; i++)
        dataTable[i] = new char[_size];

    //Build table
    for (int i = 0; i < _size * _size; i++)
        dataTable[pos[i] / _size][pos[i] % _size] = pairCharacter[i];

    delete[] pos;
    delete[] checkDuplicate;
}