// process_table.cpp
//
// Implementation of the ProcessTable class

#include "process_table.h"
#include "process.h"

#include <string>
#include <iostream>

using namespace std;

// TODO: Throughout this class, determine where synchronization
//       is required, and add it as appropriate


ProcessTable::ProcessTable(int size) :
    m_tableSize(size), m_currentIdx(-1), m_processTable(NULL)
{
    // Allocate the array of processes
    //
    // Note that the default constructor should run 
    // for each of the array elements

    m_processTable = new Process[m_tableSize];
}

ProcessTable::~ProcessTable()
{
    delete[] m_processTable;
}

int
ProcessTable::getSize() 
{
    return m_tableSize;
}

int
ProcessTable::add(const Process& p)
{
    lock_guard<mutex> guard(m_mutex);

    // Start with the next index (currentIndex + 1)
    // Keep iterating until we reach currentIndex.
    // If we find an empty spot before we get back
    // around, that's our next spot.
    // 
    // Note the loop incrementer which has to 
    // get the remainder so i wraps around to 
    // 0 
    int newIdx = -1;

    for (int i = (m_currentIdx + 1) % m_tableSize; 
         i != m_currentIdx; 
         i = (i + 1) % m_tableSize) {

        if (m_processTable[i].processId() == -1) {
           newIdx = i;
           break;
        }
    }

    if (newIdx == -1) {
        return -1;
    }

    m_processTable[newIdx].setProcessId(newIdx + 1);
    m_processTable[newIdx].setProcessName(p.processName());
    m_processTable[newIdx].setPriority(p.priority());
    m_processTable[newIdx].setCpuNeeded(p.cpuNeeded());
    m_currentIdx = newIdx;
    return newIdx + 1;
}


bool ProcessTable::remove(int processId)
{
    lock_guard<mutex> guard(m_mutex);

    if (m_processTable[processId - 1].processId() == -1) {
        return false;
    }

    m_processTable[processId - 1].setProcessId(-1);
    m_processTable[processId - 1].setProcessName("");
    m_processTable[processId - 1].setPriority(-1);
    m_processTable[processId - 1].setCpuNeeded(0);
    return true;
}

Process * ProcessTable::find(int processId)
{
    lock_guard<mutex> guard(m_mutex);

    if(m_processTable[processId - 1].processId() == -1) {
        return nullptr;
    }

    return &(m_processTable[processId - 1]);
}


// Friend function to print the object
std::ostream& operator<<(std::ostream& os, const ProcessTable& t)
{
    for (int i = 0; i < t.m_tableSize; ++i)
    {
        if (t.m_processTable[i].processId() != -1) {
            os << t.m_processTable[i] << endl;
        }
    }
    return os;
}