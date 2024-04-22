#ifndef _STIM_H_
#define _STIM_H_

#include <iomanip>
using std::setw;
#include "adder.h"
#include "ready_valid_port.h"

// WIDTH is defined in adder.h
const int DEPTH = (1 << WIDTH);

SC_MODULE(stim) {

  sc_in_clk i_clk;
  sc_out<bool> o_rst;
  //o_a output ports: message, ready, valid signals
  rdyvld_port_out<sc_uint<WIDTH> > o_a;
  //o_b output ports: message, ready, valid signals
  rdyvld_port_out<sc_uint<WIDTH> > o_b;
  //i_sum input ports: message, ready, valid signals
  rdyvld_port_in<sc_uint<WIDTH+1> > i_sum;
  //Store the previous inputs to FIFOs
  sc_uint<WIDTH> t_a;
  sc_uint<1> t_a_rdy;
  sc_uint<1> t_a_vld;
  sc_uint<WIDTH> t_b;
  sc_uint<1> t_b_rdy;
  sc_uint<1> t_b_vld;
  sc_uint<WIDTH+1> t_sum;
  sc_uint<1> t_sum_rdy;
  sc_uint<1> t_sum_vld;

  void stim_gen() {
    float k;
    //initilize handshaking signals
    //o_a.vld.write(false); 
    //o_b.vld.write(false); 
    //i_sum.rdy.write(false);
    const float x_input_signal[128]={0.493,  0.521,  0.56 ,  0.567,  0.591,  0.624,  0.651,  0.679,  0.68 ,  0.735,
                            0.738,  0.747,  0.787,  0.799,  0.787,  0.836,  0.855,  0.848,  0.888,  0.913,
                            0.918,  0.939,  0.946,  0.962,  0.944,  0.96 ,  0.99 ,  1.003,  1.001,  0.999,
                            1.007,  1.012,  1.017,  0.998,  1.001,  0.988,  0.988,  0.974,  0.986,  0.97 ,
                            0.974,  0.941,  0.936,  0.92 ,  0.9  ,  0.893,  0.9  ,  0.864,  0.848,  0.829,
                            0.8  ,  0.788,  0.787,  0.735,  0.711,  0.704,  0.677,  0.629,  0.642,  0.597,
                            0.584,  0.566,  0.548,  0.5  ,  0.486,  0.464,  0.444,  0.41 ,  0.395,  0.373,
                            0.354,  0.309,  0.293,  0.272,  0.259,  0.229,  0.219,  0.198,  0.19 ,  0.152,
                            0.131,  0.117,  0.091,  0.102,  0.069,  0.06 ,  0.06 ,  0.034,  0.031,  0.035,
                            0.026,  0.018,  0.004,  0.007, -0.003, -0.004,  0.002,  0.012,  0.01 ,  0.038,
                            0.002,  0.013,  0.054,  0.042,  0.036,  0.056,  0.067,  0.075,  0.09 ,  0.113,
                            0.143,  0.147,  0.166,  0.165,  0.184,  0.203,  0.213,  0.272,  0.264,  0.298,
                            0.311,  0.348,  0.369,  0.398,  0.43 ,  0.439,  0.484,  0.502}
    for (int a = 0; a < 128; a++) {
      for(int v = a-4; v < a+5 ; v++){
        if(v>=0 && v<128){
          k = x_input_signal[v];
        }
        else{
          k = 0;
        }
        o_a.write(k);
      }
      wait();
    }
  }

  void sink() {
    while(true) {
      t_sum=i_sum.read();
      wait();
    }
  }

  void monitor() {
    cout << setw(8) << "time" << setw(8) << "a" << setw(8) << "a rdy" << setw(8) << "a vld" << setw(8) << "b" 
         << setw(8) << "b rdy" << setw(8) << "b vld" 
         << setw(8) << "sum" << setw(8) << "sum rdy" 
         << setw(8) << "sum vld" << endl;
    while (true) {
      wait();
      t_a=o_a.msg.read();
      t_a_rdy=o_a.rdy.read();
      t_a_vld=o_a.vld.read();
      t_b=o_b.msg.read();
      t_b_rdy=o_b.rdy.read();
      t_b_vld=o_b.vld.read();
      t_sum=i_sum.msg.read();
      t_sum_rdy=i_sum.rdy.read();
      t_sum_vld=i_sum.vld.read();
      cout << setw(8) << sc_time_stamp();
      cout << setw(8) << t_a.to_string(SC_BIN);
      cout << setw(8) << t_a_rdy.to_string(SC_BIN);
      cout << setw(8) << t_a_vld.to_string(SC_BIN);
      cout << setw(8) << t_b.to_string(SC_BIN);
      cout << setw(8) << t_b_rdy.to_string(SC_BIN);
      cout << setw(8) << t_b_vld.to_string(SC_BIN);
      cout << setw(8) << t_sum.to_string(SC_BIN);
      cout << setw(8) << t_sum_rdy.to_string(SC_BIN);
      cout << setw(8) << t_sum_vld.to_string(SC_BIN) << endl;
      cout << "===============================================================================================" << endl;
    }
  }
  

  SC_CTOR(stim) {

    SC_THREAD(stim_gen);
    sensitive << i_clk.pos();
    dont_initialize();

    SC_THREAD(sink);
    sensitive << i_clk.pos();

    // the first row of output table
    SC_THREAD(monitor);
    sensitive << i_clk.pos();
 
  }
};

#endif
