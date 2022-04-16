#include "GameLinkedList.h"

GameLL::GameLL(int mode)
{
	_mode = mode;
	if (_mode == 4) _left += CELL_LENGTH;
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
	_board->drawInformationBoard();
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
	char tmp1 = _board->_dataColumn[firstCell.second].getPos(_mode - firstCell.first - 1)->_charHolder;
	char tmp2 = _board->_dataColumn[secondCell.second].getPos(_mode - secondCell.first - 1)->_charHolder;
	return tmp1 == tmp2;
}

bool GameLL::checkMatchI(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	if (firstCell.second == secondCell.second && abs(firstCell.first - secondCell.first) == 1) return 1;

	if (firstCell.first == secondCell.first) {
		if (secondCell.second < firstCell.second) swap(firstCell, secondCell);
		for (int i = firstCell.second + 1; i < secondCell.second; i++)
			if (_board->getTopRow(i) <= firstCell.first)
				return 0;
		return 1;
	}
	return 0;
}

bool GameLL::checkMatchL(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	if (firstCell.first > secondCell.first && _board->_dataColumn[firstCell.second]._tail->_r != firstCell.first) return 0;
	if (firstCell.first < secondCell.first && _board->_dataColumn[secondCell.second]._tail->_r != secondCell.first) return 0;

	if (secondCell.second < firstCell.second) swap(firstCell, secondCell);

	for (int i = firstCell.second + 1; i < secondCell.second; i++)
		if (_board->getTopRow(i) <= min(firstCell.first,secondCell.first))
			return 0;
	return 1;
}

bool GameLL::checkMatchZ(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	if (firstCell.second == secondCell.second) return 0;
	if (firstCell.second > secondCell.second) swap(firstCell, secondCell);

	for (int i = firstCell.second + 1; i < secondCell.second; i++)
		if (_board->getTopRow(i) <= min(firstCell.first, secondCell.first))
			return 0;

	if (firstCell.first > secondCell.first && _board->getTopRow(firstCell.second + 1) > firstCell.first) return 1;
	if (firstCell.first < secondCell.first && _board->getTopRow(secondCell.second - 1) > secondCell.first) return 1;

	return 0;
}

bool GameLL::checkMatchU(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	//Up - down
	if (_board->_dataColumn[firstCell.second]._head->_r == firstCell.first &&
		_board->_dataColumn[secondCell.second]._head->_r == secondCell.first)
			return 1;
	if (_board->_dataColumn[firstCell.second]._tail->_r == firstCell.first &&
		_board->_dataColumn[secondCell.second]._tail->_r == secondCell.first)
			return 1;

	//Left - right
	if (firstCell.second > secondCell.second) swap(firstCell, secondCell);

	//Same column
	if (firstCell.second == secondCell.second) {
		if (firstCell.second == 0 || firstCell.second == _mode - 1 ||
			_board->getTopRow(firstCell.second - 1) > max(firstCell.first, secondCell.first) ||
			_board->getTopRow(firstCell.second + 1) > max(firstCell.first, secondCell.first))
				return 1;
	}

	//U Left
	if (firstCell.first > secondCell.first) {
		for (int i = firstCell.second; i < secondCell.second; i++)
			if (_board->getTopRow(i) <= secondCell.first)
				return 0;
		if (firstCell.second == 0 || _board->getTopRow(firstCell.second - 1) > firstCell.first)
			return 1;
	}
	
	//U Right
	if (secondCell.first > firstCell.first) {
		for (int i = firstCell.second + 1; i <= secondCell.second; i++)
			if (_board->getTopRow(i) <= firstCell.first)
				return 0;
		if (secondCell.second == _mode - 1 || _board->getTopRow(secondCell.second + 1) > secondCell.first)
			return 1;
	}

	return 0;
}

bool GameLL::checkMatch(std::pair<int, int> firstCell, std::pair<int, int> secondCell, const bool& outputNofitication)
{
	if (outputNofitication) {
		if (!checkMatchEqualChar(firstCell, secondCell)) return _board->outputNoMatch();
		if (checkMatchI(firstCell, secondCell)) return _board->outputMatchI();
		if (checkMatchL(firstCell, secondCell)) return _board->outputMatchL();
		if (checkMatchZ(firstCell, secondCell)) return _board->outputMatchZ();
		if (checkMatchU(firstCell, secondCell)) return _board->outputMatchU();
		return _board->outputNoMatch();
	}
	if (!checkMatchEqualChar(firstCell, secondCell)) return 0;
	if (checkMatchI(firstCell, secondCell)) return 1;
	if (checkMatchL(firstCell, secondCell)) return 1;
	if (checkMatchZ(firstCell, secondCell)) return 1;
	if (checkMatchU(firstCell, secondCell)) return 1;
	return 0;
}

////////////////////////////////////////////////////////////////////////////////

void GameLL::unselectCell()
{
	_y = _board->getYCoor(_r);
	_x = _board->getXCoor(_c);
	Common::gotoXY(_x, _y);

	char charHolder;
	int status = (_mode - _board->_dataColumn[_c]._size) > _r ? DELETED : _board->_dataColumn[_c].getPos(_mode - _r - 1)->_status;
	if (status != DELETED)
		charHolder = _board->_dataColumn[_c].getPos(_mode - _r - 1)->_charHolder;

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

	char charHolder;
	int status = (_mode - _board->_dataColumn[_c]._size) > _r ? DELETED : _board->_dataColumn[_c].getPos(_mode - _r - 1)->_status;
	if (status != DELETED)
		charHolder = _board->_dataColumn[_c].getPos(_mode - _r - 1)->_charHolder;

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
	int status = (_mode - _board->_dataColumn[_c]._size) > _r ? DELETED : _board->_dataColumn[_c].getPos(_mode - _r - 1)->_status;

	if (status == LOCK || status == DELETED) {
		Common::playSound(ERROR_SOUND);
		return;
	}

	selectCell(RED);
	_board->lockCell(_r, _c);
	_lockedCellsArr.push_back(std::pair<int, int>(_r, _c));
	_lockedCells++;

	if (_lockedCells == 2) {
		sort(_lockedCellsArr.begin(), _lockedCellsArr.end());
		deleteCells();
		Common::gotoXY(_x, _y);
		selectCell(GREEN);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////

void GameLL::renderSuggestion(const int& r1, const int& c1, const int& r2, const int& c2)
{
	const int BGcolor[] = { AQUA, BRIGHT_WHITE };
	const int TXcolor[] = { BRIGHT_WHITE, BLACK };

	int cnt = 0, loop = 2;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_board->_size + 1) + _left + 12, _top + 10);
	cout << '(' << (char)(r1 + 'A') << ',' << c1 + 1 << ") and (" << (char)(r2 + 'A') << ',' << c2 + 1 << ')';

	while (cnt < loop) {
		Common::setConsoleColor(BGcolor[cnt], TXcolor[cnt]);

		int x = _board->getXCoor(c1), y = _board->getYCoor(r1);

		for (int i = y - 1; i <= y + 1; i++)
			for (int j = x - 3; j <= x + 3; j++) {
				Common::gotoXY(j, i);
				if (j == x && i == y)
					putchar(_board->_dataColumn[c1].getPos(_mode-r1-1)->_charHolder);
				else putchar(' ');
			}

		x = _board->getXCoor(c2); y = _board->getYCoor(r2);
		for (int i = y - 1; i <= y + 1; i++)
			for (int j = x - 3; j <= x + 3; j++) {
				Common::gotoXY(j, i);
				if (j == x && i == y)
					putchar(_board->_dataColumn[c2].getPos(_mode-r2-1)->_charHolder);
				else putchar(' ');
			}

		++cnt;

		if (cnt < loop) Sleep(500);
	}
	selectCell(GREEN);
}

bool GameLL::findPair(const bool& suggestion)
{
	for (int c1 = 0; c1 < _mode; c1++) {

		NodeLL* tmp = _board->_dataColumn[c1]._head;
		int size = _board->_dataColumn[c1]._size;

		for (int i = 0; i < size; i++) {
			int r1 = _mode - i - 1;

			for (int c2 = c1; c2 < _mode; c2++) {
				NodeLL* tmp2 = _board->_dataColumn[c2]._head;
				int size2 = _board->_dataColumn[c2]._size;

				for (int j = 0; j < size2; j++) {
					if (c1 == c2 && j <= i) continue;

					int r2 = _mode - j - 1;

					if (checkMatch(std::make_pair(r1, c1), std::make_pair(r2, c2), 0)) {
						if (suggestion) renderSuggestion(r1, c1, r2, c2);
						return 1;
					}

					tmp2 = tmp2->_next;
				}
			}
			tmp = tmp->_next;
		}
	}
	return 0;
}