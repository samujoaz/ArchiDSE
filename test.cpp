#include <comps_interaction.h>

#include <main_behaviour_0.h>
#include <slice_behaviour_1.h>
#include <slice_behaviour_2.h>
#include <filter_behaviour_1.h>
#include <filter_behaviour_2.h>
#include <write_buffer_behaviour_0.h>
#include <generator_behaviour_0.h>
#include <cypher_behaviour_0.h>
#include <coder_behaviour_0.h>
#include <modulator_behaviour_0.h>
#include <void_behaviour_1.h>
#include <void_behaviour_2.h>
#include <void_behaviour_3.h>
#include <void_behaviour_4.h>
#include <snk_behaviour_0.h>
#include <timer_manager_behaviour_0.h>
#include <Timer_impl.h>
#include <Timer_impl.h>
#include <Timer_impl.h>
#include <Timer_impl.h>
#include <Timer_impl.h>
#include <Timer_impl.h>
#include <Raw_ip_interface.h>
#include <Trace.h>
#include <sys/mman.h>

int main( int argc, char** argv )
{
 mlockall( MCL_CURRENT | MCL_FUTURE );
main_behaviour_0* main = create_main_timing_characs_0();
slice_behaviour_1* slice1 = create_slice_timing_characs_1();
slice_behaviour_2* slice2 = create_slice_timing_characs_2();
filter_behaviour_1* filter1 = create_filter_timing_characs_1();
filter_behaviour_2* filter2 = create_filter_timing_characs_2();
write_buffer_behaviour_0* write_buffer = create_write_buffer_timing_characs_0();
generator_behaviour_0* generator = create_generator_timing_characs_0();
cypher_behaviour_0* cypher = create_cypher_timing_characs_0();
coder_behaviour_0* coder = create_coder_timing_characs_0();
modulator_behaviour_0* modulator = create_modulator_timing_characs_0();
void_behaviour_1* void1 = create_void_timing_characs_1();
void_behaviour_2* void2 = create_void_timing_characs_2();
void_behaviour_3* void3 = create_void_timing_characs_3();
void_behaviour_4* void4 = create_void_timing_characs_4();
snk_behaviour_0* snk = create_snk_timing_characs_0();
timer_manager_behaviour_0* timer_manager = create_timer_manager_timing_characs_0();
Timer_impl* t1 = create_timer();
Timer_impl* t2 = create_timer();
Timer_impl* t3 = create_timer();
Timer_impl* t4 = create_timer();
Timer_impl* t5 = create_timer();
Trace::initialise();
Synchronous_interaction cnx_1;
cnx_1.name = "cnx_1";
cnx_1.target_ = t1->get_start();
timer_manager->timer_1_start_ = &cnx_1;
Synchronous_interaction cnx_2;
cnx_2.name = "cnx_2";
cnx_2.target_ = t2->get_start();
timer_manager->timer_2_start_ = &cnx_2;
Synchronous_interaction cnx_3;
cnx_3.name = "cnx_3";
cnx_3.target_ = t3->get_start();
timer_manager->timer_3_start_ = &cnx_3;
Synchronous_interaction cnx_4;
cnx_4.name = "cnx_4";
cnx_4.target_ = t4->get_start();
timer_manager->timer_4_start_ = &cnx_4;
Synchronous_interaction cnx_5;
cnx_5.name = "cnx_5";
cnx_5.target_ = t5->get_start();
timer_manager->timer_5_start_ = &cnx_5;
Synchronous_interaction cnx_1_stop;
cnx_1_stop.name = "cnx_1_stop";
cnx_1_stop.target_ = t1->get_stop();
timer_manager->timer_1_stop_ = &cnx_1_stop;
Synchronous_interaction cnx_2_stop;
cnx_2_stop.name = "cnx_2_stop";
cnx_2_stop.target_ = t2->get_stop();
timer_manager->timer_2_stop_ = &cnx_2_stop;
Synchronous_interaction cnx_3_stop;
cnx_3_stop.name = "cnx_3_stop";
cnx_3_stop.target_ = t3->get_stop();
timer_manager->timer_3_stop_ = &cnx_3_stop;
Synchronous_interaction cnx_4_stop;
cnx_4_stop.name = "cnx_4_stop";
cnx_4_stop.target_ = t4->get_stop();
timer_manager->timer_4_stop_ = &cnx_4_stop;
Synchronous_interaction cnx_5_stop;
cnx_5_stop.name = "cnx_5_stop";
cnx_5_stop.target_ = t5->get_stop();
timer_manager->timer_5_stop_ = &cnx_5_stop;
Asynchronous_interaction cnx_main;
cnx_main.name = "cnx_main";
cnx_main.set_target( main->get_input_timer() );
cnx_main.set_memory( main->get_memory_input_timer() );
t1->tick_ = &cnx_main;
Asynchronous_interaction cnx_slice1;
cnx_slice1.name = "cnx_slice1";
cnx_slice1.set_target( slice1->get_input() );
cnx_slice1.set_memory( slice1->get_memory_input() );
main->comm_slice1_ = &cnx_slice1;
Asynchronous_interaction cnx_slice2;
cnx_slice2.name = "cnx_slice2";
cnx_slice2.set_target( slice2->get_input() );
cnx_slice2.set_memory( slice2->get_memory_input() );
main->comm_slice2_ = &cnx_slice2;
Asynchronous_interaction cnx_filter1;
cnx_filter1.name = "cnx_filter1";
cnx_filter1.set_target( filter1->get_input() );
cnx_filter1.set_memory( filter1->get_memory_input() );
slice1->output_ = &cnx_filter1;
Asynchronous_interaction cnx_filter2;
cnx_filter2.name = "cnx_filter2";
cnx_filter2.set_target( filter2->get_input() );
cnx_filter2.set_memory( filter2->get_memory_input() );
slice2->output_ = &cnx_filter2;
Asynchronous_interaction cnx_out1;
cnx_out1.name = "cnx_out1";
cnx_out1.set_target( main->get_input_slice1() );
cnx_out1.set_memory( main->get_memory_input_slice1() );
filter1->output_ = &cnx_out1;
Asynchronous_interaction cnx_out2;
cnx_out2.name = "cnx_out2";
cnx_out2.set_target( main->get_input_slice2() );
cnx_out2.set_memory( main->get_memory_input_slice2() );
filter2->output_ = &cnx_out2;
Asynchronous_interaction cnx_write_buffer;
cnx_write_buffer.name = "cnx_write_buffer";
cnx_write_buffer.set_target( write_buffer->get_input() );
cnx_write_buffer.set_memory( write_buffer->get_memory_input() );
main->comm_write_buffer_ = &cnx_write_buffer;
Asynchronous_interaction cnx_main2;
cnx_main2.name = "cnx_main2";
cnx_main2.set_target( generator->get_input1051188() );
cnx_main2.set_memory( generator->get_memory_input1051188() );
t2->tick_ = &cnx_main2;
Asynchronous_interaction cnx_main3;
cnx_main3.name = "cnx_main3";
cnx_main3.set_target( generator->get_input10111132() );
cnx_main3.set_memory( generator->get_memory_input10111132() );
t3->tick_ = &cnx_main3;
Asynchronous_interaction cnx_main4;
cnx_main4.name = "cnx_main4";
cnx_main4.set_target( generator->get_input12111132() );
cnx_main4.set_memory( generator->get_memory_input12111132() );
t4->tick_ = &cnx_main4;
Asynchronous_interaction cnx_main5;
cnx_main5.name = "cnx_main5";
cnx_main5.set_target( generator->get_input1221118() );
cnx_main5.set_memory( generator->get_memory_input1221118() );
t5->tick_ = &cnx_main5;
Asynchronous_interaction cnx_cypher10111132;
cnx_cypher10111132.name = "cnx_cypher10111132";
cnx_cypher10111132.set_target( cypher->get_input10111132() );
cnx_cypher10111132.set_memory( cypher->get_memory_input10111132() );
generator->output10111132_ = &cnx_cypher10111132;
Asynchronous_interaction cnx_cypher1051188;
cnx_cypher1051188.name = "cnx_cypher1051188";
cnx_cypher1051188.set_target( cypher->get_input1051188() );
cnx_cypher1051188.set_memory( cypher->get_memory_input1051188() );
generator->output1051188_ = &cnx_cypher1051188;
Asynchronous_interaction cnx_cypher12111132;
cnx_cypher12111132.name = "cnx_cypher12111132";
cnx_cypher12111132.set_target( cypher->get_input12111132() );
cnx_cypher12111132.set_memory( cypher->get_memory_input12111132() );
generator->output12111132_ = &cnx_cypher12111132;
Asynchronous_interaction cnx_cypher1221118;
cnx_cypher1221118.name = "cnx_cypher1221118";
cnx_cypher1221118.set_target( cypher->get_input1221118() );
cnx_cypher1221118.set_memory( cypher->get_memory_input1221118() );
generator->output1221118_ = &cnx_cypher1221118;
Asynchronous_interaction cnx_coder10111132;
cnx_coder10111132.name = "cnx_coder10111132";
cnx_coder10111132.set_target( coder->get_input10111132() );
cnx_coder10111132.set_memory( coder->get_memory_input10111132() );
cypher->output10111132_ = &cnx_coder10111132;
Asynchronous_interaction cnx_coder1051188;
cnx_coder1051188.name = "cnx_coder1051188";
cnx_coder1051188.set_target( coder->get_input1051188() );
cnx_coder1051188.set_memory( coder->get_memory_input1051188() );
cypher->output1051188_ = &cnx_coder1051188;
Asynchronous_interaction cnx_coder12111132;
cnx_coder12111132.name = "cnx_coder12111132";
cnx_coder12111132.set_target( coder->get_input12111132() );
cnx_coder12111132.set_memory( coder->get_memory_input12111132() );
cypher->output12111132_ = &cnx_coder12111132;
Asynchronous_interaction cnx_coder1221118;
cnx_coder1221118.name = "cnx_coder1221118";
cnx_coder1221118.set_target( coder->get_input1221118() );
cnx_coder1221118.set_memory( coder->get_memory_input1221118() );
cypher->output1221118_ = &cnx_coder1221118;
Asynchronous_interaction cnx_modulator10111132;
cnx_modulator10111132.name = "cnx_modulator10111132";
cnx_modulator10111132.set_target( modulator->get_input10111132() );
cnx_modulator10111132.set_memory( modulator->get_memory_input10111132() );
coder->output10111132_ = &cnx_modulator10111132;
Asynchronous_interaction cnx_modulator1051188;
cnx_modulator1051188.name = "cnx_modulator1051188";
cnx_modulator1051188.set_target( modulator->get_input1051188() );
cnx_modulator1051188.set_memory( modulator->get_memory_input1051188() );
coder->output1051188_ = &cnx_modulator1051188;
Asynchronous_interaction cnx_modulator12111132;
cnx_modulator12111132.name = "cnx_modulator12111132";
cnx_modulator12111132.set_target( modulator->get_input12111132() );
cnx_modulator12111132.set_memory( modulator->get_memory_input12111132() );
coder->output12111132_ = &cnx_modulator12111132;
Asynchronous_interaction cnx_modulator1221118;
cnx_modulator1221118.name = "cnx_modulator1221118";
cnx_modulator1221118.set_target( modulator->get_input1221118() );
cnx_modulator1221118.set_memory( modulator->get_memory_input1221118() );
coder->output1221118_ = &cnx_modulator1221118;
Asynchronous_interaction cnx_snk10111132;
cnx_snk10111132.name = "cnx_snk10111132";
cnx_snk10111132.set_target( snk->get_input10111132() );
cnx_snk10111132.set_memory( snk->get_memory_input10111132() );
modulator->output10111132_ = &cnx_snk10111132;
Asynchronous_interaction cnx_snk1051188;
cnx_snk1051188.name = "cnx_snk1051188";
cnx_snk1051188.set_target( snk->get_input1051188() );
cnx_snk1051188.set_memory( snk->get_memory_input1051188() );
modulator->output1051188_ = &cnx_snk1051188;
Asynchronous_interaction cnx_snk12111132;
cnx_snk12111132.name = "cnx_snk12111132";
cnx_snk12111132.set_target( snk->get_input12111132() );
cnx_snk12111132.set_memory( snk->get_memory_input12111132() );
modulator->output12111132_ = &cnx_snk12111132;
Asynchronous_interaction cnx_snk1221118;
cnx_snk1221118.name = "cnx_snk1221118";
cnx_snk1221118.set_target( snk->get_input1221118() );
cnx_snk1221118.set_memory( snk->get_memory_input1221118() );
modulator->output1221118_ = &cnx_snk1221118;
Asynchronous_interaction cnx_end10111132;
cnx_end10111132.name = "cnx_end10111132";
cnx_end10111132.set_target( void1->get_input() );
cnx_end10111132.set_memory( void1->get_memory_input() );
snk->output10111132_ = &cnx_end10111132;
Asynchronous_interaction cnx_end1051188;
cnx_end1051188.name = "cnx_end1051188";
cnx_end1051188.set_target( void2->get_input() );
cnx_end1051188.set_memory( void2->get_memory_input() );
snk->output1051188_ = &cnx_end1051188;
Asynchronous_interaction cnx_end12111132;
cnx_end12111132.name = "cnx_end12111132";
cnx_end12111132.set_target( void3->get_input() );
cnx_end12111132.set_memory( void3->get_memory_input() );
snk->output12111132_ = &cnx_end12111132;
Asynchronous_interaction cnx_end1221118;
cnx_end1221118.name = "cnx_end1221118";
cnx_end1221118.set_target( void4->get_input() );
cnx_end1221118.set_memory( void4->get_memory_input() );
snk->output1221118_ = &cnx_end1221118;
t1->configure_timerspec_and_sched_fifo( 0, 100000, 0, 80000000, true, 99 );
t2->configure_timerspec_and_sched_fifo( 0, 110000, 0, 82000000, true, 99 );
t3->configure_timerspec_and_sched_fifo( 0, 22000000, 0, 62000000, true, 99 );
t4->configure_timerspec_and_sched_fifo( 0, 42000000, 0, 72000000, true, 99 );
t5->configure_timerspec_and_sched_fifo( 0, 62000000, 0, 92000000, true, 99 );
cnx_main.configure_priority_and_sched_fifo( 99, true );
cnx_main.configure_affinity( 0 );
cnx_slice1.configure_priority_and_sched_fifo( 34, true );
cnx_slice1.configure_affinity( 1 );
cnx_slice2.configure_priority_and_sched_fifo( 34, true );
cnx_slice2.configure_affinity( 2 );
cnx_filter1.configure_priority_and_sched_fifo( 33, true );
cnx_filter1.configure_affinity( 1 );
cnx_filter2.configure_priority_and_sched_fifo( 33, true );
cnx_filter2.configure_affinity( 2 );
cnx_out1.configure_priority_and_sched_fifo( 32, true );
cnx_out1.configure_affinity( 0 );
cnx_out2.configure_priority_and_sched_fifo( 32, true );
cnx_out2.configure_affinity( 1 );
cnx_write_buffer.configure_priority_and_sched_fifo( 31, true );
cnx_write_buffer.configure_affinity( 1 );
cnx_main2.configure_priority_and_sched_fifo( 99, true );
cnx_main2.configure_affinity( 1 );
cnx_main3.configure_priority_and_sched_fifo( 99, true );
cnx_main3.configure_affinity( 2 );
cnx_main4.configure_priority_and_sched_fifo( 99, true );
cnx_main4.configure_affinity( 3 );
cnx_main5.configure_priority_and_sched_fifo( 99, true );
cnx_main5.configure_affinity( 0 );
cnx_cypher10111132.configure_priority_and_sched_fifo( 37, true );
cnx_cypher10111132.configure_affinity( 1 );
cnx_cypher1051188.configure_priority_and_sched_fifo( 37, true );
cnx_cypher1051188.configure_affinity( 2 );
cnx_cypher12111132.configure_priority_and_sched_fifo( 37, true );
cnx_cypher12111132.configure_affinity( 3 );
cnx_cypher1221118.configure_priority_and_sched_fifo( 37, true );
cnx_cypher1221118.configure_affinity( 0 );
cnx_coder10111132.configure_priority_and_sched_fifo( 38, true );
cnx_coder10111132.configure_affinity( 1 );
cnx_coder1051188.configure_priority_and_sched_fifo( 38, true );
cnx_coder1051188.configure_affinity( 2 );
cnx_coder12111132.configure_priority_and_sched_fifo( 38, true );
cnx_coder12111132.configure_affinity( 3 );
cnx_coder1221118.configure_priority_and_sched_fifo( 38, true );
cnx_coder1221118.configure_affinity( 0 );
cnx_modulator10111132.configure_priority_and_sched_fifo( 39, true );
cnx_modulator10111132.configure_affinity( 1 );
cnx_modulator1051188.configure_priority_and_sched_fifo( 39, true );
cnx_modulator1051188.configure_affinity( 2 );
cnx_modulator12111132.configure_priority_and_sched_fifo( 39, true );
cnx_modulator12111132.configure_affinity( 3 );
cnx_modulator1221118.configure_priority_and_sched_fifo( 39, true );
cnx_modulator1221118.configure_affinity( 0 );
cnx_snk10111132.configure_priority_and_sched_fifo( 40, true );
cnx_snk10111132.configure_affinity( 1 );
cnx_snk1051188.configure_priority_and_sched_fifo( 40, true );
cnx_snk1051188.configure_affinity( 2 );
cnx_snk12111132.configure_priority_and_sched_fifo( 40, true );
cnx_snk12111132.configure_affinity( 3 );
cnx_snk1221118.configure_priority_and_sched_fifo( 40, true );
cnx_snk1221118.configure_affinity( 0 );
cnx_end10111132.configure_priority_and_sched_fifo( 41, true );
cnx_end10111132.configure_affinity( 3 );
cnx_end1051188.configure_priority_and_sched_fifo( 41, true );
cnx_end1051188.configure_affinity( 2 );
cnx_end12111132.configure_priority_and_sched_fifo( 41, true );
cnx_end12111132.configure_affinity( 2 );
cnx_end1221118.configure_priority_and_sched_fifo( 41, true );
cnx_end1221118.configure_affinity( 2 );
timer_manager->get_start()->run();
sleep( 3 );
timer_manager->get_stop()->run();
Trace::dump();

return 0;
}
