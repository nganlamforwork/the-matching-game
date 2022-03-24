﻿#pragma once

#include <iostream>

#define NORMAL 0
#define LOCK 1
#define DELETED -1

class Node {
private:
	char _CharHolder = ' ';		//Ký tự char hiện tại mà Node đang hold
	char _HiddenChar = ' ';
	int _Status = 0;			//Đánh dấu: normal, lock: được chọn và chờ check possible
	int _x = 0;					//Vị trí x trên console của Node
	int _y = 0;					//Vị trí y trên console của Node
	Node* _next;
public:
	Node();
	Node(char, int, int, int);

	char getCharHolder();
	char getHiddenChar();
	int getStatus();
	int getX();
	int getY();
	Node* getNext();

	void setCharHolder(const char& charHolder);
	void setStatus(const int& status);
	void setX(const int& x);
	void setY(const int& y);
	void setNext();
	void setNext(Node*& next);
	void swapChar();
};