#ifndef write_buffer_behaviour_h
#define write_buffer_behaviour_h

#include <benchmark_types.h>
#include <vector>
#include <cstdio>
using namespace std;

class write_buffer_behaviour;

class write_buffer_behaviour_input: public Runnable, public Memory 
{
  public:
    write_buffer_behaviour* this_;
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
class write_buffer_behaviour
{
   public:
    write_buffer_behaviour();


   Runnable* get_input();
   Memory* get_memory_input();


// private : 

  write_buffer_behaviour_input input_;
   vector< Characteristics* > input_run_characs_1;
};

write_buffer_behaviour* create_write_buffer_timing_characs();
#endif
