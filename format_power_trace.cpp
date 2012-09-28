#include <fstream>
#include <iostream>
#include <map>
#include <list>
#include <utility>
#include <algorithm>
#include <vector>
#include <deque>
using namespace std;

#include "regression.h"
bool my_vector_sort(vector < double >i, vector < double >j)
{
    return i[0] > j[0];
}



vector <double> compute_conso( vector < vector <  double> > polynom , double frequence )
{
  vector <  double>  vector_conso;
  double conso=0.0;
  int i=0;

  for(vector < vector < double > >::iterator iter1 = polynom.begin(); iter1 != polynom.end(); iter1++)
  {   

    int j=0; 
    conso=0.0;
    for(vector < double  >::iterator iter2 = polynom[i].begin(); iter2 != polynom[i].end(); iter2++)
    { 
	switch (j)
	{
	  case 0: 
	  conso+= frequence * frequence * (*iter2); break;
	  case 1: 
	  conso+= frequence * (*iter2);break;
	  case 2: 
	  conso+= (*iter2); break;
	}
    j++;
    }
  vector_conso.push_back(conso);
  i++;
  }
  return vector_conso;
}
/*void compute_conso(  vector <  double>  polynom , double frequence, double *conso)
{
  *conso=0.0;
  int i=0;
  for( vector < double >::iterator iter = polynom.begin(); iter != polynom.end(); iter++)  
  {
    switch (i)
      {
	  case 0: 
	  *conso+= frequence * frequence * (*iter); break;
	  case 1: 
	  *conso+= frequence * (*iter);break;
	  case 2: 
	  *conso+= (*iter); break;
      }
    i++;
  }
}*/
// focntion origne
//on va remplacer le  0.0000098 par la valeur extrapoler par la fonction regression.
// void compute_iL1_cache(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector)
// {
//     *cur_value += (cur_time - *prev_time) * (my_vector[1] 
// 					     + my_vector[4] * ((8 * 64) / 64) //  64 bytes per line, bus line of 64bits
//         ) * 0.000000098 + (cur_time - *prev_time) * 1.21068; // Powerconsumption
//     *f << cur_time << " " << *cur_value << endl;// static 0.662431
// }

/// DEBUT ZONE DE MODIFICATION

void compute_iL1_cache_new(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector,double conso)
{
  
    *cur_value += (cur_time - *prev_time) * (my_vector[1] 
					     + my_vector[4] * ((8 * 64) / 64) //  64 bytes per line, bus line of 64bits
        )* conso  ;
	//+ (cur_time - *prev_time) * 1.21068; // Powerconsumption
    *f << cur_time << " " << *cur_value << endl;// static 0.662431 ecriture dans le fichier;
}

void compute_dL1_cache_new(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector,double conso)
{
    *cur_value += (cur_time - *prev_time) * (my_vector[2]  // nb_load
                                             + my_vector[5] * ((8 * 64) / 64)  // nb load miss
                                             + (my_vector[3] - my_vector[6])    // nb write hit -> write through
        ) *conso; 
    *f << cur_time << " " << *cur_value << endl;//254437
}

void compute_L2_cache_new(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector,double conso)
{
    *cur_value += (cur_time - *prev_time) * (my_vector[4] * ((8 * 64) / 64) // write to iL1
					     + my_vector[7] * ((8 * 128) / 64) // iL2 miss (come from mainMem)
                                             + my_vector[5] * ((8 * 64) / 64)  // nb load dataL1 miss
                                             + my_vector[3]    // all data write (because L1cache = write through
					     + my_vector[8] * ((8 * 128) / 64) // data load L2 miss (come from mainMem)
					     + my_vector[9] * ((8 * 128) / 64) // data write L2 miss (come from mainMem)
        ) * conso  ;
    *f << cur_time << " " << *cur_value << endl; //376 461
}



void compute_leackage(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector,double conso)
{
    *cur_value += (cur_time - *prev_time) *  conso;
    *f << cur_time << " " << *cur_value << endl; //376 461
}

void compute_cpu(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector,double conso)
{
    *cur_value += (cur_time - *prev_time) * my_vector[1] *  conso;
    *f << cur_time << " " << *cur_value << endl; //376 461
}


/// FIN ZONE DE MODIFICATION ////
void compute_iL1_cache(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector)
{
  
    *cur_value += (cur_time - *prev_time) * (my_vector[1] 
					     + my_vector[4] * ((8 * 64) / 64) //  64 bytes per line, bus line of 64bits
        )* 0.000000098 + (cur_time - *prev_time) * 1.21068; // Powerconsumption
    *f << cur_time << " " << *cur_value << endl;// static 0.662431 ecriture dans le fichier;
}

void compute_dL1_cache(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector)
{
    *cur_value += (cur_time - *prev_time) * (my_vector[2]  // nb_load
                                             + my_vector[5] * ((8 * 64) / 64)  // nb load miss
                                             + (my_vector[3] - my_vector[6])    // nb write hit -> write through
        ) * 0.000000098 + (cur_time - *prev_time) * 1.21068; // Powerconsumption
    *f << cur_time << " " << *cur_value << endl;//254437
}

void compute_L2_cache(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector)
{
    *cur_value += (cur_time - *prev_time) * (my_vector[4] * ((8 * 64) / 64) // write to iL1
					     + my_vector[7] * ((8 * 128) / 64) // iL2 miss (come from mainMem)
                                             + my_vector[5] * ((8 * 64) / 64)  // nb load dataL1 miss
                                             + my_vector[3]    // all data write (because L1cache = write through
					     + my_vector[8] * ((8 * 128) / 64) // data load L2 miss (come from mainMem)
					     + my_vector[9] * ((8 * 128) / 64) // data write L2 miss (come from mainMem)
        ) *   0.000000125 + (cur_time - *prev_time) * 20.0304; // Powerconsumption
    *f << cur_time << " " << *cur_value << endl; //376 461
}

void compute_MMem(fstream * f, double *cur_value, double *prev_time, double cur_time, vector < double >my_vector)
{

    *cur_value += (cur_time - *prev_time) * (my_vector[7] * ((8 * 128) / 64) // iL2 miss (come from mainMem)
                                             + my_vector[8] * ((8 * 128) / 64) // data load L2 miss (come from mainMem)
                                             + my_vector[9] * ((8 * 128) / 64) // data write L2 miss (come from mainMem)
        ) *   0.000000822966149321 ;//+ (cur_time - *prev_time) * (4 * 36.412473852);// Powerconsumption
    //*cur_value += 0;
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
// vector < double > ma_liste_v;


    list < string > selected_connections;
    list < string > selected_cpus;
    vector < string > cpus_list (8, "Generic CPU");                            
    vector < int > cpus_number;                             
    vector <double> vector_conso;
    vector_conso = compute_conso(compute_regression("consoleak.txt"), 1000);
    /// Pour l'instant sont rangés dans vector_conso dans l'ordre
    /// vector_conso[0] conso cache L2
    /// vector_conso[1] conso cache L1
    /// vector_conso[2] conso cpu
    /// vector_conso[3] conso Leackage
    /// si on rajoute d'autres conso au modèle ils seront à la suite. voir/modifier aussi les fichiers (regression.cpp et consoleak.txt
    ///  si on veut rajouter d'autres conso 
//     for(vector <double> ::iterator iter=vector_conso.begin();iter != vector_conso.end(); iter++)
//       cout<<*iter<< " == "<<vector_conso[pppp++]<<endl;
//     exit(0);
    if (argc <= 2) {
        cerr << "Usage : " << argv[0]
            << " [trace_file_name.txt] selected_connection1 ... selected_connection_n -cpu selected_cpu1 name_cpu1 ... selected_cpu_n name_cpu_n" << endl;
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
		//cout << "cpu index : " << cpu_index << cpus_list[cpu_index] << endl;
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

	//cout << "cpu name : " << cpu_name << endl;

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
                //cout << time_value << endl;
                //time_value = used_time[cpu_name].front();
                used_time[cpu_name].pop_front();
                double wait_value = time_value + used_time[cpu_name].front();
                if (used_time[cpu_name].size() == 0) {
                    // No more signal ON
                } else {
                    used_time[cpu_name].pop_front();
                    used_time[cpu_name].push_front(wait_value);
                }
                cout << waiting_memory_trace[cpu_name].front()[1] << endl;
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
// 		ma_liste_v.push.back(2);
                waiting_memory_trace[cpu_name].pop_front();
            }


        }
        
      

// for (list < string >::iterator iter = selected_cpus.begin(); iter != selected_cpus.end(); iter++) 
//  nb_ligne_par_fichier.push_back (double(slope_memory_trace[*iter].size()));

        infile >> s;
        if (s != ")") {
            cerr << "Error 4" << endl;
            exit(1);
        }
    }

    infile.close();

    // Sort the table from lowest time to highest time
    for (list < string >::iterator iter = selected_cpus.begin(); iter != selected_cpus.end(); iter++) {
        sort(slope_memory_trace[*iter].begin(), slope_memory_trace[*iter].end(), my_vector_sort);
    }

    //cout << slope_memory_trace["CPU0"][0][1] << " " << slope_memory_trace["CPU0"][1][1] << endl;
    //cout << slope_memory_trace["CPU0"].back()[0] << " " << slope_memory_trace["CPU0"][1][0] << endl;


    int counter = 1;

    /* For CPU activity */

    for (list < string >::iterator iter = selected_cpus.begin(); iter != selected_cpus.end(); iter++) {
        string individual_file_power = string(argv[1]) + string("_") + *iter + string("_power.gnu");

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
        double total_time = 2.0;
        outfilepower << "0.0 " << "0.0" << endl;


        for (list < pair < bool, double > >::iterator iter2 = cpu_activity_trace[*iter].begin(); iter2 != cpu_activity_trace[*iter].end(); iter2++) {
            if (iter2->first == true) {

                mean0 += (iter2->second - prev_time) * counter;
                power_counter = power_counter + (15.7 * (iter2->second - prev_time));
                outfilepower << iter2->second << " " << power_counter << endl;
                prev_time = iter2->second;
            }
            if (iter2->first == false) {

                mean0 += (iter2->second - prev_time) * (counter + 0.5);
                power_counter = power_counter + (303 * (iter2->second - prev_time));
                outfilepower << iter2->second << " " << power_counter << endl;
                prev_time = iter2->second;
            }
        }

        cout << "mean CPUload : " << ((mean0 / prev_time) - (counter)) * 200 << " \%." << endl;
        cout << "mean CPUload (courbe): " << mean0 / prev_time << endl;

        outfilepower.close();


        list < string >::iterator iter3 = iter;
        iter3++;

        if (iter3 != selected_cpus.end()) {
        } else {
        }

        counter++;
        cout << counter << *iter << endl;
    }




    /* For MEMORY activity */

    fstream gnu_file_mem((string(argv[1]) + string("_all_mem.gnu")).c_str(), ios::out);
    gnu_file_mem << "# file refering to specific files ..." << endl;
    gnu_file_mem << "plot ";

    double current_time = 0.0;
    vector < double >current_value(6, 0.0);
    list < vector < double > >slope_list;
    list < vector < double > >temp_list;

    slope_list.push_front(vector < double >(11, 0.0));

    for (list < string >::iterator iter = selected_cpus.begin(); iter != selected_cpus.end(); iter++) {
        current_time = 0.0;
        current_value = vector < double >(6, 0.0);

        string individual_file_mem = string(argv[1]) + string("_") + *iter + string("_iL1_power.gnu");
        fstream outfileiL1(individual_file_mem.c_str(), ios::out);

        individual_file_mem = string(argv[1]) + string("_") + *iter + string("_dL1_power.gnu");
        fstream outfiledL1(individual_file_mem.c_str(), ios::out);

        individual_file_mem = string(argv[1]) + string("_") + *iter + string("_L2_power.gnu");
        fstream outfileL2(individual_file_mem.c_str(), ios::out);

        individual_file_mem = string(argv[1]) + string("_") + *iter + string("_MMEM_power.gnu");
        fstream outfileMMEM(individual_file_mem.c_str(), ios::out);

        individual_file_mem = string(argv[1]) + string("_") + *iter + string("_allmem_power.gnu");
        fstream outfileallmempower(individual_file_mem.c_str(), ios::out);
	
	 individual_file_mem = string(argv[1]) + string("_") + *iter + string("_cpu_power.gnu");
        fstream outfilecpu(individual_file_mem.c_str(), ios::out);
	
	 individual_file_mem = string(argv[1]) + string("_") + *iter + string("_leackage_power.gnu");
        fstream outfileleackage(individual_file_mem.c_str(), ios::out);
	
// 	individual_file_mem = string(argv[1]) + string("_") + *iter + string("_all_leackage_power.gnu");
//         fstream outfileallleackage(individual_file_mem.c_str(), ios::out);
// 	
// 	individual_file_mem = string(argv[1]) + string("_") + *iter + string("_all_cpu_power.gnu");
//         fstream outfileallcpuconso(individual_file_mem.c_str(), ios::out);
// 	

        outfileiL1 << "0.0 " << "0.0" << endl;
        outfiledL1 << "0.0 " << "0.0" << endl;
        outfileL2 << "0.0 " << "0.0" << endl;
        outfileMMEM << "0.0 " << "0.0" << endl;
        outfileallmempower << "0.0 " << "0.0" << endl;
	outfilecpu << "0.0 " << "0.0" << endl;
	outfileleackage << "0.0 " << "0.0" << endl;
// 	outfileallleackage << "0.0 " << "0.0" << endl;
// 	outfileallcpuconso << "0.0 " << "0.0" << endl;

        while (!slope_memory_trace[*iter].empty()) {
            compute_iL1_cache_new(&outfileiL1, &current_value[0], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front(),vector_conso[1]);
            compute_dL1_cache_new(&outfiledL1, &current_value[1], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front(),vector_conso[1]);
            compute_L2_cache_new(&outfileL2, &current_value[2], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front(),vector_conso[0]);
            compute_MMem(&outfileMMEM, &current_value[3], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front());
	    compute_cpu(&outfilecpu, &current_value[4], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front(),vector_conso[2]);
	    compute_leackage(&outfileleackage, &current_value[5], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front(),vector_conso[3]);
            outfileallmempower << slope_memory_trace[*iter].back()[0] << " " << current_value[0]+current_value[1]+current_value[2]+current_value[3] + current_value[4] + current_value[5] << endl;

            current_time = slope_memory_trace[*iter].back()[0]; // Update current time


            //cout << slope_memory_trace[*iter].back()[0] << endl;
            slope_list.push_front(slope_memory_trace[*iter].back());



            if (slope_memory_trace[*iter].size() == 1) {   // This is the last
                compute_iL1_cache_new(&outfileiL1, &current_value[0], &current_time, slope_memory_trace[*iter].back()[10], slope_list.front(),vector_conso[1]);
                compute_dL1_cache_new(&outfiledL1, &current_value[1], &current_time, slope_memory_trace[*iter].back()[10], slope_list.front(),vector_conso[1]);
                compute_L2_cache_new(&outfileL2, &current_value[2], &current_time, slope_memory_trace[*iter].back()[10], slope_list.front(),vector_conso[0]);
		compute_MMem(&outfileMMEM, &current_value[3], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front());
		compute_cpu(&outfilecpu, &current_value[4], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front(),vector_conso[2]);
		compute_leackage(&outfileleackage, &current_value[5], &current_time, slope_memory_trace[*iter].back()[0], slope_list.front(),vector_conso[3]);
                outfileallmempower << slope_memory_trace[*iter].back()[10] << " " << current_value[0]+current_value[1]+current_value[2]+current_value[3] + current_value[4] + current_value[5] << endl;

                current_time = slope_memory_trace[*iter].back()[10];    // Update current time

                slope_memory_trace[*iter].pop_back();
                slope_list.pop_front();

                while (!temp_list.empty()) {
                    //cout << "enter while end" << endl;
                    compute_iL1_cache_new(&outfileiL1, &current_value[0], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[1]);
                    compute_dL1_cache_new(&outfiledL1, &current_value[1], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[1]);
                    compute_L2_cache_new(&outfileL2, &current_value[2], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[0]);
		    compute_MMem(&outfileMMEM, &current_value[3], &current_time, temp_list.front()[10], slope_list.front());
		    compute_cpu(&outfilecpu, &current_value[4], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[2]);
		    compute_leackage(&outfileleackage, &current_value[5], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[3]);
		    outfileallmempower << temp_list.front()[10] << " " << current_value[0]+current_value[1]+current_value[2]+current_value[3] + current_value[4] + current_value[5] << endl;

                    current_time = temp_list.front()[10];  // Update current time

                    temp_list.pop_front();
                    slope_list.pop_front();

                }
                cout << "after while end" << endl;


            } else {
                // TODO : Ajouter a une liste l'element courrant
                temp_list.push_front(slope_memory_trace[*iter].back());
                slope_memory_trace[*iter].pop_back();
                if (slope_memory_trace[*iter].back()[0] < temp_list.front()[10]) {      // overlap
                    //slope_memory_trace[*iter].back()[0] - current_time;
                } else {
                    compute_iL1_cache_new(&outfileiL1, &current_value[0], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[1]);
                    compute_dL1_cache_new(&outfiledL1, &current_value[1], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[1]);
		    compute_L2_cache_new(&outfileL2, &current_value[2], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[0]);
		    compute_MMem(&outfileMMEM, &current_value[3], &current_time, temp_list.front()[10], slope_list.front());
		    compute_cpu(&outfilecpu, &current_value[4], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[2]);
		    compute_leackage(&outfileleackage, &current_value[5], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[3]);
                    outfileallmempower << temp_list.front()[10] << " " << current_value[0]+current_value[1]+current_value[2]+current_value[3] + current_value[4] + current_value[5] << endl;

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
                            compute_iL1_cache_new(&outfileiL1, &current_value[0], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[1]);
                            compute_dL1_cache_new(&outfiledL1, &current_value[1], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[1]);
                            compute_L2_cache_new(&outfileL2, &current_value[2], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[0]);
			    compute_MMem(&outfileMMEM, &current_value[3], &current_time, temp_list.front()[10], slope_list.front());
			    compute_cpu(&outfilecpu, &current_value[4], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[2]);
			    compute_leackage(&outfileleackage, &current_value[5], &current_time, temp_list.front()[10], slope_list.front(),vector_conso[3]);
                            outfileallmempower << temp_list.front()[10] << " " << current_value[0]+current_value[1]+current_value[2]+current_value[3] + current_value[4] + current_value[5]  << endl;

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
	outfileleackage.close();
	outfilecpu.close();
        outfileMMEM.close();
    }
    
    cout <<"coiucou"<<endl;
    list <double> head_leackage;
    list <double> head_cpu;
    double * SUM_leackage;
    double * SUM_cpu;
    int jj=0;
    string line;
    bool first_time=true;
    int taille_leackage =0,taille_cpu=0; 
        for (list < string >::iterator iter = selected_cpus.begin(); iter != selected_cpus.end(); iter++) {
	  /// ouvrir tout les fichiers 
	  double val=0.0;
	  string individual_file_mem;
	  individual_file_mem = string(argv[1]) + string("_") + *iter + string("_cpu_power.gnu");
        fstream infilecpu(individual_file_mem.c_str(), ios::in);
	 
	individual_file_mem = string(argv[1]) + string("_") + *iter + string("_leackage_power.gnu");
        fstream infileleackage(individual_file_mem.c_str(), ios::in);
	deque <double> machaine_cpu; 
	deque <double> machaine_leackage; 
	 // taille_leackage =0;taille_cpu=0; 
	while(infilecpu>>line)
	{ 
	  infilecpu>>line;
	  machaine_cpu.push_back(atof(line.c_str()));
 	  if(first_time) 
	    taille_cpu++;
	}
	while(infileleackage>>line)
	{
	  infileleackage>>line;
	  machaine_leackage.push_back(atof(line.c_str()));
 	  if(first_time) 
	    taille_leackage++;
	}
	
	if(first_time)
	{
	SUM_cpu = new double[taille_cpu]; 
	SUM_leackage = new double[taille_leackage];
	for(int y=0; y<taille_cpu;y++) SUM_cpu[y]=0.0;
	for(int y=0; y<taille_leackage;y++) SUM_leackage[y]=0.0;
	first_time=false;
	}
	int i=0;
	while (!machaine_cpu.empty())
	{
	  if(i<taille_cpu){
	  SUM_cpu[i++] += machaine_cpu.front();
// 	  cout<<SUM_cpu[i-1]<<endl;
	  machaine_cpu.pop_front();
	}
	  
	}
	i=0;
	while (!machaine_leackage.empty())
	{
	  if(i<taille_leackage){
	  SUM_leackage[i++] += machaine_leackage.front();
// 	  cout<<SUM_leackage[i-1]<<endl;
	  machaine_leackage.pop_front();
	}
	}
	 	
// 	  
// 	  	
// 	individual_file_mem = string(argv[1]) + string("_") + *iter + string("_all_leackage_power.gnu");
//         fstream outfileallleackage(individual_file_mem.c_str(), ios::out);
// 	individual_file_mem = string(argv[1]) + string("_") + *iter + string("_all_cpu_power.gnu");
//         fstream outfileallcpuconso(individual_file_mem.c_str(), ios::out);
// 	
//
// 
// 	outfileallleackage << "0.0 " << "0.0" << endl;
// 	outfileallcpuconso << "0.0 " << "0.0" << endl;
	}
	cout <<taille_leackage << " et " << taille_cpu<< endl;
	string individual_file_mem;
	individual_file_mem = string(argv[1]) + string("_all_leackage_power.gnu");
        fstream outfileallleackage(individual_file_mem.c_str(), ios::out);
	individual_file_mem = string(argv[1]) + string("_all_cpu_power.gnu");
        fstream outfileallcpuconso(individual_file_mem.c_str(), ios::out);
// 	outfileallleackage << "0.0 " << "0.0" << endl;
// 	outfileallcpuconso << "0.0 " << "0.0" << endl;
	for(int i=0; i<taille_leackage;i++)
	outfileallleackage << SUM_leackage[i++] << endl;
	for(int i=0; i<taille_cpu;i++)
	outfileallcpuconso << SUM_cpu[i++] << endl;



    return 0;
}
