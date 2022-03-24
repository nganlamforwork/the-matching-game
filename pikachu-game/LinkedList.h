#pragma once
#include <iostream>
#include "Node.h"

class LinkedList {
private:
	Node* _head = nullptr;
	Node* _tail = nullptr;
public:
    LinkedList();
    ~LinkedList();

    Node* getHead();
    Node* getTail();

    Node* createNode(Node* data);
    void addHead(Node* data);
    void addTail(Node*& pHead, Node* data);
    void removeHead(Node*& pHead);
    void removeTail(Node*& pHead);
    void removeAll(Node*& pHead);
    bool addPos(Node*& pHead, Node* data, int pos);
    void removePos(Node*& pHead, int pos);
    void printList();
};