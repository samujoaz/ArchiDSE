#ifndef void_behaviour_2_h
#define void_behaviour_2_h

#include <benchmark_types.h>
#include <vector>
#include <cstdio>
using namespace std;

class void_behaviour_2;

class void_behaviour_2_input: public Runnable, public Memory 
{
  public:
    void_behaviour_2* this_;
     void run();
     int get_instr();
     int get_load();
     int get_store();
     int get_iL1_miss();
     int get_lL1_miss();
     int get_sL1_miss();
     int get_iL2_miss();
     int get_lL2_miss();
     int get_sL2_miss();
};
class void_behaviour_2
{
   public:
    void_behaviour_2();


   Runnable* get_input();
   Memory* get_memory_input();


// private : 

  void_behaviour_2_input input_;
   vector< Characteristics* > input_run_characs_1;
};

void_behaviour_2* create_void_timing_characs_2();
#endif
