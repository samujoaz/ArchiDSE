
#ifndef DEF_GENERATEFILE
#define DEF_GENERATEFILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "fonctionsUtils.h"
#include "regularisation.h"


using namespace std;

enum {AFF_FIXE,AFF_VAR,AFF_GROUP};

/** structure opour contenir les caractéristique des affinités.
* le nom des connections, le type d'affinité, sa valeur, le nombre d'entrée du composant qui cette affinité....
* */
typedef struct Group_TBC{
  int nb_input;  
  int *affinity;
  string *TypeAff; ///ex  type : char
  string include_name;
  string *input_name;
  string *component_name;
  string *cnx_name;
  struct Group_TBC *next;
}Group_TBC;
typedef Group_TBC *GROUP_TBC;

bool findnotint(int *list, int index, int taille);
bool G_TBC_estVide(GROUP_TBC L);
void G_TBC_Afficher(GROUP_TBC L);
void G_TBC_InitListe(GROUP_TBC *L);
void G_TBC_Ajouter(GROUP_TBC *L,int nb_input,int *Liste_affinity,string include_name,string *input_name, string *component_name, string *cnx_name,string  *typeAff);
GROUP_TBC CloneG_TBC(GROUP_TBC mon_tbc);


void FindGroupCpuFix(GROUP_TBC Liste, int Group_Aff[], int *taille);
void FindSimilarGroup(GROUP_TBC Liste, string Type, string Group_cnxname[], int *taille);
void CalculTBC(GROUP_TBC Liste, CPU MesCPU);
void GenerateCpuFileMultiInput(string output,string input,CPU MesCPU,GROUP_TBC Liste,char *indice);
int  getValAffinity(string x); //ex char
void GenerateCpuFile(string output,string input,CPU C,char *indice);
void GenerateDspFile(char *output,string input, COMPONENTDSP C);
void GenerateCompositionFile(const char* output,const char* input,const char* newmain, const char* newslice,string indice);
void GenerateCompCpuFile(string input,string output,string includeListe[], string componentListe[], uint* N_affinity,uint* NB_COMPONENT);
void ReadCompositionFile(string compositionfile);
void ChangeAffinity(string compositionfile, string compositionfile_temp,string component,uint NewAffinity);
int  getAffinityOf(string inputfile, string componentname);
void FindAndReplaceOneAffinity(string compositionfile, string compositionfile_temp,uint OldAffinity,uint NewAffinity);
void FindAndReplaceAffinity(string compositionfile, string compositionfile_temp,uint OldAffinity,uint NewAffinity);

#endif