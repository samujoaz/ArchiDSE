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
enum {IS_HYPER_LOW,IS_LOW, IS_MEDIUM,IS_HIGH,IS_HYPER_HIGH};
enum {SEQUENTIEL,MIXTE};
enum {TYPE1,TYPE2,TYPE3,TYPE4};/// pour le type d'algo qu'on choisira!
/**
 * on pensera a ajouter un niveau intermédiaire pour le getSpeedTickTimer (IS_LOW, IS_MEDIUM,IS_HIGH)/// pas encore implémenter
 * TYPE1 algo sequentiel + upFreq(100) car il n'y a pas beaucoup de (Slice, filter...)  et la vitesse du tickTimer est faible
 * TYPE2 algo sequentiel + upFreq(50) car il n'y a pas beaucoup de (Slice, filter...)  et la vitesse du tickTimer est éleve
 * TYPE1 algo MIxte (partie parallèle) + NBMaxCpu moyen upFre(50) car il y a beaucoup de (Slice, filter...)  et la vitesse du tickTimer est faible/moyen
 * TYPE1 algo MIxte (partie parallèle) + NBMaxCpu grand upFre(100) car il y a beaucoup de (Slice, filter...)  et la vitesse du tickTimer est haut
 * 
 * */
using namespace std;

bool notFindName(string listename[] ,string index,int taille);
bool notComprisEntre(float valeur,float x, float y);
uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num);
int getSpeedTickTimer(string intput);
bool ComprisEntre(float valeur,float x, float y);


#endif