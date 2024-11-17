// Author: Nouran Mahfouz
// Date:   5/15/24
// File:   PatientPriorityQueue.h

// This class stores patient in a minimum heap according to their priority code and considering their arrival order
// It provides functionalities to add patients to the queue, remove the highest priority patient, peek at the next
// patient to be seen, and manage the patient list.

#ifndef P3_PATIENTPRIORITYQUEUE_H
#define P3_PATIENTPRIORITYQUEUE_H

// min heap
#include "Patient.h"
#include <cassert>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class PatientPriorityQueue {

public:
    PatientPriorityQueue();     // Constructor
    ~PatientPriorityQueue();    // Destructor

    void add(Patient);      // Adds patient to priority queue
    Patient remove();       // Removes and returns the patient with the highest priority.
    Patient peek() const;   // Returns the patient with the highest priority without removing them.
    int size() const;       // Returns the size of the priority queue.
    bool empty() const;     // Checks if the priority queue is empty.
    string to_string() const;   // Returns a string representation of the patients in the queue.

private:
    vector<Patient> list;   // Vector to store patients in a min heap structure.
    int nextPatientNumber;  // Counter for the next patient number.

    void siftUp(int);   // Sifts a node up the heap to restore heap order.
    void siftDown(int); // Sifts a node down the heap to restore heap order.
    int getParent(int) const;   // Gets the index of the parent node.
    int getLeftChild(int) const;    // Gets the index of the left child node.
    int getRightChild(int) const;   // Gets the index of the right child node.
};

//*********************
// PUBLIC FUNCTIONS   *
//*********************

PatientPriorityQueue::PatientPriorityQueue() {
    nextPatientNumber = 0;
}

PatientPriorityQueue::~PatientPriorityQueue(){
    list.clear();
}

int PatientPriorityQueue::size() const{
    return  list.size();
}

void PatientPriorityQueue::add(Patient p) {

    p.setArrivalOrder(++nextPatientNumber);
    list.push_back(p);
    siftUp(list.size() - 1);
}

Patient PatientPriorityQueue::remove() {
    assert(!empty());
    Patient temp = list[0];
    list[0] = list.back();
    list.pop_back();
    if (!empty())
        siftDown(0);
    return temp;
}

Patient PatientPriorityQueue::peek() const {
    assert(!empty());
    return list[0];
}

bool PatientPriorityQueue::empty() const {
    return list.empty();
}
string PatientPriorityQueue::to_string() const{
    stringstream ss;
    for(const auto &patient : list) {
        ss << patient.stringList();
    }
    return ss.str();
}

//*********************
// PRIVATE FUNCTIONS  *
//*********************

void PatientPriorityQueue::siftUp(int index) {
    int parentIdx;
    Patient temp;
    if (index != 0) {
        parentIdx = getParent(index);
        if (list[parentIdx] > list[index]) {
            temp = list[parentIdx];
            list[parentIdx] = list[index];
            list[index] = temp;
            siftUp(parentIdx);
        }
    }
}

void PatientPriorityQueue::siftDown(int index) {
    int leftIdx, rightIdx, minIdx;
    Patient temp;
    leftIdx = getLeftChild(index);
    rightIdx = getRightChild(index);

    // find minIdx
    if (rightIdx >= static_cast<int>(list.size())) {
        if (leftIdx >= static_cast<int>(list.size()))
            return;
        else
            minIdx = leftIdx;
    } else {
        if (list[leftIdx] <= list[rightIdx])
            minIdx = leftIdx;
        else
            minIdx = rightIdx;
    }

    // swap?
    if (list[index] > list[minIdx]) {
        temp = list[minIdx];
        list[minIdx] = list[index];
        list[index] = temp;
        siftDown(minIdx);
    }
}

int PatientPriorityQueue::getParent(int index) const {
    return (index - 1) / 2;
}

int PatientPriorityQueue::getLeftChild(int index) const {
    return 2 * index + 1;
}

int PatientPriorityQueue::getRightChild(int index) const {
    return 2 * index + 2;
}



#endif //P3_PATIENTPRIORITYQUEUE_H
