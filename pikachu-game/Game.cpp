#include "Game.h"

Game::Game(int mode)
{
	_mode = mode;
	if (_mode == 4) _left += CELL_LENGTH * 2;
	else _left += CELL_LENGTH;
	_board = new Board(_mode, _left, _top);
	_player = new Players(_mode);
	_r = _c = 0;
	_x = _board->getXCoor(_c);
	_y = _board->getYCoor(_r);
	_remainCells = _mode * _mode;
	_lockedCells = 0;
	_lockedCellsArr.clear();
}

Game::~Game()
{
	delete _board;
	_board = nullptr;
	delete _player;
	_player = nullptr;
}

////////////////////////////////////////////////////////////////////////////////

void Game::renderBoard()
{
	_board->drawBoard();
	_board->generateBoardData();
	_board->initBoardBackground();
	_board->renderBoardData();
	_board->drawScoreBoard();
}

void Game::startGame()
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
			switch (Common::getConsoleInput())
			{
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

void Game::endGame()
{
	_timeEnd = system_clock::now();

	_player->_time_played = _timeEnd - _timeStart;
	_player->calculateScore(_player->_time_played, _remainCells);

	Sleep(1500);

	_player->writePlayersFile();

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);					//phải để dòng này ở đây thì nó mới fix được ô đen

	_board->drawEndgame(_player->_score);
	Sleep(5000);
	_board->drawLeaderBoard();
}

////////////////////////////////////////////////////////////////////////////////

void Game::moveLeft()
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

void Game::moveRight()
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

void Game::moveUp()
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

void Game::moveDown()
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
		for (int i = start + 1; i < end; i++)
		{
			if (_board->getStatus(firstCell.first, i) != DELETED) return 0;
		}
		return 1;
	}
	if (firstCell.second == secondCell.second)//Same collumn
	{
		int start = firstCell.first;
		int end = secondCell.first;
		if (start > end) swap(start, end);
		for (int i = start + 1; i < end; i++)
		{
			if (_board->getStatus(i, firstCell.second) != DELETED) return 0;
		}
		return 1;
	}
	
	return 0;
}

bool Game::checkMatchL(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	std::pair<int, int> tmp;

	tmp.first = firstCell.first;
	tmp.second = secondCell.second;

	if (_board->getStatus(tmp.first, tmp.second) == DELETED){
		if (checkMatchI(tmp, secondCell) && checkMatchI(tmp, firstCell)) return 1;
	}

	tmp.first = secondCell.first;
	tmp.second = firstCell.second;
	if (_board->getStatus(tmp.first, tmp.second) == DELETED){
		if (checkMatchI(tmp, secondCell) && checkMatchI(tmp, firstCell)) return 1;
	}

	return 0;
}

bool Game::checkMatchZ(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	//First: row - Second: column
	std::pair<int, int> A, B;
	if (firstCell.second > secondCell.second) swap(firstCell, secondCell); //Cố định firstCell là ô bên trái

	//Horizontal check (Z)
	A.first = firstCell.first;
	B.first = secondCell.first;
	for (int i = firstCell.second + 1; i < secondCell.second; i++) {
		A.second = B.second = i;
		int x = _board->getStatus(A.first, A.second);
		if (_board->getStatus(A.first, A.second) != DELETED) break;
		if (_board->getStatus(B.first, B.second) != DELETED) continue;
		if (!checkMatchI(secondCell, B)) continue;
		if (checkMatchI(A, B)) return 1;
	}

	if (firstCell.first > secondCell.first) swap(firstCell, secondCell); //Cố định firstCell là ô ở trên
	//Vertical check
	A.second = firstCell.second;
	B.second = secondCell.second;
	for (int i = firstCell.first + 1; i < secondCell.first; i++) {
		A.first = B.first = i;
		if (_board->getStatus(A.first, A.second) != DELETED) break;
		if (_board->getStatus(B.first, B.second) != DELETED) continue;
		if (!checkMatchI(secondCell, B)) continue;
		if (checkMatchI(A, B)) return 1;
	}
	return 0;
}

bool Game::checkMatchU_R(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	int size = _board->_size;

	if (firstCell.first != secondCell.first) return 0;
	if (firstCell.first == 0 || firstCell.first == size - 1) return 1;//If both cells are at the top or bottom edge

	std::pair<int, int> A, B;

	A.second = firstCell.second;
	B.second = secondCell.second;

	for (int i = firstCell.first - 1; i >= 0; i--){
		A.first = B.first = i;
		if (_board->getStatus(A.first, A.second) != DELETED ||
			_board->getStatus(B.first, B.second) != DELETED) break;
		if (i == 0 || checkMatchI(A, B)) return 1;
	}

	for (int i = firstCell.first + 1; i < size; i++){
		A.first = B.first = i;
		if (_board->getStatus(A.first, A.second) != DELETED ||
			_board->getStatus(B.first, B.second) != DELETED) break;
		if (i == size - 1 || checkMatchI(A, B)) return 1;
	}

	return 0;
}

bool Game::checkMatchU_C(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	int size = _board->_size;

	if (firstCell.second != secondCell.second) return 0;
	if (firstCell.second == 0 || firstCell.second == size - 1)//If both cells are at the left or right edge
		return 1;

	std::pair<int, int> A, B;

	A.first = firstCell.first;
	B.first = secondCell.first;

	for (int i = firstCell.second - 1; i >= 0; i--){
		A.second = B.second = i;
		if (_board->getStatus(A.first, A.second) != DELETED ||
			_board->getStatus(B.first, B.second) != DELETED) break;
		if (i == 0 || checkMatchI(A, B)) return 1;
	}

	for (int i = firstCell.second + 1; i < size; i++)
	{
		A.second = i;
		B.second = i;
		if (_board->getStatus(A.first, A.second) != DELETED ||
			_board->getStatus(B.first, B.second) != DELETED) break;
		if (i == size - 1 || checkMatchI(A, B)) return 1;
	}

	return 0;
}

bool Game::checkMatchU(std::pair<int, int> firstCell, std::pair<int, int> secondCell)
{
	if (checkMatchU_R(firstCell, secondCell) || checkMatchU_C(firstCell, secondCell)) return 1;

	std::pair<int, int>A, B;
	if (firstCell.first > secondCell.first) swap(firstCell, secondCell);

	//U - Up
	A.first  = firstCell.first;
	A.second = secondCell.second;
	if (_board->getStatus(A.first, A.second) == DELETED){
		if (checkMatchI(A, secondCell) && checkMatchU_R(firstCell, A)) return 1;
		if (checkMatchI(A, firstCell) && checkMatchU_C(A, secondCell)) return 1;
	}

	//U - Down
	B.first  = secondCell.first;
	B.second = firstCell.second;
	if (_board->getStatus(B.first, B.second) == DELETED){
		if (checkMatchI(B, firstCell) && checkMatchU_R(B, secondCell)) return 1;
		if (checkMatchI(B, secondCell) && checkMatchU_C(firstCell, B)) return 1;
	}

	return 0;
}

bool Game::checkMatch(std::pair<int, int> firstCell, std::pair<int, int> secondCell, const bool& outputNofitication)
{
	if (!outputNofitication) {
		if (!checkMatchEqualChar(firstCell, secondCell)) return 0;
		if (checkMatchI(firstCell, secondCell)) return 1;
		if (checkMatchL(firstCell, secondCell)) return 1;
		if (checkMatchZ(firstCell, secondCell)) return 1;
		if (checkMatchU(firstCell, secondCell)) return 1;
		return 0;
	}
	if (!checkMatchEqualChar(firstCell, secondCell)) return _board->outputNoMatch();
	if (checkMatchI(firstCell, secondCell)) return _board->outputMatchI();
 	if (checkMatchL(firstCell, secondCell)) return _board->outputMatchL();
	if (checkMatchZ(firstCell, secondCell)) return _board->outputMatchZ();
	if (checkMatchU(firstCell, secondCell)) return _board->outputMatchU();
	return _board->outputNoMatch();
}

////////////////////////////////////////////////////////////////////////////////

void Game::unselectCell()
{
	_y = _board->getYCoor(_r);
	_x = _board->getXCoor(_c);
	Common::gotoXY(_x, _y);

	if (_board->getStatus(_r, _c) == 1)
		Common::setConsoleColor(RED, BRIGHT_WHITE);
	else
		Common::setConsoleColor(BRIGHT_WHITE, BLACK);

	for (int i = _y - 1; i <= _y + 1; i++)
		for (int j = _x - 3; j <= _x + 3; j++) {
			Common::gotoXY(j, i);
			if (_board->_dataBoard[_r][_c]._Status == DELETED) {
				putchar(_board->_imageBoard[i - _top][j - _left]);
				continue;
			}
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
			if (_board->_dataBoard[_r][_c]._Status == DELETED) {
				putchar(_board->_imageBoard[i - _top][j - _left]);
				continue;
			}
			if (j == _x && i == _y)
				putchar(_board->getCharRC(_r, _c));
			else putchar(' ');
		}
	Common::gotoXY(_x, _y);
}

void Game::deleteCells()
{
	_lockedCells = 0;
	if (!checkMatch(_lockedCellsArr[0], _lockedCellsArr[1],1)) {
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

void Game::lockCell()
{
	if (_board->getStatus(_r, _c) == LOCK || _board->getStatus(_r, _c) == DELETED) {
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

void Game::renderSuggestion(const int& r1, const int& c1, const int& r2, const int& c2)
{
	const int BGcolor[] = { AQUA, BRIGHT_WHITE };
	const int TXcolor[] = { BRIGHT_WHITE, BLACK };

	int cnt = 0, loop = 2;

	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
	Common::gotoXY(CELL_LENGTH * (_board->_size + 1) + 6 + _left, 2 + _top);
	cout << '(' << (char)(r1 + 'A') << ',' << c1 + 1 << ") and (" << (char)(r2 + 'A') << ',' << c2 + 1 << ')';

	while (cnt < loop) {
		Common::setConsoleColor(BGcolor[cnt], TXcolor[cnt]);

		int x = _board->getXCoor(c1), y = _board->getYCoor(r1);

		for (int i = y - 1; i <= y + 1; i++)
			for (int j = x - 3; j <= x + 3; j++) {
				Common::gotoXY(j, i);
				if (j == x && i == y)
					putchar(_board->getCharRC(r1,c1));
				else putchar(' ');
			}

		x = _board->getXCoor(c2); y = _board->getYCoor(r2);
		for (int i = y - 1; i <= y + 1; i++)
			for (int j = x - 3; j <= x + 3; j++) {
				Common::gotoXY(j, i);
				if (j == x && i == y)
					putchar(_board->getCharRC(r2, c2));
				else putchar(' ');
			}

		++cnt;

		if (cnt<loop) Sleep(500);
	}
	selectCell(GREEN);
}

bool Game::findPair(const bool& suggestion)
{
	for (int r1 = 0; r1 < _mode; r1++)
		for (int c1 = 0; c1 < _mode; c1++) {

			if (_board->_dataBoard[r1][c1]._Status == DELETED) continue;
			char charHolder1 = _board->_dataBoard[r1][c1]._CharHolder;

			for (int r2 = r1; r2 < _mode; r2++)
				for (int c2 = 0; c2 < _mode; c2++) {

					if (r1 == r2 && c2 <= c1) continue;

					if (_board->_dataBoard[r2][c2]._Status == DELETED) continue;
					char charHolder2 = _board->_dataBoard[r2][c2]._CharHolder;

					if (charHolder1 != charHolder2) continue;

					if (checkMatch(std::make_pair(r1, c1), std::make_pair(r2, c2), 0)) {
						if (suggestion) renderSuggestion(r1,c1,r2,c2);
						return 1;
					}
				}
		}
	return 0;
}