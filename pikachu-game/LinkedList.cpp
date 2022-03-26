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
    if (_head == nullptr) {
        _head = tmp;
        _tail = tmp;
    }
    else {
        _head->_prev = tmp;
        tmp->_next = _head;
        _head = tmp;
    }
}

void LinkedList::addTail(Node* data)
{
    Node* tmp, * p;
    tmp = createNode(data);
    if (_head == nullptr) {
        _head = tmp;
        _tail = tmp;
    }
    else {
        _tail->_next = tmp;
        tmp->_prev = _tail;
        _tail = tmp;
    }
}
void LinkedList::removeHead()
{
    if (_head == nullptr) return;
    _head = _head->_next;
    if (_head != nullptr)_head->_prev = nullptr;
}
void LinkedList::removeTail()
{
    if (_head == nullptr) return;
    _tail = _tail->_prev;
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
    _tail = nullptr;
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
    if (tmp != nullptr) tmp->_prev = p;
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

    Node* tmp = p->_next->_next;
    if (tmp != nullptr) tmp->_prev = p;
    p->_next = tmp;

    return 1;
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

    tmp->_prev = p;
    if (tmp->_next != nullptr) tmp->_next->_prev = tmp;
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

///////////////////////////////////////////////////////////////

bool LinkedList::isNext(const int& r1, const int& c1, const int& r2, const int& c2) //Always has r1, c1
{
    Node* tmp = getRC(r1, c1);
    if (tmp == nullptr) return 0;
    if (tmp->_next == nullptr) return 1;
    int nextR2 = tmp->_next->_r;
    int nextC2 = tmp->_next->_c;
    if (r1 == r2) return nextC2 > c1;
    return nextR2 > r1;
}

bool LinkedList::isBefore(const int& r1, const int& c1, const int& r2, const int& c2) //Always has r1, c1
{
    Node* tmp = getRC(r1, c1);
    if (tmp == nullptr) return 0;
    if (tmp->_prev == nullptr) return 1;
    int prevR2 = tmp->_prev->_r;
    int prevC2 = tmp->_prev->_c;
    if (r1 == r2) return prevC2 < c2;
    return prevR2 < r2;
}

bool LinkedList::isAnyBetween(int r1, int c1, int r2, int c2)
{
    Node* p = _head;

    //Same row
    if (r1 == r2) {
        if (c1 > c2) std::swap(c1, c2);
        while (p != nullptr) {
            if (p->_c > c1 && p->_c < c2) return 1;
            p = p->_next;
        }
        return 0;
    }

    //Same column
    if (r1 > r2) std::swap(r1, r2);
    while (p != nullptr) {
        if (p->_r > r1 && p->_r < r2) return 1;
        p = p->_next;
    }
    return 0;
}