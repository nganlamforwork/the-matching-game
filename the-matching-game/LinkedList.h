#pragma once
#include <iostream>
#include "NodeLinkedList.h"

struct LinkedList {

	NodeLL* _head = nullptr;
	NodeLL* _tail = nullptr;
    int _size = 0;

    LinkedList();
    ~LinkedList();

    NodeLL* getHead();
    NodeLL* getTail();

    NodeLL* createNodeLL(NodeLL* data);

    void addHead(NodeLL* data);
    void addTail(NodeLL* data);

    void removeHead();
    void removeTail();

    void removeAll();

    NodeLL* getPos(int pos);
    bool addPos(NodeLL* data, int pos);
    void removePos(int pos);

    NodeLL* getRC(int r, int c);
    bool addRC(NodeLL* data, int r, int c);
    bool removeRC(int r, int c);

    void printList();
    int countElements();
};