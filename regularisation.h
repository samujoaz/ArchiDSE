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
/* CETTE METHODE N'EST PLUS UTILIS�E */
enum {IS_HYPER_LOW,IS_LOW, IS_MEDIUM,IS_HIGH,IS_HYPER_HIGH};
enum {SEQUENTIEL,MIXTE};
enum {TYPE1,TYPE2,TYPE3,TYPE4};/// pour le type d'algo qu'on choisira!
/**
 * on pensera a ajouter un niveau interm�diaire pour le getSpeedTickTimer (IS_LOW, IS_MEDIUM,IS_HIGH)/// pas encore impl�menter
 * TYPE1 algo sequentiel + upFreq(100) car il n'y a pas beaucoup de (Slice, filter...)  et la vitesse du tickTimer est faible
 * TYPE2 algo sequentiel + upFreq(50) car il n'y a pas beaucoup de (Slice, filter...)  et la vitesse du tickTimer est �leve
 * TYPE1 algo MIxte (partie parall�le) + NBMaxCpu moyen upFre(50) car il y a beaucoup de (Slice, filter...)  et la vitesse du tickTimer est faible/moyen
 * TYPE1 algo MIxte (partie parall�le) + NBMaxCpu grand upFre(100) car il y a beaucoup de (Slice, filter...)  et la vitesse du tickTimer est haut
 * 
 * */
using namespace std;
/**
 * * fonction de sortie d'ex�cution du programme en mode debug
 * */
void e();

/**
 * pour chercher une chaine de caracter� dans une liste de chaine de caract�re 
 * retour true si la chaine n'est pas trouv�e et false si elle s'y trouve
 * */
bool notFindName(string listename[] ,string index,int taille);
/**
 * pour savoir si une valeur (type double) n'est pas comprise entre x et y
 * retour false si elle comprise entre x et y 
 * et true sinon
 * 
 * */
bool notComprisEntre(double valeur,double x, double y);

uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num);

/**
 * N'est plus utilis�: 
 * permettait de savoir quelle fr�quene de traitement avait le fichier de composition allait lire ce type de ligne avec timer: 
 * onfiguration t1->configure_timerspec_and_sched_fifo( 0, 100000, 0, 30000000, true, 10 );

 * */
int getSpeedTickTimer(string intput);


#endif