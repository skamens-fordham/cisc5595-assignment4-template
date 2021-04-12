#include "cpu_scheduler_fcfs.h"
#include "process.h"

#include <deque>

// Add a process to be scheduled.
bool CpuSchedulerFcfs::addProcess(Process process)
{
    // TODO: Add lock_guard here using the mutex that is a member of the class

    // TODO: Add implementation of addProcess here. This should be
    //       identical to the implementation from assignment 3
}

// Put a process that was previously scheduled back
// into the scheduler.
bool CpuSchedulerFcfs::requeueProcess(Process process)
{
   // TODO: Add lock_guard here using the mutex that is a member of the class
   //
   // TODO: Place the process back into the data structure
   //       in the correct place
}


// Find the next process to run
int CpuSchedulerFcfs::nextProcess()
{
    // TODO: Add lock_guard here using the mutex that is a member of the class


    // TODO: Find the next process that should be executed.
    //       Note: the difference between this implementation
    //       and the one from assignment 3 is that the
    //       process to be executed should be *removed* from
    //       the scheduler before it is returned 
    //       to the caller.
    
}
