#pragma once
#include <iostream>
#include <vector>
#include <chrono>

#include "Common.h"
#include "BoardLinkedList.h"
#include "Players.h"

struct GameLL {

	BoardLL* _board;
	Players* _player;
	int _mode;
	int _x, _y;						//Vị trí x, y cursor trên màn hình console - Init tại ô [0,0] (hiện trên màn hình console)
	int _r, _c;						//Vị trí i,j của cursor trên dataBoard (ẩn)
	int _left = 15, _top = 2;		//Vị trí board game
	bool _finish = 0;
	int _remainCells, _lockedCells;				//Biến đếm số card đã được lock. Chỉ nằm trong khoảng: 0..2
	std::vector<std::pair<int, int> > _lockedCellsArr; //First: row - Second: column
	time_point<system_clock> _timeStart, _timeEnd;


	GameLL(int);
	~GameLL();

	void renderBoard();
	void startGame();
	void endGame();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	bool checkMatchEqualChar(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatchI(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatchL(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatchZ(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatchU(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatch(std::pair<int, int> firstCell, std::pair<int, int> secondCell, const bool& outputNofitication);

	void selectCell(const int& color);
	void unselectCell();
	void deleteCells();
	void lockCell();

	void renderSuggestion(const int& r1, const int& c1, const int& r2, const int& c2);
	bool findPair(const bool& suggestion);
};