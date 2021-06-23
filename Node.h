#pragma once
#include <string>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
public:
	unsigned int sequenceNumber = 0;
	string name = "Name";
	int month = 0;
	int day = 0;
	int year = 0;
	int hour = 0;
	int minute = 0;
	string serviceRequired = "Service Required";
	Node* next = nullptr;
};

#endif // ! NODE_H
