



#include "regularisation.h"
#include <time.h>
#include <list>
#include <map>
#include <sstream>


// extern LISTE_TBC thisTBC;
// extern LISTE_TBC thisTBC2;
extern CPU thisMesCPU;
extern GROUP_TBC GroupAffinity;
//extern uint NbMaxCpu;
extern uint TSIZE;
// extern uint nbTBC;
double LoadMax;
double LoadMin;
double MinTolere =20.0;
list < pair < string,double > > selected_connections;
list < pair < string,double > > max_time_connections;
uint LIMIT=7;
int ALGO;
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

bool ComprisEntre(double valeur,double x, double y)
{
  if((valeur>=x && valeur<=y))
    return true;
  return false;
}
void e(){cout<<endl<<"Program under construction..... "<<endl;exit(0);}
uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num)
{
  uint i=0,j=0,o,nb_component=0,nb_affinity =0,numerodossier,indice=0,offset_frequence;
  int frequence[nb_cpu],NbThread,NbMaxCpu,TYPE=509,SIZE_MIXTE=0,SIZE_RESTE=0, max,nb_priority;
  char str_indice[100];
  //string  name,component,output, input;
  double cpuload_cur[nb_cpu];
  double MaxCpuload,MinCpuload, tabcpuload[nb_cpu-1];
  uint indice_cpuMax, indice_cpuMin;
  bool sortie=true,quit=true;
  bool stop =true;
     string Group_cnxname[TSIZE]; 
   int taille,Group_Aff[TSIZE];
  string compositionfile="composition.txt", composition_copie=string(_argv[2])+"composition_copie.txt",compositionfile_temp="composition_temp.txt";
  CPU cpu_tmp=NULL,cpu_access=NULL;
  LISTE_TBC copieListeTBC=NULL;

  ///  on fare deux copie de la liste une pour la convergence(while !=NUL) et l'autre pour le parcours et research
  GROUP_TBC ListOuvert=NULL,ListFerme=NULL;
  /// init variables 
  cpu_tmp = CloneCPU(MesCPU);
  cpu_access=CloneCPU(MesCPU);
  
  once=true;
  GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
//    for (int u=0; u<nb_component;u++) cout <<componentListe[u]<<endl;
 
  once=false;
//    e();
  ListOuvert=CloneG_TBC(GroupAffinity);
  ListFerme =CloneG_TBC(GroupAffinity);
//     CalculTBC(ListFerme, cpu_access);
// G_TBC_Afficher(GroupAffinity); e();
//   LoadMax= LoadMax;
//   G_TBC_Afficher(GroupAffinity);
//     CalculTBC(ListFerme, cpu_access);
//    e();
//   CalculTBC(ListFerme, cpu_access);
//    FindGroupCpuFix(ListFerme, Group_Aff, &taille);
//    for(int u=0; u<taille;u++) cout<<Group_Aff[u]<<endl;

   
//    FindSimilarGroup(ListFerme, 'C', Group_cnxname, &taille); 
//      for(int u=0; u<taille;u++) ChangeAffinity(composition_copie,compositionfile_temp,Group_cnxname[u],3);
//      e();
//     GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);

 // copieListeTBC=CloneListeTBC(thisTBC);/// on fait un clone pour pouvoir modifier les valeurs sans modifier l'originale (pointeur)
  NbThread = nb_component;
   numerodossier=num;
//    cout<<"nb_affinity "<<nb_affinity<<endl;
//    e();
    
//    for(i=0; i<nb_cpu ;i++) /// copie des frequences des cpu pour l'écriture  dans les fichiers de sortie
// 	    {
// 		if(cpu_tmp->work_frequency<200)
// 		{
// 		    cout << " tbc bas + low " << endl;
// 		    SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+offset_frequence);
// 		    AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
// 		}
// 		frequence[i]=cpu_tmp->work_frequency;
// 		cpu_tmp=cpu_tmp->next;
// 	    }
//    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
//     getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);

  /// fin init variables 
   
  
  /// determination du type d'algo :
   
   
  if( nb_cpu <=4 || NbThread <LIMIT )
  {

      SIZE_MIXTE=NbThread/nb_cpu;
//       SIZE_RESTE=NbThread%nb_cpu;
      NbMaxCpu=nb_cpu;
//         cout << "hehehe  "<<SIZE_MIXTE <<endl<< NbThread <<endl;e();
  }
  else
  { 
    if(nb_cpu>4)
    {
      SIZE_MIXTE=(NbThread/nb_cpu)/2;
//       SIZE_RESTE=NbThread%nb_cpu;
//         cout << SIZE_MIXTE <<endl<< NbThread <<endl;e();
      NbMaxCpu=nb_cpu-1;
      
    }
  }
 

	offset_frequence=100;
	for(i=0; i<nb_cpu ;i++) /// copie des frequences des cpu pour l'écriture  dans les fichiers de sortie
	{
	    if(cpu_tmp->work_frequency<200)
	    {
		SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+ offset_frequence);
		AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
	    }
	    
	    frequence[i]=cpu_tmp->work_frequency;
	    cpu_tmp=cpu_tmp->next;
	}
	i=0;j=1;
	CalculTBC(ListFerme, cpu_access);
// 	cpuload_cur[0]=90;
	//getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
//        if(cpuload_cur[0]<LoadMax){cout<<"cpuLoad_"<<0<<" < "MinTolere<<LoadMax<<endl;return numerodossier; }
	/// on va changer l'affinity de NbMaxCpu en parallèle si le ticktimer n'est pas trop élévé 
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
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	indice=0;
	cpu_tmp = AccessToCPU(cpu_access,indice);
// 	 G_TBC_Afficher(ListOuvert);e();
// 	 
	/// fin de la partie parallèle on regarde d'abord s'il n'y plus de threads dans notre liste !
	if(ListOuvert==NULL)/// si liste vide 
	{
	/// cette partie est à revoir  : genre unn prend un thread du max seulement
	    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
// 	    goto ici;
	    /// maintenant on va vérifier les cas où le cpu_0  a un chargement inférieur à 5%
	    for(i=0;i<nb_cpu-1;i++) { tabcpuload[i]=cpuload_cur[i+1];}
	    getMinMaxCpuLoad( tabcpuload,NULL,nb_cpu-1,  0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin); /// recherche min et max  
	    if(cpuload_cur[0]<30.0)
	    {
		cpu_tmp=AccessToCPU(cpu_access,0);
		FindAndReplaceAffinity(composition_copie,compositionfile_temp,indice_cpuMin+1,0);
		GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
		CalculTBC(ListFerme, cpu_tmp);
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	    }


	}	    
	else								  				/// sinon on sait que la liste des threads n'est pas encore vide !
	    {
	    indice=1;
	    sortie = true;
	    while(ListOuvert !=NULL && indice<nb_cpu &&  cpuload_cur[0]>LoadMax )/// tant que la liste n'est pas vide ou bien  qu'on pas au cpu_0
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
	
	while(ListOuvert!=NULL)
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
	
	while(max> 1 && numerodossier<20 ) /// tant qu'il y en aura un cpuload superieur à 83-85%  on augementera la fréquence 
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

// coucou();
// e();

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
	if(cpuload_cur[indice]<=MinTolere){ sortie = false;i=indice;}/// pour les cacahuettes
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


	for(indice=0;indice<nb_cpu && numerodossier<30;indice++) 
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
	/*
		for(indice=0;indice<nb_cpu && numerodossier<20 && sortie;indice++) 
	 { 

	      while(notComprisEntre(cpuload_cur[indice],LoadMin,LoadMax) && numerodossier<20 && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency) && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
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
*/
indice=0;
/// ICI ON NE FAIT QU'UNE DERNIERE VERIFICATION DES CPULOAD 
// list < list <  double > >::iterator time_cnx_iter=0;;
// ici:	


quit=true;
while(quit)
{
for (list < pair < string, double > >::iterator iter = selected_connections.begin(); iter != selected_connections.end()&& numerodossier<40; iter++) 
	{
	  string cnx_name_dat = iter->first + ".dat";
	    cout<<cnx_name_dat<<endl;
	    ofstream cnx_dat(cnx_name_dat.c_str(),ios::app);
	  string name_file = iter->first;
// 	  cout<<"mon fichier bidulle "<<name_file<<endl;
	  
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
	
	  while(file_connections>>value && stop && numerodossier<40)
	  {
	    if(value>iter->second && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency))
	    {
	      cnx_dat<<value<<endl;
	      name_file = iter->first;
	      //iter--;
	      stop=false;
	      /// substr; getaffinyof, upfreq cpu_x
	      name_file=name_file.substr(4,name_file.size());
	      indice = getAffinityOf(composition_copie,name_file); 
	      frequence[indice]=AccessToCPU(cpu_access,indice)->work_frequency+25;
	      AccessToCPU(cpu_access,indice)->work_frequency+=25;
	      
// 	      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	      //cout<<name_file<<endl;
	      quit = true;
	    }
	   
	  //cout<< iter->first <<" "<<iter->second<<endl;
	  }
	  if(stop)
	    {
	       ifstream file_connections2(save_name.c_str());
	      
		cnx_dat<<value<<endl;
	       list < double > mylist_to_sort;
	       while(file_connections2>>value) mylist_to_sort.push_back(value);
	       mylist_to_sort.sort();
	       max_time_connections.push_back(pair < string, double> (iter->first,mylist_to_sort.back()));
	     
	      //cout<<"max time for " <<iter->first<< ": "<<mylist_to_sort.back()<<" ms "<<endl;
	      quit = false;
	     
	    }
	  
	  
	  
	}
	CalculTBC(ListFerme,cpu_access);
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
}

	 ofstream cnx_max_gnu("cnx_all_max.gnu");
	 string mybuffer;
	 mybuffer.clear();
// 	 i=0 ; 
// 	 cnx_max_gnu<< "plot  ";
	for (list < pair < string, double > >::iterator iter = selected_connections.begin(); iter != selected_connections.end(); iter++) 
	{
 	  string name_file = iter->first ;ostringstream oss;
 	  oss << iter->second;
 	  mybuffer +=" '" + name_file +".dat' with linespoints ,  " +  oss.str() + " with lines title \"Max_" + name_file +"\", " ;
	 oss.str(""); oss.clear(); 
	 

// 	 cnx_max_gnu<<"'" << iter->first <<".dat' with linespoints ,  " <<  iter->second << " with lines title \"Max_" << iter->first <<"\", " ;
// 	 else {iter--;cnx_max_gnu<<"'" << iter->first <<".dat' with lines ,  " <<  iter->second << " with lines title \"Max_" << iter->first <<"\", " ;}
	  
	}

	mybuffer = mybuffer.substr(0,mybuffer.size()-2);
	cnx_max_gnu<< "plot  "<<mybuffer<<";\n pause -1" <<endl;
// 	cnx_max_gnu<< ";\n pause -1" <<endl;
	/*
	for(indice=0;indice<nb_cpu && numerodossier<20 && sortie;indice++) 
	 { 

	      while(notComprisEntre(cpuload_cur[indice],LoadMin,LoadMax) && numerodossier<20 && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency) && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
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

