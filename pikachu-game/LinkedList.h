#pragma once
#include <iostream>
#include "Node.h"

class LinkedList {
private:
	Node* p_head = nullptr;
	Node* p_tail = nullptr;
public:
    LinkedList();
    ~LinkedList();
    Node* createNode(Node* data);
    void addHead(Node*& pHead, Node* data);
    void addTail(Node*& pHead, Node* data);
    void removeHead(Node*& pHead);
    void removeTail(Node*& pHead);
    void removeAll(Node*& pHead);
    bool addPos(Node*& pHead, Node* data, int pos);
    void RemovePos(Node*& pHead, int pos);
};