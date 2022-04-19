#include <cmath>
#include <iomanip>

#include "bubblesort.h"

bubblesort::bubblesort(sc_module_name n)
    : sc_module(n), t_skt("t_skt"), base_offset(0) {
  SC_THREAD(do_bubblesort);

  t_skt.register_b_transport(this, &bubblesort::blocking_transport);
}

bubblesort::~bubblesort() = default;

void bubblesort::do_bubblesort() {
  int tmp;
  while (true) {
    for (unsigned int i = 0; i < 100; ++i) {
      val[i] = 0;
    }
      
        for (unsigned int i = 0; i < 100; i++) {
          val[i] = sort.read();
  
        }

        for(unsigned int i = 99; i > 0; i--){
         for(unsigned int j = 0; j <= i-1; j++){
            if( val[j] > val[j+1]){  
               
               tmp = val[j];
               val[j] = val[j+1];
               val[j+1] = tmp;            		  
            }	      
          }
        }

        for (unsigned int i = 0; i < 100; i++) {
         o_result.write(val[i]);
        }
  }
}

void bubblesort::blocking_transport(tlm::tlm_generic_payload &payload,
                                     sc_core::sc_time &delay) {
  sc_dt::uint64 addr = payload.get_address();
  addr -= base_offset;
  unsigned char *mask_ptr = payload.get_byte_enable_ptr();
  unsigned char *data_ptr = payload.get_data_ptr();
  word buffer;
  switch (payload.get_command()) {
  case tlm::TLM_READ_COMMAND:
    switch (addr) {
    case bubblesort_FILTER_RESULT_ADDR:
      buffer.uint = o_result.read();
      break;
    case bubblesort_FILTER_CHECK_ADDR:
      buffer.uint = o_result.num_available();
    break;
    default:
      std::cerr << "Error! bubblesort::blocking_transport: address 0x"
                << std::setfill('0') << std::setw(8) << std::hex << addr
                << std::dec << " is not valid" << std::endl;
    }
    data_ptr[0] = buffer.uc[0];
    break;
  case tlm::TLM_WRITE_COMMAND:
    switch (addr) {
    case bubblesort_FILTER_R_ADDR:
      if (mask_ptr[0] == 0xff) {
        sort.write(data_ptr[0]);
      }
      break;
    default:
      std::cerr << "Error! bubblesort::blocking_transport: address 0x"
                << std::setfill('0') << std::setw(8) << std::hex << addr
                << std::dec << " is not valid" << std::endl;
    }
    break;
  case tlm::TLM_IGNORE_COMMAND:
    payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return;
  default:
    payload.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    return;
  }
  payload.set_response_status(tlm::TLM_OK_RESPONSE); // Always OK
}