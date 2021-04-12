#!/usr/bin/python3

from process import Process
from process_table import ProcessTable
from cpu_scheduler_fcfs import CpuSchedulerFcfs
from cpu_scheduler_priority_rr import CpuSchedulerPriorityRoundRobin

import json
import sys
import threading


# In Python, threading is performed by creating a subclass
# of the threading.Thread class, as shown here
class ScheduleThread(threading.Thread):
    # TODO: Add additional parameters here which will contain all the data
    #       needed to perform the scheduling algorithm
    def __init__(self, ): 
        
        # This connects this class to the parent threading.Thread class
        threading.Thread.__init__(self)

        # TODO: Initialze appropriate class member variables
        #       from the parameters you defined above

    def run(self):
        # TODO: Implement your scheduling loop in this function.
        #       The thread will have the same logic you used in assignment 3.
        #
        # NOTE: Remember the way the nextProcess() method has changed
        #       in this assignment. Make sure you make the appropriate changes 
        #       here to reflect the changes to nextProcess() and the new
        #       requeueProcess() method.

    
        


def main():

    # Initialize some variables that will be used later on
    table_size = 100
    scheduling_quantum = 1
    num_threads = 1
    scheduler = None

    # First read the input file

    if (len(sys.argv) != 2) :
        sys.exit("Usage: " + sys.argv[0] + " <input file>")

    input = {}

    with open(sys.argv[1]) as f:
        input = json.load(f)

    # Process the options section. 
    # The only current option is the table size
    if 'options' in input:
        options = input['options']
        if 'table_size' in options:
            table_size = options['table_size']

    # Initialize the process table with the given size
    table = ProcessTable(table_size)

    # Figure out which scheduling algorithm we should use
    if 'schedule' in input and 'scheduling_algorithm' in input['schedule'] :
        algorithm = input['schedule']['scheduling_algorithm']

        if algorithm == 'fcfs' :
            scheduler = CpuSchedulerFcfs()
        elif algorithm == 'priority_round_robin':
            scheduler = CpuSchedulerPriorityRoundRobin()
    else :
        sys.exit("Error: schedule/scheduling_algorithm must be specified")

    # Get the the scheduling quantum, if it's found
    # (if not, we will just use the default of 1 from above)
    if 'scheduling_quantum' in input['schedule'] :
        scheduling_quantum = input['schedule']['scheduling_quantum']

    # TODO: There is a new parameter called "num_threads" in the "schedule" 
    #       section that indicates how many threads the program should create.
    #       Retrieve that value here and assign it to num_threads.

    # Load the processes from the input into the process table and the scheduler
    for process in input['processes']:
        p = Process(process['process_name'], -1, process['priority'], process['cpu_needed'])

        p.setProcessId(table.add(p))
        scheduler.addProcess(p)

    # Print the process table one time after all processes are loaded
    print(table)



    # Now we will start the threads that will perform the actual execution
    # of the processes
    threads = []

    for threadNum in range(0, num_threads) :
        
        # TODO: Add the appropriate parameters to the ScheduleThread constructor here
        newThread = ScheduleThread()
        
        threads.append(newThread)
        newThread.start()

    # Wait for all threads to complete
    for t in threads:
        t.join()

    return 0

if __name__ == "__main__":
    main()
