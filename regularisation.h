#ifndef DEF_REGULARISATION
#define DEF_REGULARISATION
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>


#include "fonctionsUtils.h"
#include "generatefile.h"
#include "utils.h"
using namespace std;

bool notFindName(string listename[] ,string index,int taille);
uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num);

#endif