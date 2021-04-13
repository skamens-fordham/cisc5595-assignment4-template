# Operating Systems Assignment 4: Synchronization

In this assignment, we will implement multi-threaded execution of processes, which 
will require synchronization between the threads.

As with the previous assignment, the template code files have TODO comments 
that indicate where your code should be added.

# Scheduler Classes

## Changes in class behavior from Assignment 3
The scheduler classes for this assignment will behave slightly differently than
the ones implemented in assignment 3. Here are the differences:

* The `nextProcess()` method should remove the process from its data structure when it returns a process to schedule.
* The `removeProcess()` method has been removed
* A new method `requeueProcess()` has been added, which should be used to put the process back into the scheduler after it has executed.

The template files for the scheduling classes have been updated to reflect these changes in behavior. 

### Synchronization
Since this program will be multi-threaded, you will need to add protection to your scheduler classes to ensure that the critical sections in your classes are protected. The template files define the variables that will be needed for the locking to be implemented.

### C++
If you are programming in C++, use RAII )(see https://en.cppreference.com/w/cpp/language/raii)

### Python
If you are programming in Python, use the with statement (see https://www.bogotobogo.com/python/Multithread/python_multithreading_Using_Locks_with_statement_Context_Manager.php)

# Process class
The Process class is identical to the one from assignment 3, and has been included here.

# Process Table

Think about what methods of your process table will be used as part of the execution portion of the code. Add synchronization protection to those methods in a way similar to what you did in the scheduling classes.

# execute
The `execute.cpp` and `execute.py` files in this directory contain TODO entries for how to implement your thread-based execution. Implement the code as directed in this file.

# Assignment Submission
When you have completed the assignment, be sure to commit your changes and push them to github, and then upload your submit.txt file to Blackboard.


