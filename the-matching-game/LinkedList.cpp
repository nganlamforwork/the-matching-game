#include "LinkedList.h"

#include <fstream>

LinkedList::LinkedList(){}
LinkedList::~LinkedList(){}

////////////////////////////////////////////////////////////////////////////

NodeLL* LinkedList::getHead()
{
    return _head;
}

NodeLL* LinkedList::getTail()
{
    return _tail;
}

////////////////////////////////////////////////////////////////////////////

NodeLL* LinkedList::createNodeLL(NodeLL* data)
{
    NodeLL* tmp = new NodeLL(data);
    return tmp;
}

////////////////////////////////////////////////////////////////////////////

void LinkedList::addHead(NodeLL* data)
{
    NodeLL* tmp = createNodeLL(data);
    _size++;
    if (_head == nullptr) {
        _head = tmp;
        _tail = tmp;
        return;
    }
    _head->_prev = tmp;
    tmp->_next = _head;
    _head = tmp;
}

void LinkedList::addTail(NodeLL* data)
{
    NodeLL* tmp = createNodeLL(data);

    _size++;

    if (_head == nullptr) {
        _head = tmp;
        _tail = tmp;
        return;
    }

    _tail->_next = tmp;
    tmp->_prev = _tail;
    _tail = tmp;
}

void LinkedList::removeHead()
{
    if (_head == nullptr) return;
    _head = _head->_next;
    if (_head != nullptr)_head->_prev = nullptr;
    _size--;
}

void LinkedList::removeTail()
{
    if (_head == nullptr) return;
    
    _tail = _tail->_prev;
    if (_tail != nullptr)  _tail->_next = nullptr;

    _size--;
}

////////////////////////////////////////////////////////////////////////////

void LinkedList::removeAll()
{
    NodeLL* p = _head;
    NodeLL* tmp;
    while (p != nullptr) {
        tmp = p;
        p = p->_next;
        delete tmp;
    }
    _head = nullptr;
    _size = 0;
}

NodeLL* LinkedList::getPos(int pos)
{
    NodeLL* p = _head;
    int i = 0;
    while (p != nullptr && i != pos) {
        p = p->_next;
        i++;
    }
    if (i == pos && p != nullptr)
        return p;
    return nullptr;
}
bool LinkedList::addPos(NodeLL* data, int pos)
{
    if (pos == 0 || _head == nullptr) {
        addHead(data);
        return 1;
    }

    int i = 0;
    NodeLL* p = _head;
    while (p != nullptr && i != pos - 1) {
        p = p->_next;
        ++i;
    }

    if (i != pos - 1) return 0;

    NodeLL* tmp = createNodeLL(data);
    tmp->_next = p->_next;
    p->_next = tmp;

    _size++;

    return 1;
}
void LinkedList::removePos(int pos)
{
    if (pos == 0 || _head == nullptr) {
        removeHead();
        return;
    }

    int i = 0;
    NodeLL* p = _head;
    while (p->_next->_next != nullptr && i != pos - 1) {
        p = p->_next;
        ++i;
    }

    if (i != pos - 1) return; //Not found

    NodeLL* tmp = p->_next->_next;
    if (tmp != nullptr)
        tmp->_prev = p;
    else _tail = p;
    p->_next = tmp;

    _size--;
    //printList();
}

////////////////////////////////////////////////////////////////////////////

NodeLL* LinkedList::getRC(int r, int c)
{
    NodeLL* p = _head;
    while (p != nullptr && (p->_r != r || p->_c != c))
        p = p->_next;
    if (p != nullptr)
        return p;
    return nullptr;
}
bool addRC(NodeLL* data, int r, int c) { return 1; }
bool LinkedList::removeRC(int r, int c)
{
    if (_head->_r == r && _head->_c == c) {
        removeHead();
        return 1;
    }
    int i = 0;
    NodeLL* p = _head;
    while (p->_next->_next != nullptr && (p->_next->_r != r || p->_next->_c != c)) {
        p = p->_next;
        ++i;
    }

    if (p->_next->_r != r || p->_next->_c != c) return 0; //Not found

    NodeLL* tmp = p->_next->_next;
    if (tmp != nullptr)
        tmp->_prev = p;
    else _tail = p;
    p->_next = tmp;

    _size--;

    //printList();
}

////////////////////////////////////////////////////////////////////////////

void LinkedList::printList()
{
    std::ofstream out("check.txt", std::ios::app);
    NodeLL* p = _head;
    while (p != nullptr) {
        out << p->_charHolder << ' ';
        p = p->_next;
    }
    out << '\n';
    out.close();
}
int LinkedList::countElements()
{
    NodeLL* p = _head;
    int cnt = 0;
    while (p != nullptr) {
        cnt++;
        p = p->_next;
    }
    return cnt;
}
