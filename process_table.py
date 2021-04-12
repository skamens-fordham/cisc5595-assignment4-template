
# The ProcessTable class contains all of the processes in the system.

# The internal table of processes is represented as a circular buffer
# It will be a list of a fixed number of processes which will be filled
# in sequentially. When the last process in the list is populated,
# the structure wraps around to add values from the beginning

from process import Process
import threading

# TODO: Throughout this class, add locking where needed

class ProcessTable:

    # Constructor
    # The constructor takes the size that the table should be.
    def __init__(self, tableSize=100):
        self.table_size = tableSize
        self.current_index = -1
        self.table = []

        # Initialize the list containing the process entries
        # with default values
        for _ in range(0, tableSize):
            self.table.append(Process())

        # This lock will be used to synchronize access to the 
        # Process table data structure
        self.lock = threading.Lock()

    # Return the table size
    def getSize(self):
        return self.table_size

    # Add a process to the table by name
    # Returns the process ID of the table, or
    # -1 if the process can not be added.
    def add(self, p):

        self.lock.acquire()

        # We start looking for an empty spot one above the location
        # of the current process, and continue incrementing until we either
        # find an empty slot or wrap around back to the current location.
        # Note the use of the remainder operator (%) to wrap around to the beginning as needed.
        new_index = (self.current_index + 1) % self.table_size
        while (new_index != self.current_index) and (self.table[new_index].processId() != -1) :
            new_index = (new_index + 1) % self.table_size

        if new_index == self.current_index:
            # new_index wrapped around to the current index, which means we are out of space
            self.lock.release()
            return -1

        # Found the place to put the new entry

        # The process ID is one greater than the index, because the list starts at 0 but we
        # want process ID's to start at 1
        new_process_id = new_index + 1 
        self.table[new_index].setProcessName(p.processName())
        self.table[new_index].setProcessId(new_process_id)
        self.table[new_index].setPriority(p.priority())
        self.table[new_index].setCpuNeeded(p.cpuNeeded())

        self.current_index = new_index

        self.lock.release()
        return new_process_id


    # Remove the indicated process ID from the table
    # Returns True if successfully removed, or False if the 
    # process ID is not found

    def remove(self, process_id):
        self.lock.acquire()
        
        # The index will be one less than the process ID
        index = process_id -1

        if (self.table[index].processId() != -1):
            # the process is there. Remove it.

            self.table[index].setProcessName("")
            self.table[index].setProcessId(-1)
            return_value = True
        else :
            return_value = False

        self.lock.release()
        return return_value
        
    # Find the indicated process by process ID
    # Returns a copy of the process 
    def find(self, process_id):
        return self.table[process_id - 1]

    # Method that is called when someone calls print() on a ProcessTable.
    # This invokes the __str__ method for each active process (i.e. each
    # process with a pid that isn't -1), to print that process on its own line
    def __str__(self):
        s = ""
        for i in range(0, self.table_size):
            if self.table[i].processId() != -1 :
                if s:
                    s += "\n"
                s += self.table[i].__str__()
        return s

