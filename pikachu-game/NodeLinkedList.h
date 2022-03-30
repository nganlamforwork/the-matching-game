#pragma once

#include <iostream>

#define NORMAL 0
#define LOCK 1
#define DELETED -1

struct NodeLL {

	char _charHolder = ' ';				//Ký tự char hiện tại mà Node đang hold
	int _status = 0;					
	int _x = 0, _y = 0;					//Vị trí x, y trên console của Node
	int _r = -1, _c = -1;
	NodeLL* _next, * _prev;

	NodeLL();
	NodeLL(NodeLL*);
	NodeLL(char, int);
	NodeLL(char, int, int, int);
	NodeLL(char, int, int, int, int, int);

	int getX();
	int getY();
	int getR();
	int getC();

	void setCharHolder(const char& charHolder);
	void setStatus(const int& status);
	void setX(const int& x);
	void setY(const int& y);
	void setR(const int& r);
	void setC(const int& c);
};