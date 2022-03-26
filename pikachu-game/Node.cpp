#include "Node.h"

Node::Node()
{
	_next = nullptr;
	_prev = nullptr;
}

Node::Node(Node* tmp)
{
	_CharHolder = tmp->getCharHolder();
	_HiddenChar = tmp->getHiddenChar();
	_Status = tmp->_Status;			
	_x = tmp->_x;					
	_y = tmp->_y;
	_r = tmp->_r;
	_c = tmp->_c;
	_next = tmp->getNext();
	_prev = tmp->getPre();
}
Node::Node(char charHolder, int status)
{
	this->_CharHolder = charHolder;
	this->_Status = status;
	this->_next = nullptr;
	this->_prev = nullptr;
}
Node::Node(char charHolder, int status, int x, int y)
{
	this->_CharHolder = charHolder;
	this->_Status = status;
	this->_x = x;
	this->_y = y;
	this->_next = nullptr;
	this->_prev = nullptr;
}
Node::Node(char charHolder, int status, int x, int y, int r, int c)
{
	this->_CharHolder = charHolder;
	this->_Status = status;
	this->_x = x;
	this->_y = y;
	this->_r = r;
	this->_c = c;
	this->_next = nullptr;
	this->_prev = nullptr;
}

char Node::getCharHolder()
{
	return _CharHolder;
}

char Node::getHiddenChar()
{
	return _HiddenChar;
}

Node* Node::getNext()
{
	return _next;
}

Node* Node::getPre()
{
	return _prev;
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