#ifndef filter_behaviour_cpu_1_h
#define filter_behaviour_cpu_1_h

#include <benchmark_types.h>
#include <vector>
#include <cstdio>
using namespace std;

class filter_behaviour_cpu_1;

class filter_behaviour_cpu_1_input: public Runnable, public Memory 
{
  public:
    filter_behaviour_cpu_1* this_;
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
class filter_behaviour_cpu_1
{
   public:
    filter_behaviour_cpu_1();


   Runnable* get_input();
   Memory* get_memory_input();

    Runnable* output_;

// private : 

  filter_behaviour_cpu_1_input input_;
   vector< Characteristics* > input_run_characs_1;
};

filter_behaviour_cpu_1* create_filter_timing_characs_cpu_1();
#endif
