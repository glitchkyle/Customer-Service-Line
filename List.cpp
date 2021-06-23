#pragma warning(disable : 4996)
#include "List.h"
#include <chrono>
#include <ctime>

using namespace std;

// Constructor for the pointers
List::List()
{
	head = nullptr;
	last = nullptr;
}

// Inserts a new node (customer) in the list
void List::InsertNode(string nodeName, string nodeService)
{
	// Sequence variable is based on how many times this function was called (customer is added)
	static int sequence = 0;
	sequence += 1;
	nodePtr newNode = new Node;

	// Seed and initialize the current time
	time_t now = time(0);
	tm* ltm = localtime(&now);

	newNode->sequenceNumber = sequence;
	newNode->name = nodeName;
	newNode->month = ltm->tm_mon + 1; // +1 because months starts with 0 as January
	newNode->day = ltm->tm_mday;
	newNode->year = ltm->tm_year + 1900; // Year is how many years since 1900
	newNode->hour = ltm->tm_hour;
	newNode->minute = ltm->tm_min;
	newNode->serviceRequired = nodeService;

	// Based off instructions, make the new node the new head
	newNode->next = head;
	head = newNode;
	// If this node is the only node in the list, make it be pointed by last pointer as well
	if (head->next == nullptr) {
		last = newNode;
	}
}

// Deletes an existing node (customer) in the list, returns if existing customer was found and deleted
bool List::DeleteNode(string customerName)
{
	// Find the node to delete
	nodePtr delPtr = SearchNode(customerName);
	// Trail pointer to locate node before the delete node
	nodePtr trail = head;
	// Node to connect to after delete node is deleted
	nodePtr connect = nullptr;

	// If customer was found
	if (delPtr != nullptr) {
		// If node is the last in the list
		if (delPtr == head && delPtr == last) {
			head = nullptr;
			last = nullptr;
		}
		// If node being deleted is the head pointer
		else if (delPtr == head) {
			head = head->next;
		}
		// If node being deleted is the last pointer
		else if (delPtr == last) {
			// Find the next customer to be served
			last = head;
			while (last->next != delPtr && last->next != nullptr) {
				last = last->next;
			}
			// Make the last node point to nothing to remove any dangling pointers
			last->next = nullptr;
		}
		else {
			// Find and connect the two nodes with a gap after deleting delete node
			connect = delPtr->next;
			while (trail->next != delPtr) {
				trail = trail->next;
			}
			trail->next = connect;
		}
		delete delPtr;
		return true;
	}
	else {
		return false;
	}
}

// Find the node with the given customer name
Node* List::SearchNode(string customerName)
{
	// If list is not empty
	if (head != nullptr) {
		// Create a node called search node pointing to the beginning of the list
		nodePtr search = head;
		// While the search pointer is not the end of the list and is not the node being searched 
		while (search != nullptr && search->name != customerName) {
			search = search->next;
		}
		return search;
	}
	else {
		return nullptr;
	}
}

// Serve the customer at the beginning of the list 
void List::ServeCustomer()
{
	// Pointer declared for deletion
	nodePtr delPtr = nullptr;
	// If list is not empty
	if (last != nullptr) {
		delPtr = last;
		// If the node being deleted is not the last node in the list
		if (delPtr != head) {
			// Find the next customer to be served
			last = head;
			while (last->next != delPtr) {
				last = last->next;
			}
			// Make the last node point to nothing to remove any dangling pointers
			last->next = nullptr;
		}
		else {
			head = nullptr;
			last = nullptr;
		}
		cout << delPtr->name << " has been served." << endl;
		delete delPtr;
	}
	else {
		cout << "\nThere are no customers." << endl;
	}
}

// Print details of every node (customer) in the list
int List::ListAll()
{
	// Counts how many nodes (customer) there are in the list
	int totalNodes = 0;
	// Create a pointer that will traverse throughout the list
	nodePtr current = head;
	// If list is not empty
	if (current != nullptr) {
		// While current pointer has not reached the end of the list
		while (current != nullptr) {
			// Display details of the node
			cout << setw(13) << left << current->sequenceNumber
				<< setw(20) << left << current->name
				<< setfill('0') << setw(2) << left << current->month << "/"
				<< setw(2) << left << current->day << "/" << setfill(' ')
				<< setw(6) << left << current->year
				<< setfill('0') << setw(2) << current->hour << ":"
				<< setfill('0') << setw(2) << current->minute << setfill(' ')
				<< setw(20) << right << current->serviceRequired << endl;
			current = current->next;
			totalNodes++;
		}
	}
	else {
		cout << "\nThere are no customers." << endl;
	}
	
	return totalNodes;
}

// Destroy all nodes
List::~List()
{
	// Pointer declared for deletion
	nodePtr delPtr = nullptr;
	// Starting from the head pointer, go through the list and delete the nodes
	while (head != nullptr) {
		delPtr = head;
		head = head->next;
		delete delPtr;
	}
}
