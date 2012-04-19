
#ifndef DEF_GENERATEFILE
#define DEF_GENERATEFILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "fonctionsUtils.h"

using namespace std;
// 

void GenerateCpuFile(char *output,string input, COMPONENTCPU C);
void GenerateDspFile(char *output,string input, COMPONENTDSP C);
void ReadCompositionFile(char * compositionfile);






#endif