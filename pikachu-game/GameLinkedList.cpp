#include "GameLinkedList.h"

GameLL::GameLL(int mode)
{
	_mode = mode;
	_board = new BoardLL(_mode, _left, _top);
	_player = new Players(_mode, _left, _top);
	_r = _c = 0;
	_x = _board->getXCoor(_c);
	_y = _board->getYCoor(_r);
	_remainCells = _mode * _mode;
	_lockedCells = 0;
	_lockedCellsArr.clear();
}

GameLL::~GameLL()
{
	delete _board;
	_board = nullptr;
	delete _player;
	_player = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void GameLL::renderBoard()
{
	_board->drawBoard();
	_board->generateBoardData();
	_board->initBoardBackground();
	_board->renderBoardData();
	_board->drawScoreBoard();
}

void GameLL::startGame()
{
	Common::clearConsole();
	_board->drawEnterName();
	_player->getPlayerName();


	Common::clearConsole();
	renderBoard();

	_timeStart = system_clock::now();

	if (findPair(0)) {
		_y = _board->getYCoor(0);
		_x = _board->getXCoor(0);
		selectCell(GREEN);

		while (!_finish && _remainCells) {
			switch (Common::getConsoleInput()){
			case 0:
				Common::playSound(4);
				break;
			case 1:
				Common::playSound(4);
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
			case 7:
				findPair(1);
				break;
			}
		}
	}
	endGame();
}

void GameLL::endGame()
{
	_timeEnd = system_clock::now();

	_player->_time_played = _timeEnd - _timeStart;
	_player->calculateScore(_player->_time_played, _remainCells);

	Sleep(1500);

	_player->writePlayersFile();

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);					//phải để dòng này ở đây thì nó mới fix được ô đen

	_board->drawEndgame(_player->_score);
	Sleep(1000);
	_board->drawLeaderBoard();
}

////////////////////////////////////////////////////////////////////////////////

void GameLL::moveLeft()
{
	if (_c > 0) {
		unselectCell();
		_c--;
		selectCell(GREEN);

		Common::playSound(MOVE_SOUND);
	}
	else {
		Common::playSound(ERROR_SOUND);
	}
}

void GameLL::moveRight()
{
	if (_c < _board->_size - 1) {
		unselectCell();
		_c++;
		selectCell(GREEN);

		Common::playSound(MOVE_SOUND);
	}
	else {
		Common::playSound(ERROR_SOUND);
	}
}

void GameLL::moveUp()
{
	if (_r > 0) {
		unselectCell();
		_r--;
		selectCell(GREEN);

		Common::playSound(MOVE_SOUND);
	}
	else {
		Common::playSound(ERROR_SOUND);
	}
}

void GameLL::moveDown()
{
	if (_r < _board->_size - 1) {
		unselectCell();
		_r++;
		selectCell(GREEN);

		Common::playSound(MOVE_SOUND);
	}
	else {
		Common::playSound(ERROR_SOUND);
	}
}

////////////////////////////////////////////////////////////////////////////////

bool GameLL::checkMatchEqualChar(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	return 1;
}

bool GameLL::checkMatchI(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	return 1;
}

bool GameLL::checkMatchL(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	return 1;
}

bool GameLL::checkMatchZ(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	return 1;
}

bool GameLL::checkMatchU_R(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	return 1;
}

bool GameLL::checkMatchU_C(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	return 1;
}

bool GameLL::checkMatchU(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	return 1;
}

bool GameLL::checkMatch(std::pair<int, int> firstCell, std::pair<int, int> secondCell, const bool& outputNofitication)
{
	return 1;
}

////////////////////////////////////////////////////////////////////////////////

void GameLL::unselectCell()
{
	_y = _board->getYCoor(_r);
	_x = _board->getXCoor(_c);
	Common::gotoXY(_x, _y);

	int status = _board->_dataColumn[_c].getPos(_mode - _r - 1)->_status;
	char charHolder = _board->_dataColumn[_c].getPos(_mode - _r - 1)->_charHolder;

	if (status == 1)
		Common::setConsoleColor(RED, BRIGHT_WHITE);
	else
		Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	for (int i = _y - 1; i <= _y + 1; i++)
		for (int j = _x - 3; j <= _x + 3; j++) {
			Common::gotoXY(j, i);
			if (status == DELETED) {
				putchar(_board->_imageBoard[i - _top][j - _left]);
				continue;
			}
			if (j == _x && i == _y) putchar(charHolder);
			else putchar(' ');
		}
	Common::gotoXY(_x, _y);
}

void GameLL::selectCell(const int& color)
{
	_y = _board->getYCoor(_r);
	_x = _board->getXCoor(_c);
	Common::gotoXY(_x, _y);
	Common::setConsoleColor(color, BRIGHT_WHITE);

	int status = _board->_dataColumn[_c].getPos(_mode - _r - 1)->_status;
	char charHolder = _board->_dataColumn[_c].getPos(_mode - _r - 1)->_charHolder;

	for (int i = _y - 1; i <= _y + 1; i++)
		for (int j = _x - 3; j <= _x + 3; j++) {
			Common::gotoXY(j, i);
			if (status == DELETED) {
				putchar(_board->_imageBoard[i - _top][j - _left]);
				continue;
			}
			if (j == _x && i == _y)
				putchar(charHolder);
			else putchar(' ');
		}
	Common::gotoXY(_x, _y);
}

void GameLL::deleteCells()
{
	_lockedCells = 0;
	if (!checkMatch(_lockedCellsArr[0], _lockedCellsArr[1], 1)) {
		Common::playSound(ERROR_SOUND);
		for (auto card : _lockedCellsArr)
			_board->unlockCell(card.first, card.second);
		_lockedCellsArr.clear();
		return;
	}

	_remainCells -= 2;
	for (auto card : _lockedCellsArr) {
		_board->deleteCell(card.first, card.second);		//First: row - Second: column
	}
	_lockedCellsArr.clear();

	if (!findPair(0)) _finish = 1;
}

void GameLL::lockCell()
{
	int status = _board->_dataColumn[_c].getPos(_mode - _r - 1)->_status;
	char charHolder = _board->_dataColumn[_c].getPos(_mode - _r - 1)->_charHolder;

	if (status == LOCK || status == DELETED) {
		Common::playSound(ERROR_SOUND);
		return;
	}

	selectCell(RED);
	_board->lockCell(_r, _c);
	_lockedCellsArr.push_back(std::pair<int, int>(_r, _c));
	_lockedCells++;

	if (_lockedCells == 2) {
		deleteCells();
		Common::gotoXY(_x, _y);
		selectCell(GREEN);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

void GameLL::renderSuggestion(const int& r1, const int& c1, const int& r2, const int& c2)
{
	
}

bool GameLL::findPair(const bool& suggestion)
{
	
	return 1;
}