#include "Node.h"

Node::Node()
{
}

Node::Node(char charHolder, int status, int x, int y)
{
	_CharHolder = charHolder;
	_Status = status;
	_x = x;
	_y = y;
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

void Node::swapChar()
{
	std::swap(_CharHolder, _HiddenChar);
}