#pragma once
#include <string>
#include <iomanip>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

struct Data {
	int operand;
};

struct Node {
	Data data;
	Node* nextPtr;
};

class LinkedList {
protected:
	Node* headPtr;
	Node* tailPtr;
public:
	LinkedList();
	~LinkedList();
	void virtual addNode(Data d);
	Data virtual delNode(Data d);
	bool isEmpty();
	void printList();
};

class Stack : public LinkedList {
public:
	// Default contructor
	Stack();

	void addNode(Data d) override;
	Data delNode();
};
