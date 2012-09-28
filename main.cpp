

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <list>
#include <utility>
#include <algorithm>
#include <vector>


#include "fonctionsUtils.h"
#include "generatefile.h"
#include "utils.h"
#include "regularisation.h"
#include "regression.h"
#define NbBoucle 1

using namespace std;

extern COMPONENTDSP thisComposantsDSP;
extern COMPONENTCPU thisComposantsCPU;
extern CPU thisMesCPU;
extern GROUP_TBC GroupAffinity;


extern uint TSIZE;
extern double TableTBC[100];
extern uint nbTBC;
char **_argv;
extern double LoadMax;
extern double LoadMin;
extern list <pair < string,double> > selected_connections;
extern list < pair < string,double > > max_time_connections;
/**
 * Main.cpp
 * on verifie d'abord le nombre d'arguments d'exécution, 
 * puis on extraire les datas : comme le  cpulaodMAX/MIN, le nom des connections ainsi que leur durée
 * 
 * Exemple de ligne de commande d'exécution : 
 * la première avec de contrainte de temps pour les connections des slice 1 et 2 
 * et la seconde commande est sans contrainte de temps
 * 			./test_cpu_exploration.exe DSE comparaison_imx/  compositionarchi2.txt composition_filter2.txt cpuloadfile 80 90 cnx_slice1 20 cnx_slice2 20 
 *			./test_cpu_exploration.exe DSE inputfile3/  compositionarchi.txt composition.txt  cpuloadfile 80 90

 * 
 * dans ce programme   les list selected_connections et max_time_connections sont utilisées dans la fonction setCpuLoadLevel(...)  qui est la fonction d'exploration d'architecture
 * 
 * les etapes : 
 * 1) recupération des arguments d'exécution : deux cas peuvent être demandés soit avec contrainte temps réel ou sans. 
 * 2) lecture du fichier de l'architecture matérielle et calcul du nombre de cpu de l'architecture
 * 3) copie de la configuration logicielle, une copie du nom composition_copie.txt est créée
 * 4) lancement de l'exploration
 * 5) ecriture de l'histogramme de l'exploration 
 * 6)et compute_regression("consoleak.txt") : calcul des coefficients des équation de consommation (à finir ce modele /  à completer)
 * */

int main (int argc,char* argv[])
{
  uint nb_cpu, numerodossier=0;
  string includeListe[TSIZE], componentListe[TSIZE],tmp;    
  cpu *cpu_tmp=NULL,*cpu_nb=NULL,*access_cpu=NULL;
  G_TBC_InitListe(&GroupAffinity);
  time_t start,end;
  char szInput [256];
  double dif; 
    if (argc >= 8 && strcmp(argv[1],"DSE")==0)
    {  
	_argv =argv;
	if(argc==8)
	{
	tmp =  argv[argc-1];
        LoadMax=atof(tmp.c_str()); 
	tmp =  argv[argc-2];
	LoadMin=atof(tmp.c_str());   
	}
	else
	{
	  if(!(argc%2))
	  {
	    
	    tmp =  argv[7];
	    LoadMax=atof(tmp.c_str()); 
	    tmp =  argv[6];
	    LoadMin=atof(tmp.c_str());
	    for(int i=0;i+8<argc;)
	    {
	      tmp = argv[i+9];	   
	      selected_connections.push_back(pair < string, double >(string(argv[i+8]),double(atof(tmp.c_str()))));
	      i+=2;
	    }
	  }
	  else { cout<<"manque d'arguments  "<<endl ;  goto  here; }
	  
	}
	time (&start);
	tmp = string(argv[2])+string(argv[3]);
	ReadCompositionFile(tmp);			/// lecture du fichier de l'architecture matérielle exemple : comparaison_imx:compositionarchi2.txt
  	nb_cpu=NB_CPU(CloneCPU(thisMesCPU));		/// calcul du nombre de cpu
	tmp = string(argv[2])+string(argv[4]);
	CopieCompositionFile(tmp.c_str(),argv[2]);	///copie du fichier composition.txt en composition_copie.txt, on pourra travailler dessus
	
	cout<<"LoadMin :"<<LoadMin<<endl<<"LoadMax :"<<LoadMax<<endl;
	numerodossier = numerodossier+ setCpuLoadLevel(CloneCPU(thisMesCPU),nb_cpu,includeListe,componentListe,numerodossier);/// demande de lancer l'exploration
	GenScriptHistogram(nb_cpu ); /// ecriture de l'histogramme de l'exploration
	time (&end);
	cout<<"Elapsed time process : " << int(difftime(end,start))/60 <<" min "<<int(difftime(end,start))%60<<" sec.\n";
	
	for (list < pair < string, double > >::iterator iter = max_time_connections.begin(); iter != max_time_connections.end(); iter++) 
	{
	   cout<<"max time for " <<iter->first<< ": "<<iter->second<<" ms "<<endl;
	}
  	double coeff[3];
  	affiche_regression(compute_regression("consoleak.txt"));

    }
    else 
    {
 here:     cout<< "usage :\n<./executable> < DSE >   < folder_component_name/ > < Description_Architecture_file.txt> < Description_composition.txt> < cpuloadfile> <LoadMin>  <LoadMax> [<cnx_1> <value1>  <cnx_2> <value2> ......] "<<endl;
  
	exit(0);
    }
        
        
        return 0;
}


