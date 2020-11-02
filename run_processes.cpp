// Main program for assignment 3 - Process Scheduling
//
// This program will be run as follows:
//
// run_processes --algorithm=<algo> --num_threads=<threads> <json_files>
//    Where <algo> will be either "fcfs" or "priority",
//          <threads> is the number of threads to run, and 
//          <json_files> is a set of one or more processes to run

#include "cpu_scheduler_base.h"
#include "cpu_scheduler_fcfs.h"
#include "cpu_scheduler_priority_rr.h"
#include "process.h"
#include "process_table.h"

#include <getopt.h>
#include <iostream>
#include <fstream>

using namespace std;

// Thread functions take a single pointer to any data that
// they might need to use. 
// Add members to this structure to represent all the data your
// thread function will need.
struct processRunnerData {
   
};


// This is the function that will be executed by your threads.

void * processRunner(void * data)
{
    // Here you take the pointer to your thread data and convert it
    // to the struct defined above.
    struct processRunnerData * d = (struct processRunnerData *) data;

    // Implement your scheduling loop in this function.
    // The thread will have the same logic you used in the 
    // run_processes program in assignment 3.
    //
    // NOTE: Remember the way the nextProcess() method has changes
    //       in this assignment. Make sure you make the appropriate changes 
    //       here to reflect the changes to nextProcess() and the new
    //       requeueProcess() method.

    


    // Once you have completed the implementation of your 
    // scheduling, this causes your thread to exit.
    pthread_exit(NULL);
}


int main(int argc, char ** argv)
{
    ProcessTable table;             // Will contain the processes to be scheduled
    CpuSchedulerBase * scheduler;   // Scheduler that will be used 
    string algorithm;               // String choosing which scheduling algorithm to use
    int numThreads = 1;             // Number of threads to start

    // Copy your command line processing from assignment 3, and update it to
    // add the new argument (--num_threads) for assignment 4.



    // Allocate a scheduling object based on the
    // chosen algorithm.
    if (algorithm == "fcfs") {
        scheduler = (CpuSchedulerBase *) new CpuSchedulerFcfs;
    } else if (algorithm == "priority") {
        scheduler = (CpuSchedulerBase *) new CpuSchedulerPriorityRr;
    } else {
        cerr << "No algorithm specified!" << endl;
        return(9);
    }

    // The rest of the arguments will be files in json format containing 
    // specifications for processes to be added to the table.

    // Copy your code for loading the processes from the input json files and 
    // adding them to your process table and scheduler, using the same
    // logic as assignment 3.





    // Now start the threads that will perform the actual execution
    // of the processes

    pthread_t threads[numThreads];

    for (int i = 0; i < numThreads; ++i) {
        // Set up the data that will be passed to each thread
        struct processRunnerData * d = new struct processRunnerData;

        // Populate the thread data object with the data that 
        // the thread will need to execute.

        // This creates the thread
        pthread_create(&threads[i], NULL, processRunner, (void *) d);
    }

    // Now wait for the threads to finish
    void * ret;
    for (int i = 0; i < numThreads; ++i) {
        pthread_join(threads[i], &ret);
    }
   
    // Return 0 when complete
    return 0;
}