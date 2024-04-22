#ifndef _READY_VALID_H_
#define _READY_VALID_H_

//Define a read/valid input signal ports
//Ports only, need to be connected to actual sc_signals
//All ports public for explicit access and connection
template<class T>  
class rdyvld_port_in {  
  public: 
  sc_in<T> msg;
  sc_out<bool> rdy;
  sc_in<bool> vld;

  T read() {
  
    rdy.write(true);
    do {
        wait();
    } while (vld.read() != true); //若vld為false時，繼續wait()
    T t_m=msg.read(); //把從msg讀取的資料存在t_m
    rdy.write(false); //將rdy改成false，模組不再準備接收資料。
    
    return t_m;
  }
};

//Define a read/valid output signal ports
//Ports only, need to be connected to actual sc_signals
//All ports public for explicit access and connection
template<class T>  
class rdyvld_port_out {  
  public: 
  sc_out<T> msg;
  sc_in<bool> rdy;
  sc_out<bool> vld;

  void write(T m) {
    
    vld.write(true);
    msg.write(m); //將資料 m 寫入 msg，即向外部輸出資料。
    do{
      wait();
    } while (rdy.read() != true);
    vld.write(false);//表示模組不再輸出有效資料。
  }

};

#endif