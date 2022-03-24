﻿#pragma once
#include <iostream>
#include "Node.h"
#include "LinkedList.h"

#define CELL_LENGTH 8
#define CELL_HEIGHT 4

class Board {
private:
	int _size = 4;						//Kích cỡ bàn cờ
	int _left = 0 , _top = 0;			//Tọa độ bắt đầu bàn cờ
	int _remainCouple = 0;				//Số card còn lại - For scoring
	int* _pairCharacter;
	Node** _dataBoard;
	LinkedList _pairCharacterLL;
	int* _pos;
public:
	Board(int,int,int);
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
	
	int getXCoor(const int& c);
	int getYCoor(const int& r);
	int getRCoor(const int& y);
	int getCCoor(const int& x);
	int getStatus(const int& r, const int& c);
	char getCharRC(const int& r, const int& c);

	void lockCell(const int& r, const int& c);
	void unlockCell(const int& r, const int& c);
	void deleteCell(const int& r, const int& c);

	bool outputMatchI();
	bool outputMatchL(int left, int top);
	bool outputMatchU(int left, int top);
	bool outputMatchZ(int left, int top);
};