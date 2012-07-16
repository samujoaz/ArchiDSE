#include <slice_behaviour_cpu_3.h>

slice_behaviour_cpu_3::slice_behaviour_cpu_3()
{
input_.this_ = this;
counter = 0;
current_state_ = SA;
}
Runnable* slice_behaviour_cpu_3::get_input()
{
   return &input_;
}
Memory* slice_behaviour_cpu_3::get_memory_input()
{
   return &input_;
}
void slice_behaviour_cpu_3_input::run()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
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
   this_->current_state_ = slice_behaviour_cpu_3::SA;
   return;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
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
   this_->current_state_ = slice_behaviour_cpu_3::SA;
   return;
}
}
int slice_behaviour_cpu_3_input::get_instr()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
{
   return 6774460;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
{
   return 7000000;
}
}
int slice_behaviour_cpu_3_input::get_load()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
{
   return 1461621;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
{
   return 1500000;
}
}
int slice_behaviour_cpu_3_input::get_store()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
{
   return 733589;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
{
   return 750000;
}
}
int slice_behaviour_cpu_3_input::get_iL1_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
{
   return 2000;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
{
   return 2000;
}
}
int slice_behaviour_cpu_3_input::get_lL1_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
{
   return 1461;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
{
   return 1500;
}
}
int slice_behaviour_cpu_3_input::get_sL1_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
{
   return 733;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
{
   return 800;
}
}
int slice_behaviour_cpu_3_input::get_iL2_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
{
   return 50;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
{
   return 50;
}
}
int slice_behaviour_cpu_3_input::get_lL2_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
{
   return 800;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
{
   return 800;
}
}
int slice_behaviour_cpu_3_input::get_sL2_miss()
{
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter < 3 )  ))
{
   return 500;
}
if( ( this_->current_state_ == slice_behaviour_cpu_3::SA)&& ( ( this_->counter == 3 )  ))
{
   return 500;
}
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

slice_behaviour_cpu_3* create_slice_timing_characs_cpu_3()
{   slice_behaviour_cpu_3* to_return = new slice_behaviour_cpu_3;

Timing_characteristics::initialise();

  {
     to_return->input_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 14754.7;
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
    t_car_0->duration.tv_usec = 15172;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_run_characs_2[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_run_characs_2[ 1 ] = t_car_1;
}
  return to_return;
}

