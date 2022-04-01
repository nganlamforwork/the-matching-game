#include "Node.h"

Node::Node()
{
}

Node::Node(Node* tmp)
{
	this->_CharHolder = tmp->getCharHolder();
	this->_HiddenChar = tmp->getHiddenChar();
	this->_Status = tmp->getStatus();			
	this->_x = tmp->getX();					
	this->_y = tmp->getY();					
	this->_r = tmp->getR();
	this->_c = tmp->getC();
}
Node::Node(char charHolder, int status)
{
	this->_CharHolder = charHolder;
	this->_Status = status;
}
Node::Node(char charHolder, int status, int x, int y)
{
	this->_CharHolder = charHolder;
	this->_Status = status;
	this->_x = x;
	this->_y = y;
}
Node::Node(char charHolder, int status, int x, int y, int r, int c)
{
	this->_CharHolder = charHolder;
	this->_Status = status;
	this->_x = x;
	this->_y = y;
	this->_r = r;
	this->_c = c;
}

char Node::getCharHolder()
{
	return _CharHolder;
}

char Node::getHiddenChar()
{
	return _HiddenChar;
}

int Node::getStatus()
{
	return _Status;
}

int Node::getX()
{
	return _x;
}

int Node::getY()
{
	return _y;
}

int Node::getR()
{
	return _r;
}

int Node::getC()
{
	return _c;
}

void Node::setCharHolder(const char& charHolder)
{
	_CharHolder = charHolder;
}

void Node::setStatus(const int& status)
{
	_Status = status;
}

void Node::setX(const int& x)
{
	_x = x;
}

void Node::setY(const int& y)
{
	_y = y;
}

void Node::setR(const int& r)
{
	_r = r;
}

void Node::setC(const int& c)
{
	_c = c;
}

void Node::swapChar()
{
	std::swap(_CharHolder, _HiddenChar);
}