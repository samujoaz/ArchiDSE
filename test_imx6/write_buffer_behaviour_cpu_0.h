#ifndef write_buffer_behaviour_cpu_0_h
#define write_buffer_behaviour_cpu_0_h

#include <benchmark_types.h>
#include <vector>
#include <cstdio>
using namespace std;

class write_buffer_behaviour_cpu_0;

class write_buffer_behaviour_cpu_0_input: public Runnable, public Memory 
{
  public:
    write_buffer_behaviour_cpu_0* this_;
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
class write_buffer_behaviour_cpu_0
{
   public:
    write_buffer_behaviour_cpu_0();


   Runnable* get_input();
   Memory* get_memory_input();


// private : 

  write_buffer_behaviour_cpu_0_input input_;
   vector< Characteristics* > input_run_characs_1;
};

write_buffer_behaviour_cpu_0* create_write_buffer_timing_characs_cpu_0();
#endif
