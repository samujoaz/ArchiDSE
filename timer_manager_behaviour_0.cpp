#include <timer_manager_behaviour_0.h>

timer_manager_behaviour_0::timer_manager_behaviour_0()
{
start_.this_ = this;
stop_.this_ = this;
}
Runnable* timer_manager_behaviour_0::get_start()
{
   return &start_;
}
Memory* timer_manager_behaviour_0::get_memory_start()
{
   return &start_;
}
Runnable* timer_manager_behaviour_0::get_stop()
{
   return &stop_;
}
Memory* timer_manager_behaviour_0::get_memory_stop()
{
   return &stop_;
}
void timer_manager_behaviour_0_start::run()
{
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->start_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_1_start_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->start_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_2_start_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->start_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_3_start_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->start_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_4_start_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->start_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_5_start_->run();
   }
   this_->start_run_characs_1[ car_counter ]->apply();

   return;
}
}
int timer_manager_behaviour_0_start::get_instr()
{
  return 0;
}
int timer_manager_behaviour_0_start::get_load()
{
  return 0;
}
int timer_manager_behaviour_0_start::get_store()
{
  return 0;
}
int timer_manager_behaviour_0_start::get_iL1_miss()
{
  return 0;
}
int timer_manager_behaviour_0_start::get_lL1_miss()
{
  return 0;
}
int timer_manager_behaviour_0_start::get_sL1_miss()
{
  return 0;
}
int timer_manager_behaviour_0_start::get_iL2_miss()
{
  return 0;
}
int timer_manager_behaviour_0_start::get_lL2_miss()
{
  return 0;
}
int timer_manager_behaviour_0_start::get_sL2_miss()
{
  return 0;
}
void timer_manager_behaviour_0_stop::run()
{
{
   int car_counter = 0;
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->stop_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_1_stop_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->stop_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_2_stop_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->stop_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_3_stop_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->stop_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_4_stop_->run();
   }
   for( int ct = 0; ct < 1; ct++ )
   {
     this_->stop_run_characs_1[ car_counter ]->apply();
     car_counter++;
     this_->timer_5_stop_->run();
   }
   this_->stop_run_characs_1[ car_counter ]->apply();

   return;
}
}
int timer_manager_behaviour_0_stop::get_instr()
{
  return 0;
}
int timer_manager_behaviour_0_stop::get_load()
{
  return 0;
}
int timer_manager_behaviour_0_stop::get_store()
{
  return 0;
}
int timer_manager_behaviour_0_stop::get_iL1_miss()
{
  return 0;
}
int timer_manager_behaviour_0_stop::get_lL1_miss()
{
  return 0;
}
int timer_manager_behaviour_0_stop::get_sL1_miss()
{
  return 0;
}
int timer_manager_behaviour_0_stop::get_iL2_miss()
{
  return 0;
}
int timer_manager_behaviour_0_stop::get_lL2_miss()
{
  return 0;
}
int timer_manager_behaviour_0_stop::get_sL2_miss()
{
  return 0;
}

#include <timing_characteristics.h>
#include <sleep_characteristics.h>

timer_manager_behaviour_0* create_timer_manager_timing_characs_0()
{   timer_manager_behaviour_0* to_return = new timer_manager_behaviour_0;

Timing_characteristics::initialise();

  {
     to_return->start_run_characs_1.resize( 6);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 0;
    t_car_0->duration.tv_sec  = 0;
    to_return->start_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->start_run_characs_1[ 1 ] = t_car_1;
    Timing_characteristics* t_car_2 = new Timing_characteristics;
    t_car_2->duration.tv_usec = 0;
    t_car_2->duration.tv_sec  = 0;
    to_return->start_run_characs_1[ 2 ] = t_car_2;
    Timing_characteristics* t_car_3 = new Timing_characteristics;
    t_car_3->duration.tv_usec = 0;
    t_car_3->duration.tv_sec  = 0;
    to_return->start_run_characs_1[ 3 ] = t_car_3;
    Timing_characteristics* t_car_4 = new Timing_characteristics;
    t_car_4->duration.tv_usec = 0;
    t_car_4->duration.tv_sec  = 0;
    to_return->start_run_characs_1[ 4 ] = t_car_4;
    Timing_characteristics* t_car_5 = new Timing_characteristics;
    t_car_5->duration.tv_usec = 0;
    t_car_5->duration.tv_sec  = 0;
    to_return->start_run_characs_1[ 5 ] = t_car_5;
}
  {
     to_return->stop_run_characs_1.resize( 6);

    Timing_characteristics* t_car_0 = new Timing_characteristics;
    t_car_0->duration.tv_usec = 0;
    t_car_0->duration.tv_sec  = 0;
    to_return->stop_run_characs_1[ 0 ] = t_car_0;
    Timing_characteristics* t_car_1 = new Timing_characteristics;
    t_car_1->duration.tv_usec = 0;
    t_car_1->duration.tv_sec  = 0;
    to_return->stop_run_characs_1[ 1 ] = t_car_1;
    Timing_characteristics* t_car_2 = new Timing_characteristics;
    t_car_2->duration.tv_usec = 0;
    t_car_2->duration.tv_sec  = 0;
    to_return->stop_run_characs_1[ 2 ] = t_car_2;
    Timing_characteristics* t_car_3 = new Timing_characteristics;
    t_car_3->duration.tv_usec = 0;
    t_car_3->duration.tv_sec  = 0;
    to_return->stop_run_characs_1[ 3 ] = t_car_3;
    Timing_characteristics* t_car_4 = new Timing_characteristics;
    t_car_4->duration.tv_usec = 0;
    t_car_4->duration.tv_sec  = 0;
    to_return->stop_run_characs_1[ 4 ] = t_car_4;
    Timing_characteristics* t_car_5 = new Timing_characteristics;
    t_car_5->duration.tv_usec = 0;
    t_car_5->duration.tv_sec  = 0;
    to_return->stop_run_characs_1[ 5 ] = t_car_5;
}
  return to_return;
}

