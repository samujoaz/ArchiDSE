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
class main_behaviour_cpu_0_input_slice3: public Runnable, public Memory 
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
class main_behaviour_cpu_0_input_slice4: public Runnable, public Memory 
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
class main_behaviour_cpu_0_input_slice5: public Runnable, public Memory 
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
class main_behaviour_cpu_0_input_slice6: public Runnable, public Memory 
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
class main_behaviour_cpu_0_input_slice7: public Runnable, public Memory 
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
class main_behaviour_cpu_0_input_slice8: public Runnable, public Memory 
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
class main_behaviour_cpu_0_input_slice9: public Runnable, public Memory 
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
class main_behaviour_cpu_0_input_slice10: public Runnable, public Memory 
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
   Runnable* get_input_slice3();
   Memory* get_memory_input_slice3();
   Runnable* get_input_slice4();
   Memory* get_memory_input_slice4();
   Runnable* get_input_slice5();
   Memory* get_memory_input_slice5();
   Runnable* get_input_slice6();
   Memory* get_memory_input_slice6();
   Runnable* get_input_slice7();
   Memory* get_memory_input_slice7();
   Runnable* get_input_slice8();
   Memory* get_memory_input_slice8();
   Runnable* get_input_slice9();
   Memory* get_memory_input_slice9();
   Runnable* get_input_slice10();
   Memory* get_memory_input_slice10();

    Runnable* comm_slice1_;
    Runnable* comm_slice2_;
    Runnable* comm_slice3_;
    Runnable* comm_slice4_;
    Runnable* comm_slice5_;
    Runnable* comm_slice6_;
    Runnable* comm_slice7_;
    Runnable* comm_slice8_;
    Runnable* comm_slice9_;
    Runnable* comm_slice10_;
    Runnable* comm_write_buffer_;

// private : 

  int counter;
  main_behaviour_cpu_0_input_timer input_timer_;
  main_behaviour_cpu_0_input_slice1 input_slice1_;
  main_behaviour_cpu_0_input_slice2 input_slice2_;
  main_behaviour_cpu_0_input_slice3 input_slice3_;
  main_behaviour_cpu_0_input_slice4 input_slice4_;
  main_behaviour_cpu_0_input_slice5 input_slice5_;
  main_behaviour_cpu_0_input_slice6 input_slice6_;
  main_behaviour_cpu_0_input_slice7 input_slice7_;
  main_behaviour_cpu_0_input_slice8 input_slice8_;
  main_behaviour_cpu_0_input_slice9 input_slice9_;
  main_behaviour_cpu_0_input_slice10 input_slice10_;
   vector< Characteristics* > input_timer_run_characs_1;
