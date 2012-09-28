#ifndef DEF_UTILS
#define DEF_UTILS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "fonctionsUtils.h"
#include "generatefile.h"

using namespace std;

/**
 * Pour Diminuer la fr�quence d'un cpu de la valeur de delta
 * */
void DownFreqCpu(CPU C, uint delta);

/**
 * Pour Augmenter la fr�quence d'un cpu de la valeur de delta
 * */
void UpFreqCpu(CPU C, uint delta);
/**
 * Pour avoir le taux de chargement de tout les cpu lors de l'ex�cution de la trace
 * uint nb_cpu, le nombre de cpu que comporte l'architecture 
 * int numerodossier, le num�ro de l'it�ration 
 * double cpuload[], pointeur dans laquelle on stockera les cpuload calcul�s par la trace
 * int frequence[] : les frequences de fonctionnement des cpu.
 * */
void getAllCpuLoad(uint nb_cpu, int numerodossier,double cpuload[], int frequence[]) ;
/**
 * Pour faire une copie d'un fichier le premier parametre est le fichier txt � copier et le second le dossier dans lequel 
 * la copie du fichier sera cr�er. le fichier copie aura une extension "_copie.txt"
 * */
void CopieCompositionFile(string file, string destination);
/**
 * pour trier de mami�re croissante les valeurs contenu dans un tableau, n repr�sente la taille du tableau � trier
 * */
void tri_bulle( double *tab, int n);
/**
 * Pour les affichages du tri
 * */
void afficheTBC( double * tab, int longeur);
/**
 * calcul des min et max des cpuload et on a aussi un pointeur  sur les indices des valeurs mix et max
 * excpt[] se sont les valeurs qu'on ne veut pas prendre en compte dans le calcul du min et max 
 * */
void getMinMaxCpuLoad(double cpuload[], uint except[], uint nb_cpu, uint nb_except, double *Max, double *Min, uint *indice_cpuMax, uint *indice_cpuMin);
/**
 * Pour avoir une histogramme de l'exploration  les deux fonctions ci-dessous  permettent de creer un fichier gnuplot 
 * et un fichier data necessaire pour l'histogramme (hist_all_archi.gnu  et all_cpu_hist.dat)
 * */
void write_Data_histogram(double cpuload[], int nb_cpu);
void GenScriptHistogram(uint nb_cpu);

/// focntion d'affichage pour debug 
void coucou();

#endif