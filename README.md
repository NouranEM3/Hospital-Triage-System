# Hospital Triage System

## Overview
This project is a **C++ hospital triage system** created as part of my **Data Structures course**. The program simulates an emergency room management system using a priority queue with heap-based ordering. It demonstrates key concepts such as custom class design, heap-based sorting, dynamic memory management, and command-line interface (CLI) programming.

## Features
### Priority Queue System:
1. Patients are assigned one of the following priority levels:
   - **1 (immediate)**: Should be seen within 0 minutes.
   - **2 (emergency)**: Should be seen within 15 minutes.
   - **3 (urgent)**: Should be seen within 30 minutes.
   - **4 (minimal)**: Should be seen within 120 minutes.
2. Patients are processed based on:
   - Priority code (higher priority first).
   - Arrival order (earlier arrivals first in case of tie).

### Command-Line Interface:
- **add <priority-code> <patient-name>:** Adds a patient to the triage system.
- **peek:** Displays the next patient to be seen without removing them from the queue.
- **next:** Removes the next patient and announces their name.
- **list:** Displays all patients currently in the queue, in heap order.
- **load <file>:** Loads commands from a text file and executes them.
- **help:** Displays a list of available commands.
- **quit:** Exits the program.

### File Structure:
Hospital-Triage-System
  ─ p3.cpp                     # Main driver program (UI and logic)
  ─ Patient.h                  # Patient class for managing patient data
  ─ PatientPriorityQueue.h     # Priority queue implementation using a heap
  ─ commands.txt               # Sample input file with commands
  ─ README.md                  # Project documentation

### Key Concepts Learned
  - Heap Data Structures: Implementing a priority queue using a heap for efficient ordering.
  - Dynamic Memory Management: Managing dynamic arrays and maintaining heap order.
  - Object-Oriented Design: Designing and implementing modular classes.
  - Command-Line Interface: Building a text-based interface for interaction.
  - File I/O: Reading and executing commands from external files.
