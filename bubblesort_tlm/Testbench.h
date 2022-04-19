#ifndef TESTBENCH_H_
#define TESTBENCH_H_

#include <string>
using namespace std;

#include <systemc>
using namespace sc_core;

#include "Initiator.h"
#include "MemoryMap.h"
#include "filter_def.h"


class Testbench: public sc_module {
public:
    
    Initiator initiator;

    SC_HAS_PROCESS(Testbench);
    Testbench(sc_module_name n);
    ~Testbench();

    void read_input(string infile_name);
    void write_output(string outfile_name);
    void do_bubblesort();
    int  sort[100];  

};
#endif