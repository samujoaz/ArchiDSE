#include <modulator_behaviour_cpu_0.h>

modulator_behaviour_cpu_0::modulator_behaviour_cpu_0()
{
input10111132_.this_ = this;
input1051188_.this_ = this;
input12111132_.this_ = this;
input1221118_.this_ = this;
}
Runnable* modulator_behaviour_cpu_0::get_input10111132()
{
   return &input10111132_;
}
Memory* modulator_behaviour_cpu_0::get_memory_input10111132()
{
   return &input10111132_;
}
Runnable* modulator_behaviour_cpu_0::get_input1051188()
{
   return &input1051188_;
}
Memory* modulator_behaviour_cpu_0::get_memory_input1051188()
{
   return &input1051188_;
}
Runnable* modulator_behaviour_cpu_0::get_input12111132()
{
   return &input12111132_;
}
Memory* modulator_behaviour_cpu_0::get_memory_input12111132()
{
   return &input12111132_;
}
Runnable* modulator_behaviour_cpu_0::get_input1221118()
{
   return &input1221118_;
}
Memory* modulator_behaviour_cpu_0::get_memory_input1221118()
{
   return &input1221118_;
}
void modulator_behaviour_cpu_0_input10111132::run()
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
int modulator_behaviour_cpu_0_input10111132::get_instr()
{
{
   return 56465687;
}
}
int modulator_behaviour_cpu_0_input10111132::get_load()
{
{
   return 12455392;
}
}
int modulator_behaviour_cpu_0_input10111132::get_store()
{
{
   return 7523449;
}
}
int modulator_behaviour_cpu_0_input10111132::get_iL1_miss()
{
{
   return 1038;
}
}
int modulator_behaviour_cpu_0_input10111132::get_lL1_miss()
{
{
   return 10200;
}
}
int modulator_behaviour_cpu_0_input10111132::get_sL1_miss()
{
{
   return 22570;
}
}
int modulator_behaviour_cpu_0_input10111132::get_iL2_miss()
{
{
   return 589;
}
}
int modulator_behaviour_cpu_0_input10111132::get_lL2_miss()
{
{
   return 600;
}
}
int modulator_behaviour_cpu_0_input10111132::get_sL2_miss()
{
{
   return 200;
}
}
void modulator_behaviour_cpu_0_input1051188::run()
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
int modulator_behaviour_cpu_0_input1051188::get_instr()
{
{
   return 5911643;
}
}
int modulator_behaviour_cpu_0_input1051188::get_load()
{
{
   return 1304010;
}
}
int modulator_behaviour_cpu_0_input1051188::get_store()
{
{
   return 787663;
}
}
int modulator_behaviour_cpu_0_input1051188::get_iL1_miss()
{
{
   return 109;
}
}
int modulator_behaviour_cpu_0_input1051188::get_lL1_miss()
{
{
   return 3912;
}
}
int modulator_behaviour_cpu_0_input1051188::get_sL1_miss()
{
{
   return 787;
}
}
int modulator_behaviour_cpu_0_input1051188::get_iL2_miss()
{
{
   return 62;
}
}
int modulator_behaviour_cpu_0_input1051188::get_lL2_miss()
{
{
   return 30;
}
}
int modulator_behaviour_cpu_0_input1051188::get_sL2_miss()
{
{
   return 8;
}
}
void modulator_behaviour_cpu_0_input12111132::run()
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
int modulator_behaviour_cpu_0_input12111132::get_instr()
{
{
   return 56465687;
}
}
int modulator_behaviour_cpu_0_input12111132::get_load()
{
{
   return 12455392;
}
}
int modulator_behaviour_cpu_0_input12111132::get_store()
{
{
   return 7523449;
}
}
int modulator_behaviour_cpu_0_input12111132::get_iL1_miss()
{
{
   return 1038;
}
}
int modulator_behaviour_cpu_0_input12111132::get_lL1_miss()
{
{
   return 10200;
}
}
int modulator_behaviour_cpu_0_input12111132::get_sL1_miss()
{
{
   return 22570;
}
}
int modulator_behaviour_cpu_0_input12111132::get_iL2_miss()
{
{
   return 589;
}
}
int modulator_behaviour_cpu_0_input12111132::get_lL2_miss()
{
{
   return 600;
}
}
int modulator_behaviour_cpu_0_input12111132::get_sL2_miss()
{
{
   return 200;
}
}
void modulator_behaviour_cpu_0_input1221118::run()
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
int modulator_behaviour_cpu_0_input1221118::get_instr()
{
{
   return 4180927;
}
}
int modulator_behaviour_cpu_0_input1221118::get_load()
{
{
   return 1022736;
}
}
int modulator_behaviour_cpu_0_input1221118::get_store()
{
{
   return 679916;
}
}
int modulator_behaviour_cpu_0_input1221118::get_iL1_miss()
{
{
   return 323;
}
}
int modulator_behaviour_cpu_0_input1221118::get_lL1_miss()
{
{
   return 3068;
}
}
int modulator_behaviour_cpu_0_input1221118::get_sL1_miss()
{
{
   return 679;
}
}
int modulator_behaviour_cpu_0_input1221118::get_iL2_miss()
{
{
   return 176;
}
}
int modulator_behaviour_cpu_0_input1221118::get_lL2_miss()
{
{
   return 31;
}
}
int modulator_behaviour_cpu_0_input1221118::get_sL2_miss()
{
{
   return 7;
}
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

modulator_behaviour_cpu_0* create_modulator_timing_characs_cpu_0()
{   modulator_behaviour_cpu_0* to_return = new modulator_behaviour_cpu_0;

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
    t_car_0->duration.tv_usec = 30644.1;
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
    t_car_0->duration.tv_usec = 23462.2;
    t_car_0->duration.tv_sec  = 0;
    to_return->input1221118_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input1221118_run_characs_1[ 1 ] = t_car_1;
}
  return to_return;
}

