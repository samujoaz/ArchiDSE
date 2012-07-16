#include <main_behaviour_cpu_1.h>

main_behaviour_cpu_1::main_behaviour_cpu_1()
{
input_timer_.this_ = this;
input_slice1_.this_ = this;
input_slice2_.this_ = this;
input_slice3_.this_ = this;
input_slice4_.this_ = this;
counter = 0;
current_state_ = SA;
}
Runnable* main_behaviour_cpu_1::get_input_timer()
{
   return &input_timer_;
}
Memory* main_behaviour_cpu_1::get_memory_input_timer()
{
   return &input_timer_;
}
Runnable* main_behaviour_cpu_1::get_input_slice1()
{
   return &input_slice1_;
}
Memory* main_behaviour_cpu_1::get_memory_input_slice1()
{
   return &input_slice1_;
}
Runnable* main_behaviour_cpu_1::get_input_slice2()
{
   return &input_slice2_;
}
Memory* main_behaviour_cpu_1::get_memory_input_slice2()
{
   return &input_slice2_;
}
Runnable* main_behaviour_cpu_1::get_input_slice3()
{
   return &input_slice3_;
}
Memory* main_behaviour_cpu_1::get_memory_input_slice3()
{
   return &input_slice3_;
}
Runnable* main_behaviour_cpu_1::get_input_slice4()
{
   return &input_slice4_;
}
Memory* main_behaviour_cpu_1::get_memory_input_slice4()
{
   return &input_slice4_;
}
void main_behaviour_cpu_1_input_timer::run()
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
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_timer_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->comm_slice3_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_timer_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->comm_slice4_->run();
   }
   this_->input_timer_run_characs_1[ car_counter ]->apply();

   return;
}
}
int main_behaviour_cpu_1_input_timer::get_instr()
{
{
   return 3010872;
}
}
int main_behaviour_cpu_1_input_timer::get_load()
{
{
   return 649610;
}
}
int main_behaviour_cpu_1_input_timer::get_store()
{
{
   return 326040;
}
}
int main_behaviour_cpu_1_input_timer::get_iL1_miss()
{
{
   return 3000;
}
}
int main_behaviour_cpu_1_input_timer::get_lL1_miss()
{
{
   return 949;
}
}
int main_behaviour_cpu_1_input_timer::get_sL1_miss()
{
{
   return 326;
}
}
int main_behaviour_cpu_1_input_timer::get_iL2_miss()
{
{
   return 50;
}
}
int main_behaviour_cpu_1_input_timer::get_lL2_miss()
{
{
   return 50;
}
}
int main_behaviour_cpu_1_input_timer::get_sL2_miss()
{
{
   return 30;
}
}
void main_behaviour_cpu_1_input_slice1::run()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   int car_counter = 0;
   this_->input_slice1_run_characs_1[ car_counter ]->apply();
this_->counter++;
   this_->current_state_ = main_behaviour_cpu_1::SA;
   return;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_slice1_run_characs_2[ car_counter ]->apply();
     car_counter++;
     this_->comm_write_buffer_->run();
   }
   this_->input_slice1_run_characs_2[ car_counter ]->apply();
this_->counter=0;
   this_->current_state_ = main_behaviour_cpu_1::SA;
   return;
}
}
int main_behaviour_cpu_1_input_slice1::get_instr()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 10000;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 10000;
}
}
int main_behaviour_cpu_1_input_slice1::get_load()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 1200;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 1200;
}
}
int main_behaviour_cpu_1_input_slice1::get_store()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 500;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 500;
}
}
int main_behaviour_cpu_1_input_slice1::get_iL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 100;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 100;
}
}
int main_behaviour_cpu_1_input_slice1::get_lL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 120;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 120;
}
}
int main_behaviour_cpu_1_input_slice1::get_sL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 50;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 50;
}
}
int main_behaviour_cpu_1_input_slice1::get_iL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 10;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 10;
}
}
int main_behaviour_cpu_1_input_slice1::get_lL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 12;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 12;
}
}
int main_behaviour_cpu_1_input_slice1::get_sL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 5;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 5;
}
}
void main_behaviour_cpu_1_input_slice2::run()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   int car_counter = 0;
   this_->input_slice2_run_characs_1[ car_counter ]->apply();
this_->counter++;
   this_->current_state_ = main_behaviour_cpu_1::SA;
   return;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_slice2_run_characs_2[ car_counter ]->apply();
     car_counter++;
     this_->comm_write_buffer_->run();
   }
   this_->input_slice2_run_characs_2[ car_counter ]->apply();
this_->counter=0;
   this_->current_state_ = main_behaviour_cpu_1::SA;
   return;
}
}
int main_behaviour_cpu_1_input_slice2::get_instr()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 10000;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 10000;
}
}
int main_behaviour_cpu_1_input_slice2::get_load()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 1200;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 1200;
}
}
int main_behaviour_cpu_1_input_slice2::get_store()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 500;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 500;
}
}
int main_behaviour_cpu_1_input_slice2::get_iL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 100;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 100;
}
}
int main_behaviour_cpu_1_input_slice2::get_lL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 120;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 120;
}
}
int main_behaviour_cpu_1_input_slice2::get_sL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 50;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 50;
}
}
int main_behaviour_cpu_1_input_slice2::get_iL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 10;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 10;
}
}
int main_behaviour_cpu_1_input_slice2::get_lL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 12;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 12;
}
}
int main_behaviour_cpu_1_input_slice2::get_sL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 5;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 5;
}
}
void main_behaviour_cpu_1_input_slice3::run()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   int car_counter = 0;
   this_->input_slice3_run_characs_1[ car_counter ]->apply();
this_->counter++;
   this_->current_state_ = main_behaviour_cpu_1::SA;
   return;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_slice3_run_characs_2[ car_counter ]->apply();
     car_counter++;
     this_->comm_write_buffer_->run();
   }
   this_->input_slice3_run_characs_2[ car_counter ]->apply();
this_->counter=0;
   this_->current_state_ = main_behaviour_cpu_1::SA;
   return;
}
}
int main_behaviour_cpu_1_input_slice3::get_instr()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 10000;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 10000;
}
}
int main_behaviour_cpu_1_input_slice3::get_load()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 1200;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 1200;
}
}
int main_behaviour_cpu_1_input_slice3::get_store()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 500;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 500;
}
}
int main_behaviour_cpu_1_input_slice3::get_iL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 100;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 100;
}
}
int main_behaviour_cpu_1_input_slice3::get_lL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 120;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 120;
}
}
int main_behaviour_cpu_1_input_slice3::get_sL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 50;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 50;
}
}
int main_behaviour_cpu_1_input_slice3::get_iL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 10;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 10;
}
}
int main_behaviour_cpu_1_input_slice3::get_lL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 12;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 12;
}
}
int main_behaviour_cpu_1_input_slice3::get_sL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 5;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 5;
}
}
void main_behaviour_cpu_1_input_slice4::run()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   int car_counter = 0;
   this_->input_slice4_run_characs_1[ car_counter ]->apply();
this_->counter++;
   this_->current_state_ = main_behaviour_cpu_1::SA;
   return;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->input_slice4_run_characs_2[ car_counter ]->apply();
     car_counter++;
     this_->comm_write_buffer_->run();
   }
   this_->input_slice4_run_characs_2[ car_counter ]->apply();
this_->counter=0;
   this_->current_state_ = main_behaviour_cpu_1::SA;
   return;
}
}
int main_behaviour_cpu_1_input_slice4::get_instr()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 10000;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 10000;
}
}
int main_behaviour_cpu_1_input_slice4::get_load()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 1200;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 1200;
}
}
int main_behaviour_cpu_1_input_slice4::get_store()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 500;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 500;
}
}
int main_behaviour_cpu_1_input_slice4::get_iL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 100;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 100;
}
}
int main_behaviour_cpu_1_input_slice4::get_lL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 120;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 120;
}
}
int main_behaviour_cpu_1_input_slice4::get_sL1_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 50;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 50;
}
}
int main_behaviour_cpu_1_input_slice4::get_iL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 10;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 10;
}
}
int main_behaviour_cpu_1_input_slice4::get_lL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 12;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 12;
}
}
int main_behaviour_cpu_1_input_slice4::get_sL2_miss()
{
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter < 3 )  ))
{
   return 5;
}
if( ( this_->current_state_ == main_behaviour_cpu_1::SA)&& ( ( this_->counter >= 3 )  ))
{
   return 5;
}
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

main_behaviour_cpu_1* create_main_timing_characs_cpu_1()
{   main_behaviour_cpu_1* to_return = new main_behaviour_cpu_1;

Timing_characteristics::initialise();

  {
     to_return->input_timer_run_characs_1.resize( 5);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 5151.01;
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
    Timing_characteristics* t_car_3 = new Timing_characteristics;
    t_car_3->duration.tv_usec = 0;
    t_car_3->duration.tv_sec  = 0;
    to_return->input_timer_run_characs_1[ 3 ] = t_car_3;
    Timing_characteristics* t_car_4 = new Timing_characteristics;
    t_car_4->duration.tv_usec = 0;
    t_car_4->duration.tv_sec  = 0;
    to_return->input_timer_run_characs_1[ 4 ] = t_car_4;
}
  {
     to_return->input_slice1_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 207.344;
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
    t_car_0->duration.tv_usec = 207.344;
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
    t_car_0->duration.tv_usec = 207.344;
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
    t_car_0->duration.tv_usec = 207.344;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_slice2_run_characs_2[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_slice2_run_characs_2[ 1 ] = t_car_1;
}
  {
     to_return->input_slice3_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 207.344;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_slice3_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_slice3_run_characs_1[ 1 ] = t_car_1;
}
  {
     to_return->input_slice3_run_characs_2.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 207.344;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_slice3_run_characs_2[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_slice3_run_characs_2[ 1 ] = t_car_1;
}
  {
     to_return->input_slice4_run_characs_1.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 207.344;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_slice4_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_slice4_run_characs_1[ 1 ] = t_car_1;
}
  {
     to_return->input_slice4_run_characs_2.resize( 2);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 207.344;
    t_car_0->duration.tv_sec  = 0;
    to_return->input_slice4_run_characs_2[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->input_slice4_run_characs_2[ 1 ] = t_car_1;
}
  return to_return;
}

