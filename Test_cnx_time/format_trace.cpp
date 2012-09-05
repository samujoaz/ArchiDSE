#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
using namespace std;

bool my_vector_sort(vector < double >i, vector < double >j)
{
    return i[0] > j[0];
}

void compute_iL1_cache(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector)
{
    *cur_value += (cur_time - *prev_time) * (my_vector[1] + my_vector[4] * ((8 * 64) / 64)); //  64 bytes per line, bus line of 64bits
    *f << cur_time << " " << *cur_value << endl;
}

void compute_dL1_cache(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector)
{
    *cur_value += (cur_time - *prev_time) * (my_vector[2]  // nb_load
                                             + my_vector[5] * ((8 * 64) / 64)  // nb load miss
                                             + (my_vector[3] - my_vector[6])    // nb write hit -> write through
        );
    *f << cur_time << " " << *cur_value << endl;
}

void compute_L2_cache(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector)
{
    *cur_value += (cur_time - *prev_time) * (my_vector[4] * ((8 * 64) / 64) // write to iL1
					     + my_vector[7] * ((8 * 128) / 64) // iL2 miss (come from mainMem)
                                             + my_vector[5] * ((8 * 64) / 64)  // nb load dataL1 miss
                                             + my_vector[3]    // all data write (because L1cache = write through
					     + my_vector[8] * ((8 * 128) / 64) // data load L2 miss (come from mainMem)
					     + my_vector[9] * ((8 * 128) / 64) // data write L2 miss (come from mainMem)
        );
    *f << cur_time << " " << *cur_value << endl;
}

void compute_MMem(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector)
{
    *cur_value += (cur_time - *prev_time) * (my_vector[7] * ((8 * 128) / 64) // iL2 miss (come from mainMem)
                                             + my_vector[8] * ((8 * 128) / 64) // data load L2 miss (come from mainMem)
                                             + my_vector[9] * ((8 * 128) / 64) // data write L2 miss (come from mainMem)
        );
    *f << cur_time << " " << *cur_value << endl;
}



int main(int argc, char **argv)
{
    map < string, list < pair < bool, double > > >selected_traces;
    map < string, list < pair < bool, double > > >cpu_activity_trace;
    map < string, list < pair < bool, double > > >memory_activity_trace;

    map < string, list < vector < double > > >waiting_memory_trace;
    map < string, list < double > >used_time;

    map < string, vector < vector < double > > >slope_memory_trace;




    list < string > selected_connections;
    list < string > selected_cpus;
    vector < string > cpus_list (8, "Generic CPU");

    if (argc <= 2) {
        cerr << "Usage : " << argv[0]
            << " [trace_file_name.txt] selected_connection1 ... selected_connection_n -cpu selected_cpu1 ... selected_cpu_n" << endl;
        exit(1);
    }
    int ct = 2;
    for (ct = 2; ct < argc; ct++) {
        if (string(argv[ct]) != "-cpu")
            selected_connections.push_back(string(argv[ct]));
	
        else
            break;
    }

    int cpt_cpu = 0;
    int cpu_index = 0;
    ct++;
    for (; ct < argc; ct++) {
        if(cpt_cpu == 0) {
                cpu_index = atoi(argv[ct]);
                cpt_cpu++;
        }
        else {
                selected_cpus.push_back(string(argv[ct]));
                cpus_list[cpu_index] = string(argv[ct]);
                cpt_cpu = 0;
                //cout << "cpu index : " << cpu_index << endl;
        }
    }



    int activity_of_cpus[selected_cpus.size()];
    
    for (int i = 0; i < selected_cpus.size(); i++)
        activity_of_cpus[i] = 0;
    
    fstream infile(argv[1], ios::in);

    if (!infile) {
        cerr << "File " << argv[1] << " does not exist" << endl;
        exit(1);
    }

    while (infile.good()) {
        string s;
        infile >> s;

        if (!infile.good())
            break;

        if (s != "(") {
            cerr << "Error 1" << endl;
            exit(1);
        }

        string name_connection;
        infile >> name_connection;

        infile >> s;
        if (s != ",") {
            cerr << "Error 2" << endl;
            exit(1);
        }

        bool in_or_out;
        infile >> in_or_out;


        infile >> s;
        if (s != ",") {
            cerr << "Error 3" << endl;
            exit(1);
        }

        double time;
        infile >> time;

        infile >> s;
        if (s != ",") {
            cerr << "Error 5" << endl;
            exit(1);
        }

        int cpu;
        infile >> cpu;

        infile >> s;
        if (s != ",") {
            cerr << "Error 6 : nb_instr missing" << endl;
            exit(1);
        }

        int nb_instr;
        infile >> nb_instr;

        infile >> s;
        if (s != ",") {
            cerr << "Error 7 : nb_load missing" << endl;
            exit(1);
        }

        int nb_load;
        infile >> nb_load;

        infile >> s;
        if (s != ",") {
            cerr << "Error 8 : nb_store missing" << endl;
            exit(1);
        }

        int nb_store;
        infile >> nb_store;

        infile >> s;
        if (s != ",") {
            cerr << "Error 9 : nb_iL1 missing" << endl;
            exit(1);
        }

        int nb_iL1_miss;
        infile >> nb_iL1_miss;

        infile >> s;
        if (s != ",") {
            cerr << "Error 10 : nb_lL1 missing" << endl;
            exit(1);
        }

        int nb_lL1_miss;
        infile >> nb_lL1_miss;

        infile >> s;
        if (s != ",") {
            cerr << "Error 11 : nb_sL1 missing" << endl;
            exit(1);
        }

        int nb_sL1_miss;
        infile >> nb_sL1_miss;

        infile >> s;
        if (s != ",") {
            cerr << "Error 12 : nb_iL2 missing" << endl;
            exit(1);
        }

        int nb_iL2_miss;
        infile >> nb_iL2_miss;

        infile >> s;
        if (s != ",") {
            cerr << "Error 13 : nb_lL2 missing" << endl;
            exit(1);
        }

        int nb_lL2_miss;
        infile >> nb_lL2_miss;

        infile >> s;
        if (s != ",") {
            cerr << "Error 14 : nb_sL2 missing" << endl;
            exit(1);
        }

        int nb_sL2_miss;
        infile >> nb_sL2_miss;





        if (find(selected_connections.begin(), selected_connections.end(), name_connection) != selected_connections.end()) {
            selected_traces[name_connection].push_back(pair < bool, double >(in_or_out, time));
// 	    cout<<"name_connection : "<<name_connection<<endl;
        }
        
        
 

        string cpu_name;
        int cpu_number = 0;
        switch (cpu) {
        case 1:
            cpu_number = 0;
            cpu_name = cpus_list[cpu_number];                             // cpus_list[cpu]; cpus_list.front();
            break;
        case 2:
            cpu_number = 1;
            cpu_name = cpus_list[cpu_number];                             // cpus_list[cpu]; cpus_list.front();
            break;
        case 4:
            cpu_number = 2;
            cpu_name = cpus_list[cpu_number];                             // cpus_list[cpu]; cpus_list.front();
            break;
        case 8:
            cpu_number = 3;
            cpu_name = cpus_list[cpu_number];                             // cpus_list[cpu]; cpus_list.front();
            break;
        case 16:
            cpu_number = 4;
            cpu_name = cpus_list[cpu_number];                             // cpus_list[cpu]; cpus_list.front();
            break;
        case 32:
            cpu_number = 5;
            cpu_name = cpus_list[cpu_number];                             // cpus_list[cpu]; cpus_list.front();
            break;
        case 64:
            cpu_number = 6;
            cpu_name = cpus_list[cpu_number];                             // cpus_list[cpu]; cpus_list.front();
            break;
        case 128:
            cpu_number = 7;
            cpu_name = cpus_list[cpu_number];                             // cpus_list[cpu]; cpus_list.front();
            break;
        }


        if (in_or_out) {
            if (find(selected_cpus.begin(), selected_cpus.end(), cpu_name) != selected_cpus.end()) {

                if (activity_of_cpus[cpu_number] == 0) {
                    cpu_activity_trace[cpu_name].push_back(pair < bool, double
                                                           >(in_or_out, time));
                }
            }

            activity_of_cpus[cpu_number]++;
        } else {
            activity_of_cpus[cpu_number]--;

            if (find(selected_cpus.begin(), selected_cpus.end(), cpu_name) != selected_cpus.end()) {

                if (activity_of_cpus[cpu_number] == 0) {
                    cpu_activity_trace[cpu_name].push_back(pair < bool, double
                                                           >(in_or_out, time));
                    //cout << "CPU : " << cpu_name << " sens : " << in_or_out << " CPU_number : " << cpu_number << endl;
                }
            }
        }
        
       



        // Memory trace
        if (find(selected_cpus.begin(), selected_cpus.end(), cpu_name) != selected_cpus.end()) {
            if (in_or_out) {
                double mydoubles[] =
                    { time, nb_instr, nb_load, nb_store, nb_iL1_miss, nb_lL1_miss, nb_sL1_miss, nb_iL2_miss, nb_lL2_miss, nb_sL2_miss };
                waiting_memory_trace[cpu_name].push_front(vector < double >(mydoubles, mydoubles + sizeof(mydoubles) / sizeof(double)));

                used_time[cpu_name].push_front(0);

            } else {
                double time_value = time - waiting_memory_trace[cpu_name].front()[0] - used_time[cpu_name].front();
                //cout <<" time_value : "<<time_value<< endl;
                //time_value = used_time[cpu_name].front();
                used_time[cpu_name].pop_front();
                double wait_value = time_value + used_time[cpu_name].front();
                if (used_time[cpu_name].size() == 0) {
                    // No more signal ON
                } else {
                    used_time[cpu_name].pop_front();
                    used_time[cpu_name].push_front(wait_value);
                }
                //cout << waiting_memory_trace[cpu_name].front()[1] << endl;
                double mydoubles[] = { waiting_memory_trace[cpu_name].front()[0],
                    waiting_memory_trace[cpu_name].front()[1] / time_value,
                    waiting_memory_trace[cpu_name].front()[2] / time_value,
                    waiting_memory_trace[cpu_name].front()[3] / time_value,
                    waiting_memory_trace[cpu_name].front()[4] / time_value,
                    waiting_memory_trace[cpu_name].front()[5] / time_value,
                    waiting_memory_trace[cpu_name].front()[6] / time_value,
                    waiting_memory_trace[cpu_name].front()[7] / time_value,
                    waiting_memory_trace[cpu_name].front()[8] / time_value,
                    waiting_memory_trace[cpu_name].front()[9] / time_value,
                    time
                };
                slope_memory_trace[cpu_name].push_back(vector < double >(mydoubles, mydoubles + sizeof(mydoubles) / sizeof(double)));

                waiting_memory_trace[cpu_name].pop_front();
            }


        }



        infile >> s;
        if (s != ")") {
            cerr << "Error 4" << endl;
            exit(1);
        }
    }/// while (infile.good())
    

    infile.close(); 
    // Sort the table from lowest time to highest time
    for (list < string >::iterator iter = selected_cpus.begin(); iter != selected_cpus.end(); iter++) {
        sort(slope_memory_trace[*iter].begin(), slope_memory_trace[*iter].end(), my_vector_sort);
    }

    //cout << slope_memory_trace["CPU0"][0][1] << " " << slope_memory_trace["CPU0"][1][1] << endl;
    //cout << slope_memory_trace["CPU0"].back()[0] << " " << slope_memory_trace["CPU0"][1][0] << endl;
    
/// DEBUT partie1 ajouter par:samuel 
    cout<<"coucou"<<endl;
     char c[100];    
    
    uint l_argc = argc-1;
    //cout <<"argc "<<argc<<endl;sleep(3);
    sprintf(c,"mkdir cpuloadfile%s",argv[l_argc]);
    system(c);
   
    ///  Calcul du temps des connections
      for (list < string >::iterator iter = selected_connections.begin(); iter != selected_connections.end(); iter++)
     {
      double prec_time=0;
      // string cnx_name = *iter;
      
       if (find(selected_connections.begin(), selected_connections.end(), *iter) != selected_connections.end() && selected_traces[*iter].size()>0)
       { 
// 	 int  nb_front=0;
	 cout<< "nom de la connection :  "<<*iter<<endl;
	 string tmp = *iter;
	 sprintf(c,"cpuloadfile%s/%s.txt",argv[l_argc],tmp.c_str());
	  ofstream cnx_file(c);
	 for (list < pair < bool, double > >::iterator iter2 = selected_traces[*iter].begin(); iter2 != selected_traces[*iter].end(); iter2++) {
            if (iter2->first == true) {
//                 cout << "H"<<iter2->second <<" " << endl;
		prec_time = iter2->second;

            }
            if (iter2->first == false) {
//                 cout << "L"<<iter2->second <<" "<<  endl; 
		double tempo = (iter2->second - prec_time)*1000.0;
		//cout<<"\n\t  temps passe à l'etat haut: "<<tempo<< " ms "<<endl; 
		cnx_file<<tempo<<endl;
// 		nb_front++;
            }
	 }
// 	 cout <<"nb front : "<< nb_front<<endl;
       }
       else cout<<" name not found "<<endl;
     }
        ///  Calcul du temps des connections
    

  


  
   
    sprintf(c,"cpuloadfile%s/cpuload.txt",argv[l_argc]);
    ofstream outputcpuload(c);
   
	
/// FIN partie1 ajouter par:samuel
    
    fstream gnu_file_all((string("cpuloadfile") +string(argv[l_argc])+string("/") +string(argv[1]) + string("_all.gnu")).c_str(), ios::out);
    gnu_file_all << "# file refering to specific files ..." << endl;
    gnu_file_all << "plot ";

    int counter = 1;

    fstream gnu_file_signals((string("cpuloadfile") +string(argv[l_argc])+string("/") +string(argv[1]) + string("_all_signals.gnu")).c_str(), ios::out);

    gnu_file_signals << "# file refering to specific files ..." << endl;

    gnu_file_signals << "plot ";

    for (list < string >::iterator iter = selected_connections.begin(); iter != selected_connections.end(); iter++) {
        string individual_file = string(string("cpuloadfile") +string(argv[l_argc])+string("/") +argv[1]) + string("_") + *iter + string(".gnu");
	string individual_fileBIS = string(argv[1]) + string("_") + *iter + string(".gnu");
	//cout<< " individual_fileBIS : cnx_"<<individual_fileBIS<<endl;
        fstream outfile(individual_file.c_str(), ios::out);

        outfile << "0.0 " << counter << endl;

        for (list < pair < bool, double > >::iterator iter2 = selected_traces[*iter].begin(); iter2 != selected_traces[*iter].end(); iter2++) {
            if (iter2->first == true) {
                outfile << iter2->second - 1e-7 << " " << counter << endl;
                outfile << iter2->second << " " << counter + 0.5 << endl;
            }
            if (iter2->first == false) {
                outfile << iter2->second << " " << counter + 0.5 << endl;
                outfile << iter2->second + 1e-7 << " " << counter << endl;
            }
        }

        outfile.close();

        gnu_file_signals << " " << "\"" << individual_fileBIS << "\" with lines title " << "\"" << *iter << "\"";
        gnu_file_all << " " << "\"" << individual_fileBIS << "\" with lines title " << "\"" << *iter << "\"";

        list < string >::iterator iter3 = iter;
        iter3++;

        if (iter3 != selected_connections.end()) {
            gnu_file_signals << ",";
            gnu_file_all << ",";
        } else {
            gnu_file_signals << endl;
            gnu_file_signals << "set yrange[0:" << 3 * counter << "]" << endl;
            gnu_file_signals << "pause -1" << endl;
        }

        counter++;
    }


    gnu_file_signals.close();


    gnu_file_all << ",";


    /* For CPU activity */

    //counter = 1;

    fstream gnu_file_cpu((string("cpuloadfile") +string(argv[l_argc])+string("/") +string(argv[1]) + string("_all_CPU.gnu")).c_str(), ios::out);

    gnu_file_cpu << "# file refering to specific files ..." << endl;

    gnu_file_cpu << "plot ";
 

    for (list < string >::iterator iter = selected_cpus.begin(); iter != selected_cpus.end(); iter++) {
        string individual_file = string("cpuloadfile") +string(argv[l_argc])+string("/") +string(argv[1]) + string("_") + *iter + string(".gnu");
        string individual_fileBIS = string(argv[1]) + string("_") + *iter + string(".gnu");

        fstream outfile(individual_file.c_str(), ios::out);

        outfile << "0.0 " << counter << endl;

        string individual_file_power = string("cpuloadfile") +string(argv[l_argc])+string("/") +string(argv[1]) + string("_") + *iter + string("_power.gnu");

        fstream outfilepower(individual_file_power.c_str(), ios::out);

        double power_counter = 0;
        double prev_time = 0.0;
        double mean0 = 0.0;
        double mean1 = 0.0;
        double mean2 = 0.0;
        double mean3 = 0.0;
        double mean4 = 0.0;
        double mean5 = 0.0;
        double mean6 = 0.0;
        double mean7 = 0.0;
        double total_time = 3.0;
        outfilepower << "0.0 " << "0.0" << endl;

	cpu_activity_trace[*iter].push_back(pair < bool, double>(!cpu_activity_trace[*iter].back().first, 3.0));

        for (list < pair < bool, double > >::iterator iter2 = cpu_activity_trace[*iter].begin(); iter2 != cpu_activity_trace[*iter].end(); iter2++) {
            if (iter2->first == true) {
                outfile << iter2->second - 1e-7 << " " << counter << endl;
                outfile << iter2->second << " " << counter + 0.5 << endl;

                mean0 += (iter2->second - prev_time) * counter;
                power_counter = power_counter + (15.7 * (iter2->second - prev_time));
                outfilepower << iter2->second << " " << power_counter << endl;
                prev_time = iter2->second;
            }
            if (iter2->first == false) {
                outfile << iter2->second << " " << counter + 0.5 << endl;
                outfile << iter2->second + 1e-7 << " " << counter << endl;

                mean0 += (iter2->second - prev_time) * (counter + 0.5);
                power_counter = power_counter + (303 * (iter2->second - prev_time));
                outfilepower << iter2->second << " " << power_counter << endl;
                prev_time = iter2->second;
            }
        }

       // cout << "mean CPUload : " << ((mean0 / prev_time) - (counter)) * 200 << " \%." << endl;
       // cout << "mean CPUload (courbe): " << mean0 / prev_time << endl;
/// DEBUT partie ajouter par:samuel 

	if(prev_time<1e-5)
	{
	    outputcpuload<<"mean " <<*iter<<": " <<0.0<<endl;
	    cout<<"mean CPUload du " <<*iter<<": " <<0.0<<endl;
	}
	else 
	{
	    outputcpuload<<"mean " <<*iter<<": " <<((mean0 / prev_time) - (counter)) * 200<<endl;
	    cout<<"mean CPUload du " <<*iter<<": " <<((mean0 / prev_time) - (counter)) * 200<<endl;
	}
/// FIN partie ajouter par:samuel  
	
	outfile.close();
        outfilepower.close();

        gnu_file_cpu << " " << "\"" << individual_fileBIS << "\" with lines title " << "\"" << *iter << "\"";
        gnu_file_all << " " << "\"" << individual_fileBIS << "\" with lines title " << "\"" << *iter << "\"";

//         gnu_file_all << " , " << mean0 / prev_time << " title " << "\"" << *iter << " (mean)\"";
	
	if(prev_time<1e-5)
		gnu_file_all << " , " << 0.0<< " title " << "\"" << *iter << " (mean)\"";
	else 	gnu_file_all << " , " << mean0 / prev_time << " title " << "\"" << *iter << " (mean)\"";


        list < string >::iterator iter3 = iter;
        iter3++;

        if (iter3 != selected_cpus.end()) {
            gnu_file_cpu << ",";
            gnu_file_all << ",";
        } else {
            gnu_file_cpu << endl;
            gnu_file_cpu << "set yrange[0:" << 3 * counter << "]" << endl;
            gnu_file_cpu << "pause -1" << endl;

            gnu_file_all << endl;
            gnu_file_all << "set yrange[0:" << 3 * counter << "]" << endl;
            gnu_file_all << "pause -1" << endl;
        }

        counter++;
        //cout << counter << *iter << endl;
    }
    
    outputcpuload.close();
    gnu_file_cpu.close();
    gnu_file_all.close();




    /* For MEMORY activity */

    fstream gnu_file_mem((string("cpuloadfile") +string(argv[l_argc])+string("/") +string(argv[1]) + string("_all_mem.gnu")).c_str(), ios::out);
    gnu_file_mem << "# file refering to specific files ..." << endl;
    gnu_file_mem << "plot ";

    double current_time = 0.0;
    vector < double >current_value(4, 0.0);
    list < vector < double > >slope_list;
    list < vector < double > >temp_list;

    slope_list.push_front(vector < double >(11, 0.0));

    for (list < string >::iterator iter = selected_cpus.begin(); iter != selected_cpus.end(); iter++) {

        current_time = 0.0;
        current_value = vector < double >(4, 0.0);

        string individual_file_mem = string(string("cpuloadfile") +string(argv[l_argc])+string("/") +argv[1]) + string("_") + *iter + string("_iL1.gnu");
        fstream outfileiL1(individual_file_mem.c_str(), ios::out);

        individual_file_mem = string(string("cpuloadfile") +string(argv[l_argc])+string("/") +argv[1]) + string("_") + *iter + string("_dL1.gnu");
        fstream outfiledL1(individual_file_mem.c_str(), ios::out);

        individual_file_mem = string(string("cpuloadfile") +string(argv[l_argc])+string("/") +argv[1]) + string("_") + *iter + string("_L2.gnu");
        fstream outfileL2(individual_file_mem.c_str(), ios::out);

        individual_file_mem = string(string("cpuloadfile") +string(argv[l_argc])+string("/") +argv[1]) + string("_") + *iter + string("_MMEM.gnu");
        fstream outfileMMEM(individual_file_mem.c_str(), ios::out);

        outfileiL1 << "0.0 " << "0.0" << endl;
        outfiledL1 << "0.0 " << "0.0" << endl;
        outfileL2 << "0.0 " << "0.0" << endl;
        outfileMMEM << "0.0 " << "0.0" << endl;

        while (!slope_memory_trace[*iter].empty()) {
            compute_iL1_cache(&outfileiL1, &current_value[0], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front());
            compute_dL1_cache(&outfiledL1, &current_value[1], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front());
            compute_L2_cache(&outfileL2, &current_value[2], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front());
            compute_MMem(&outfileMMEM, &current_value[3], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front());

            current_time = slope_memory_trace[*iter].back()[0]; // Update current time


            //cout << slope_memory_trace[*iter].back()[0] << endl;
            slope_list.push_front(slope_memory_trace[*iter].back());



            if (slope_memory_trace[*iter].size() == 1) {   // This is the last
                compute_iL1_cache(&outfileiL1, &current_value[0], &current_time, slope_memory_trace[*iter].back()[10], slope_list.front());
                compute_dL1_cache(&outfiledL1, &current_value[1], &current_time, slope_memory_trace[*iter].back()[10], slope_list.front());
                compute_L2_cache(&outfileL2, &current_value[2], &current_time, slope_memory_trace[*iter].back()[10], slope_list.front());
                compute_MMem(&outfileMMEM, &current_value[3], &current_time, slope_memory_trace[*iter].back()[10], slope_list.front());

                current_time = slope_memory_trace[*iter].back()[10];    // Update current time

                slope_memory_trace[*iter].pop_back();
                slope_list.pop_front();

                while (!temp_list.empty()) {
                    //cout << "enter while end" << endl;
                    compute_iL1_cache(&outfileiL1, &current_value[0], &current_time, temp_list.front()[10], slope_list.front());
                    compute_dL1_cache(&outfiledL1, &current_value[1], &current_time, temp_list.front()[10], slope_list.front());
                    compute_L2_cache(&outfileL2, &current_value[2], &current_time, temp_list.front()[10], slope_list.front());
                    compute_MMem(&outfileMMEM, &current_value[3], &current_time, temp_list.front()[10], slope_list.front());

                    current_time = temp_list.front()[10];  // Update current time

                    temp_list.pop_front();
                    slope_list.pop_front();

                }
                //cout << "after while end" << endl;


            } else {
                // TODO : Ajouter a une liste l'element courrant
                temp_list.push_front(slope_memory_trace[*iter].back());
                slope_memory_trace[*iter].pop_back();
                if (slope_memory_trace[*iter].back()[0] < temp_list.front()[10]) {      // overlap
                    //slope_memory_trace[*iter].back()[0] - current_time;
                } else {
                    compute_iL1_cache(&outfileiL1, &current_value[0], &current_time, temp_list.front()[10], slope_list.front());
                    compute_dL1_cache(&outfiledL1, &current_value[1], &current_time, temp_list.front()[10], slope_list.front());
                    compute_L2_cache(&outfileL2, &current_value[2], &current_time, temp_list.front()[10], slope_list.front());
                    compute_MMem(&outfileMMEM, &current_value[3], &current_time, temp_list.front()[10], slope_list.front());

                    current_time = temp_list.front()[10];  // Update current time

                    temp_list.pop_front();
                    slope_list.pop_front();

                    bool overlap = false;
                    while (!temp_list.empty() && (overlap == false)) {
                        //cout << "enter while" << endl;
                        if (slope_memory_trace[*iter].back()[0] < temp_list.front()[10]) {      // overlap
                            overlap = true;
                            //cout << "overlap" << slope_memory_trace[*iter].back()[0] << " " << temp_list.front()[10] << endl;
                        } else {
                            compute_iL1_cache(&outfileiL1, &current_value[0], &current_time, temp_list.front()[10], slope_list.front());
                            compute_dL1_cache(&outfiledL1, &current_value[1], &current_time, temp_list.front()[10], slope_list.front());
                            compute_L2_cache(&outfileL2, &current_value[2], &current_time, temp_list.front()[10], slope_list.front());
                            compute_MMem(&outfileMMEM, &current_value[3], &current_time, temp_list.front()[10], slope_list.front());

                            current_time = temp_list.front()[10];       // Update current time

                            temp_list.pop_front();
                            slope_list.pop_front();
                        }
                    }
                }
            }
        }
        outfileiL1.close();
        outfiledL1.close();
        outfileL2.close();
        outfileMMEM.close();
    }



    return 0;
}
