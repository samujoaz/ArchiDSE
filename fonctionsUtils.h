
#ifndef DEF_FONCTIONUTILS
#define DEF_FONCTIONUTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

/// structure des CPU
typedef struct cpu{
  string name_cpu;
  uint start_frequency;
  uint work_frequency;
  uint end_frequency;
  float dmips;
  uint pipeline;
  uint indice_cache_L1;
  uint indice_CPU;
  struct cpu *next;
  }cpu;
typedef cpu *CPU;

/// structure des CACHES
typedef struct cache{
  uint taille;
  uint associativity;
  uint bpl;
  string namelink;
  struct cache *next;
  }cache;
typedef cache *CACHE;

/// structure des DSP
typedef struct dsp{
  string name_dsp;
  uint start_frequency;
  uint work_frequency;
  uint end_frequency;
  float dmips;
  uint pipeline;
  uint indice_cache_L1;
  uint indice_DSP;
  struct dsp *next;
}dsp;
typedef dsp *DSP;

typedef struct componentcpu{
  CPU CPU_;
  CACHE L1_;
  CACHE L2_;
  struct componentcpu *next;
}componentcpu; 
typedef componentcpu *COMPONENTCPU;

typedef struct componentdsp{
  DSP DSP_;
  CACHE L1_;
  CACHE L2_;
  struct componentdsp *next;
}componentdsp; 
typedef componentdsp *COMPONENTDSP;


CPU ADD_CPU(CPU mon_cpu, string name,uint freq);
DSP ADD_DSP(DSP mon_dsp, string name,uint freq);
CACHE ADD_CACHE(CACHE ma_cache,uint taille, uint assoc, uint bpl);
COMPONENTCPU ADD_COMPONENTCPU(COMPONENTCPU my_component,CPU mon_cpu,CACHE ma_cache,uint indice_cache,uint indice_cpu, string link);
COMPONENTDSP ADD_COMPONENTDSP(COMPONENTDSP my_component,DSP mon_dsp,CACHE ma_cache, uint indice_cache,uint indice_dsp, string link);
void ADD_CACHE_L2_TO_COMPONENTCPU(COMPONENTCPU my_component,CACHE L2);
void ADD_CACHE_L2_TO_COMPONENTDSP(COMPONENTDSP my_component,CACHE L2);
string GetNamelinkCache(CACHE ma_cache);
uint GetLinkCacheL1DSP(COMPONENTDSP my_component, uint indice);
uint GetLinkCacheL1CPU(COMPONENTCPU my_component, uint indice);

CPU AccessToCPU(CPU mon_cpu, uint indice);
DSP AccessToDSP(DSP mon_dsp, uint indice);
CACHE AccessToCACHE(CACHE ma_cache, uint indice);
COMPONENTCPU AccessToCOMPONENTCPU(COMPONENTCPU my_component, uint indice);
COMPONENTDSP AccessToCOMPONENTDSP(COMPONENTDSP my_component, uint indice);

/// nombre d'�l�ments
int NB_CPU(CPU A);
int NB_DSP(DSP A);
int NB_CACHE(CACHE A);
int NB_COMPONENTCPU(COMPONENTCPU A);
int NB_COMPONENTDSP(COMPONENTDSP A);

/// pour les affichages 
void Affiche_CPU(CPU A);
void Affiche_DSP(CPU A);
void Affiche_CACHE(CPU A);
void Affiche_COMPONENTDSP(COMPONENTDSP A);
void Affiche_COMPONENTCPU(COMPONENTCPU A);





#endif