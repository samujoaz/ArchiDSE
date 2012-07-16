#include <cypher_behaviour_cpu_0.h>

cypher_behaviour_cpu_0::cypher_behaviour_cpu_0()
{
input10111132_.this_ = this;
input1051188_.this_ = this;
input12111132_.this_ = this;
input1221118_.this_ = this;
}
Runnable* cypher_behaviour_cpu_0::get_input10111132()
{
   return &input10111132_;
}
Memory* cypher_behaviour_cpu_0::get_memory_input10111132()
{
   return &input10111132_;
}
Runnable* cypher_behaviour_cpu_0::get_input1051188()
{
   return &input1051188_;
}
Memory* cypher_behaviour_cpu_0::get_memory_input1051188()
{
   return &input1051188_;
}
Runnable* cypher_behaviour_cpu_0::get_input12111132()
{
   return &input12111132_;
}
Memory* cypher_behaviour_cpu_0::get_memory_input12111132()
{
   return &input12111132_;
}
Runnable* cypher_behaviour_cpu_0::get_input1221118()
{
   return &input1221118_;
}
Memory* cypher_behaviour_cpu_0::get_memory_input1221118()
{
   return &input1221118_;
}
void cypher_behaviour_cpu_0_input10111132::run()
{
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input10111132_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->output10111132_->run();
   }
   this_->input10111132_run_characs_1[ car_counter ]->apply();

   return;
}
}
int cypher_behaviour_cpu_0_input10111132::get_instr()
{
{
   return 56465687;
}
}
int cypher_behaviour_cpu_0_input10111132::get_load()
{
{
   return 12455392;
}
}
int cypher_behaviour_cpu_0_input10111132::get_store()
{
{
   return 7523449;
}
}
int cypher_behaviour_cpu_0_input10111132::get_iL1_miss()
{
{
   return 1038;
}
}
int cypher_behaviour_cpu_0_input10111132::get_lL1_miss()
{
{
   return 10200;
}
}
int cypher_behaviour_cpu_0_input10111132::get_sL1_miss()
{
{
   return 22570;
}
}
int cypher_behaviour_cpu_0_input10111132::get_iL2_miss()
{
{
   return 589;
}
}
int cypher_behaviour_cpu_0_input10111132::get_lL2_miss()
{
{
   return 600;
}
}
int cypher_behaviour_cpu_0_input10111132::get_sL2_miss()
{
{
   return 200;
}
}
void cypher_behaviour_cpu_0_input1051188::run()
{
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input1051188_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->output1051188_->run();
   }
   this_->input1051188_run_characs_1[ car_counter ]->apply();

   return;
}
}
int cypher_behaviour_cpu_0_input1051188::get_instr()
{
{
   return 282328;
}
}
int cypher_behaviour_cpu_0_input1051188::get_load()
{
{
   return 62276;
}
}
int cypher_behaviour_cpu_0_input1051188::get_store()
{
{
   return 37617;
}
}
int cypher_behaviour_cpu_0_input1051188::get_iL1_miss()
{
{
   return 5;
}
}
int cypher_behaviour_cpu_0_input1051188::get_lL1_miss()
{
{
   return 187;
}
}
int cypher_behaviour_cpu_0_input1051188::get_sL1_miss()
{
{
   return 37;
}
}
int cypher_behaviour_cpu_0_input1051188::get_iL2_miss()
{
{
   return 3;
}
}
int cypher_behaviour_cpu_0_input1051188::get_lL2_miss()
{
{
   return 1;
}
}
int cypher_behaviour_cpu_0_input1051188::get_sL2_miss()
{
{
   return 1;
}
}
void cypher_behaviour_cpu_0_input12111132::run()
{
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input12111132_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->output12111132_->run();
   }
   this_->input12111132_run_characs_1[ car_counter ]->apply();

   return;
}
}
int cypher_behaviour_cpu_0_input12111132::get_instr()
{
{
   return 56465687;
}
}
int cypher_behaviour_cpu_0_input12111132::get_load()
{
{
   return 12455392;
}
}
int cypher_behaviour_cpu_0_input12111132::get_store()
{
{
   return 7523449;
}
}
int cypher_behaviour_cpu_0_input12111132::get_iL1_miss()
{
{
   return 1038;
}
}
int cypher_behaviour_cpu_0_input12111132::get_lL1_miss()
{
{
   return 10200;
}
}
int cypher_behaviour_cpu_0_input12111132::get_sL1_miss()
{
{
   return 22570;
}
}
int cypher_behaviour_cpu_0_input12111132::get_iL2_miss()
{
{
   return 589;
}
}
int cypher_behaviour_cpu_0_input12111132::get_lL2_miss()
{
{
   return 600;
}
}
int cypher_behaviour_cpu_0_input12111132::get_sL2_miss()
{
{
   return 200;
}
}
void cypher_behaviour_cpu_0_input1221118::run()
{
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input1221118_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->output1221118_->run();
   }
   this_->input1221118_run_characs_1[ car_counter ]->apply();

   return;
}
}
int cypher_behaviour_cpu_0_input1221118::get_instr()
{
{
   return 2476410;
}
}
int cypher_behaviour_cpu_0_input1221118::get_load()
{
{
   return 605778;
}
}
int cypher_behaviour_cpu_0_input1221118::get_store()
{
{
   return 402722;
}
}
int cypher_behaviour_cpu_0_input1221118::get_iL1_miss()
{
{
   return 191;
}
}
int cypher_behaviour_cpu_0_input1221118::get_lL1_miss()
{
{
   return 1817;
}
}
int cypher_behaviour_cpu_0_input1221118::get_sL1_miss()
{
{
   return 402;
}
}
int cypher_behaviour_cpu_0_input1221118::get_iL2_miss()
{
{
   return 104;
}
}
int cypher_behaviour_cpu_0_input1221118::get_lL2_miss()
{
{
   return 18;
}
}
int cypher_behaviour_cpu_0_input1221118::get_sL2_miss()
{
{
   return 4;
}
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

cypher_behaviour_cpu_0* create_cypher_timing_characs_cpu_0()
{   cypher_behaviour_cpu_0* to_return = new cypher_behaviour_cpu_0;

Timing_characteristics::initialise();

  {
     to_return->input10111132_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 287495;
    t_car_0->duration.tv_sec  = 0;
    to_return->input10111132_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input10111132_run_characs_1[ 1 ] = t_car_1;
}
  {
     to_return->input1051188_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 1985.46;
    t_car_0->duration.tv_sec  = 0;
    to_return->input1051188_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input1051188_run_characs_1[ 1 ] = t_car_1;
}
  {
     to_return->input12111132_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 287495;
    t_car_0->duration.tv_sec  = 0;
    to_return->input12111132_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input12111132_run_characs_1[ 1 ] = t_car_1;
}
  {
     to_return->input1221118_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 14119.8;
    t_car_0->duration.tv_sec  = 0;
    to_return->input1221118_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input1221118_run_characs_1[ 1 ] = t_car_1;
}
  return to_return;
}

