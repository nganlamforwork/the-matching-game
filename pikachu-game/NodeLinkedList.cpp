#include "NodeLinkedList.h"

NodeLL::NodeLL()
{
}

NodeLL::NodeLL(NodeLL* tmp)
{
	this->_charHolder = tmp->_charHolder;
	this->_status = tmp->_status;
	this->_x = tmp->getX();
	this->_y = tmp->getY();
	this->_r = tmp->getR();
	this->_c = tmp->getC();
	this->_next = tmp->_next;
	this->_prev = tmp->_prev;
}
NodeLL::NodeLL(char charHolder, int status)
{
	this->_charHolder = charHolder;
	this->_status = status;
}
NodeLL::NodeLL(char charHolder, int status, int x, int y)
{
	this->_charHolder = charHolder;
	this->_status = status;
	this->_x = x;
	this->_y = y;
}
NodeLL::NodeLL(char charHolder, int status, int x, int y, int r, int c)
{
	this->_charHolder = charHolder;
	this->_status = status;
	this->_x = x;
	this->_y = y;
	this->_r = r;
	this->_c = c;
}


int NodeLL::getX()
{
	return _x;
}

int NodeLL::getY()
{
	return _y;
}

int NodeLL::getR()
{
	return _r;
}

int NodeLL::getC()
{
	return _c;
}

void NodeLL::setCharHolder(const char& charHolder)
{
	_charHolder = charHolder;
}

void NodeLL::setStatus(const int& status)
{
	_status = status;
}

void NodeLL::setX(const int& x)
{
	_x = x;
}

void NodeLL::setY(const int& y)
{
	_y = y;
}

void NodeLL::setR(const int& r)
{
	_r = r;
}

void NodeLL::setC(const int& c)
{
	_c = c;
}
