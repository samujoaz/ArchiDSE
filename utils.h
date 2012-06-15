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
void getAllCpuLoad(uint nb_cpu, int numerodossier,float cpuload[], int frequence[]);
void CopieCompositionFile(string file, string destination);
void tri_bulle( float *tab, int n);
void afficheTBC( float * tab, int longeur);
void getMinMaxCpuLoad(float cpuload[], uint except[], uint nb_cpu, uint nb_except, float *Max, float *Min, uint *indice_cpuMax, uint *indice_cpuMin);
void write_Data_histogram(float cpuload[], int nb_cpu);
void GenScriptHistogram(uint nb_cpu);
void coucou();

#endif