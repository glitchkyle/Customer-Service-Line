#pragma once
#include "Node.h"
#include <iostream>
#include <iomanip>

using namespace std;
#ifndef LIST_H
#define LIST_H

class List {
private:
	// Created variable type definition to reduce any confusion
	typedef Node* nodePtr;
	// Pointer for first customer in the list
	nodePtr head;
	// Pointer for the last customer in the list
	nodePtr last;
public:
	List();
	void InsertNode(string, string);
	bool DeleteNode(string);
	Node* SearchNode(string);
	void ServeCustomer();
	int ListAll();
	~List();
};

#endif // ! LIST_H
