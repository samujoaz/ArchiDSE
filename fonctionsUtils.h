
#ifndef DEF_FONCTIONUTILS
#define DEF_FONCTIONUTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

/**
 *      Déclarations des différentes strucutres des listes chainées
 **/

/// structure des CPU et ses caractéristiques
typedef struct cpu{
  string name_cpu;
  uint start_frequency;
  uint work_frequency;
  uint end_frequency;
  double dmips;
  uint pipeline;
  uint indice_cache_L1;
  uint indice_CPU;
  struct cpu *next;
  }cpu;
typedef cpu *CPU;

/// structure des CACHES et ses caractéristiques
typedef struct cache{
  uint taille;
  uint associativity;
  uint bpl;
  uint indice_cache;
  string namelink;
  struct cache *next;
  }cache;
typedef cache *CACHE;

/// structure des DSP : et ses caractéristiques
typedef struct dsp{
  string name_dsp;
  uint start_frequency;
  uint work_frequency;
  uint end_frequency;
  double dmips;
  uint pipeline;
  uint indice_cache_L1;
  uint indice_DSP;
  struct dsp *next;
}dsp;
typedef dsp *DSP;
/// structure component: on peut y mettre  des cpu et leurs caches
/// avec ce type de structure, on part du principe qu'on veut creer une liste d'architecture/plate-forme
typedef struct componentcpu{
  CPU CPU_;
  CACHE L1_;
  CACHE L2_;
  struct componentcpu *next;
}componentcpu; 
typedef componentcpu *COMPONENTCPU;

/// pareil que la structure componentcpu mais ici c'est le cas des dsp
typedef struct componentdsp{
  DSP DSP_;
  CACHE L1_;
  CACHE L2_;
  struct componentdsp *next;
}componentdsp; 
typedef componentdsp *COMPONENTDSP;

/**
 *       Fonctions utiles pour les CACHES
 **/
/// pour trouver une cache en fonction de son indice
CACHE FindCACHE(CACHE mon_cache, uint indice);
CACHE AccessToCACHE(CACHE ma_cache, uint indice);
/// avoir le lien de connection d'une cache avec un autre composant
string GetNamelinkCache(CACHE ma_cache);

CACHE ADD_CACHE(CACHE ma_cache,uint taille, uint bpl, uint assoc,uint indice);

/**
 *       Fonctions utiles pour les CPU
 **/
/// pour ajouter en queue de la liste un nouveau élément type CPU
CPU ADD_CPU(CPU mon_cpu, string name,uint freq, uint indice);
///pour éviter d'écraser des valeurs ou d'en modifier nous clonons les éléments des listes chainées
CPU CloneCPU(CPU mon_cpu);
/// pour acceder au cpu via son indice
CPU FindCPU(CPU mon_cpu, uint indice);
/// pour avoir le lien entre un cpu et sa cache L1 via une archi en cours de creation 
uint GetLinkCacheL1CPU(COMPONENTCPU my_component, uint indice);
/// avoir acces au cpu indicer: indice
CPU AccessToCPU(CPU mon_cpu, uint indice);
/// pour pouvoir modifier la fréquence d'un cpu: 
///on passe en paramètre la le cpu en question, puis la nouvelle fréquence qu'on désire pour ce dernier.
void SetWorkFrequencyCPU(CPU mon_cpu, uint new_freq);
/// pour eefacer la liste de cpu en mémoire.
void DeleteCPUList(CPU mon_cpu);
/// trouver une archi en fonction de son indice
COMPONENTCPU AccessToCOMPONENTCPU(COMPONENTCPU my_component, uint indice);
/// pour ajouter une nouvelle architecture comportant un cpu, une cache L1, et le lien de connection de la cache et le cpu
COMPONENTCPU ADD_COMPONENTCPU(COMPONENTCPU my_component,CPU mon_cpu,CACHE ma_cache,uint indice_cache,uint indice_cpu, string link);
/// pour ajouter une cache L2 au une architecture déjà existante
void ADD_CACHE_L2_TO_COMPONENTCPU(COMPONENTCPU my_component,CACHE L2);


/**
 *  Fonctions utiles pour les DSP
**/

DSP FindDSP(DSP mon_dsp, uint indice);
DSP ADD_DSP(DSP mon_dsp, string name,uint freq, uint indice);
COMPONENTDSP ADD_COMPONENTDSP(COMPONENTDSP my_component,DSP mon_dsp,CACHE ma_cache, uint indice_cache,uint indice_dsp, string link);
void ADD_CACHE_L2_TO_COMPONENTDSP(COMPONENTDSP my_component,CACHE L2);
uint GetLinkCacheL1DSP(COMPONENTDSP my_component, uint indice);
DSP AccessToDSP(DSP mon_dsp, uint indice);
COMPONENTDSP AccessToCOMPONENTDSP(COMPONENTDSP my_component, uint indice);


/**
 *       Fonctions utiles pour les comptes
 **/
/// Pour savoir le nombres (d'éléments) de conmposants que conporte l'architecture. 
int NB_CPU(CPU A); 			/// pour savoir le  nombre de cpu
int NB_DSP(DSP A);			/// pour savoir le nombre de dsp
int NB_CACHE(CACHE A);			/// pour savoir le nombre de cache 
					///( attention il existe deux types de caches il faut bien penser a ce qu'on passe a cette fonction  cache L1 ou L2)

int NB_COMPONENTCPU(COMPONENTCPU A);	///le nombre d'architectures avec des cpu qu'on a créé
int NB_COMPONENTDSP(COMPONENTDSP A);	///le nombre d'architectures avec des dsp qu'on a créé


/**
 *       Fonctions utiles pour les affichages 
 **/
/// pour l'affichage des caractéristiques de la liste des: cpu, dsp, cache L1/L2 et des archi.
void Affiche_CPU(CPU A);
void Affiche_DSP(DSP A);
void Affiche_CACHE(CACHE A);
void Affiche_COMPONENTDSP(COMPONENTDSP A);
void Affiche_COMPONENTCPU(COMPONENTCPU A);





#endif