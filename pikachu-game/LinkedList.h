#pragma once
#include <iostream>
#include "Node.h"

struct LinkedList {

	Node* _head = nullptr;
	Node* _tail = nullptr;

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
    Node* getRC(int r, int c);
    void printList();
    int countElements();

    bool isNext(const int& r1, const int& c1, const int& r2, const int& c2);
    bool isBefore(const int& r1, const int& c1, const int& r2, const int& c2);
};