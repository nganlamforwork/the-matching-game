#pragma once
#include <iostream>
#include "Node.h"

class Board {
private:
	int _size = 4;						//Kích cỡ bàn cờ
	int _left = 0 , _top = 0;			//Tọa độ bắt đầu bàn cờ
	int _remainCouple = 0;				//Số card còn lại - For scoring
	int* _pairCharacter;
	Node** _dataBoard;
public:
	Board(int);
	~Board();

	int getSize();
	int getLeftCoor();
	int getTopCoor();
	void setSize(const int& size);
	void setLeftCoor(const int& left);
	void setTopCoor(const int& top);

	void generateBoardData();
	void drawBoard();
	void renderBoardData();
};