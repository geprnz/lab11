#pragma once
#include <string>
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

