#include <comps_interaction.h>

#include <main_behaviour_cpu_0.h>
#include <slice_behaviour_cpu_0.h>
#include <slice_behaviour_cpu_0.h>
#include <write_buffer_behaviour.h>
#include <Timer_impl.h>
#include <Timer_impl.h>
#include <Raw_ip_interface.h>
#include <Trace.h>
#include <sys/mman.h>

int main( int argc, char** argv )
{
 mlockall( MCL_CURRENT | MCL_FUTURE );
main_behaviour_cpu_0* main = create_main_timing_characs_cpu_0();
slice_behaviour_cpu_0* slice1 = create_slice_timing_characs();
slice_behaviour_cpu_0* slice2 = create_slice_timing_characs();
write_buffer_behaviour* write_buffer = create_write_buffer_timing_characs();
Timer_impl* t1 = create_timer();
Trace::initialise();
Asynchronous_interaction cnx_main;
cnx_main.name = "cnx_main";
cnx_main.set_target( main->get_input_timer() );
t1->tick_ = &cnx_main;
Asynchronous_interaction cnx_slice1;
cnx_slice1.name = "cnx_slice1";
cnx_slice1.set_target( slice1->get_input() );
main->comm_slice1_ = &cnx_slice1;
Asynchronous_interaction cnx_slice2;
cnx_slice2.name = "cnx_slice2";
cnx_slice2.set_target( slice2->get_input() );
main->comm_slice2_ = &cnx_slice2;
Asynchronous_interaction cnx_filter1;
cnx_filter1.name = "cnx_filter1";
cnx_filter1.set_target( main->get_input_slice1() );
slice1->output_ = &cnx_filter1;
Asynchronous_interaction cnx_filter2;
cnx_filter2.name = "cnx_filter2";
cnx_filter2.set_target( main->get_input_slice2() );
slice2->output_ = &cnx_filter2;
Asynchronous_interaction cnx_write_buffer;
cnx_write_buffer.name = "cnx_write_buffer";
cnx_write_buffer.set_target( write_buffer->get_input() );
main->comm_write_buffer_ = &cnx_write_buffer;
t1->configure_timerspec_and_sched_fifo( 0, 100000, 0, 125000000, true, 10 );
cnx_main.configure_priority_and_sched_fifo( 10, true );
cnx_main.configure_affinity( 0 );
cnx_slice1.configure_priority_and_sched_fifo( 9, true );
cnx_slice1.configure_affinity( 1 );
cnx_slice2.configure_priority_and_sched_fifo( 8, true );
cnx_slice2.configure_affinity( 0 );
cnx_filter1.configure_priority_and_sched_fifo( 7, true );
cnx_filter1.configure_affinity( 1 );
cnx_filter2.configure_priority_and_sched_fifo( 6, true );
cnx_filter2.configure_affinity( 0 );
cnx_write_buffer.configure_priority_and_sched_fifo( 15, true );
cnx_write_buffer.configure_affinity( 0 );
t1->get_start()->run();
sleep( 2 );
t1->get_stop()->run();
Trace::dump();

return 0;
}