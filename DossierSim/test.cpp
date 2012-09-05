#include <comps_interaction.h>

#include <main_behaviour_0.h>
#include <slice_behaviour_1.h>
#include <slice_behaviour_2.h>
#include <slice_behaviour_3.h>
#include <slice_behaviour_4.h>
#include <filter_behaviour_1.h>
#include <filter_behaviour_2.h>
#include <filter_behaviour_3.h>
#include <filter_behaviour_4.h>
#include <write_buffer_behaviour_0.h>
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
slice_behaviour_3* slice3 = create_slice_timing_characs_3();
slice_behaviour_4* slice4 = create_slice_timing_characs_4();
filter_behaviour_1* filter1 = create_filter_timing_characs_1();
filter_behaviour_2* filter2 = create_filter_timing_characs_2();
filter_behaviour_3* filter3 = create_filter_timing_characs_3();
filter_behaviour_4* filter4 = create_filter_timing_characs_4();
write_buffer_behaviour_0* write_buffer = create_write_buffer_timing_characs_0();
Timer_impl* t1 = create_timer();
Trace::initialise();
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
Asynchronous_interaction cnx_slice3;
cnx_slice3.name = "cnx_slice3";
cnx_slice3.set_target( slice3->get_input() );
cnx_slice3.set_memory( slice3->get_memory_input() );
main->comm_slice3_ = &cnx_slice3;
Asynchronous_interaction cnx_slice4;
cnx_slice4.name = "cnx_slice4";
cnx_slice4.set_target( slice4->get_input() );
cnx_slice4.set_memory( slice4->get_memory_input() );
main->comm_slice4_ = &cnx_slice4;
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
Asynchronous_interaction cnx_filter3;
cnx_filter3.name = "cnx_filter3";
cnx_filter3.set_target( filter3->get_input() );
cnx_filter3.set_memory( filter3->get_memory_input() );
slice3->output_ = &cnx_filter3;
Asynchronous_interaction cnx_filter4;
cnx_filter4.name = "cnx_filter4";
cnx_filter4.set_target( filter4->get_input() );
cnx_filter4.set_memory( filter4->get_memory_input() );
slice4->output_ = &cnx_filter4;
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
Asynchronous_interaction cnx_out3;
cnx_out3.name = "cnx_out3";
cnx_out3.set_target( main->get_input_slice3() );
cnx_out3.set_memory( main->get_memory_input_slice3() );
filter3->output_ = &cnx_out3;
Asynchronous_interaction cnx_out4;
cnx_out4.name = "cnx_out4";
cnx_out4.set_target( main->get_input_slice4() );
cnx_out4.set_memory( main->get_memory_input_slice4() );
filter4->output_ = &cnx_out4;
Asynchronous_interaction cnx_write_buffer;
cnx_write_buffer.name = "cnx_write_buffer";
cnx_write_buffer.set_target( write_buffer->get_input() );
cnx_write_buffer.set_memory( write_buffer->get_memory_input() );
main->comm_write_buffer_ = &cnx_write_buffer;
t1->configure_timerspec_and_sched_fifo( 0, 10000, 0, 80000000, true, 10 );
cnx_main.configure_priority_and_sched_fifo( 15, true );
cnx_main.configure_affinity( 1 );
cnx_slice1.configure_priority_and_sched_fifo( 14, true );
cnx_slice1.configure_affinity( 1 );
cnx_slice2.configure_priority_and_sched_fifo( 14, true );
cnx_slice2.configure_affinity( 2 );
cnx_slice3.configure_priority_and_sched_fifo( 13, true );
cnx_slice3.configure_affinity( 3 );
cnx_slice4.configure_priority_and_sched_fifo( 13, true );
cnx_slice4.configure_affinity( 2 );
cnx_filter1.configure_priority_and_sched_fifo( 10, true );
cnx_filter1.configure_affinity( 1 );
cnx_filter2.configure_priority_and_sched_fifo( 10, true );
cnx_filter2.configure_affinity( 2 );
cnx_filter3.configure_priority_and_sched_fifo( 10, true );
cnx_filter3.configure_affinity( 3 );
cnx_filter4.configure_priority_and_sched_fifo( 10, true );
cnx_filter4.configure_affinity( 3 );
cnx_out1.configure_priority_and_sched_fifo( 6, true );
cnx_out1.configure_affinity( 1 );
cnx_out2.configure_priority_and_sched_fifo( 6, true );
cnx_out2.configure_affinity( 2 );
cnx_out3.configure_priority_and_sched_fifo( 6, true );
cnx_out3.configure_affinity( 3 );
cnx_out4.configure_priority_and_sched_fifo( 6, true );
cnx_out4.configure_affinity( 0 );
cnx_write_buffer.configure_priority_and_sched_fifo( 15, true );
cnx_write_buffer.configure_affinity( 1 );
t1->get_start()->run();
sleep( 3 );
t1->get_stop()->run();
Trace::dump();

return 0;
}
