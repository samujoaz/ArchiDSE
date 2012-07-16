#ifndef slice_behaviour_cpu_2_h
#define slice_behaviour_cpu_2_h

#include <benchmark_types.h>
#include <vector>
#include <cstdio>
using namespace std;

class slice_behaviour_cpu_2;

class slice_behaviour_cpu_2_input: public Runnable, public Memory 
{
  public:
    slice_behaviour_cpu_2* this_;
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
class slice_behaviour_cpu_2
{
   public:
    slice_behaviour_cpu_2();


enum STATE {SA};
  slice_behaviour_cpu_2::STATE current_state_;
   Runnable* get_input();
   Memory* get_memory_input();

    Runnable* output_;

// private : 

  int counter;
  slice_behaviour_cpu_2_input input_;
   vector< Characteristics* > input_run_characs_1;
   vector< Characteristics* > input_run_characs_2;
};

slice_behaviour_cpu_2* create_slice_timing_characs_cpu_2();
#endif
