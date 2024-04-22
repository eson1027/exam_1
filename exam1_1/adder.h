#ifndef _ADDER_H_
#define _ADDER_H_

#include <iostream>
#include <systemc.h>
using namespace std;

#include <systemc>
using namespace sc_dt;
using namespace sc_core;

const int WIDTH = 2;

#include "ready_valid_port.h"

class adder : public sc_module {
public:
  sc_in_clk i_clk;
  sc_in<bool> i_rst;
  //i_a input ports: message, ready, valid signals
  rdyvld_port_in<sc_uint<WIDTH> > i_a_port;
  //i_b input ports: message, ready, valid signals
  rdyvld_port_in<sc_uint<WIDTH> > i_b_port;
  //o_sum output ports: message, ready, valid signals
  rdyvld_port_out<sc_uint<WIDTH+1> > o_sum_port;

  void do_add() {
    const float FIR[9]={
      −0.00006,−0.01265,0.02011,0.50403,0.97714,0.50403,0.02011,−0.01265,−0.00006
    }
    //initilize handshaking signals
    i_a_port.rdy.write(false); 
    i_b_port.rdy.write(false); 
    o_sum_port.vld.write(false);
    int filled_elements=0;
    while (true) {
      
      for(int i = 8 ; i > 0 ; i--){
        buffer_gray[i]=buffer_gray[i-1];
      }

      buffer_gray[0]=_i_a = i_a_port.read();
      filled_elements = std::min(filled_elements + 1, 9);
      bool buffer_full = (filled_elements == 9);
      
      if(buffer_full){
        for(int j = 0 ; j < 9 ; j++){
        _o_sum += buffer_gray[j]*FIR[j];
        }
        o_sum_port.write(_o_sum);
        filled_elements=0;
        wait();
      }
      else{
        wait();
      }
      
    }
  }

  SC_HAS_PROCESS(adder);
  adder(sc_module_name name, int i) : id(i){ 

    SC_THREAD(do_add);  
    sensitive << i_clk.pos();
    dont_initialize();
    //reset_signal_is(i_rst, false);
    for(int k=0;k<9;k++){
      buffer_gray[k]=0;
    } 
  }

  sc_fixed_fast<4 , 1> i_a() { return _i_a; }
  sc_fixed_fast<4 , 1> i_b() { return _i_b; }
  sc_fixed_fast<4 , 1> o_sum() { return _o_sum; }

private:
  const int id;
  sc_fixed_fast<4 , 1> _i_a;
  sc_fixed_fast<4 , 1> _i_b;
  sc_fixed_fast<4 , 1> _o_sum;
  sc_fixed_fast<4 , 1>buffer_gray[9]

 
};

#endif
