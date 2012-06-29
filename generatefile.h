
#ifndef DEF_GENERATEFILE
#define DEF_GENERATEFILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <cstdlib>
#include "fonctionsUtils.h"
#include "regularisation.h"


using namespace std;


typedef struct Liste_TBC{
string name;
uint affinity;
float valeur;

struct Liste_TBC *next;
}Liste_TBC;
typedef Liste_TBC *LISTE_TBC;



bool TBC_estVide(LISTE_TBC L);
void TBC_Afficher(LISTE_TBC L);
void TBC_InitListe(LISTE_TBC *L);
void TBC_Ajouter(LISTE_TBC *L, string name,uint affinity,float valeur);
void TBC_Trier(LISTE_TBC *L);
LISTE_TBC CloneListeTBC(LISTE_TBC mon_tbc);

	

void GenerateCpuFile(string output,string input,CPU C,string name,string S1, string S2,string S3);
void GenerateDspFile(char *output,string input, COMPONENTDSP C);
void GenerateCompositionFile(const char* output,const char* input,const char* newmain, const char* newslice,string indice);
uint GenerateCompCpuFile(string input,string output,string includeListe[], string componentListe[]);
void ReadCompositionFile(char * compositionfile);
void ChangeAffinity(string compositionfile, string compositionfile_temp,string component,uint NewAffinity);
int getAffinityOf(string inputfile, string componentname);
void FindAndReplaceAffinity(string compositionfile, string compositionfile_temp,uint OldAffinity,uint NewAffinity);
void RegenerateCpuFile(CPU MesCPU,string includeListe[], string componentListe[], uint nb_component);

#endif
