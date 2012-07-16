



#include "regularisation.h"
#include <time.h>
extern LISTE_TBC thisTBC;
extern LISTE_TBC thisTBC2;
extern CPU thisMesCPU;
extern GROUP_TBC GroupAffinity;
//extern uint NbMaxCpu;
extern uint TSIZE;
// extern uint nbTBC;
float LoadMax;
float LoadMin;
uint LIMIT=10;
int ALGO;
extern bool once;
extern char **_argv;


// bool IS_HIGH = false;
// bool IS_LOW =true;
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
bool notComprisEntre(float valeur,float x, float y)
{
  if((valeur>=x && valeur<=y))
    return false;
  return true;
}

bool ComprisEntre(float valeur,float x, float y)
{
  if((valeur>=x && valeur<=y))
    return true;
  return false;
}
void e(){exit(0);}
uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num)
{
  uint i=0,o,nb_include=0,nb_affinity =0,numerodossier,indice=0,offset_frequence;
  int frequence[nb_cpu],_nbTBC,NbMaxCpu,TYPE=509,SIZE_MIXTE=0, max;
  char str_indice[100];
  string  name,component,output, input;
  float cpuload_cur[nb_cpu];
  float MaxCpuload,MinCpuload, tabcpuload[nb_cpu-1];
  uint indice_cpuMax, indice_cpuMin;
  bool sortie=true;
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
  GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_include);
  once=false;
  ListOuvert=CloneG_TBC(GroupAffinity);
  ListFerme =CloneG_TBC(GroupAffinity);
  // G_TBC_Afficher(GroupAffinity);
//   CalculTBC(ListFerme, cpu_access);
   FindGroupCpuFix(ListFerme, Group_Aff, &taille);
   for(int u=0; u<taille;u++) cout<<Group_Aff[u]<<endl;

   
e();
//    FindSimilarGroup(ListFerme, 'C', Group_cnxname, &taille); 
//      for(int u=0; u<taille;u++) ChangeAffinity(composition_copie,compositionfile_temp,Group_cnxname[u],3);
//      e();
//     GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_include);

 // copieListeTBC=CloneListeTBC(thisTBC);/// on fait un clone pour pouvoir modifier les valeurs sans modifier l'originale (pointeur)
  _nbTBC = nb_affinity;
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
  if((_nbTBC/2)+1 < LIMIT )
  {
      TYPE = getSpeedTickTimer(compositionfile);//== IS_LOW) TYPE =TYPE1;
//     else TYPE= TYPE2;
      ALGO = SEQUENTIEL;
  }
  else
  {
     if((_nbTBC/2)+1 >= LIMIT )
     {
	TYPE = getSpeedTickTimer(compositionfile);//== IS_LOW) TYPE =TYPE3;

      if(TYPE == IS_HYPER_HIGH || TYPE==IS_HYPER_LOW) ALGO = SEQUENTIEL;
      else ALGO = MIXTE;
    //  if(nb_cpu<2) ALGO = SEQUENTIEL; 
     }
  }
  
switch (ALGO)
{
case SEQUENTIEL:
	    if(TYPE==IS_HYPER_LOW) offset_frequence=100;
	    else 
	    {
	      if(TYPE == IS_HYPER_HIGH) offset_frequence=50;
	      else{
		  if(TYPE==IS_LOW) offset_frequence=50;
		  else {
			if(TYPE==IS_MEDIUM) offset_frequence=25;
			else offset_frequence=0;
			}
	      }
	    }
	    for(i=0; i<nb_cpu ;i++) /// copie des frequences des cpu pour l'écriture  dans les fichiers de sortie
	    {
		if(cpu_tmp->work_frequency<200)
		{
		    cout << " tbc bas + low " << endl;
		    SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+offset_frequence);
		    AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
		}
		frequence[i]=cpu_tmp->work_frequency;
		cpu_tmp=cpu_tmp->next;
	    }
	    indice=1;
	    CalculTBC(ListFerme, cpu_access);
	    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
// 	    X=0;
	    while(ListOuvert !=NULL && indice<nb_cpu &&  cpuload_cur[0]>LoadMax)/// tant que la liste n'est pas vide ou bien  qu'on pas au cpu_0
	    {
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		for(i=1; i<nb_cpu;i++)/// augmentation de la fréquence de tous les cpu dont le cpuload_cur[]>LoadMax 80.0
		{
		    cpu_tmp = AccessToCPU(cpu_access,i);
		    if(cpuload_cur[i]>LoadMax)
		    {			
		      if(TYPE==IS_HYPER_LOW || cpu_tmp->work_frequency<300) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100); }
		      else {
			      if(TYPE==IS_LOW && cpu_tmp->work_frequency<300) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+75); }
			      else { 
				    if(TYPE==IS_MEDIUM && cpu_tmp->work_frequency<300 )SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50); 
				    else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25); 
				   }
			   }
			AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;	
		    }
		    frequence[i]=cpu_tmp->work_frequency;
		}
		CalculTBC(ListFerme, cpu_access);
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		///modification seulement de l'affinité de la liste ! :D
		if(cpuload_cur[indice]<LoadMin  && ListOuvert!=NULL && cpuload_cur[0]>LoadMax ) ///si le cpu courant n'est pas assez chargé on lui rajoute des threads
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
			if(getValAffinity(ListOuvert->TypeAff[X])==AFF_VAR)
			{
			  ChangeAffinity(composition_copie,compositionfile_temp,ListOuvert->cnx_name[X],indice);
			  ListOuvert->affinity[X]=indice;
			}
		      }
		 }
		  GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_include);
		  //CalculTBC(ListFerme, cpu_access);
// 		    if(X++ >= ListOuvert->nb_input){
		      ListOuvert=ListOuvert->next;
		      
// 		    }	 
		}
		else
		{
		    indice++;
		}
	    }/// end while
    
break;

case MIXTE:
	    if(TYPE==IS_HYPER_LOW)
	    {
	       SIZE_MIXTE=2;/// nombre de SLICE/FILTRE par CPU
		    NbMaxCpu =nb_cpu-1;/// nombre de CPU en parallèle
		    offset_frequence=100;//50
	    }
	    else
	    {
		if(TYPE==IS_LOW)
		{
		    SIZE_MIXTE=3;/// nombre de SLICE/FILTRE par CPU
		    NbMaxCpu =nb_cpu/2+1;/// nombre de CPU en parallèle
		    offset_frequence=50;//50
		}
		else
		{
		    if(TYPE==IS_MEDIUM)
		    {
			SIZE_MIXTE=3;/// ou 4+/-:1
			NbMaxCpu=nb_cpu/2;
			offset_frequence=25;//25
		    }
		    else
		    {
		      if(TYPE==IS_HIGH)
		      {
			SIZE_MIXTE=5;/// ou 5
			NbMaxCpu =nb_cpu/2;
			offset_frequence=0;//0
		      }
		    }
		}
	    }
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
	    i=0;
	    CalculTBC(ListFerme, cpu_access);
	    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	 //   if(cpuload_cur[0]<LoadMax){return numerodossier; }
	    /// on va changer l'affinity de NbMaxCpu en parallèle si le ticktimer n'est pas trop élévé 
	    ///et le reste se fera de façon sequentielle s'il reste encore des  threads
	    for(uint t=0;t<=SIZE_MIXTE && ListOuvert !=NULL;t++)
	    {
		for(indice=1;indice<=NbMaxCpu && ListOuvert !=NULL;indice++)
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
			if(getValAffinity(ListOuvert->TypeAff[X])==AFF_VAR)
			{
			  ChangeAffinity(composition_copie,compositionfile_temp,ListOuvert->cnx_name[X],indice);
			  ListOuvert->affinity[X]=indice;
			}
		      }
		  }
		    GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_include);
		    ListOuvert=ListOuvert->next;
		}
	    }
	    indice=1;
	    cpu_tmp = AccessToCPU(cpu_access,indice);
	    /// fin de la partie parallèle on regarde d'abord s'il n'y plus de threads dans notre liste !
	    if(ListOuvert==NULL)/// si liste vide 
	    {
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		/// maintenant on va vérifier les cas où le cpu_0  a un chargement inférieur à 5%
		for(i=0;i<nb_cpu-1;i++) { tabcpuload[i]=cpuload_cur[i+1];}
		getMinMaxCpuLoad( tabcpuload,NULL,nb_cpu-1,  0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin); /// recherche min et max  
		if(cpuload_cur[0]<30.0)
		{
		    cpu_tmp=AccessToCPU(cpu_access,0);
		    FindAndReplaceAffinity(composition_copie,compositionfile_temp,indice_cpuMin+1,0);
		    GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_include);
		    CalculTBC(ListFerme, cpu_tmp);
		    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);

		}

	    }	    
	    else								///				/// sinon on sait que la liste des threads n'est pas encore vide !
		{
		indice=1;
		sortie = true;
		while(ListOuvert !=NULL && indice<nb_cpu &&  cpuload_cur[0]>LoadMax)/// tant que la liste n'est pas vide ou bien  qu'on pas au cpu_0
		    {
			if(sortie )
			{
			    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence); sortie=false;	 
			}

			for(i=0; i<nb_cpu;i++)/// augementation de la fréquence de tous les cpu dont le cpuload_cur[]>LoadMax 80.0
			{
			    cpu_tmp = AccessToCPU(cpu_access,i);
			    if(cpuload_cur[i]>LoadMax)
			    {
				if(TYPE==IS_HYPER_LOW || cpu_tmp->work_frequency<300) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100); }
				else
				{
				    if(TYPE==IS_LOW && cpu_tmp->work_frequency<300) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+75); }
				    else { 
					if(TYPE==IS_MEDIUM && cpu_tmp->work_frequency<300 )SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50); 
					else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25); 
					}
				}
				AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
				CalculTBC(ListFerme, cpu_access);
// 				RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_affinity,nb_include);
				  //TBC_Afficher(thisTBC);

				sortie=true;
			    }
			    frequence[i]=cpu_tmp->work_frequency;
			}

			if(sortie) 
			{
			    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence); sortie=false;	 
			}
			if(cpuload_cur[indice]<LoadMin  && ListOuvert!=NULL && cpuload_cur[0]>LoadMax) ///si le cpu courant n'est pas assez chargé on lui rajoute des threads
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
				    if(getValAffinity(ListOuvert->TypeAff[X])==AFF_VAR)
				    {
				      ChangeAffinity(composition_copie,compositionfile_temp,ListOuvert->cnx_name[X],indice);
				      ListOuvert->affinity[X]=indice;
				    }
				  }
			    }
			    GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_include);
			    ListOuvert=ListOuvert->next;
			}
			else
			{
			    indice++;
			}

		    }/// end while
	    }/// end else

break;

default:
    cout << "algo non implémenté " << endl;  break;
    
}/// fin du Switch

	max=nb_cpu;
	while(max>0) /// tant qu'il y en aura un cpuload superieur à 83-85%  on augementera la fréquence 
	{	
	    for(indice=0; indice<nb_cpu && max>0;indice++)/// on regardera tout les niveaux de chargement des CPU qui fonctionnent !
	    {
		if(cpuload_cur[indice]>LoadMax && frequence[indice]<=(AccessToCPU(cpu_access,indice)->end_frequency))
		{
		    if(max<=nb_cpu+1) {max++;}
		    cpu_tmp =AccessToCPU(cpu_access,indice);
		    if(TYPE==IS_HYPER_LOW) SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
		    if(TYPE==IS_HIGH) SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25);
		    if(TYPE==IS_MEDIUM || TYPE ==IS_LOW) SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
		    frequence[indice]=cpu_tmp->work_frequency;
		    AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
		    //RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_affinity,nb_include);  
		      //TBC_Afficher(thisTBC);

		}
		else
		{
		    if(cpuload_cur[indice]>30.0 && cpuload_cur[indice]<LoadMin && frequence[indice]>=(AccessToCPU(cpu_access,indice)->start_frequency))
		    {

			if(max<=nb_cpu+1) {max++;}
			cpu_tmp =AccessToCPU(cpu_access,indice);
			SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-25);
			frequence[indice]=cpu_tmp->work_frequency;
			AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;

		    }
		    else
			if(max>1){ max--; }
		}
	    }
	    CalculTBC(ListFerme, cpu_access);
	   if(max>0)///0
	    {
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		max--;
	    }
	}
	/// maintenant on va vérifier les cas où le cpu_0  a un chargement inférieur à 40%
	for(i=0;i<nb_cpu-1;i++) { tabcpuload[i]=cpuload_cur[i+1];}
	getMinMaxCpuLoad( tabcpuload,NULL,nb_cpu-1,  0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin); /// recherche min et max  
	if( cpuload_cur[0]<40.0 )
	{
	      cpu_tmp=AccessToCPU(cpu_access,0);
	      FindAndReplaceAffinity(composition_copie,compositionfile_temp,indice_cpuMin+1,0);
	      GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_include);
	      CalculTBC(ListFerme, cpu_access);
// 	      RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_affinity,nb_include);
	        //TBC_Afficher(thisTBC);

	      while(notComprisEntre(cpuload_cur[0],LoadMin,LoadMax) && frequence[0]<(AccessToCPU(cpu_access,0)->end_frequency) && frequence[0]>=(AccessToCPU(cpu_access,0)->start_frequency))
	      {
		
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		if(cpuload_cur[0]>LoadMax && frequence[0]<=(AccessToCPU(cpu_access,0)->end_frequency))
		  {
		      SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25);
		      frequence[0]=cpu_tmp->work_frequency;
		      AccessToCPU(cpu_access,0)->work_frequency=cpu_tmp->work_frequency;
		      CalculTBC(ListFerme, cpu_access);
// 		      RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_affinity,nb_include);  
		        //TBC_Afficher(thisTBC);

		  }
		  else
		  {
		      if(cpuload_cur[0]>30.0 && cpuload_cur[0]<LoadMin && frequence[0]>=(AccessToCPU(cpu_access,0)->start_frequency))
		      {
			  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-25);
			  frequence[0]=cpu_tmp->work_frequency;
			  AccessToCPU(cpu_access,0)->work_frequency=cpu_tmp->work_frequency;
			  CalculTBC(ListFerme, cpu_access);
// 			  RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_affinity,nb_include); 
			    //TBC_Afficher(thisTBC);
		      }
		    
		  }
	      }
	}
	 
	 for(indice=0;indice<nb_cpu;indice++) 
	 { max=0;
	   if(cpuload_cur[indice]>1.0 && cpuload_cur[indice]<50.0)
	   {
	      for(i=0;i<nb_cpu;i++) { if(i!=indice && cpuload_cur[i]!=0.0) tabcpuload[max++]=cpuload_cur[i];}
	      getMinMaxCpuLoad( tabcpuload,NULL,max,  0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin);
	      cpu_tmp=AccessToCPU(cpu_access,indice_cpuMin);
	      FindAndReplaceAffinity(composition_copie,compositionfile_temp,indice,indice_cpuMin);
// 	      nb_include = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
	      GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_include);
	      CalculTBC(ListFerme, cpu_access);
// 	      RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_affinity,nb_include);
	        //TBC_Afficher(thisTBC);

	      indice=indice_cpuMin;
	      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);

	      while(notComprisEntre(cpuload_cur[indice],LoadMin,LoadMax) && frequence[indice]<=(AccessToCPU(cpu_access,indice)->end_frequency) && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
	      {
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		if(cpuload_cur[indice]>LoadMax && frequence[indice]<=(AccessToCPU(cpu_access,indice)->end_frequency))
		  {
		      SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25);
		      frequence[indice]=cpu_tmp->work_frequency;
		      AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
		      

		  }
		  else
		  {
		      if(cpuload_cur[indice]>30.0 && cpuload_cur[indice]<LoadMin && frequence[indice]>=(AccessToCPU(cpu_access,indice)->start_frequency))
		      {
			  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-25);
			  frequence[indice]=cpu_tmp->work_frequency;
			  AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
// 			  RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_affinity,nb_include); 
// 			  CalculTBC(ListFerme, cpu_access);
			    //TBC_Afficher(thisTBC);

		      }
		    
		  }
		  CalculTBC(ListFerme, cpu_access);
	      }
	      indice=0;
	   }
	   
	  }



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
// 	cout<<line<<endl;
	    inputfile.seekg(-line.size()-1,ios::cur);
	    inputfile>>mot; 
// 	    cout<<mot<<endl;
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



/*
exit(0);
  
  
  //sortie= getSpeedTickTimer(compositionfile);
  for(i=0; i<nb_cpu ;i++) /// copie des frequences des cpu pour l'écriture  dans les fichiers de sortie
  {
    if(cpu_tmp->work_frequency<200 )
    {
    SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
    AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
    }
    frequence[i]=cpu_tmp->work_frequency;
    cpu_tmp=cpu_tmp->next;
  }
    numerodossier=num;
    i=0;
   // sortie=true;
   // getSpeedTickTimer(compositionfile);
  
    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
    
    if(cpuload_cur[0]<LoadMax){return numerodossier; }
    if(nb_cpu>NbMaxCpu+1 && getSpeedTickTimer(compositionfile))/// on va changer l'affinity de NbMaxCpu en parallèle si le ticktimer n'est pas trop élévé 
    {			///et le reste se fera de façon sequentielle s'il reste encore des  threads
      for(uint t=0;t<=NbMaxCpu;t++)
      {
	for(indice=1;indice<=NbMaxCpu && copieListeTBC !=NULL;indice++)
	{
	  if(nb_cpu>indice)/// :d petite précaution
	  {
	    o=0;
	    name= copieListeTBC->name;
	    ChangeAffinity(composition_copie,compositionfile_temp,name,indice);
	    nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
	    while((componentListe[o++].compare(name))!=0);
	    o--;
	    component= includeListe[o].substr(0,includeListe[o].size()-10);
	    sprintf(c,"_cpu_%d.txt",indice);
	    output= component+c;
	    input =_argv[2]+component+".txt";
	    cpu_tmp = AccessToCPU(cpu_access,indice);
	    GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
	    copieListeTBC=copieListeTBC->next;
	  }
	}
      }
      indice=1;
    cpu_tmp = AccessToCPU(cpu_access,indice);

    }
    else
    {
      cpu_tmp = AccessToCPU(cpu_access,1);
      sprintf(c,"_cpu_%d.txt",1);

      for(indice=1;indice<=2*NbMaxCpu && copieListeTBC !=NULL;indice++)
	{
	  
	    o=0;
	    name= copieListeTBC->name;
	    ChangeAffinity(composition_copie,compositionfile_temp,name,1);
	    nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
	    while((componentListe[o++].compare(name))!=0);
	    o--;
	    component= includeListe[o].substr(0,includeListe[o].size()-10);
	    output= component+c;
	    input =_argv[2]+component+".txt";
	    GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
	    copieListeTBC=copieListeTBC->next;
	  
	}
    }
    /// fin de la partie parallèle on regarde d'abord s'il n'y plus de threads dans notre liste !
    if(copieListeTBC==NULL)
    {
    
      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
      int max=nb_cpu-1;
      while(max>0) /// tant qu'il y en aura un cpuload superieur à 83-85%  on augementera la fréquence 
      {	
	  for(i=1; i<nb_cpu && max>0;i++)/// on regardera tout les niveaux de chargement des CPU qui fonctionnent !
	  {
	    if(cpuload_cur[i]>LoadMax)
	    {
	      if(max<nb_cpu-1){ max++; }
	      
	      cpu_tmp = AccessToCPU(cpu_access,i);
	      if(cpu_tmp->work_frequency<300){ SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100); }
	      else {  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50); }
	      frequence[i]=cpu_tmp->work_frequency;
	      AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
	      RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	    }
	    else 
	      if(max>1){ max--; }
	  }
	    if(max>0)
	    {
	      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	      ////write_Data_histogram(cpuload_cur,nb_cpu);
	      max--;
	    }
      }
    
/// maintenant on va vérifier les cas où le cpu_0  a un chargement inférieur à 5%
      for(i=0;i<nb_cpu-1;i++) { tabcpuload[i]=cpuload_cur[i+1];}
      getMinMaxCpuLoad( tabcpuload,NULL,nb_cpu-1,  0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin); /// recherche min et max  
// 	  cout <<" Max : "<< MaxCpuload << " cpu_"<<indice_cpuMax+1<<endl;
// 	  cout <<" Min : "<< MinCpuload << " cpu_"<<indice_cpuMin+1<<endl;
// 	  exit(0);
      if(cpuload_cur[0]<5.0 && cpuload_cur[indice_cpuMin+1]<LoadMax)
      {
	cpu_tmp=AccessToCPU(cpu_access,0);
	FindAndReplaceAffinity(composition_copie,compositionfile_temp,indice_cpuMin+1,0);
	nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
	RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	////write_Data_histogram(cpuload_cur,nb_cpu);
      }
 }
 else/// sinon on sait que la liste des threads n'est pas encore vide !
 {
    indice=1;
    sortie = true;
    while(copieListeTBC !=NULL && indice<nb_cpu &&  !ComprisEntre(cpuload_cur[0],LoadMax-10.0,LoadMax+5.0 ))/// tant que la liste n'est pas vide ou bien  qu'on npas au cpu_0
    {
      
	if(sortie)
	{
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	  ////write_Data_histogram(cpuload_cur,nb_cpu);	    
	  sortie=false;	 
	}
	
	for(i=0; i<nb_cpu;i++)/// augementation de la fréquence de tous les cpu dont le cpuload_cur[]>LoadMax 80.0
	{
	  cpu_tmp = AccessToCPU(cpu_access,i);
	    if(cpuload_cur[i]>(LoadMax+5.0))
	    {
	      if(cpu_tmp->work_frequency<300) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100); }
	      else { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50); }
		
	      AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
	      RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);
	      sortie=true;
	    }
	    
	  frequence[i]=cpu_tmp->work_frequency;
	}
	
	if(sortie) 
	{
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	  ////write_Data_histogram(cpuload_cur,nb_cpu);
	  sortie=false;	 
	}
	
	if(cpuload_cur[indice]<LoadMax-10.0  && copieListeTBC!=NULL ) ///si le cpu courant n'est pas assez chargé on lui rajoute des threads
	{
	   o=0;
	  cpu_tmp = AccessToCPU(cpu_access,indice);
	  name = copieListeTBC->name;
	  ChangeAffinity(composition_copie,compositionfile_temp,name,indice);
	  nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
	  while((componentListe[o++].compare(name))!=0);
	  o--;///  \o/
	  component= includeListe[o].substr(0,includeListe[o].size()-10);
	  cout<<"name :"<<name<<endl;
	  cout<<"component :"<<component<<endl;
	  sprintf(c,"_cpu_%d.txt",indice);
	  output= component+c;
	  input =_argv[2]+component+".txt";
	  GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
	  copieListeTBC=copieListeTBC->next;	
	  sortie = true;
	}
	else
	{
	  indice++;
	}
      
    }/// end while
}/// end else
//       o=0;
//       for(i=0;i<nb_cpu;i++)
//       {
// 	if(cpuload_cur[i]<5.0 && cpuload_cur[i]>0.1) 
// 	 {
// 	    tabcpuload[i]=cpuload_cur[i];
// 	    o++;
// 	 }
//       }

      
      for(i=1;i<nb_cpu;i++)tabcpuload[i-1]=cpuload_cur[i];
      getMinMaxCpuLoad(tabcpuload,NULL,nb_cpu-1, 0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin);
      
      if(cpuload_cur[0]<5.0 && cpuload_cur[indice_cpuMin+1]<LoadMax-5.0)/// on change la frequence des
      {
	cpu_tmp=AccessToCPU(cpu_access,0);
	FindAndReplaceAffinity(composition_copie,compositionfile_temp,0,indice_cpuMin+1);
	nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
	RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	////write_Data_histogram(cpuload_cur,nb_cpu);
      }
      else
      {
	  indice=0;
	  while(cpuload_cur[indice]>LoadMax+5.0) /// sinon tant que le cpu_0  a une charge > à 85.6  on augmente la frequence de fonctionnement 
	{
	  cpu_tmp =AccessToCPU(cpu_access,indice);
	if(cpu_tmp->work_frequency<400)SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
	else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
	frequence[indice]=cpu_tmp->work_frequency;
	AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
	RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	////write_Data_histogram(cpuload_cur,nb_cpu);
	}
      }
      
      
      for(indice=0;indice<nb_cpu;)/// diminution de la frequence pour les cpu qui ont une charge inféieur à 70!!!
      {
	if(cpuload_cur[indice]>30.0 && cpuload_cur[indice]<LoadMax-10.0 && frequence[indice]>100)
	{
	  cpu_tmp =AccessToCPU(cpu_access,indice);
	  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-25);
	  frequence[indice]=cpu_tmp->work_frequency;
	  AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
	  RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	}
	else indice++;
      }
      
      
      
      if(cpuload_cur[0]<5.0)
      {
	 o=0;
	for(i=1;i<nb_cpu;i++) 
	{
	  if(cpuload_cur[i]>30.0) 
	  {
	    tabcpuload[i-1]=cpuload_cur[i];
	    o++;
	  }
	}
      getMinMaxCpuLoad(tabcpuload,NULL,o-1, 0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin);
      cpu_tmp=AccessToCPU(cpu_access,0);
      FindAndReplaceAffinity(composition_copie,compositionfile_temp,0,indice_cpuMin+1);
      nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
      RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);
      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
   
      }*/