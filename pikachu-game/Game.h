#pragma once
#include <iostream>
#include <vector>
#include "Board.h"

class Game{
private:
	Board* _board;
	int _mode;				
	int _x, _y;						//Vị trí x, y cursor trên màn hình console - Init tại ô [0,0] (hiện trên màn hình console)
	int _r, _c;						//Vị trí i,j của cursor trên dataBoard (ẩn)
	int _left = 0, _top = 0;		//Vị trí board game
	bool _loop = 1,_finish = 0;
	int _remainCards;
	int _lockedCards;				//Biến đếm số card đã được lock. Chỉ nằm trong khoảng: 0..2
	std::vector<std::pair<int, int> > _lockedCardsArr; //First: row - Second: column

	void moveRight();					 //Di chuyển phải
	void moveLeft();					 //Di chuyển trái
	void moveUp();						 //Di chuyển lên
	void moveDown();					 //Di chuyển xuống

	bool checkMatchEqualChar(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatchI(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatchL(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatchZ(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatchU(std::pair<int, int> firstCell, std::pair<int, int> secondCell);
	bool checkMatch(std::pair<int, int> firstCell, std::pair<int, int> secondCell);			//Check match tổng

public:
	Game(int);
	~Game();
	
	void setMode(int mode);

	void startGame();					 //Bắt đầu trò chơi
	void renderBoard();					//In bảng ban đầu
	void selectCell(const int& color);
	void unselectCell();
	void deleteCards();
	void lockCell();
};