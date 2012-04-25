#ifndef main_behaviour_cpu_0_h
#define main_behaviour_cpu_0_h

#include <benchmark_types.h>
#include <vector>
#include <cstdio>
using namespace std;

class main_behaviour_cpu_0;

class main_behaviour_cpu_0_input_timer: public Runnable, public Memory 
{
  public:
    main_behaviour_cpu_0* this_;
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
class main_behaviour_cpu_0_input_slice1: public Runnable, public Memory 
{
  public:
    main_behaviour_cpu_0* this_;
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
class main_behaviour_cpu_0_input_slice2: public Runnable, public Memory 
{
  public:
    main_behaviour_cpu_0* this_;
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
class main_behaviour_cpu_0
{
   public:
    main_behaviour_cpu_0();


enum STATE {SA};
  main_behaviour_cpu_0::STATE current_state_;
   Runnable* get_input_timer();
   Memory* get_memory_input_timer();
   Runnable* get_input_slice1();
   Memory* get_memory_input_slice1();
   Runnable* get_input_slice2();
   Memory* get_memory_input_slice2();

    Runnable* comm_slice1_;
    Runnable* comm_slice2_;
    Runnable* comm_write_buffer_;

// private : 

  int counter;
  main_behaviour_cpu_0_input_timer input_timer_;
  main_behaviour_cpu_0_input_slice1 input_slice1_;
  main_behaviour_cpu_0_input_slice2 input_slice2_;
   vector< Characteristics* > input_timer_run_characs_1;
   vector< Characteristics* > input_slice1_run_characs_1;
   vector< Characteristics* > input_slice1_run_characs_2;
   vector< Characteristics* > input_slice2_run_characs_1;
   vector< Characteristics* > input_slice2_run_characs_2;
};

main_behaviour_cpu_0* create_main_timing_characs_cpu_0();
#endif
