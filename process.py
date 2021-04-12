
# The Process class represents a process in our system.

# When we print processes, we will print them in json format
import json

class Process:

    # Contructor - the default values for the member variables
    # are as indicated - an empty string for the process name,
    # and -1 for the process id
    def __init__(self, process_name="", process_id=-1, priority = 0, cpu_needed = 0):
        self.process_name = process_name
        self.process_id = process_id
        self.my_priority = priority
        self.cpu_needed = cpu_needed
        self.cpu_used = 0

    
    # Set the process name 
    def setProcessName(self, process_name):
        self.process_name = process_name

    # Set the process ID
    def setProcessId(self, process_id):
        self.process_id = process_id

    # Set the prioroty
    def setPriority(self, priority):
        self.my_priority = priority

    def setCpuNeeded(self, cpu_needed):
        self.cpu_needed = cpu_needed

    # get the process name
    def processName(self):
        return self.process_name
    
    # get the process id
    def processId(self):
        return self.process_id

    def priority(self):
        return self.my_priority

    def cpuNeeded(self):
        return self.cpu_needed

    def cpuUsed(self):
        return self.cpu_used

    def run(self, num_cycles):
        cycles_to_run = min(num_cycles, self.cpu_needed - self.cpu_used)

        self.cpu_used += cycles_to_run
        return cycles_to_run


    # This method is called when print() is called. 
    # It converts the contents of the object
    # to json, and then dumps the json format. 
    def __str__(self):
        return json.dumps({"process_name" : self.process_name,
                           "process_id" : self.process_id,
                           "priority" : self.my_priority,
                           "cpu_needed" : self.cpu_needed,
                           "cpu_used" : self.cpu_used}, 
                           separators = (",",":"), sort_keys = True)
