#pragma once
#include <iostream>
#include <ctime>
#include <sstream>

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
	LinkedList* _dataColumn;
	std::string* _imageBoard;

	BoardLL(int, int, int);
	BoardLL();
	~BoardLL();

	int getXCoor(const int& c);
	int getYCoor(const int& r);
	int getRCoor(const int& y);
	int getCCoor(const int& x);

	int getStatus(const int& r, const int& c);
	void setStatus(const int& r, const int& c, const int& status);

	//Return the coordination (row) of the top of the specific c column in the board
	int getTopRow(const int& c);

	void generateBoardData();
	void drawBoard();
	void renderBoardData();
	void initBoardBackground();

	void drawInformationBoard();

	void drawEnterName();
	void drawEndgame(int);
	static void drawLeaderBoard();

	void repaintColumn(const int& c);

	void lockCell(const int& r, const int& c);
	void unlockCell(const int& r, const int& c);
	void deleteCell(const int& r, const int& c);

	bool outputMatchI();
	bool outputMatchL();
	bool outputMatchU();
	bool outputMatchZ();
	bool outputNoMatch();
};