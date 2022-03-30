//#include "BoardLinkedList.h"
//
//
//BoardLL::BoardLL(int size, int left, int top)
//{
//	_size = size;
//	_left = left;
//	_top = top;
//	_remainCouple = _size * _size / 2;
//	_pairCharacter = new int[_size * _size];
//
//	//Board
//	_dataBoard = new Node * [_size];
//	for (int i = 0; i < _size; i++)
//		_dataBoard[i] = new Node[_size];
//
//	//Linked list
//	_dataRow = new LinkedList[_size];
//	_dataColumn = new LinkedList[_size];
//}
//
//BoardLL::~BoardLL()
//{
//	for (int i = 0; i < _size; i++)
//		delete[] _dataBoard[i];
//	delete[] _dataBoard,
//		_dataBoard = nullptr;
//
//	delete[] _dataRow, _dataRow = nullptr;
//	delete[] _dataColumn, _dataColumn = nullptr;
//
//	delete[] _pos;
//}
//
//////////////////////////////////////////////////////////////////////////////
//
//void BoardLL::generateBoardData()
//{
//	srand(time(NULL));
//
//	bool* checkDuplicate = new bool[_size * _size];
//	_pos = new int[_size * _size];
//
//	//Build random character pair
//	for (int i = 0; i < _size * _size; i += 2) 
//		_pairCharacter[i] = rand() % 26 + 'A';
//
//	//Build position array
//	for (int i = 0; i < _size * _size; i++) checkDuplicate[i] = 0;
//	for (int i = 0; i < _size * _size; i++) {
//		int tmp = 0;
//
//		do {
//			tmp = rand() % (_size * _size);
//		} while (checkDuplicate[tmp]);
//
//		checkDuplicate[tmp] = 1;
//		_pos[i] = tmp;
//	}
//
//
//	//Build table
//	for (int i = 0; i < _size * _size; i++) {
//		int r = _pos[i] / _size;
//		int c = _pos[i] % _size;
//		_dataBoard[r][c].setCharHolder(_pairCharacter[i]);
//	}
//
//	delete[] checkDuplicate;
//}
//
//void BoardLL::drawBoard()
//{
//	Common::clearConsole();
//
//	Common::gotoXY(120, 28);
//	Common::setConsoleColor(BRIGHT_WHITE, AQUA);
//	cout << "H: MOVE SUGGESTION";
//	Common::gotoXY(120, 30);
//	Common::setConsoleColor(BRIGHT_WHITE, YELLOW);
//	cout << "ESC: EXIT";
//
//	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
//	//Vẽ biên trên
//	Common::gotoXY(_left + 1, _top);
//	putchar(201);
//	for (int i = 1; i < _size * CELL_LENGTH; i++) {
//		//Sleep(2);
//		if (i % CELL_LENGTH == 0)
//			putchar(205);
//		else
//			putchar(205);
//	}
//	putchar(187);
//
//
//	//Vẽ biên phải
//	for (int i = 1; i < _size * CELL_HEIGHT; i++) {
//		//Sleep(5);
//		Common::gotoXY(_size * CELL_LENGTH + _left + 1, i + _top);
//		if (i % CELL_HEIGHT == 0)
//			putchar(186);
//		else
//			putchar(186);
//	}
//	Common::gotoXY(_size * CELL_LENGTH + _left + 1, _size * CELL_HEIGHT + _top);
//	putchar(188);
//
//
//	//Ve biên dưới
//	for (int i = 1; i < _size * CELL_LENGTH; i++) {
//		Common::gotoXY(_size * CELL_LENGTH + _left - i + 1, _size * CELL_HEIGHT + _top);
//		//Sleep(2);
//		if (i % CELL_LENGTH == 0)
//			putchar(205);
//		else
//			putchar(205);
//	}
//	Common::gotoXY(_left + 1, _size * CELL_HEIGHT + _top);
//	putchar(200);
//
//	//Ve biên trái
//	for (int i = 1; i < _size * CELL_HEIGHT; i++) {
//		//Sleep(5);
//		Common::gotoXY(_left + 1, _size * CELL_HEIGHT + _top - i);
//		if (i % CELL_HEIGHT == 0)
//			putchar(186);
//		else
//			putchar(186);
//	}
//
//	//Vẽ đường dọc
//	for (int i = 1; i < _size * CELL_HEIGHT; i++) {
//		for (int j = CELL_LENGTH; j < _size * CELL_LENGTH; j += CELL_LENGTH) {
//			if (i % CELL_HEIGHT != 0) {
//				Common::gotoXY(j + _left + 1, i + _top);
//				putchar(179);
//			}
//		}
//		//Sleep(5);
//	}
//
//	//Vẽ đường ngang
//	for (int i = 1; i < _size * CELL_LENGTH; i++) {
//		for (int j = CELL_HEIGHT; j < _size * CELL_HEIGHT; j += CELL_HEIGHT) {
//			Common::gotoXY(i + _left + 1, j + _top);
//			if (i % CELL_LENGTH == 0)
//				putchar(32);
//			else
//				putchar(196);
//		}
//		//Sleep(2);
//	}
//
//}
//
//void BoardLL::drawScoreBoard()
//{
//	//Vẽ biên trên
//	for (int i = 1; i < CELL_LENGTH * 3; i++)
//	{
//		Common::gotoXY(CELL_LENGTH * (_size + 1) + i + _left, 0 + _top);
//		putchar('-');
//		//Sleep(5);
//	}
//
//	//Vẽ biên phải
//	for (int i = 1; i < CELL_HEIGHT * 4; i++)
//	{
//		Common::gotoXY(CELL_LENGTH * (_size + 4) + _left, i + _top);
//		putchar('|');
//		//Sleep(5);
//	}
//
//	//Vẽ biên dưới
//	for (int i = 1; i < CELL_LENGTH * 3; i++)
//	{
//		Common::gotoXY(CELL_LENGTH * (_size + 4) - i + _left, CELL_HEIGHT * 4 + _top);
//		putchar('-');
//		//Sleep(5);
//	}
//
//	//Vẽ biên trái
//	for (int i = CELL_HEIGHT * 4 - 1; i >= 1; i--)
//	{
//		Common::gotoXY(CELL_LENGTH * (_size + 1) + _left, i + _top);
//		putchar('|');
//		//Sleep(5);
//	}
//
//	//drawDuck();
//	drawCat();
//
//}
//
//void BoardLL::drawDuck()
//{
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 8 + _left, 10 + _top);
//	cout << "  __";
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 8 + _left, 11 + _top);
//	cout << "<(o )___";
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 8 + _left, 12 + _top);
//	cout << " ( ._> /";
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 8 + _left, 13 + _top);
//	cout << "  `---' ";
//}
//
//void BoardLL::drawCat()
//{
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 10 + _left, 10 + _top);
//	cout << "___/|";
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 10 + _left, 11 + _top);
//	cout << "\\o.O|";
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 10 + _left, 12 + _top);
//	cout << "(___)";
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 10 + _left, 13 + _top);
//	cout << "  U";
//}
//
//void BoardLL::renderBoardData()
//{
//	for (int i = 0; i < _size; i++)
//		for (int j = 0; j < _size; j++) {
//			Common::gotoXY(_left + 5 + CELL_LENGTH * j, _top + 2 + CELL_HEIGHT * i);
//			_dataBoard[i][j].setX(_left + 5 + CELL_LENGTH * j);
//			_dataBoard[i][j].setY(_top + 2 + CELL_HEIGHT * i);
//			_dataBoard[i][j].setR(i);
//			_dataBoard[i][j].setC(j);
//
//			putchar(_dataBoard[i][j].getCharHolder());
//
//			//Add to linked lists
//			Node* tmp = new Node(_dataBoard[i][j]);
//			_dataRow[i].addTail(tmp);
//			_dataColumn[j].addTail(tmp);
//			//_dataRow[i].printList();
//		}
//}
//
//////////////////////////////////////////////////////////////////////////////
//
//int BoardLL::getXCoor(const int& c)
//{
//	return _left + 5 + CELL_LENGTH * c;
//}
//
//int BoardLL::getYCoor(const int& r)
//{
//	return _top + 2 + CELL_HEIGHT * r;
//}
//
//int BoardLL::getCCoor(const int& x)
//{
//	return (x - _left - 5) / CELL_LENGTH;
//}
//
//int BoardLL::getRCoor(const int& y)
//{
//	return (y - _top - 2) / CELL_HEIGHT;
//}
//
//char BoardLL::getCharRC(const int& r, const int& c)
//{
//	if (_dataBoard[r][c]._Status == DELETED) return ' ';
//	return _dataBoard[r][c]._CharHolder;
//}
//
//int BoardLL::getStatus(const int& r, const int& c)
//{
//	return _dataBoard[r][c].getStatus();
//}
//
//////////////////////////////////////////////////////////////////////////////
//
//void BoardLL::lockCell(const int& r, const int& c)
//{
//	_dataBoard[r][c].setStatus(LOCK);
//}
//
//void BoardLL::unlockCell(const int& r, const int& c)
//{
//	_dataBoard[r][c].setStatus(NORMAL);
//
//	int x = getXCoor(c), y = getYCoor(r);
//
//	Common::gotoXY(x, y);
//	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
//	for (int i = y - 1; i <= y + 1; i++)
//		for (int j = x - 3; j <= x + 3; j++) {
//			Common::gotoXY(j, i);
//			if (j == x && i == y) putchar(getCharRC(r, c));
//			else putchar(' ');
//		}
//	Common::gotoXY(x, y);
//}
//
//void BoardLL::deleteCell(const int& r, const int& c)
//{
//	_dataBoard[r][c].setStatus(DELETED);
//
//	int x = getXCoor(c), y = getYCoor(r);
//
//	Common::gotoXY(x, y);
//	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
//	putchar(getCharRC(r, c));						//In hình: image[r][c]???
//
//	for (int i = y - 1; i <= y + 1; i++)
//		for (int j = x - 3; j <= x + 3; j++) {
//			Common::gotoXY(j, i);
//			putchar(' ');
//		}
//
//	//Delete left border
//	if (c > 0 && getStatus(r, c - 1) == DELETED)
//		for (int i = y - 1; i <= y + 1; i++) {
//			Common::gotoXY(x - 4, i);
//			putchar(' ');
//		}
//	//Delete right border
//	if (c < _size - 1 && getStatus(r, c + 1) == DELETED)
//		for (int i = y - 1; i <= y + 1; i++) {
//			Common::gotoXY(x + 4, i);
//			putchar(' ');
//		}
//	//Delete top border
//	if (r > 0 && getStatus(r - 1, c) == DELETED)
//		for (int i = x - 3; i <= x + 3; i++) {
//			Common::gotoXY(i, y - 2);
//			putchar(' ');
//		}
//	//Delete bottom border
//	if (r < _size - 1 && getStatus(r + 1, c) == DELETED)
//		for (int i = x - 3; i <= x + 3; i++) {
//			Common::gotoXY(i, y + 2);
//			putchar(' ');
//		}
//
//	//Go back to center
//	Common::gotoXY(x, y);
//}
//
//////////////////////////////////////////////////////////////////////////////
//
//bool BoardLL::outputMatchI()
//{
//	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	cout << "I-Matched!! :D" << endl;
//	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	Sleep(WAIT_TIME);
//	cout << "             " << endl;*/
//	return 1;
//}
//
//bool BoardLL::outputMatchU()
//{
//	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	cout << "U-Matched!! :D" << endl;
//	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	Sleep(WAIT_TIME);
//	cout << "             " << endl;*/
//	return 1;
//}
//
//bool BoardLL::outputMatchL()
//{
//	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	cout << "L-Matched!! :D" << endl;
//	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	Sleep(WAIT_TIME);
//	cout << "             " << endl;*/
//	return 1;
//}
//
//bool BoardLL::outputMatchZ()
//{
//	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	cout << "Z-Matched!! :D" << endl;
//	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	Sleep(WAIT_TIME);
//	cout << "             " << endl;*/
//	return 1;
//}
//
//bool BoardLL::outputNoMatch()
//{
//	Common::setConsoleColor(BRIGHT_WHITE, BLACK);
//	Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	cout << "Not a match :(" << endl;
//	/*Common::gotoXY(CELL_LENGTH * (_size + 1) + 6 + _left, 2 + _top);
//	Sleep(WAIT_TIME + 100);
//	cout << "              " << endl;*/
//	return 0;
//}