#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

#include "Common.h"
#include "Node.h"
#include "Players.h"		//this might be the reason why i will cry tonight

#define CELL_LENGTH 8
#define CELL_HEIGHT 4
#define WAIT_TIME 600

struct Board {
	int _size = 4;						//Kích cỡ bàn cờ
	int _left = 0 , _top = 0;			//Tọa độ bắt đầu bàn cờ
	int _remainCouple = 0;				//Số card còn lại - For scoring
	int* _pairCharacter, * _pos;
	Node** _dataBoard;
	std::string* _imageBoard;

	Board(int,int,int);
	Board();
	~Board();

	int getXCoor(const int& c);
	int getYCoor(const int& r);
	int getRCoor(const int& y);
	int getCCoor(const int& x);
	int getStatus(const int& r, const int& c);
	char getCharRC(const int& r, const int& c);

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
	static void fireworksAni();

	void lockCell(const int& r, const int& c);
	void unlockCell(const int& r, const int& c);
	void deleteCell(const int& r, const int& c);

	bool outputMatchI();
	bool outputMatchL();
	bool outputMatchU();
	bool outputMatchZ();
	bool outputNoMatch();
};