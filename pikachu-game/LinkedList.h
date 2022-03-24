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
    void addTail(Node* data);
    void removeHead();
    void removeTail();
    void removeAll();
    void removePos(int pos);
    bool removeRC(int r, int c);
    bool addPos(Node* data, int pos);
    Node* getPos(int pos);
    void printList();
    int countElements();
};