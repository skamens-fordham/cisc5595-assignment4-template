#include "cpu_scheduler_fcfs.h"
#include "process.h"

// Add a process to be scheduled.
// Since this is first come, first served, this just adds
// the process ID of the process to be scheduled to 
// the queue.
bool CpuSchedulerFcfs::addProcess(Process process)
{

}

// Put a process that was previously scheduled back
// into the scheduler. Since this is first come, first-served,
// we want to requeue the process at the beginning of the
// list rather than the end (as we do with add)
bool CpuSchedulerFcfs::requeueProcess(Process process)
{

}


// Find the next process to run
int CpuSchedulerFcfs::nextProcess()
{

}
