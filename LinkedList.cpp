#include "LinkedList.h"

// Constructor: Initializes an empty list with head and tail pointers set to nullptr
LinkedList::LinkedList() {
    headPtr = nullptr;
    tailPtr = nullptr;
}

// Destructor: Clears the list by deleting all nodes
LinkedList::~LinkedList() {
    Node* currentNode = headPtr;
    while (currentNode != nullptr) {
        Node* tempNode = currentNode;
        currentNode = currentNode->nextPtr;
        delete tempNode;
    }
}

// Add a new node at the end of the list
void LinkedList::addNode(Data d) {
    Node* newNode = new Node;
    newNode->data = d;
    newNode->nextPtr = nullptr;

    if (isEmpty()) {
        headPtr = newNode; // The list was empty, new node is both head and tail
        tailPtr = newNode;
    }
    else {
        tailPtr->nextPtr = newNode; // Add the new node after the tail
        tailPtr = newNode; // Update the tail pointer
    }
}

// Delete a node that matches the provided data
Data LinkedList::delNode(Data d) {
    if (isEmpty()) {
        throw std::runtime_error("Cannot delete from an empty list");
    }

    Node* currentNode = headPtr;
    Node* previousNode = nullptr;
    Data deletedData;

    // Search for the node containing the data
    while (currentNode != nullptr) {
        if (currentNode->data.operand == d.operand) {
            deletedData = currentNode->data; // Store the data to return
            if (previousNode == nullptr) {
                // Deleting the head node
                headPtr = currentNode->nextPtr;
                if (headPtr == nullptr) {
                    tailPtr = nullptr; // If the list is empty now, reset the tail
                }
            }
            else {
                // Deleting a middle or tail node
                previousNode->nextPtr = currentNode->nextPtr;
                if (currentNode == tailPtr) {
                    tailPtr = previousNode; // If we are deleting the tail, update it
                }
            }
            delete currentNode; // Free the memory of the deleted node
            return deletedData; // Return the deleted data
        }

        previousNode = currentNode;
        currentNode = currentNode->nextPtr;
    }

    throw std::runtime_error("Node with given data not found");
}

// Check if the list is empty
bool LinkedList::isEmpty() {
    return headPtr == nullptr;
}

// Print the contents of the list
void LinkedList::printList() {
    if (isEmpty()) {
        cout << "The list is empty." << endl;
        return;
    }

    Node* currentNode = headPtr;
    while (currentNode != nullptr) {
        cout << currentNode->data.operand << " ";
        currentNode = currentNode->nextPtr;
    }
    cout << endl;
}

// Stack Constuctor
Stack::Stack() {
    headPtr = nullptr;
    tailPtr = nullptr;
}

// Override addNode for Stack child class
void Stack::addNode(Data d) {
    Node* newNode = new Node;
    newNode->data = d;
    newNode->nextPtr = headPtr;
    headPtr = newNode;
}

// Override delNode for Stack child class
Data Stack::delNode() {
    if (isEmpty()) throw runtime_error("Stack is empty.");
    Data deletedData = headPtr->data; // Data to be deleted
    Node* tempNode = headPtr; // Temporary node pointer to hold node to be deleted
    headPtr = headPtr->nextPtr; // Assign head to next pointer
    if (headPtr == nullptr) tailPtr = nullptr;
    delete tempNode; // Delete head node

    return deletedData;
}