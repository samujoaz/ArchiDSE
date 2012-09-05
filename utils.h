#ifndef DEF_UTILS
#define DEF_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "fonctionsUtils.h"
#include "generatefile.h"

using namespace std;

void DownFreqCpu(CPU C, uint delta);
void UpFreqCpu(CPU C, uint delta);
void getAllCpuLoad(uint nb_cpu, int numerodossier,double cpuload[], int frequence[]) ;
void CopieCompositionFile(string file, string destination);
void tri_bulle( double *tab, int n);
void afficheTBC( double * tab, int longeur);
void getMinMaxCpuLoad(double cpuload[], uint except[], uint nb_cpu, uint nb_except, double *Max, double *Min, uint *indice_cpuMax, uint *indice_cpuMin);
void write_Data_histogram(double cpuload[], int nb_cpu);
void GenScriptHistogram(uint nb_cpu);
void coucou();

#endif