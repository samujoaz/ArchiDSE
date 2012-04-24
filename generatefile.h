
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


void GenerateCpuFile(string output,string input, COMPONENTCPU C,string S1, string S2);
void GenerateDspFile(char *output,string input, COMPONENTDSP C);
void GenerateCompositionFile(const char* output,const char* input,const char* newmain, const char* newslice,string indice);
void ReadCompositionFile(char * compositionfile, char * compositionmain);
void GenerateCompCpuFile(string input,string output,string S1);

#endif