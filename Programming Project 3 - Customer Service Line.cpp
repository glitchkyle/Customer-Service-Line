#include "List.h"
#include <Windows.h>

using namespace std;

void ShowMenu();
int GetUserInput();
void NewCustomerArrival(List*);
void ServeCustomer(List*);
void CustomerLeft(List*);
void ListAll(List*);

int main() {
	// Create the list instance
	List customerServiceQueue;
	// Holds the bool variable whether user wants to quit or not
	bool quit = false;

	do {
		system("cls");
		int userMenuChoice;
		ShowMenu();
		userMenuChoice = GetUserInput();
		system("cls");
		// Switch Statement for Menu
		switch (userMenuChoice) {
		// New Customer Arrival
		case 1:
			NewCustomerArrival(&customerServiceQueue);
			break;
		// Serve Customer
		case 2:		
			ServeCustomer(&customerServiceQueue);
			break;
		// Customer Left
		case 3:			
			CustomerLeft(&customerServiceQueue);
			break;
		// List All
		case 4:
			
			ListAll(&customerServiceQueue);
			break;
		// Quit
		case 5:
			quit = true;
			break;
		}
	} while (!quit);
}

// Show the Menu Options
void ShowMenu() {
	cout << "APPLE CUSTOMER SERVICE MENU\n" << endl;
	cout << "1) New Customer Arrival" << endl;
	cout << "2) Serve Customer" << endl;
	cout << "3) Customer Left" << endl;
	cout << "4) List Awaiting Customers" << endl;
	cout << "5) Quit" << endl;
	cout << endl;
}

// Get User Input function so that user can input either the option or the number for the option
int GetUserInput()
{
	// Infinite Loop for Input Validation
	while (true) {
		// Holds user input
		string userStringInput;
		cout << "What would you like to do?" << endl;
		getline(cin, userStringInput);
		// Make every character in string lowercase
		for (int index = 0; index < userStringInput.length(); index++) {
			userStringInput[index] = tolower(userStringInput[index]);
		}
		// Check if string only had one character
		if (userStringInput.length() == 1) {
			// Convert that one character into an integer
			int userIntegerInput = userStringInput[0] - '0';
			// Check if integer within range
			if (userIntegerInput >= 1 && userIntegerInput <= 5) {
				return userIntegerInput;
			}
			else {
				cout << "\nInvalid Input." << endl;
				continue;
			}
		}
		// Else if statements if user inputted option instead of number
		else if (userStringInput == "new customer arrival") {
			return 1;
		}
		else if (userStringInput == "serve customer") {
			return 2;
		}
		else if (userStringInput == "customer left") {
			return 3;
		}
		else if (userStringInput == "list awaiting customers") {
			return 4;
		}
		else if (userStringInput == "quit") {
			return 5;
		}
		else {
			cout << "\nInvalid Input." << endl;
			continue;
		}
	}
}

// Get the new customer information, passing in the list instance
void NewCustomerArrival(List *queue)
{
	// Holds user input and service required
	string customerName, customerService;
	// Infinite Loop for Input Validation
	while (true) {
		// Bool variable for checking whether the user inputted a valid string
		bool validString = true;

		cout << "What is the customer's name?" << endl;
		getline(cin, customerName);

		// Check if the name contains a number
		for (int index = 0; index < customerName.length(); index++) {
			if (isdigit(customerName[index])) {
				validString = false;
			}
		}

		cout << "\nWhat is the customer's purpose of visting?" << endl;
		getline(cin, customerService);

		// If it was a valid string and neither of the variables are empty
		if (validString && (!customerService.empty() && !customerName.empty())) {
			(*queue).InsertNode(customerName, customerService);
			break;
		}
		else {
			cout << "\nInvalid Input." << endl;
			continue;
		}
	}
}

// Serve the next customer in the list, passing in the list instance
void ServeCustomer(List *queue)
{
	(*queue).ServeCustomer();
	cout << "\nPress ENTER to continue." << endl;
	cin.ignore();
}

// Removes a customer in the list, passing in the list instance
void CustomerLeft(List *queue)
{
	// Holds the customer name
	string customerName;
	cout << "What is the name of the customer that left?" << endl;
	getline(cin, customerName);

	// Returns true if customer was in the list and removed 
	bool validCustomer = (*queue).DeleteNode(customerName);
	system("cls");
	if (validCustomer) {
		cout << customerName << " was not served and removed." << endl;
	}
	else {
		cout << customerName << " was not found. Customer has probably been served or left earlier." << endl;
	}
	cout << "\nPress ENTER to continue." << endl;
	cin.ignore();
}

// Lists all awaiting customers in the list, passing in the list instance
void ListAll(List *queue)
{
	// Holds the number of awaiting customers
	int numberOfCustomers;
	cout << "APPLE CUSTOMER SERVICE WAITING LIST" << endl;
	cout << setw(13) << left << "SEQUENCE"
		<< setw(20) << left << "NAME"
		<< setw(14) << left << "ARRIVAL DATE/TIME"
		<< setw(20) << right << "PURPOSE OF VISIT" << endl;
	numberOfCustomers = (*queue).ListAll();
	cout << "\nThere is/are " << numberOfCustomers << " customer(s) waiting to be served." << endl;
	cout << "\nPress ENTER to continue." << endl;
	cin.ignore();
}
