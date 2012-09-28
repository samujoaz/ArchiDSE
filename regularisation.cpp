



#include "regularisation.h"
#include <time.h>
#include <list>
#include <map>
#include <sstream>

#define iterMax 40
#define  LIMIT 7

extern CPU thisMesCPU;
extern GROUP_TBC GroupAffinity;
extern uint TSIZE;
double LoadMax;
double LoadMin;
double MinTolere =30.0;
list < pair < string,double > > selected_connections;
list < pair < string,double > > max_time_connections;
extern bool once;
extern char **_argv;

struct myclass {
  bool operator() (double i,double j) { return (i<j);}
} mysort;


bool notFindName(string listename[] ,string index,int taille)
{
  
for(int i=0;i<taille;i++)
{
      if((listename[i].compare(index))==0)
      {
      return false;
      }
  }
  return true;
}
bool notComprisEntre(double valeur,double x, double y)
{
  if((valeur>=x && valeur<=y))
    return false;
  return true;
}


void e(){coucou();cout<<endl<<"Program under construction..... "<<endl;exit(0);}///meilleure fonction d'exit() \o/

/**
 * uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num)
 * esl la fonction qui fait l'exploration des architectures
 * Etapes : 
 * 1) on calcul le nombre de cpu qu'il faut mettre en parallèle (SIZE_MIXTE) 
 * 2)augmentaation de la frequence de tous les cpu en dessous de 200MHz
 * 3)on place sur les differents processeurs les threads parallèles ( en même temps) avant de faire une trace et de regarder le cpuload. 
 * 4) ensuite on regarde les cpuloads de tous les processeurs. s'il reste encore des threads a placer on les met sur les cpu dont les taux de chargement est inferieur à la borne minimum
 * qu'on s'est fixé. sinon on chage de processeur ou bien on augmente la fréquence. 
 * 5)un fois le boucle et la repartition des threads sont terminés on on verifie cpu par cpu le taux de chargement pis la durée des connections.
 * */
uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num)
{
  uint i=0,j=0,o,nb_component=0,nb_affinity =0,numerodossier,indice=0,offset_frequence;
  int frequence[nb_cpu],NbThread,NbMaxCpu,TYPE=509,SIZE_MIXTE=0,SIZE_RESTE=0, max,nb_priority;
  char str_indice[100];
  double cpuload_cur[nb_cpu];
  double MaxCpuload,MinCpuload, tabcpuload[nb_cpu-1];
  uint indice_cpuMax, indice_cpuMin;
  bool sortie=true,quit=true;
  bool stop =true;
  string Group_cnxname[TSIZE]; 
  int taille,Group_Aff[TSIZE];
  string compositionfile="composition.txt", composition_copie=string(_argv[2])+"composition_copie.txt",compositionfile_temp="composition_temp.txt";
  CPU cpu_tmp=NULL,cpu_access=NULL;

  ///  on fait deux clone de la liste cpu une pour la convergence(while(nb_element) !=NUL) et l'autre pour le parcours et la research des caractéristiques des cpu
  /// le clonage permet aux nouvelles listes d'avoir une adresse propre les deux seront indépendantes
  GROUP_TBC ListOuvert=NULL,ListFerme=NULL;
  /// init variables 
  cpu_tmp = CloneCPU(MesCPU);
  cpu_access=CloneCPU(MesCPU);
  
  once=true;/// c'est une variable globale à ce fichier et à generatefile.cpp once permet de faire une boucle une seule  une des boucles dans GenerateCompCpuFile(...)
  /// cette boucle en question doit remplir la liste des TBC qui corespond au nombres de threads et ses caractéristiques (nom, affinity, cnx_name...)
  GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
//    for (int u=0; u<nb_component;u++) cout <<componentListe[u]<<endl;
 
  once=false;

  ListOuvert=CloneG_TBC(GroupAffinity);/// pour le bouclage et la condition de fin de boucle 
  ListFerme =CloneG_TBC(GroupAffinity);/// pour le calcul et la génération des fichiers avec  TBC. 
// CalculTBC(ListFerme, cpu_access);
// G_TBC_Afficher(GroupAffinity); e();
  NbThread = nb_component;
  numerodossier=num; /// pour les itérations

/**
 * Calcul du taux de paralélisme : nombre de cou à mettre en parallèle.
 * */
  if( nb_cpu <=4 || NbThread <LIMIT )
  {

      SIZE_MIXTE=NbThread/nb_cpu;
      NbMaxCpu=nb_cpu;
  }
  else
  { 
    if(nb_cpu>4 && nb_cpu<6)
    {
      SIZE_MIXTE=(NbThread/nb_cpu)/2;
      NbMaxCpu=nb_cpu-1;
      
    }
     else
    {
        if(nb_cpu>=6)
    {
      SIZE_MIXTE=NbThread/2;
      NbMaxCpu=nb_cpu-1;
    }
    }
  }
  
  
/// augmentation des fréquences inférieurs à 200 MHz
	offset_frequence=100;
	for(i=0; i<nb_cpu ;i++) /// copie des frequences des cpu pour l'écriture  dans les fichiers de sortie
	{
	    if(cpu_tmp->work_frequency<200)
	    {
		SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+ offset_frequence);
		AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
	    }

	    frequence[i]=cpu_tmp->work_frequency;/// pour pouvoir écrire dans le fichier histoiric.txt la fréquence des cpu lors des tests des architectures
	    cpu_tmp=cpu_tmp->next;
	}
	i=0;j=1;
	CalculTBC(ListFerme, cpu_access);
	
// 	cpuload_cur[0]=90;
	//getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
//        if(cpuload_cur[0]<LoadMax){cout<<"cpuLoad_"<<0<<" < "MinTolere<<LoadMax<<endl;return numerodossier; }
	/// on va charger l'affinity de NbMaxCpu en parallèle 
	///et le reste se fera de façon sequentielle s'il reste encore des  threads

	for(uint t=0;t<SIZE_MIXTE && ListOuvert !=NULL;t++)
	{
	    for(indice=0;indice<NbMaxCpu && ListOuvert !=NULL;indice++)
	    {   
	      for(uint X=0; X<ListOuvert->nb_input;X++)/// nombre de branchement par composant (generator, snk...)
	      {
		  if(getValAffinity(ListOuvert->TypeAff[X])==AFF_GROUP && ListOuvert->affinity[X]==0)/// pour les affinité en Groupe : type( A,B,C,....Z)
		  {
		    FindSimilarGroup(ListFerme, ListOuvert->TypeAff[X], Group_cnxname, &taille); 
		    for( int p=0; p<taille;p++)
		    {
		      ChangeAffinity(composition_copie,compositionfile_temp,Group_cnxname[p],indice);
		      ListOuvert->affinity[p]=indice;
		    }
		  }
		  else
		  {
		    if(getValAffinity(ListOuvert->TypeAff[X])==AFF_VAR && ListOuvert->affinity[X]==0)
		    {
		      ChangeAffinity(composition_copie,compositionfile_temp,ListOuvert->cnx_name[X],indice);
		      ListOuvert->affinity[X]=indice;
		      
		    }
		  }
	      }
		ListOuvert=ListOuvert->next;
	    }
	}
	
	GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);/// exécution de la première trace 
	indice=0;
	cpu_tmp = AccessToCPU(cpu_access,indice);/// on se place sur le premier processeur
// 	 
	/// fin de la partie parallèle on regarde d'abord s'il n'y plus de threads dans notre liste !
	if(ListOuvert==NULL)/// si liste vide 
	{
	    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	    /// maintenant on va vérifier les cas où le cpu_0  a un chargement inférieur à MinTolere
	    for(i=0;i<nb_cpu-1;i++) { tabcpuload[i]=cpuload_cur[i+1];}
	    getMinMaxCpuLoad( tabcpuload,NULL,nb_cpu-1,  0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin); /// recherche min et max  
	    if(cpuload_cur[0]<MinTolere)
	    {
		cpu_tmp=AccessToCPU(cpu_access,0);
		FindAndReplaceAffinity(composition_copie,compositionfile_temp,indice_cpuMin+1,0);
		GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
		CalculTBC(ListFerme, cpu_tmp);
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	    }


	}	    
	else	/// sinon on sait que la liste des threads n'est pas encore vide !
	    {
	    indice=1;
	    sortie = true;
	    while(ListOuvert !=NULL && indice<nb_cpu &&  cpuload_cur[0]>LoadMax )/// tant que la liste n'est pas vide ou bien  qu'on au cpu_0 >LoadMax
		{
		 
		    if(sortie)
		    {
			getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence); sortie=false;	 
		    }
		    for(i=0; i<nb_cpu;i++)/// augementation de la fréquence de tous les cpu dont le cpuload_cur[]>LoadMax 80.0
		    {
			cpu_tmp = AccessToCPU(cpu_access,i);
			if(cpuload_cur[i]>LoadMax)
			{
			   if(cpuload_cur[i]>LoadMax+5.0) offset_frequence =100;
			   else offset_frequence =50;
			    SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+offset_frequence); 
			    AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
			    CalculTBC(ListFerme, cpu_access);
			    sortie=true;
			}
			frequence[i]=cpu_tmp->work_frequency;
		    }

		    if(sortie) 
		    {
			getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence); sortie=false;	 
		    }
		    if(cpuload_cur[indice]<LoadMin  && ListOuvert!=NULL  &&  cpuload_cur[0]>LoadMax ) ///si le cpu courant n'est pas assez chargé on lui rajoute des threads
		    {
			for(uint X=0; X<ListOuvert->nb_input;X++)
			{
			      if(getValAffinity(ListOuvert->TypeAff[X])==AFF_GROUP && ListOuvert->affinity[X]==0)/// pour les affinité en Groupe : type( A,B,C,....Z)
			      {
				FindSimilarGroup(ListFerme, ListOuvert->TypeAff[X], Group_cnxname, &taille); 
				for( int p=0; p<taille;p++)
				{
				  ChangeAffinity(composition_copie,compositionfile_temp,Group_cnxname[p],indice);
				  ListOuvert->affinity[p]=indice;
				}
			      }
			      else
			      {
				if(getValAffinity(ListOuvert->TypeAff[X])==AFF_VAR && ListOuvert->affinity[X]==0)
				{
				  ChangeAffinity(composition_copie,compositionfile_temp,ListOuvert->cnx_name[X],indice);
				  ListOuvert->affinity[X]=indice;
				}
			      }
			}
			GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
			ListOuvert=ListOuvert->next;
		    }
		    else
		    {
		     
// 			if (indice < nb_cpu)
			  indice++;
// 			else indice=0;
		    }

		}/// end while
	}/// end else
	
	while(ListOuvert!=NULL) /// par precaution on tester si on a vraiment vider la liste!
	{
	 for(indice=0;indice<nb_cpu && ListOuvert!=NULL;indice++)
	 {
	 for(uint X=0; X<ListOuvert->nb_input;X++)
	  {
		if(getValAffinity(ListOuvert->TypeAff[X])==AFF_GROUP )/// pour les affinité en Groupe : type( A,B,C,....Z)
		{
		  FindSimilarGroup(ListFerme, ListOuvert->TypeAff[X], Group_cnxname, &taille); 
		  for( int p=0; p<taille;p++)
		  {
		    ChangeAffinity(composition_copie,compositionfile_temp,Group_cnxname[p],indice);
		    ListOuvert->affinity[p]=indice;
		  }
		}
		else
		{
		  if(getValAffinity(ListOuvert->TypeAff[X])==AFF_VAR )
		  {
		    ChangeAffinity(composition_copie,compositionfile_temp,ListOuvert->cnx_name[X],indice);
		    ListOuvert->affinity[X]=indice;
		  }
		}
	  }
	  GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
	  ListOuvert=ListOuvert->next;
	 }
	}/// fin ListOvert toujours non vide
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	sortie = true;
	max=nb_cpu;
	
	while(max> 1 && numerodossier<iterMax-20 ) /// tant qu'il y en aura un cpuload superieur à CPULOADMAX  on augementera la fréquence 
	{	
	    for(indice=0; indice<nb_cpu ;indice++)/// on regardera tout les niveaux de chargement des CPU qui fonctionnent !
	    {
		if(cpuload_cur[indice]>LoadMax && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency))
		{
		    if(max<=nb_cpu+1) {max++;}
		    if(cpuload_cur[indice]>LoadMax+5.0) offset_frequence =100;
		    else offset_frequence =50;
		    cpu_tmp =AccessToCPU(cpu_access,indice);
		    SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+offset_frequence);
		    frequence[indice]=cpu_tmp->work_frequency;
		    AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
		    CalculTBC(ListFerme, cpu_access);
		}
		else
		{
		    if(cpuload_cur[indice]<LoadMin && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency) )
		    {

			if(max<=nb_cpu+1) {max++;}
			if(cpuload_cur[indice]<LoadMin-5.0) offset_frequence =50;
			else offset_frequence =25;
			cpu_tmp =AccessToCPU(cpu_access,indice);
			SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-offset_frequence);
			frequence[indice]=cpu_tmp->work_frequency;
			AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
			CalculTBC(ListFerme, cpu_access);

		    }
		    else
			if(max>1){ max--; }
		}
	    }
	    
	   if(max>1)///0
	    {
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		max--;
	    }
	}

	/// s'il y a un cpu qui dépasse la limite on enlève un threads puis un autre s'il le faut pour le mettre sur celui qui est le moins charger

 coucou();

  for(i=0;i<nb_cpu;i++) {  tabcpuload[i]=cpuload_cur[i];}
	getMinMaxCpuLoad( tabcpuload,NULL,nb_cpu,0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin); /// recherche min et max  
  /// pour le Max : on mettera sa frequence à moitiée  et distriburera certain de ses threads 
	if(MaxCpuload>(LoadMax+5.0) && MinCpuload<LoadMin-5.0)
	{	
	cpu_tmp =AccessToCPU(cpu_access,indice_cpuMax);
	SetWorkFrequencyCPU(cpu_tmp,(cpu_tmp->work_frequency)-200);
	frequence[indice_cpuMax]=cpu_tmp->work_frequency;
	AccessToCPU(cpu_access,indice_cpuMax)->work_frequency=cpu_tmp->work_frequency;
	  for(i=0;i<nb_cpu && cpuload_cur[indice_cpuMax]>(LoadMax+5.0) ;i++)
	  { 
	    if(i!=indice_cpuMax && cpuload_cur[indice_cpuMax]>(LoadMax+5.0) )
	    {
	      FindAndReplaceOneAffinity(composition_copie,compositionfile_temp,indice_cpuMax,i);
	      GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
	      
	    }
	    CalculTBC(ListFerme,cpu_access);
	    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	  }
	
	
	}
	
      sortie=true;
      for(indice=0; indice<nb_cpu && sortie;indice++) 
      {
	if(cpuload_cur[indice]<=MinTolere){ sortie = false;i=indice;}/// pour les cpu qui ont un taux de chargement trop bas <= 30; ici
      }
      
      indice=i;
      if(!sortie)
      {
	while(cpuload_cur[indice]>0.0)
	{
		for(i=0;i<nb_cpu ;i++)
		{
		  if(i!=indice)
		  {
		    FindAndReplaceOneAffinity(composition_copie,compositionfile_temp,indice,i);
		    GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
		    
		  }
		  
		}
		CalculTBC(ListFerme,cpu_access);
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	}
      }

/**
 * Regularisation de niveau de chargement cpu par cpu
 * */
  for(indice=0;indice<nb_cpu && numerodossier<iterMax-10;indice++) 
	 { 
		if(cpuload_cur[indice]>LoadMax && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency))
		  {
		      if(cpuload_cur[indice]>LoadMax+5.0) offset_frequence =50;
			else offset_frequence =25;
		      cpu_tmp =AccessToCPU(cpu_access,indice);
		      SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+offset_frequence);
		      frequence[indice]=cpu_tmp->work_frequency;
		      AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
		      CalculTBC(ListFerme, cpu_access);
		      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);

		  }
		  else
		  {
		      if(cpuload_cur[indice]<LoadMin && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
		      {
			if(cpuload_cur[indice]<LoadMin-5.0) offset_frequence =50;
			else offset_frequence =25;
			  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-offset_frequence);
			  frequence[indice]=cpu_tmp->work_frequency;
			  AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
			  CalculTBC(ListFerme, cpu_access);
			  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		      }
		    
		  }
	   
	  }
	/// ce cas est fait s'il n'y a pas de contrainte  de temps : on fixe tout les cpu entre les bornes.
  for(indice=0;indice<nb_cpu && numerodossier<iterMax-10 && sortie && selected_connections.empty();indice++) 
	 { 

	      while(notComprisEntre(cpuload_cur[indice],LoadMin,LoadMax) && numerodossier<iterMax-10 && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency) && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
	      {
		if(cpuload_cur[indice]>LoadMax && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency))
		  {
		    if(cpuload_cur[indice]>LoadMax+5.0) offset_frequence =50;
		    else offset_frequence =25;
		      SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+offset_frequence);
		      frequence[indice]=cpu_tmp->work_frequency;
		      AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
		      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);


		  }
		  else
		  {
		      if(cpuload_cur[indice]<LoadMin && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
		      {
			  if(cpuload_cur[indice]<LoadMin-5.0) offset_frequence =50;
			  else offset_frequence =25;
			  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-25);
			  frequence[indice]=cpu_tmp->work_frequency;
			  AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
			  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		      }
		    
		  }
	      }
	   
	  }

indice=0;
/// ICI ON NE FAIT QU'UNE DERNIERE VERIFICATION DES CPULOAD 

/// où l'on a mis des contraintes temps alors on verifies la durée des connections en parallèles 
/// on augmente la fréquence du cpu en question s'il s'y trouve des threads dont temps de connections est supérieur à la valeur fixée 

quit=true;
while(quit && !selected_connections.empty())
{
for (list < pair < string, double > >::iterator iter = selected_connections.begin(); iter != selected_connections.end()&& numerodossier<iterMax; iter++) 
	{
	  string cnx_name_dat = iter->first + ".dat";
	    cout<<cnx_name_dat<<endl;
	    ofstream cnx_dat(cnx_name_dat.c_str(),ios::app);
	  string name_file = iter->first;
	  
	  double value=0.0;
	  stop =true;
	  char folder[256];
	  sprintf(folder,"cpuloadfile%d/",numerodossier-1);
	  name_file=folder+name_file+".txt";
	  ifstream file_connections(name_file.c_str());
	  string save_name = name_file;
	  if (!file_connections) {
	    cerr << "File " << name_file << " does not exist" << endl;
	    exit(1);
	    }
	
	  while(file_connections>>value && stop && numerodossier<iterMax)
	  {
	    if(value>(iter->second-.5) && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency))
	    {
	      cnx_dat<<value<<endl;
	      name_file = iter->first;
	      stop=false;
	      /// substr; getaffinyof, upfreq cpu_x
	      name_file=name_file.substr(4,name_file.size());
	      indice = getAffinityOf(composition_copie,name_file); 
	      frequence[indice]=AccessToCPU(cpu_access,indice)->work_frequency+25;
	      AccessToCPU(cpu_access,indice)->work_frequency+=25;
	      quit = true;
	    }
	    }
	  if(stop)
	    {
	       ifstream file_connections2(save_name.c_str());
	      
		cnx_dat<<value<<endl;
	       list < double > mylist_to_sort;
	       while(file_connections2>>value) mylist_to_sort.push_back(value);
	       mylist_to_sort.sort();
	       max_time_connections.push_back(pair < string, double> (iter->first,mylist_to_sort.back()));
	      quit = false;
	     
	    } 
	}
	CalculTBC(ListFerme,cpu_access);
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
}


/// generation d'un fichier de visualisation des  de l'evolution de connections
	 ofstream cnx_max_gnu("cnx_all_max.gnu");
	 string mybuffer;
	 mybuffer.clear();
	for (list < pair < string, double > >::iterator iter = selected_connections.begin(); iter != selected_connections.end(); iter++) 
	{
 	  string name_file = iter->first ;ostringstream oss;
 	  oss << iter->second;
 	  mybuffer +=" '" + name_file +".dat' with linespoints ,  " +  oss.str() + " with lines title \"Max_" + name_file +"\", " ;
	 oss.str(""); oss.clear(); 
	}

	mybuffer = mybuffer.substr(0,mybuffer.size()-2);
	cnx_max_gnu<< "plot  "<<mybuffer<<";\n pause -1" <<endl;
	/*
	for(indice=0;indice<nb_cpu && numerodossier<iterMax && sortie;indice++) 
	 { 

	      while(notComprisEntre(cpuload_cur[indice],LoadMin,LoadMax) && numerodossier<iterMax && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency) && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
	      {
		if(cpuload_cur[indice]>LoadMax && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency))
		  {
		    if(cpuload_cur[indice]>LoadMax+5.0) offset_frequence =50;
		    else offset_frequence =25;
		      SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+offset_frequence);
		      frequence[indice]=cpu_tmp->work_frequency;
		      AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
		      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);


		  }
		  else
		  {
		      if(cpuload_cur[indice]<LoadMin && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
		      {
			  if(cpuload_cur[indice]<LoadMin-5.0) offset_frequence =50;
			  else offset_frequence =25;
			  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-25);
			  frequence[indice]=cpu_tmp->work_frequency;
			  AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
			  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		      }
		    
		  }
	      }
	   
	  }*/

      thisMesCPU=NULL;
    coucou();
    return numerodossier;
}





int getSpeedTickTimer(string input)
{
  string line,mot,S1="configure_timerspec_and_sched_fifo"; 
  size_t pos;
  int i=0,seconde=0,nanoseconde;
  uint nb_ligne=0;
  ifstream inputfile(input.c_str());
   while(getline(inputfile,line) && i<9 ) 
      {	 
	nb_ligne++;
	pos=line.find(S1);
	if (pos!=-1)
	{/// on  va se repositionner au debut de la ligne
	    inputfile.seekg(-line.size()-1,ios::cur);
	    inputfile>>mot; 
	    while(mot.compare("\n")!=0 && i++<9)
	    {
	      inputfile>>mot; 
	      if( i==4)
	      {
		mot= mot.substr(0,mot.size()-1);
		seconde = atoi(mot.c_str());
	      }
	      if( i==5)
	      {
		mot= mot.substr(0,mot.size()-1);
		nanoseconde = atoi(mot.c_str());
	      }
	    }
	  
	}
	    
      }
      if(seconde>0) return IS_HYPER_HIGH;
      else
      {
	if(nanoseconde>=600000000 && nanoseconde<1000000000) return IS_HIGH;
	if(nanoseconde>=400000000 && nanoseconde<600000000) return IS_MEDIUM;
	if(nanoseconde>=100000000 && nanoseconde<600000000) return IS_LOW;
	if(nanoseconde>=20000000 &&nanoseconde<100000000) return IS_HYPER_LOW;
	else/// aucun des cas précédent n'est respecté on quite le programme
	{
	  cout<< "le programme a echoué dans la fonction getSpeedTickTimer(...)\n";
	  cout <<"Raison: dans le fichier "<<input<<" il y a un problème de format à la ligne: "<<nb_ligne--<<endl; 
	  exit(0);
	}
      }

}

