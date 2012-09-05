#include <write_buffer_behaviour_0.h>

write_buffer_behaviour_0::write_buffer_behaviour_0()
{
input_.this_ = this;
}
Runnable* write_buffer_behaviour_0::get_input()
{
   return &input_;
}
Memory* write_buffer_behaviour_0::get_memory_input()
{
   return &input_;
}
void write_buffer_behaviour_0_input::run()
{
{
   int car_counter = 0;
   this_->input_run_characs_1[ car_counter ]->apply();

   return;
}
}
int write_buffer_behaviour_0_input::get_instr()
{
  return 0;
}
int write_buffer_behaviour_0_input::get_load()
{
  return 0;
}
int write_buffer_behaviour_0_input::get_store()
{
  return 0;
}
int write_buffer_behaviour_0_input::get_iL1_miss()
{
  return 0;
}
int write_buffer_behaviour_0_input::get_lL1_miss()
{
  return 0;
}
int write_buffer_behaviour_0_input::get_sL1_miss()
{
  return 0;
}
int write_buffer_behaviour_0_input::get_iL2_miss()
{
  return 0;
}
int write_buffer_behaviour_0_input::get_lL2_miss()
{
  return 0;
}
int write_buffer_behaviour_0_input::get_sL2_miss()
{
  return 0;
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

write_buffer_behaviour_0* create_write_buffer_timing_characs_0()
{   write_buffer_behaviour_0* to_return = new write_buffer_behaviour_0;

Timing_characteristics::initialise();

  {
     to_return->input_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 10;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_run_characs_1[ 1 ] = t_car_1;
}
  return to_return;
}

