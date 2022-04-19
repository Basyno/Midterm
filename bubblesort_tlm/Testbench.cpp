#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;

#include "Testbench.h"

Testbench::Testbench(sc_module_name n)
    : sc_module(n), initiator("initiator") {
  SC_THREAD(do_bubblesort);
}

Testbench::~Testbench() {}

void Testbench::read_input(string infile_name){

    FILE *fp_s = NULL; // source file handler

    fp_s = fopen(infile_name.c_str(), "r");
    if(!fp_s){
        cout << "open data file ERROR" << endl;
    }
    for(int i=0;i<100;i++){
        fscanf(fp_s, "%d",&sort[i]);
    }
    fclose(fp_s);  
}

void Testbench::write_output(string outfile_name){

    FILE *fp_t = NULL; // source file handler

    fp_t = fopen(outfile_name.c_str(), "wb");
    if(!fp_t){
        cout << "open output file  ERROR" << endl;
    }
    for(int i=0;i<100;i++){
        fprintf(fp_t, "%d\n",sort[i]);
    }
    fclose(fp_t);  
}



void Testbench::do_bubblesort() {
  int i;       // for loop counter
//  unsigned char R, G, B; // color of R, G, B
  word data;
  unsigned char mask[4];
  for(i=0;i<100;i++){

          data.uc[0] = (unsigned char)sort[i];
          mask[0] = 0xff;
          mask[1] = 0;
          mask[2] = 0;
          mask[3] = 0;
          initiator.write_to_socket(bubblesort_MM_BASE + bubblesort_FILTER_R_ADDR, mask,
                                    data.uc, 4);
          wait(1 * CLOCK_PERIOD, SC_NS);
        
  }
  
  for(i=0;i<100;i++){
      bool done=false;
      int output_num=0;

      while(!done){
        initiator.read_from_socket(bubblesort_MM_BASE + bubblesort_FILTER_CHECK_ADDR, mask, data.uc, 4);
        output_num = data.sint;
        if(output_num>0) done=true;
      }
      wait(11 * CLOCK_PERIOD, SC_NS);

      initiator.read_from_socket(bubblesort_MM_BASE + bubblesort_FILTER_RESULT_ADDR, mask,
                                 data.uc, 4);
      sort[i] = data.uc[0];
      //debug
      //cout << "Now at " << sc_time_stamp() << endl; //print current sc_time
    
  }

  sc_stop();
}
