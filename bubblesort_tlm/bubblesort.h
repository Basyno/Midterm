#ifndef BUBBLESORT_H_
#define BUBBLESORT_H_
#include <systemc>
using namespace sc_core;

#include <tlm>
#include <tlm_utils/simple_target_socket.h>

#include "filter_def.h"

class bubblesort : public sc_module {
public:
  tlm_utils::simple_target_socket<bubblesort> t_skt;

  sc_fifo<unsigned char> sort;
  sc_fifo<unsigned char> o_result;

  SC_HAS_PROCESS(bubblesort);
  bubblesort(sc_module_name n);
  ~bubblesort();
  

private:
  void do_bubblesort();
  unsigned char val[100];

  unsigned int base_offset;
  void blocking_transport(tlm::tlm_generic_payload &payload,
                          sc_core::sc_time &delay);
};
#endif
