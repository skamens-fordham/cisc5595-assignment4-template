CPPFLAGS = -g -I.
LDFLAGS = -lpthread

libsrc = process.cpp process_table.cpp cpu_scheduler_fcfs.cpp cpu_scheduler_priority_rr.cpp
libobj = $(libsrc:.cpp=.o)

all: execute $(libobj)

execute: execute.o $(libobj)
	$(CXX) -o $@ execute.o $(libobj) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f process_test process_test.o execute execute.o $(libobj)
