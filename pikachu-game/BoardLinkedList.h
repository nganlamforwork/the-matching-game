﻿#pragma once
#include <iostream>
#include <ctime>

#include "Players.h"
#include "Common.h"
#include "NodeLinkedList.h"
#include "LinkedList.h"

#define CELL_LENGTH 8
#define CELL_HEIGHT 4

struct BoardLL {

	int _size = 4;						//Kích cỡ bàn cờ
	int _left = 0, _top = 0;			//Tọa độ bắt đầu bàn cờ
	int _remainCouple = 0;				//Số card còn lại - For scoring
	int* _pairCharacter, * _pos;
	LinkedList* _dataColumn;
	std::string* _imageBoard;

	BoardLL(int, int, int);
	BoardLL();
	~BoardLL();

	int getXCoor(const int& c);
	int getYCoor(const int& r);
	int getRCoor(const int& y);
	int getCCoor(const int& x);

	void generateBoardData();
	void drawBoard();
	void renderBoardData();
	void initBoardBackground();

	void drawDuck();
	void drawCat();
	void drawScoreBoard();

	void drawEnterName();
	void drawEndgame(int);
	static void drawLeaderBoard();

	void lockCell(const int& r, const int& c);
	void unlockCell(const int& r, const int& c);
	void deleteCell(const int& r, const int& c);

	bool outputMatchI();
	bool outputMatchL();
	bool outputMatchU();
	bool outputMatchZ();
	bool outputNoMatch();
};