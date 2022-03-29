﻿#pragma once
#include <iostream>
#include <ctime>
#include "Common.h"
#include "Node.h"
#include "LinkedList.h"

#define CELL_LENGTH 8
#define CELL_HEIGHT 4

struct BoardLL {
	int _size = 4;						//Kích cỡ bàn cờ
	int _left = 0, _top = 0;			//Tọa độ bắt đầu bàn cờ
	int _remainCouple = 0;				//Số card còn lại - For scoring
	int* _pairCharacter;
	Node** _dataBoard;
	LinkedList* _dataRow;
	LinkedList* _dataColumn;
	int* _pos;


	BoardLL(int, int, int);
	~BoardLL();

	void generateBoardData();
	void drawBoard();
	void drawDuck();
	void drawCat();
	void drawScoreBoard();
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
	bool outputMatchL();
	bool outputMatchU();
	bool outputMatchZ();
	bool outputNoMatch();
};