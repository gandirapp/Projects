/*
Program Description: This program demonstrates a hospital simulation. It adds patients into a room and then checks them into one of the three vacant operating rooms based on priority value.
					 The program welcomes the user and lets them choose between 4 functional choices and 1 exit command. It can add patients into a queue, schedule them into vacant
					 operating rooms, show the patients in the waiting room, check a patient out of the operating room, and exit the simulation.

Written By: Gandira Prahandika, Brian Purnomo, Irwan Winarto, Surya Rangasamy

Date Submitted: 06/16/2015

IDE Used: Visual Studio Express 2013
*/
// All include statements starting from here
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include "Heap_PriorityQueue.h"
#include "LinkedList.h"

using namespace std;

// All global constants starting from here
static const int maxRooms = 3; // Maximum operating rooms available in the hospital.

// The Patient class holds the data of the patients. It also has setters, getters, and overloaded operators
class Patient{
private:
	string name;		// name of patient
	string disease;		// name of patient's disease
	int priorityValue;	// priority value of patient
	int patientID;
public:
	// Default constructor:
	// sets the name and disease to nothing and priority value to 0
	Patient() {
		name = "";
		disease = "";
		priorityValue = 0;
		patientID = 0;
	}

	// Constructor:
	// sets the name, disease, and priority value of the patient to the inputted information
	Patient(string aName, string aDisease, int aPriority, int anID) {
		name = aName;
		disease = aDisease;
		priorityValue = aPriority;
		patientID = anID;
	}

	// Returns the name of the patient
	string getName() {
		return name;
	}

	// Returns the information on a patient's disease
	string getDisease() {
		return disease;
	}

	// Returns the priority value of the patient
	int getPriorityValue() {
		return priorityValue;
	}

	int getPatientID() {
		return patientID;
	}

	// Overloaded "<" operator
	bool operator <(Patient& aPatient){
		if (priorityValue < aPatient.priorityValue)
			return true;
		else
			return false;
	}

	// Overloaded ">" operator
	bool operator >(const Patient& aPatient){
		if (priorityValue > aPatient.priorityValue)
			return true;
		else
			return false;
	}

	// Overloaded "<=" operator
	bool operator <=(const Patient& aPatient){
		if (priorityValue <= aPatient.priorityValue)
			return true;
		else
			return false;
	}

	// Overloaded ">=" operator
	bool operator >=(const Patient& aPatient){
		if (priorityValue >= aPatient.priorityValue)
			return true;
		else
			return false;
	}

	// Overloaded "==" operator
	bool operator ==(const Patient& aPatient){
		if (priorityValue == aPatient.priorityValue)
			return true;
		else
			return false;
	}

	// Overloaded output
	friend ostream& operator<<(ostream &output, Patient &aPatient){
		string displayPatient;
		string name = "Name       : ";
		string symptoms = "Symptoms   : ";
		string newline = "\n";
		displayPatient += name + aPatient.getName() + newline;
		displayPatient += symptoms + aPatient.getDisease();
		//displayPatient += prior + aPatient.getPriorityValue() + newline;
		output << displayPatient;
		return output;
	}
};

// All function declaration starting from here

// It is extremely important that you document each function declaration
// with the required elements: purpose, preconditions, parameters, postconditions
// and returns.

/**
* Display a welcome message at the beginning of the program.
* @pre none
* @post A welcome message has been displayed.
*/
void hello();

/**
* Display a farewell message at the end of the program.
* @pre none
* @post A farewell message has been displayed.
*/
void goodBye();

/**
* Display a menu of 4 choices for the user to choose from.
* @pre	none
* @post The user's choice will run another function.
*/
void mainMenu(LinkedList<Patient>& waitRoom, LinkedList<Patient>& operateRoom, Heap_PriorityQueue<Patient>& aQueue);

/**
* Runs another function based on the switch-case function when called
* @pre	User must have entered a choice.
* @post Another function will run based on the user's choice
*/
void operationPicker(int& aChoice, LinkedList<Patient>& waitRoom, LinkedList<Patient>& operateRoom, Heap_PriorityQueue<Patient>& aQueue);

/**
* Adds a patient object into the priority queue heap
* @pre	The heap cannot be full.
* @post The patient is added into the heap
*/
void addPatient(LinkedList<Patient>& waitRoom, Heap_PriorityQueue<Patient>& aQueue);

/**
* Schedules the patient into a vacant operating room
* @pre	There must be a patient in the heap, aQueue, and the
*		operating room must not be full
* @post Checks the patient into an operating room
*/
void scheduleOperation(LinkedList<Patient>& waitRoom, LinkedList<Patient>& operateRoom, Heap_PriorityQueue<Patient>& aQueue);

/**
* Display the names of the patients occupying the waiting room
* @pre	The waiting room must not be empty, or it will display no names.
* @post Displayes the names of the patients in the waiting room.
*/
void getWaitSchedule(LinkedList<Patient>& waitRoom);

/**
* Display the names of the patients occupying the operating room
* @pre	The operating rooms must not be empty, or it will display no names.
* @post Displayes the names of the patients in the operating rooms.
*/
void getOperateSchedule(LinkedList<Patient>& operateRoom);

/**
* Checks the patient out of the operating room
* @pre	Operating room must not be empty.
* @post The patient in the operating room is removed.
*/
void patientCheckOut(LinkedList<Patient>& aRoom);


// Main function
int main() {
	hello();

	// Linked list of patients in the waiting room
	LinkedList<Patient> waitingRoom;

	// Linked list of patients in the operating room
	LinkedList<Patient> operatingRoom;

	// Heap of Patients arranged by priority value
	Heap_PriorityQueue<Patient> waitingList;

	mainMenu(waitingRoom, operatingRoom, waitingList);

	goodBye();
	return 0;
}

// All function definitions starting from here
void hello() {
	cout << "Welcome to the Hospital!\n" << endl;
} // end hello

void goodBye() {
	cout << "End of Program." << endl;
} // end goodBye

void mainMenu(LinkedList<Patient>& waitRoom, LinkedList<Patient>& operateRoom, Heap_PriorityQueue<Patient>& aQueue) {
	int choice;
	do {
		cout << "Navigate through the main menu and enter the corresponding number to execute thecommand!\n";
		cout << "1 - Add patient into the waiting list.\n";
		cout << "2 - Schedule operation(s).\n";
		cout << "3 - Get the current schedule of the waiting room.\n";
		cout << "4 - Get the current schedule of the operating rooms.\n";
		cout << "5 - Checkout a patient from an operating room.\n";
		cout << "6 - Exit the program.\n";

		do {
			cout << "Enter the number here : ";
			cin >> choice;
			cin.ignore();
			cout << endl;
			if (choice < 0 || choice == 0 || choice > 6)
				cout << "Invalid input. Please try again.\n";
		} while (choice < 0 || choice == 0 || choice > 6);

		if ((choice > 0) && (choice < 6))
			operationPicker(choice, waitRoom, operateRoom, aQueue);
	} while (choice != 6);
} // end mainMenu

void operationPicker(int& aChoice, LinkedList<Patient>& waitRoom, LinkedList<Patient>& operateRoom, Heap_PriorityQueue<Patient>& aQueue) {
	switch (aChoice) {
	case 1:
		addPatient(waitRoom, aQueue);
		break;
	case 2:
		scheduleOperation(waitRoom, operateRoom, aQueue);
		break;
	case 3:
		getWaitSchedule(waitRoom);
		break;
	case 4:
		getOperateSchedule(operateRoom);
		break;
	case 5:
		patientCheckOut(operateRoom);
		break;
	} // end switch-case
} // end operationPicker

void addPatient(LinkedList<Patient>& waitRoom, Heap_PriorityQueue<Patient>& aQueue) {
	string patientName;
	string symptoms;
	int priorityValue;

	cout << "What's the name of the patient? ";
	getline(cin, patientName);

	cout << "What are the symptoms of the patient? ";
	getline(cin, symptoms);

	do {
		cout << "Give a priority value to the patient (1 - 10) (1 = lowest, 10 = highest) : ";
		cin >> priorityValue;
		if (priorityValue < 0 || priorityValue > 10)
			cout << "Invalid priority value input. Please try again.\n";
	} while (priorityValue < 0 || priorityValue > 10);

	srand(time(0));
	int ID = rand() % (300 - 100) + 100;
	Patient aPatient(patientName, symptoms, priorityValue, ID);
	aQueue.add(aPatient);
	waitRoom.insert(waitRoom.getLength() + 1, aPatient);

	cout << endl;
} // end addPatient

void scheduleOperation(LinkedList<Patient>& waitRoom, LinkedList<Patient>& operateRoom, Heap_PriorityQueue<Patient>& aQueue) {
	if (aQueue.isEmpty() || waitRoom.isEmpty())
		cout << "No patient in the waiting room.\n" << endl;
	else if (operateRoom.getLength() == maxRooms)
		cout << "Operating rooms are full.\n" << endl;
	else {
		if (operateRoom.getLength() > maxRooms)
			cout << "No room Available" << endl;
		else {
			while (operateRoom.getLength() < maxRooms) {
				Patient aPatient = aQueue.peek();
				aQueue.remove();

				for (int patientIndex = 1; patientIndex <= waitRoom.getLength(); patientIndex++) {
					if (waitRoom.getEntry(patientIndex).getName() == aPatient.getName())
						waitRoom.remove(patientIndex);
				}

				operateRoom.insert(operateRoom.getLength() + 1, aPatient);
				cout << "Patient " << aPatient.getName() << " is in one of the operating room.\n\n";

				if (aQueue.isEmpty())
					break;
			} // end while
		} // end else
	} // end else
} // end scheduleOperation

void getWaitSchedule(LinkedList<Patient>& waitRoom) {
	if (waitRoom.isEmpty())
		cout << "No patient in the waiting room.\n" << endl;
	else {
		cout << "Patients in the waiting room : \n\n";
		for (int roomIndex = 1; roomIndex <= waitRoom.getLength(); roomIndex++) {
			cout << "Patient ID : " << waitRoom.getEntry(roomIndex).getPatientID() << endl;
			cout << waitRoom.getEntry(roomIndex) << endl;
			cout << "Priority   : " << waitRoom.getEntry(roomIndex).getPriorityValue();
			cout << endl << endl;
		}
	}
} // end getCurrentSchedule

void getOperateSchedule(LinkedList<Patient>& operateRoom) {
	if (operateRoom.isEmpty())
		cout << "No patient in the operating rooms.\n" << endl;
	else {
		cout << "Patients in the operating rooms : \n\n";
		for (int roomIndex = 1; roomIndex <= operateRoom.getLength(); roomIndex++) {
			cout << "Patient ID : " << operateRoom.getEntry(roomIndex).getPatientID() << endl;
            cout << operateRoom.getEntry(roomIndex) << endl << endl;
		}
	}
} // end getCurrentSchedule

void patientCheckOut(LinkedList<Patient>& aRoom) {
	int patientID;

	if (aRoom.isEmpty())
		cout << "No patient in the operating room.\n\n";
	else {
		getOperateSchedule(aRoom);

		cout << "What is the ID of the patient that is checking out?\n";
		cout << "Enter patient ID here : ";
		cin >> patientID;
		cout << endl;

		for (int aIndex = 1; aIndex <= aRoom.getLength(); aIndex++) {
			if (patientID == aRoom.getEntry(aIndex).getPatientID())
				aRoom.remove(aIndex);
			else if ((aIndex == aRoom.getLength()) && (patientID != aRoom.getEntry(aIndex).getPatientID())) {
				cout << "No patient with that patient ID.\n\n";
				break;
			} // end else if
		} // end for
	} // else
} // end patientCheckOut
/*
Copy program interaction between user and the program here.
*/
