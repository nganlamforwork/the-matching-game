#include "Game.h"
#include "Common.h"

Game::Game(int mode)
{
	_mode = mode;
	_board = new Board(_mode, _left, _top);
	_r = _c = 0;
	_x = _board->getXCoor(_c);
	_y = _board->getYCoor(_r);
	_remainCards = _mode * _mode;
	_lockedCards = 0;
	_lockedCardsArr.clear();
}

Game::~Game()
{
	delete _board;
	_board = nullptr;
}

void Game::setMode(int mode)
{
	_mode = mode;
}

void Game::renderBoard()
{
	_board->drawBoard();
	_board->generateBoardData();
	_board->renderBoardData();

}

void Game::startGame()
{
	Common::clearConsole();
	renderBoard();

	_y = _board->getYCoor(0);
	_x = _board->getXCoor(0);
	selectCell(GREEN);

	while (!_finish && _remainCards) {
		switch (Common::getConsoleInput())
		{
			case 0:
				Common::playSound(4);
				_finish = 0;
				break;
			case 1:
				Common::playSound(4);
				Common::setConsoleColor(BLACK, BRIGHT_WHITE);
				_finish = 1;
				break;
			case 2:
				moveUp();
				break;
			case 3:
				moveLeft();
				break;
			case 4:
				moveRight();
				break;
			case 5:
				moveDown();
				break;
			case 6:
				Common::playSound(3);
				lockCell();
				break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

void Game::unselectCell()
{
	_y = _board->getYCoor(_r);
	_x = _board->getXCoor(_c);
	Common::gotoXY(_x, _y);
	
	if (_board->getStatus(_r,_c)==1)
		Common::setConsoleColor(RED, BRIGHT_WHITE);
	else 
		Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	for (int i = _y - 1; i <= _y + 1; i++)
		for (int j = _x - 3; j <= _x + 3; j++) {
			Common::gotoXY(j, i);
			if (j == _x && i == _y) putchar(_board->getCharRC(_r, _c));
			else putchar(' ');
		}
	Common::gotoXY(_x, _y);
}

void Game::selectCell(const int& color)
{
	_y = _board->getYCoor(_r);
	_x = _board->getXCoor(_c);
	Common::gotoXY(_x, _y);
	Common::setConsoleColor(color, BRIGHT_WHITE);

	for (int i = _y - 1; i <= _y + 1; i++)
		for (int j = _x - 3; j <= _x + 3; j++) {
			Common::gotoXY(j, i);
			if (j == _x && i == _y) putchar(_board->getCharRC(_r, _c));
			else putchar(' ');
		}
	Common::gotoXY(_x, _y);
}

////////////////////////////////////////////////////////////////////////////////

void Game::moveDown()
{
	if (_r < _board->getSize()-1){
		unselectCell();
		_r++;
		selectCell(GREEN);

		Common::playSound(MOVE_SOUND);
	}
	else{
		Common::playSound(ERROR_SOUND);
	}
}

void Game::moveUp()
{
	if (_r > 0){
		unselectCell();
		_r--;
		selectCell(GREEN);

		Common::playSound(MOVE_SOUND);
	}
	else {
		Common::playSound(ERROR_SOUND);
	}
}

void Game::moveLeft()
{
	if (_c > 0){
		unselectCell();
		_c--;
		selectCell(GREEN);

		Common::playSound(MOVE_SOUND);
	}
	else {
		Common::playSound(ERROR_SOUND);
	}
}

void Game::moveRight()
{
	if (_c < _board->getSize() - 1){
		unselectCell();
		_c++;
		selectCell(GREEN);

		Common::playSound(MOVE_SOUND);
	}
	else {
		Common::playSound(ERROR_SOUND);
	}
}

////////////////////////////////////////////////////////////////////////////////

bool Game::checkMatchEqualChar(std::pair<int,int> firstCell, std::pair<int, int> secondCell)
{
	return (_board->getCharRC(firstCell.first, firstCell.second) ==
		_board->getCharRC(secondCell.first, secondCell.second));
}

bool Game::checkMatchI(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	if (firstCell.first == secondCell.first)//Same row
	{
		int start = firstCell.second;
		int end = secondCell.second;
		if (start > end) swap(start, end);
		if (abs(start - end) == 1) return 1;
		for (int i = start + 1; i < end; i++)
		{
			if (_board->getStatus(firstCell.first, i) != -1) return 0;
		}
		return 1;
	}
	if (firstCell.second == secondCell.second)//Same collumn
	{
		int start = firstCell.first;
		int end = secondCell.first;
		if (start > end) swap(start, end);
		if (abs(start - end) == 1) return 1;
		for (int i = start + 1; i < end; i++)
		{
			if (_board->getStatus(i, firstCell.second) != -1) return 0;
		}
		return 1;
	}
	
	return 0;
}
bool Game::checkMatchL(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	std::pair<int, int> A;

	A.first = firstCell.first;
	A.second = secondCell.second;

	if (_board->getStatus(firstCell.first, secondCell.second) == -1)
	{
		if (checkMatchI(A, secondCell) && checkMatchI(A, firstCell)) return 1;
	}

	A.first = secondCell.first;
	A.second = firstCell.second;
	if (_board->getStatus(secondCell.first, firstCell.second) == -1)
	{
		if (checkMatchI(A, secondCell) && checkMatchI(A, firstCell)) return 1;
	}

	return 0;
}
bool Game::checkMatchZ(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	return 1;
}
bool Game::checkMatchU(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	return 1;
}
bool Game::checkMatch(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	if (!checkMatchEqualChar(firstCell, secondCell)) return 0;
	if (checkMatchI(firstCell, secondCell)) return 1;
	if (checkMatchL(firstCell, secondCell)) return 1;
	if (checkMatchZ(firstCell, secondCell)) return 0;
	if (checkMatchU(firstCell, secondCell)) return 0;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

void Game::deleteCards()
{
	_lockedCards = 0;
	if (!checkMatch(_lockedCardsArr[0], _lockedCardsArr[1])) {
		Common::playSound(ERROR_SOUND);
		for (auto card : _lockedCardsArr)
			_board->unlockCell(card.first, card.second);
		_lockedCardsArr.clear();
		return;
	}

	_remainCards -= 2;
	for (auto card : _lockedCardsArr) {
		_board->deleteCell(card.first, card.second);		//First: row - Second: column
	}
	_lockedCardsArr.clear();
}

void Game::lockCell()
{
	if (_board->getStatus(_r, _c) == LOCK_ || _board->getStatus(_r, _c) == DELETED_) {
		Common::playSound(ERROR_SOUND);
		return;
	}

	selectCell(RED);
	_board->lockCell(_r, _c);
	_lockedCardsArr.push_back(std::pair<int, int>(_r, _c));
	_lockedCards++;

	if (_lockedCards == 2) {
		deleteCards();
		Common::gotoXY(_x, _y);
		selectCell(GREEN);
	}
}