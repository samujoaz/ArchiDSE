
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


void GenerateCpuFile(char *output,string input, COMPONENTCPU C);
void GenerateDspFile(char *output,string input, COMPONENTDSP C);
void GenerateCompositionFile(const char* output,const char* input,const char* newmain, const char* newslice);
void ReadCompositionFile(char * compositionfile, char * compositionmain);

#endif