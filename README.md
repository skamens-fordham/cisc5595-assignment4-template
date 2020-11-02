# CISC 5595 Assignment 4: Synchronization

In this assignment, we will implement multi-threaded execution of processes, which 
will require synchronization between the threads.

# Scheduler Classes

## Differences from Assignment 3
The scheduler classes for this assignment should behave slightly differently than
the ones implemented in assignment 3. Here are the differences:

* The `nextProcess()` method should remove the process from its data structure when it returns a process to schedule.
* The `removeProcess()` method has been removed
* A new method `requeueProcess()` has been added, which should be used to put the process back into the scheduler after it has executed.

The header files for the scheduling classes have been updated to reflect these changes in behavior. 

Implement the new class behavior. You can copy your (or my) solutions from assignment 3 and modify them, if you prefer.

## Synchronization
Since this program will be multi-threaded, you will need to add protection to your scheduler classes to ensure that the critical sections in your classes are protected. 

The template header files define a mutex class member. Use a `std::lock_guard` to protect each function in this class using the mutex. (This uses RAII to protect the critical sections)

# Process class
The Process class should be the same as the one from assignment 3. Copy your (or my) files from the process class (`process.h` and `process.cpp`) into your assignment 4 directory.

# Process Table
Copy your files for the process_table class (`process_table.h` and `process_table.cpp`) into this directory.

Think about what methods of your process table will be used as part of the execution portion of the code. Add synchronization protection to those methods in a way similar to what you did in the scheduling classes.

# run_processes
The `run_processes.cpp` file in this directory contains instructions for how to implement your thread-based execution. Implement the code as directed in this file.



