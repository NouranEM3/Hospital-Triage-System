// Author: Nouran Mahfouz
// Date:   5/15/24
// File:   p3.cpp
// Purpose: This program manages a priority queue system for a hospital triage scenario, where patients are prioritized
//      based on their medical urgency. The program supports various commands to interact with the patient queue,
//      including adding new patients, viewing the next patient to be treated, removing the highest-priority patient,
//      listing all patients, changing a patient's priority, saving the current patient list to a file, and loading
//      commands from a file.

// Inputs:  Patient's name and priority code
//          Command to be executed (help, list, add, peek, next, load and quit

// Outputs: Welcome message: Displayed at the start of the program.
//          Patient with the highest priority and patient with the next highest priority
//          List displaying all patients in waiting list with priority code and order of arrival
//          Help menu with all system commands and their functionalities
//          Goodbye message: Displayed when program quits.

#include "PatientPriorityQueue.h"
#include "Patient.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

void welcome();
// Prints welcome message.

void goodbye();
// Prints goodbye message.

void help();
// Prints help menu.

bool processLine(string, PatientPriorityQueue &);
// Process the line entered from the user or read from the file.

void addPatientCmd(string, PatientPriorityQueue &);
// Adds the patient to the waiting room.

void peekNextCmd(PatientPriorityQueue &);
// Displays the next patient in the waiting room that will be called.

void removePatientCmd(PatientPriorityQueue &);
// Removes a patient from the waiting room and displays the name on the screen.

void showPatientListCmd(PatientPriorityQueue &);
// Displays the list of patients in the waiting room.

void execCommandsFromFileCmd(string, PatientPriorityQueue &); 
// Reads a text file with each command on a separate line and executes the
// lines as if they were typed into the command prompt.

string delimitBySpace(string &);
// Delimits (by space) the string from user or file input.

int main() {
	// declare variables
	string line;

	// welcome message
	welcome();

	// process commands
	PatientPriorityQueue priQueue;
	do {
		cout << "\ntriage> ";
		getline(cin, line);
	} while (processLine(line, priQueue));

	// goodbye message
	goodbye();
}

bool processLine(string line, PatientPriorityQueue &priQueue) {
	// get command
	string cmd = delimitBySpace(line);
	if (cmd.length() == 0) {
		cout << "Error: no command given.";
		return false;
	}
	
	// process user input
	if (cmd == "help")
		help();
	else if (cmd == "add")
		addPatientCmd(line, priQueue);
	else if (cmd == "peek")
		peekNextCmd(priQueue);
	else if (cmd == "next")
		removePatientCmd(priQueue);
	else if (cmd == "list")
		showPatientListCmd(priQueue);
	else if (cmd == "load")
		execCommandsFromFileCmd(line, priQueue);
	else if (cmd == "quit")
		return false;
	else
		cout << "Error: unrecognized command: " << cmd << endl;

	return true;
}

void addPatientCmd(string line, PatientPriorityQueue &priQueue) {

	string priority, name, fullName;
    int pri = 0;
	// get priority and name
	priority = delimitBySpace(line);
	if (priority.length() == 0) {
		cout << "Error: no priority code given.\n";
		return;
	}
	name = line;
    if (name.length() == 0) {
		cout << "Error: no patient name given.\n";
		return;
	}

	// add logic to remove leading/trailing spaces
    auto nameBegin = name.find_first_not_of("   ");
    auto nameEnd = name.find_last_not_of("   ");
    auto nameRange = nameEnd - nameBegin + 1;
    fullName = name.substr(nameBegin, nameRange);

	// validate priority is between 1 and 4
    if (priority == "immediate")
            pri = 1;
    else if(priority == "emergency")
        pri = 2;
    else if(priority == "urgent")
        pri = 3;
    else if(priority == "minimal")
        pri = 4;
    else
        cout << "Invalid priority code given.\n";

	// add patient
    Patient p(fullName, pri );
    priQueue.add(p);
    cout << "Added patient \"" << fullName << "\" to the priority system" << endl;
}

void peekNextCmd(PatientPriorityQueue &priQueue) {
	// shows next patient to be seen
    if(priQueue.empty())
        cout << "No patients waiting." << endl;
    else
        cout << "Highest priority patient to be called next: " << priQueue.peek().getName() << endl;
}

void removePatientCmd(PatientPriorityQueue &priQueue) {
	// removes and shows next patient to be seen
    if(priQueue.empty())
        cout << "No patients waiting." << endl;
    else
        cout << "This patient will now be seen: " << priQueue.remove().getName() << endl;
}

void showPatientListCmd(PatientPriorityQueue &priQueue) {
	cout << "# patients waiting: " << priQueue.size() << endl << endl;
	cout << "  Arrival #   Priority Code   Patient Name\n"
		  << "+-----------+---------------+--------------+\n";
	// shows patient detail in heap order
    cout << priQueue.to_string();
}

void execCommandsFromFileCmd(string filename, PatientPriorityQueue &priQueue) {
	ifstream infile;
	string line;

	// open and read from file
	infile.open(filename);
	if (infile) {
		while (getline(infile, line)) {
			cout << "\ntriage> " << line;
			// process file input 
			processLine(line, priQueue);
		} 
	} else {
		cout << "Error: could not open file.\n";
	}
	// close file
	infile.close();
}

string delimitBySpace(string &s) {
	unsigned pos = 0;
	char delimiter = ' ';
	string result = ""; 

	pos = s.find(delimiter);
	if (pos != string::npos) {
		result = s.substr(0, pos);
		s.erase(0, pos + 1);
	}
	return result;
}

void welcome() {
    cout << "***** Welcome to the hospital triage system *****" << endl;
    cout << "Enter command line or type \"help\" to display command list." << endl;
}

void goodbye() {
    cout << endl;
    cout << "Thank you for using the triage system!!"<< endl;
    cout << "GoodBye!" << endl;
}	

void help() {
	cout << "add <priority-code> <patient-name>\n"
<< "            Adds the patient to the triage system.\n"
<< "            <priority-code> must be one of the 4 accepted priority codes:\n"
<< "                1. immediate 2. emergency 3. urgent 4. minimal\n"
<< "            <patient-name>: patient's full legal name (may contain spaces)\n"
<< "next        Announces the patient to be seen next. Takes into account the\n"
<< "            type of emergency and the patient's arrival order.\n"
<< "peek        Displays the patient that is next in line, but keeps in queue\n"
<< "list        Displays the list of all patients that are still waiting\n"
<< "            in the order that they have arrived.\n"
<< "load <file> Reads the file and executes the command on each line\n"
<< "help        Displays this menu\n"
<< "quit        Exits the program\n";
}
