#pragma once

#include <iostream>

#define NORMAL_ 0
#define CURRENT_ 1
#define LOCK_ -1

class Node {
private:
	char _CharHolder;		//Ký tự char hiện tại mà Node đang hold
	int _Status = 0;		//Đánh dấu: normal, current cursor đang trỏ tới, lock: được chọn và chờ check possible
	int _x;					//Vị trí x trên console của Node
	int _y;					//Vị trí y trên console của Node
public:
	Node(char, int, int, int);
	~Node();

	char getCharHolder();
	int getStatus();
	int getX();
	int getY();

	void setStatus(const int& status);
	void setX(const int& x);
	void setY(const int& y);
};