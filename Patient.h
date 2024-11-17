// Author: Nouran Mahfouz
// Date:   5/15/24
// File:   Patient.h

// This class stores patient in a minimum heap according to their priority code and considering their arrival order
// It provides functionalities to add patients to the queue, remove the highest priority patient, peek at the next
// patient to be seen, and manage the patient list.
//

#ifndef P3_PATIENT_H
#define P3_PATIENT_H
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Patient {

public:
    Patient();      // Constructor
    Patient(string, int);  // Overloaded constructor
    //~Patient();
    //Patient(const Patient &);
    Patient& operator = (const Patient &);       // Overloaded = operator
    bool operator == (const Patient &) const;    // Overloaded == operator
    bool operator < (const Patient &) const;     // Overloaded < operator
    bool operator <= (const Patient &) const;    // Overloaded <= operator
    bool operator > (const Patient &) const;     // Overloaded > operator
    bool operator >= (const Patient &) const;    // Overloaded >= operator

    // Setters and getters
    void setName(string);
    string getName() const;
    void setArrivalOrder(int);
    int getArrivalOrder() const;

    string to_string() const;
    string stringList() const;

private:
    string name;
    int priorityCode;
    int arrivalOrder;
};

Patient::Patient(){
    priorityCode = 0;
    arrivalOrder = 0;
}

Patient::Patient(string n, int pCode){
    name = n;
    priorityCode = pCode;
}

void Patient::setArrivalOrder(int aOrder){
    arrivalOrder = aOrder;
}
int Patient::getArrivalOrder() const{
    return  arrivalOrder;
}

void Patient:: setName(string n){
    name = n;
}

string Patient::getName() const{
    return name;
}

Patient& Patient::operator = (const Patient &p){
    name = p.name;
    priorityCode = p.priorityCode;
    arrivalOrder = p.arrivalOrder;
    return *this;
}

bool Patient::operator == (const Patient &p) const {
    if(priorityCode == p.priorityCode && arrivalOrder == p.arrivalOrder && name == p.name) {
        return true;
    }
    return false;
}

bool Patient::operator < (const Patient &p) const {
    if (priorityCode < p.priorityCode) {
        return true;
    }

    else if(priorityCode == p.priorityCode) {
        if (arrivalOrder < p.arrivalOrder) {
            return true;
        }
    }
    return false;
}

bool Patient::operator <= (const Patient &p) const {
    if (priorityCode < p.priorityCode ) {
        return true;
    }

    else if(priorityCode == p.priorityCode) {
        if (arrivalOrder < p.arrivalOrder || arrivalOrder == p.arrivalOrder) {
            return true;
        }
    }
    return false;
}

bool Patient::operator > (const Patient &p) const{
    if (priorityCode > p.priorityCode) {
        return true;
    }
    else if(priorityCode == p.priorityCode) {
        if (arrivalOrder > p.arrivalOrder) {
            return true;
        }
    }
    return false;
}

bool Patient::operator >= (const Patient &p) const{
    if (priorityCode > p.priorityCode ) {
        return true;
    }
    else if(priorityCode == p.priorityCode) {
        if (arrivalOrder > p.arrivalOrder || arrivalOrder == p.arrivalOrder) {
            return true;
        }
    }
    return false;
}

// to_string function displays patient in a string format as required
string Patient::to_string() const{
    stringstream ss;
    string priority;
    switch(priorityCode){
        case 1:
            priority = "immediate";
            break;
        case 2:
            priority = "emergency";
            break;
        case 3:
            priority = "urgent";
            break;
        case 4:
            priority = "minimal";
            break;
    }
    ss << name << " { pri = " << priority << ", arrive = " << arrivalOrder << " }";
    return ss.str();
}

// to display patient in a format compatible with list  format
string Patient::stringList() const{
    stringstream ss;
    string priority;
    switch(priorityCode){
        case 1:
            priority = "immediate";
            break;
        case 2:
            priority = "emergency";
            break;
        case 3:
            priority = "urgent";
            break;
        case 4:
            priority = "minimal";
            break;
    }
    ss << "\t" << arrivalOrder << "\t\t  " << priority << "\t\t  " << name << endl;
    return ss.str();
}


#endif //P3_PATIENT_H
