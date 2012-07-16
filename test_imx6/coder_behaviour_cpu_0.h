#ifndef coder_behaviour_cpu_0_h
#define coder_behaviour_cpu_0_h

#include <benchmark_types.h>
#include <vector>
#include <cstdio>
using namespace std;

class coder_behaviour_cpu_0;

class coder_behaviour_cpu_0_input10111132: public Runnable, public Memory 
{
  public:
    coder_behaviour_cpu_0* this_;
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
class coder_behaviour_cpu_0_input1051188: public Runnable, public Memory 
{
  public:
    coder_behaviour_cpu_0* this_;
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
class coder_behaviour_cpu_0_input12111132: public Runnable, public Memory 
{
  public:
    coder_behaviour_cpu_0* this_;
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
class coder_behaviour_cpu_0_input1221118: public Runnable, public Memory 
{
  public:
    coder_behaviour_cpu_0* this_;
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
class coder_behaviour_cpu_0
{
   public:
    coder_behaviour_cpu_0();


   Runnable* get_input10111132();
   Memory* get_memory_input10111132();
   Runnable* get_input1051188();
   Memory* get_memory_input1051188();
   Runnable* get_input12111132();
   Memory* get_memory_input12111132();
   Runnable* get_input1221118();
   Memory* get_memory_input1221118();

    Runnable* output10111132_;
    Runnable* output1051188_;
    Runnable* output12111132_;
    Runnable* output1221118_;

// private : 

  coder_behaviour_cpu_0_input10111132 input10111132_;
  coder_behaviour_cpu_0_input1051188 input1051188_;
  coder_behaviour_cpu_0_input12111132 input12111132_;
  coder_behaviour_cpu_0_input1221118 input1221118_;
   vector< Characteristics* > input10111132_run_characs_1;
   vector< Characteristics* > input1051188_run_characs_1;
   vector< Characteristics* > input12111132_run_characs_1;
   vector< Characteristics* > input1221118_run_characs_1;
};

coder_behaviour_cpu_0* create_coder_timing_characs_cpu_0();
#endif
