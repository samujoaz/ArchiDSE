
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


void GenerateCpuFile(string output,string input,CPU C,string S1, string S2,string S3);
void GenerateDspFile(char *output,string input, COMPONENTDSP C);
void GenerateCompositionFile(const char* output,const char* input,const char* newmain, const char* newslice,string indice);
uint GenerateCompCpuFile(string input,string output,string includeListe[], string componentListe[]);
void ReadCompositionFile(char * compositionfile);
void ChangeAffinity(string Oldcompositionfile, string Newcompositionfile,string component,uint NewAffinity);
void FindAndReplaceAffinity(string Oldcompositionfile, string Newcompositionfile,string component,uint OldAffinity,uint NewAffinity);

#endif