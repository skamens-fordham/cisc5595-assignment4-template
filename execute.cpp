// execute.cpp
// Program to execute the instructions in an input file


#include <string>
#include <fstream>
#include <iostream>
#include <mutex>
#include <pthread.h>

#include "nlohmann/json.hpp"
#include "process_table.h"
#include "process.h"
#include "cpu_scheduler_base.h"
#include "cpu_scheduler_fcfs.h"
#include "cpu_scheduler_priority_rr.h"

using namespace std;

// TODO: This structure will contain all of the data needed for the processRunner
//       to execute the scheduling algorithm. Add appropriate data members here
struct processRunnerData {

};

mutex printMutex;

// This is the function that will be executed by your threads
void * processRunner(void * data)
{
    // Here you take the pointer to your thread data and convert it
    // to the struct defined above.
    struct processRunnerData * d = (struct processRunnerData *) data;

    // TODO: Implement your scheduling loop in this function.
    // The thread will have the same logic you used in assignment 3.
    //
    // NOTE: Remember the way the nextProcess() method has changed
    //       in this assignment. Make sure you make the appropriate changes 
    //       here to reflect the changes to nextProcess() and the new
    //       requeueProcess() method.

    


    // Once you have completed the implementation of your 
    // scheduling, this causes your thread to exit.
    pthread_exit(NULL);
}

int
main(int argc, char ** argv)
{

    // Table size defaults to 100 if not specified on the command line
    int tableSize = 100;
    std::string algorithm = "";
    int scheduling_quantum = 1;
    int num_threads = 1;


    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return(3);
    }
        
    // Open the input file. 
    ifstream in(argv[1]);
    if (! in.good()) {
        cerr << "Failed to open file " << argv[1] << endl;
        return(4);
    }

    nlohmann::json input_json;

    // Read the file into the json object.
    // If the input file is not in json format, this will
    // throw an exception

    try {
        in >> input_json;
    } catch (nlohmann::json::exception& e) {
        cerr << "Error: " << e.what() << endl
             << "exception id: " << e.id << endl;
        return(5);
    }


    // Process the options (which are still just the
    // table size)

    if (input_json.contains("options")) {
        if (input_json["options"].contains("table_size")) {
            tableSize = input_json["options"]["table_size"];
        }
    }

    // Initialize a ProcessTable with the table size obtained from
    // the options (or the default if no option was specified)
    ProcessTable table(tableSize);


    // Determine the scheduling algorithm from the schedule
    // segment.

    if (input_json.contains("schedule") && 
      input_json["schedule"].contains("scheduling_algorithm")) {
          algorithm = input_json["schedule"]["scheduling_algorithm"];
    } else {
        cerr << "Error: schedule/scheduling_algorithm must be specified" << endl;
        return(7);
    }

    // Initialize a scheduling object depending on the algorithm
    CpuSchedulerBase * scheduler;
    if (algorithm == "fcfs") {
        scheduler = (CpuSchedulerBase *) new CpuSchedulerFcfs();
    } else if (algorithm == "priority_round_robin") {
        scheduler = (CpuSchedulerBase *) new CpuSchedulerPriorityRr;
    } else {
        cerr << "Error: Unknown algorithm '" << algorithm <<
                "'. Legal values are 'fcfs' and 'priority_round_robin'" << endl;
        return(7);
    }


    // We know the input contains a "schedule" section. Let's see if
    // scheduling_quantum is set

    if(input_json["schedule"].contains("scheduling_quantum")) {
        scheduling_quantum = input_json["schedule"]["scheduling_quantum"];
    }

    // TODO: There is a new parameter called "num_threads" in the "schedule" 
    //       section that indicates how many threads the program should create.
    //       Retrieve that value here and assign it to num_threads.
   

    // Iterate the processes in the input json,
    // adding each process in turn.
    // NOTE: We do not print the process table as processes are
    // added.

    for(auto process = input_json["processes"].begin(); 
            process != input_json["processes"].end();
            ++process) {

        Process p;

        // Note that if there is an extra unrecogized keyword
        // in the input json, it will simply be ignored, and no
        // exception will be thrown.
        try {
            process->get_to(p);
        } catch (nlohmann::json::exception& e) {
            // output exception information
            cerr << "Error: " << e.what() << endl
                    << "exception id: " << e.id << std::endl;
            return(6);
        } catch (std::invalid_argument& e) {
            cerr << "Error: " << e.what() << endl;
            return(7);
        }

        int pid = table.add(p);
        if (pid == -1) {
            cerr << "Failed to add process: " << p.processName() << endl;
            return(8);
        }

        p.setProcessId(pid);
        scheduler->addProcess(p);            
    }

    // Print the process table one time after all processes are loaded
    std::cout << table;
    std::cout << endl;
    
    // Now start the threads that will perform the actual execution
    // of the processes

    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {
        // Set up the data that will be passed to each thread
        struct processRunnerData * d = new struct processRunnerData;

        // TODO: Populate the thread data object with the data that 
        // the thread will need to execute.




        pthread_create(&threads[i], NULL, processRunner, (void *) d);
    }

    // Now wait for the threads to finish
    void * ret;
    for (int i = 0; i < num_threads; ++i) {
        pthread_join(threads[i], &ret);
    }
   
    // Return 0 when complete
    return 0;

}
