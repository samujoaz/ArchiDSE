#include <void_behaviour_3.h>

void_behaviour_3::void_behaviour_3()
{
input_.this_ = this;
}
Runnable* void_behaviour_3::get_input()
{
   return &input_;
}
Memory* void_behaviour_3::get_memory_input()
{
   return &input_;
}
void void_behaviour_3_input::run()
{
{
   int car_counter = 0;
   this_->input_run_characs_1[ car_counter ]->apply();

   return;
}
}
int void_behaviour_3_input::get_instr()
{
  return 0;
}
int void_behaviour_3_input::get_load()
{
  return 0;
}
int void_behaviour_3_input::get_store()
{
  return 0;
}
int void_behaviour_3_input::get_iL1_miss()
{
  return 0;
}
int void_behaviour_3_input::get_lL1_miss()
{
  return 0;
}
int void_behaviour_3_input::get_sL1_miss()
{
  return 0;
}
int void_behaviour_3_input::get_iL2_miss()
{
  return 0;
}
int void_behaviour_3_input::get_lL2_miss()
{
  return 0;
}
int void_behaviour_3_input::get_sL2_miss()
{
  return 0;
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

void_behaviour_3* create_void_timing_characs_3()
{   void_behaviour_3* to_return = new void_behaviour_3;

Timing_characteristics::initialise();

  {
     to_return->input_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 0;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_run_characs_1[ 1 ] = t_car_1;
}
  return to_return;
}

