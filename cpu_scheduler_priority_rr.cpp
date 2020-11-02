#include "cpu_scheduler_priority_rr.h"
#include "process.h"

#include <map>
#include <deque>

// Add a process to be scheduled.
// Since this is first come, first served, this just adds
// the process ID of the process to be scheduled to 
// the queue.

bool CpuSchedulerPriorityRr::addProcess(Process process)
{

}

// Put a process that was previously scheduled back
// into the scheduler. 
bool CpuSchedulerPriorityRr::requeueProcess(Process process)
{

}


// Find the next process to run
int CpuSchedulerPriorityRr::nextProcess()
{
 
}
