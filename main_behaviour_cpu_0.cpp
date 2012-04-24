#include <main_behaviour_cpu_0.h>

main_behaviour_cpu_0::main_behaviour_cpu_0()
{
input_timer_.this_ = this;
input_slice1_.this_ = this;
input_slice2_.this_ = this;
counter = 0;
current_state_ = SA;
}
Runnable* main_behaviour_cpu_0::get_input_timer()
{
   return &input_timer_;
}
Memory* main_behaviour_cpu_0::get_memory_input_timer()
{
   return &input_timer_;
}
Runnable* main_behaviour_cpu_0::get_input_slice1()
{
   return &input_slice1_;
}
Memory* main_behaviour_cpu_0::get_memory_input_slice1()
{
   return &input_slice1_;
}
Runnable* main_behaviour_cpu_0::get_input_slice2()
{
   return &input_slice2_;
}
Memory* main_behaviour_cpu_0::get_memory_input_slice2()
{
   return &input_slice2_;
}
void main_behaviour_cpu_0_input_timer::run()
{
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_timer_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->comm_slice1_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_timer_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->comm_slice2_->run();
   }
   this_->input_timer_run_characs_1[ car_counter ]->apply();

   return;
}
}
int main_behaviour_cpu_0_input_timer::get_instr()
{
{
   return 10000;
}
}
int main_behaviour_cpu_0_input_timer::get_load()
{
{
   return 1200;
}
}
int main_behaviour_cpu_0_input_timer::get_store()
{
{
   return 500;
}
}
int main_behaviour_cpu_0_input_timer::get_iL1_miss()
{
{
   return 100;
}
}
int main_behaviour_cpu_0_input_timer::get_lL1_miss()
{
{
   return 120;
}
}
int main_behaviour_cpu_0_input_timer::get_sL1_miss()
{
{
   return 50;
}
}
int main_behaviour_cpu_0_input_timer::get_iL2_miss()
{
{
   return 10;
}
}
int main_behaviour_cpu_0_input_timer::get_lL2_miss()
{
{
   return 12;
}
}
int main_behaviour_cpu_0_input_timer::get_sL2_miss()
{
{
   return 5;
}
}
void main_behaviour_cpu_0_input_slice1::run()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   int car_counter = 0;
   this_->input_slice1_run_characs_1[ car_counter ]->apply();
this_->counter++;
   this_->current_state_ = main_behaviour_cpu_0::SA;
   return;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_slice1_run_characs_2[ car_counter ]->apply();
     car_counter++;
     this_->comm_write_buffer_->run();
   }
   this_->input_slice1_run_characs_2[ car_counter ]->apply();
this_->counter--;
   this_->current_state_ = main_behaviour_cpu_0::SA;
   return;
}
}
int main_behaviour_cpu_0_input_slice1::get_instr()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 10000;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 10000;
}
}
int main_behaviour_cpu_0_input_slice1::get_load()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 1200;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 1200;
}
}
int main_behaviour_cpu_0_input_slice1::get_store()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 500;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 500;
}
}
int main_behaviour_cpu_0_input_slice1::get_iL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 100;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 100;
}
}
int main_behaviour_cpu_0_input_slice1::get_lL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 120;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 120;
}
}
int main_behaviour_cpu_0_input_slice1::get_sL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 50;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 50;
}
}
int main_behaviour_cpu_0_input_slice1::get_iL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 10;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 10;
}
}
int main_behaviour_cpu_0_input_slice1::get_lL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 12;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 12;
}
}
int main_behaviour_cpu_0_input_slice1::get_sL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 5;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 5;
}
}
void main_behaviour_cpu_0_input_slice2::run()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   int car_counter = 0;
   this_->input_slice2_run_characs_1[ car_counter ]->apply();
this_->counter++;
   this_->current_state_ = main_behaviour_cpu_0::SA;
   return;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_slice2_run_characs_2[ car_counter ]->apply();
     car_counter++;
     this_->comm_write_buffer_->run();
   }
   this_->input_slice2_run_characs_2[ car_counter ]->apply();
this_->counter--;
   this_->current_state_ = main_behaviour_cpu_0::SA;
   return;
}
}
int main_behaviour_cpu_0_input_slice2::get_instr()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 10000;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 10000;
}
}
int main_behaviour_cpu_0_input_slice2::get_load()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 1200;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 1200;
}
}
int main_behaviour_cpu_0_input_slice2::get_store()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 500;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 500;
}
}
int main_behaviour_cpu_0_input_slice2::get_iL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 100;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 100;
}
}
int main_behaviour_cpu_0_input_slice2::get_lL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 120;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 120;
}
}
int main_behaviour_cpu_0_input_slice2::get_sL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 50;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 50;
}
}
int main_behaviour_cpu_0_input_slice2::get_iL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 10;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 10;
}
}
int main_behaviour_cpu_0_input_slice2::get_lL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 12;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 12;
}
}
int main_behaviour_cpu_0_input_slice2::get_sL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter < 1 )  ))
{
   return 5;
}
if( ( this_->current_state_ == main_behaviour_cpu_0::SA)&& ( ( this_->counter >= 1 )  ))
{
   return 5;
}
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

main_behaviour_cpu_0* create_main_timing_characs_cpu_0()
{   main_behaviour_cpu_0* to_return = new main_behaviour_cpu_0;

Timing_characteristics::initialise();

  {
     to_return->input_timer_run_characs_1.resize( 3);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 93.3048;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_timer_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_timer_run_characs_1[ 1 ] = t_car_1;
    Timing_characteristics* t_car_2 = new Timing_characteristics;
    t_car_2->duration.tv_usec = 0;
    t_car_2->duration.tv_sec  = 0;
    to_return->input_timer_run_characs_1[ 2 ] = t_car_2;
}
  {
     to_return->input_slice1_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 93.3048;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_slice1_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_slice1_run_characs_1[ 1 ] = t_car_1;
}
  {
     to_return->input_slice1_run_characs_2.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 93.3048;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_slice1_run_characs_2[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_slice1_run_characs_2[ 1 ] = t_car_1;
}
  {
     to_return->input_slice2_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 93.3048;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_slice2_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_slice2_run_characs_1[ 1 ] = t_car_1;
}
  {
     to_return->input_slice2_run_characs_2.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 93.3048;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_slice2_run_characs_2[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_slice2_run_characs_2[ 1 ] = t_car_1;
}
  return to_return;
}

