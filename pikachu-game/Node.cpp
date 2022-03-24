#include "Node.h"

Node::Node()
{
	_next = new Node;
	_next = nullptr;
}

Node::Node(char charHolder, int status, int x, int y)
{
	_CharHolder = charHolder;
	_Status = status;
	_x = x;
	_y = y;
	_next = new Node;
	_next = nullptr;
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

Node* Node::getNext()
{
	return _next;
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

void Node::setNext()
{
	_next = nullptr;
}

void Node::setNext(Node*& next)
{
	_next = next;
}

void Node::swapChar()
{
	std::swap(_CharHolder, _HiddenChar);
}