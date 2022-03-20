#pragma once

#include <iostream>

#define NORMAL_ 0
#define LOCK_ 1
#define DELETED_ -1

class Node {
private:
	char _CharHolder = ' ';		//Ký tự char hiện tại mà Node đang hold
	char _HiddenChar = ' ';
	int _Status = 0;			//Đánh dấu: normal, lock: được chọn và chờ check possible
	int _x = 0;					//Vị trí x trên console của Node
	int _y = 0;					//Vị trí y trên console của Node
public:
	Node();
	Node(char, int, int, int);

	char getCharHolder();
	char getHiddenChar();
	int getStatus();
	int getX();
	int getY();

	void setCharHolder(const char& charHolder);
	void setStatus(const int& status);
	void setX(const int& x);
	void setY(const int& y);
	void swapChar();
};