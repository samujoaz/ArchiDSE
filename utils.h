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
void getCpuLoad(uint nb_cpu, uint j,char * nomdudossier,float cpuload[]);
void RegenerateCpuFile(string includeListe[], uint nb_component);
void CopieCompositionFile(string file, string destination);


#endif