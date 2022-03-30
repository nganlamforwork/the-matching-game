#include "LinkedList.h"

#include <fstream>

LinkedList::LinkedList(){}
LinkedList::~LinkedList(){}

Node* LinkedList::createNode(Node* data)
{
    Node* tmp = new Node(data);
    return tmp;
}

Node* LinkedList::getHead()
{
    return _head;
}

Node* LinkedList::getTail()
{
    return _tail;
}

void LinkedList::addHead(Node* data)
{
    Node* tmp = createNode(data);
    if (_head == nullptr)
        _head = tmp;
    else {
        tmp->_next = _head;
        _head = tmp;
    }
}

void LinkedList::addTail(Node* data)
{
    Node* tmp, * p;
    tmp = createNode(data);
    if (_head == nullptr)
        _head = tmp;
    else {
        p = _head;
        while (p->_next != nullptr)
            p = p->_next;
        p->_next = tmp;
    }
}
void LinkedList::removeHead()
{
    if (_head == nullptr) return;
    _head = _head->_next;
}
void LinkedList::removeTail()
{
    if (_head == nullptr) return;
    if (_head->_next == nullptr) return removeHead();
    Node* p = _head;
    while (p->_next->_next != nullptr) //back-1
        p = p->_next;
    p->_next = nullptr;
}
void LinkedList::removeAll()
{
    Node* p = _head;
    Node* tmp;
    while (p != nullptr) {
        tmp = p;
        p = p->_next;
        delete tmp;
    }
    _head = nullptr;
}
void LinkedList::removePos(int pos)
{
    if (pos == 0 || _head == nullptr)
        removeHead();

    int i = 0;
    Node* p = _head;
    while (p->_next->_next != nullptr && i != pos - 1) {
        p = p->_next;
        ++i;
    }

    if (i != pos - 1) return; //Not found

    Node* tmp = p->_next->_next;
    p->_next = tmp;
    //printList();
}
bool LinkedList::removeRC(int r, int c)
{
    if (_head->_r == r && _head->_c == c) {
        removeHead();
        return 1;
    }
    int i = 0;
    Node* p = _head;
    while (p->_next->_next != nullptr && (p->_next->_r != r || p->_next->_c != c)) {
        p = p->_next;
        ++i;
    }

    if (p->_next->_r != r || p->_next->_c != c) return 0; //Not found

    p->_next = p->_next->_next;

    //printList();
}
bool LinkedList::addPos(Node* data, int pos)
{
    if (pos == 0 || _head == nullptr) {
        addHead(data);
        return 1;
    }

    int i = 0;
    Node* p = _head;
    while (p != nullptr && i != pos - 1) {
        p = p->_next;
        ++i;
    }

    if (i != pos - 1) return 0;

    Node* tmp = createNode(data);
    tmp->_next = p->_next;
    p->_next = tmp;
    return 1;
}
Node* LinkedList::getPos(int pos)
{
    Node* p = _head;
    int i = 0;
    while (p != nullptr && i != pos) {
        p = p->_next;
        i++;
    }
    if (i == pos && p != nullptr)
        return p;
    return nullptr;
}
Node* LinkedList::getRC(int r, int c)
{
    Node* p = _head;
    while (p != nullptr && (p->_r != r || p->_c != c))
        p = p->_next;
    if (p != nullptr)
        return p;
    return nullptr;
}

void LinkedList::printList()
{
    std::ofstream out("check.txt", std::ios::app);
    Node* p = _head;
    while (p != nullptr) {
       out << p->getCharHolder() << ' ';
        p = p->_next;
    }
    out << '\n';
    out.close();
}
int LinkedList::countElements()
{
    Node* p = _head;
    int cnt = 0;
    while (p != nullptr) {
        cnt++;
        p = p->_next;
    }
    return cnt;
}
