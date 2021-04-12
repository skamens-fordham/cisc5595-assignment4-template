# Implements a CPU scheduling class using the first-come, first-served
# algorithm.

import threading

from process import Process

class CpuSchedulerFcfs:
    def __init__(self):
        # This lock will be used to serialize access to the data structure
        self.lock = threading.Lock()
        
        # TODO: Copy the data structure from assignment 3 here        
        

    
    # Add a process
    def addProcess(self, p):
        # TODO: Add locking here

        # TODO: Add implementation of addProcess here. This should be
        #       identical to the implementation from assignment 3


    def nextProcess(self):
        # TODO: Add locking here

        # TODO:  Find the next process that should be executed.
        #        Note: the difference between this implementation
        #        and the one from assignment 3 is that the
        #        process to be executed should be *removed* from
        #        the scheduler before it is returned 
        #        to the caller.


    def requeueProcess(self, p):
        # TODO: Add locking here

        # TODO: Place the process back into the data structure
        #       in the correct place
