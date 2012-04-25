#include <slice_behaviour_cpu_1.h>

slice_behaviour_cpu_1::slice_behaviour_cpu_1()
{
input_.this_ = this;
counter = 0;
current_state_ = SA;
}
Runnable* slice_behaviour_cpu_1::get_input()
{
   return &input_;
}
Memory* slice_behaviour_cpu_1::get_memory_input()
{
   return &input_;
}
void slice_behaviour_cpu_1_input::run()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->output_->run();
   }
   this_->input_run_characs_1[ car_counter ]->apply();
this_->counter++;
   this_->current_state_ = slice_behaviour_cpu_1::SA;
   return;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_run_characs_2[ car_counter ]->apply();
     car_counter++;
     this_->output_->run();
   }
   this_->input_run_characs_2[ car_counter ]->apply();
this_->counter = 0;
   this_->current_state_ = slice_behaviour_cpu_1::SA;
   return;
}
}
int slice_behaviour_cpu_1_input::get_instr()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 15039303;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   return 12000000;
}
}
int slice_behaviour_cpu_1_input::get_load()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 3235056;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   return 3035056;
}
}
int slice_behaviour_cpu_1_input::get_store()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 1623677;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   return 1323677;
}
}
int slice_behaviour_cpu_1_input::get_iL1_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 10500;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   return 10000;
}
}
int slice_behaviour_cpu_1_input::get_lL1_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 6470;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   return 6000;
}
}
int slice_behaviour_cpu_1_input::get_sL1_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 3247;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   return 3000;
}
}
int slice_behaviour_cpu_1_input::get_iL2_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 270;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   return 260;
}
}
int slice_behaviour_cpu_1_input::get_lL2_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 1617;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   return 1500;
}
}
int slice_behaviour_cpu_1_input::get_sL2_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 811;
}
if( ( this_->current_state_ == slice_behaviour_cpu_1::SA)&& ( ( this_->counter == 3 )  ))
{
   return 800;
}
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

slice_behaviour_cpu_1* create_slice_timing_characs_cpu_1()
{   slice_behaviour_cpu_1* to_return = new slice_behaviour_cpu_1;

Timing_characteristics::initialise();

  {
     to_return->input_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 43533;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_run_characs_1[ 1 ] = t_car_1;
}
  {
     to_return->input_run_characs_2.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 36663.1;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_run_characs_2[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_run_characs_2[ 1 ] = t_car_1;
}
  return to_return;
}

