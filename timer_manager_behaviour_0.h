#ifndef timer_manager_behaviour_0_h
#define timer_manager_behaviour_0_h

#include <benchmark_types.h>
#include <vector>
#include <cstdio>
using namespace std;

class timer_manager_behaviour_0;

class timer_manager_behaviour_0_start: public Runnable, public Memory 
{
  public:
    timer_manager_behaviour_0* this_;
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
class timer_manager_behaviour_0_stop: public Runnable, public Memory 
{
  public:
    timer_manager_behaviour_0* this_;
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
class timer_manager_behaviour_0
{
   public:
    timer_manager_behaviour_0();


   Runnable* get_start();
   Memory* get_memory_start();
   Runnable* get_stop();
   Memory* get_memory_stop();

    Runnable* timer_1_start_;
    Runnable* timer_2_start_;
    Runnable* timer_3_start_;
    Runnable* timer_4_start_;
    Runnable* timer_5_start_;
    Runnable* timer_1_stop_;
    Runnable* timer_2_stop_;
    Runnable* timer_3_stop_;
    Runnable* timer_4_stop_;
    Runnable* timer_5_stop_;

// private : 

  timer_manager_behaviour_0_start start_;
  timer_manager_behaviour_0_stop stop_;
   vector< Characteristics* > start_run_characs_1;
   vector< Characteristics* > stop_run_characs_1;
};

timer_manager_behaviour_0* create_timer_manager_timing_characs_0();
#endif
