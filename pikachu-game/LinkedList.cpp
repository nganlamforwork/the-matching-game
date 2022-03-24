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
        tmp->setNext(_head);
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
        while (p->getNext() != nullptr)
            p = p->getNext();
        p->setNext(tmp);
    }
}
void LinkedList::removeHead()
{
    if (_head == nullptr) return;
    _head = _head->getNext();
}
void LinkedList::removeTail()
{
    if (_head == nullptr) return;
    if (_head->getNext() == nullptr) return removeHead();
    Node* p = _head;
    while (p->getNext()->getNext() != nullptr) //back-1
        p = p->getNext();
    p->setNext();
}
void LinkedList::removeAll()
{
    Node* p = _head;
    Node* tmp;
    while (p != nullptr) {
        tmp = p;
        p = p->getNext();
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
    while (p->getNext()->getNext() != nullptr && i != pos - 1) {
        p = p->getNext();
        ++i;
    }

    if (i != pos - 1) return; //Not found

    Node* tmp = p->getNext()->getNext();
    p->setNext(tmp);
    //printList();
}
bool LinkedList::removeRC(int r, int c)
{
    if (_head->getR() == r && _head->getC() == c) {
        removeHead();
        return 1;
    }
    int i = 0;
    Node* p = _head;
    while (p->getNext()->getNext() != nullptr && (p->getNext()->getR() != r || p->getNext()->getC() != c)) {
        p = p->getNext();
        ++i;
    }

    if (p->getNext()->getR() != r || p->getNext()->getC() != c) return 0; //Not found

    Node* tmp = p->getNext()->getNext();
    p->setNext(tmp);

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
        p = p->getNext();
        ++i;
    }

    if (i != pos - 1) return 0;

    Node* tmp = createNode(data);
    Node* tmp2 = p->getNext();
    tmp->setNext(tmp2);
    p->setNext(tmp);
    return 1;
}
Node* LinkedList::getPos(int pos)
{
    if (pos == 0 || _head == nullptr) 
        return _head;

    int i = 0;
    Node* p = _head;
    while (p != nullptr && i != pos - 1) {
        p = p->getNext();
        ++i;
    }

    if (i != pos - 1) return nullptr;

    return p->getNext();
}
void LinkedList::printList()
{
    std::ofstream out("check.txt", std::ios::app);
    Node* p = _head;
    while (p != nullptr) {
       out << p->getCharHolder() << ' ';
        p = p->getNext();
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
        p = p->getNext();
    }
    return cnt;
}
