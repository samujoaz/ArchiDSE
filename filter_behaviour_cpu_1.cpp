#include <filter_behaviour_cpu_1.h>

filter_behaviour_cpu_1::filter_behaviour_cpu_1()
{
input_.this_ = this;
}
Runnable* filter_behaviour_cpu_1::get_input()
{
   return &input_;
}
Memory* filter_behaviour_cpu_1::get_memory_input()
{
   return &input_;
}
void filter_behaviour_cpu_1_input::run()
{
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->output_->run();
   }
   this_->input_run_characs_1[ car_counter ]->apply();

   return;
}
}
int filter_behaviour_cpu_1_input::get_instr()
{
{
   return 17000000;
}
}
int filter_behaviour_cpu_1_input::get_load()
{
{
   return 3235056;
}
}
int filter_behaviour_cpu_1_input::get_store()
{
{
   return 1623677;
}
}
int filter_behaviour_cpu_1_input::get_iL1_miss()
{
{
   return 10500;
}
}
int filter_behaviour_cpu_1_input::get_lL1_miss()
{
{
   return 6470;
}
}
int filter_behaviour_cpu_1_input::get_sL1_miss()
{
{
   return 3247;
}
}
int filter_behaviour_cpu_1_input::get_iL2_miss()
{
{
   return 270;
}
}
int filter_behaviour_cpu_1_input::get_lL2_miss()
{
{
   return 1617;
}
}
int filter_behaviour_cpu_1_input::get_sL2_miss()
{
{
   return 811;
}
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

filter_behaviour_cpu_1* create_filter_timing_characs_cpu_1()
{   filter_behaviour_cpu_1* to_return = new filter_behaviour_cpu_1;

Timing_characteristics::initialise();

  {
     to_return->input_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 46833.8;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_run_characs_1[ 1 ] = t_car_1;
}
  return to_return;
}

