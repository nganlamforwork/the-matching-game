#include "LinkedList.h"

LinkedList::LinkedList(){}
LinkedList::~LinkedList(){}

Node* LinkedList::createNode(Node* data)
{
    Node* tmp = new Node;
    tmp->setCharHolder(data->getCharHolder());
    tmp->setNext();
    return tmp;
}
void LinkedList::addHead(Node*& pHead, Node* data)
{
    Node* tmp = createNode(data);
    if (pHead == nullptr)
        pHead = tmp;
    else {
        tmp->setNext(pHead);
        pHead = tmp;
    }
}

void LinkedList::addTail(Node*& pHead, Node* data)
{
    Node* tmp, * p;
    tmp = createNode(data);
    if (pHead == nullptr)
        pHead = tmp;
    else {
        p = pHead;
        while (p->getNext() != nullptr)
            p = p->getNext();
        p->setNext(tmp);
    }
}
void LinkedList::removeHead(Node*& pHead)
{
    if (pHead == nullptr) return;
    pHead = pHead->getNext();
}
void LinkedList::removeTail(Node*& pHead)
{
    if (pHead == nullptr) return;
    if (pHead->getNext() == nullptr) return removeHead(pHead);
    Node* p = pHead;
    while (p->getNext()->getNext() != nullptr) //back-1
        p = p->getNext();
    p->setNext();
}
void LinkedList::removeAll(Node*& pHead)
{
    Node* p = pHead;
    Node* tmp;
    while (p != nullptr) {
        tmp = p;
        p = p->getNext();
        delete tmp;
    }
    pHead = nullptr;
}
bool LinkedList::addPos(Node*& pHead, Node* data, int pos)
{
    if (pos == 0 || pHead == nullptr) {
        addHead(pHead, data);
        return 1;
    }

    int i = 0;
    Node* p = pHead;
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
void LinkedList::RemovePos(Node*& pHead, int pos)
{
    if (pos == 0 || pHead == nullptr)
        removeHead(pHead);

    int i = 0;
    Node* p = pHead;
    while (p->getNext()->getNext() != nullptr && i != pos - 1) {
        p = p->getNext();
        ++i;
    }

    if (i != pos - 1) return; //Not found

    Node * tmp = p->getNext()->getNext();
    p->setNext(tmp);
}
