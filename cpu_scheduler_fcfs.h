#ifndef CISC5595_CPU_SCHEDULER_FCFS_H
#define CISC5595_CPU_SCHEDULER_FCFS_H

// cpu_scheduler_fcfs.h
//
// First-come first-served CPU scheduler.

#include "cpu_scheduler_base.h"
#include "process.h"

#include <deque>
#include <mutex>

using namespace std;

class CpuSchedulerFcfs : public CpuSchedulerBase {

    public:

        // Add a new process to the set of processes to be
        // scheduled.
        virtual bool addProcess(Process process);
        
        // Put a process that was previously scheduled back
        // into the scheduler. 
        virtual bool requeueProcess(Process process)    ;

        // Get the process id of the next process to be scheduled
        // If no processes remain to schedule, return -1
        virtual int nextProcess();

    private:
        
        // This mutex will be used to serialize access to 
        // the data structure
        mutex m_mutex;
        
        
        // TODO: Copy the data structure from assignment 3

        
};

#endif