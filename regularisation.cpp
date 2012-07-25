



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
uint LIMIT=7;
int ALGO;
extern bool once;
extern char **_argv;


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
  uint i=0,j=0,o,nb_component=0,nb_affinity =0,numerodossier,indice=0,offset_frequence;
  int frequence[nb_cpu],NbThread,NbMaxCpu,TYPE=509,SIZE_MIXTE=0,SIZE_RESTE=0, max,nb_priority;
  char str_indice[100];
  //string  name,component,output, input;
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
  GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
  once=false;
  ListOuvert=CloneG_TBC(GroupAffinity);
  ListFerme =CloneG_TBC(GroupAffinity);
  LoadMax= LoadMax+0.7;
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
    
//    for(i=0; i<nb_cpu ;i++) /// copie des frequences des cpu pour l'�criture  dans les fichiers de sortie
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
//       if(!(NbThread%nb_cpu) )
//       {
      SIZE_MIXTE=NbThread/nb_cpu;
      SIZE_RESTE=NbThread%nb_cpu;
      NbMaxCpu=nb_cpu;
     // ALGO = SEQUENTIEL; /// /Mixte_1
//       }
  }
  else
  { 
    if(nb_cpu>4)
    {
      SIZE_MIXTE=NbThread/nb_cpu/2;
      SIZE_RESTE=NbThread%nb_cpu;
      NbMaxCpu=nb_cpu-2;
     // ALGO = SEQUENTIEL;/// MIxte_2
      
    }
  }
 
//FindGroupCpuFix(ListOuvert, Group_Aff, &nb_priority);

//  for(int h=0; h<nb_priority;h++) cout <<Group_Aff[h]<<endl;e();
//switch (ALGO)
//{
//case SEQUENTIEL: 
  /*
	    if(TYPE==IS_HYPER_LOW) offset_frequence=50;
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
	    }*/
  
// 	    offset_frequence=50;
// 	    for(i=0; i<nb_cpu ;i++) /// copie des frequences des cpu pour l'�criture  dans les fichiers de sortie
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
// 	   // coucou();
// 	    CalculTBC(ListFerme, cpu_access);
// 	    
//   	   /* for(int h=0; h<3;h++)	    
// 	    for(uint u=0; u<nb_priority;u++)
// 	    {
// 	      indice = Group_Aff[u];
// 	       for(uint X=0; X<ListOuvert->nb_input;X++)
// 		  {
// 		      if(getValAffinity(ListOuvert->TypeAff[X])==AFF_GROUP && ListOuvert->affinity[X]==0)/// pour les affinit� en Groupe : type( A,B,C,....Z)
// 		      {
// 			FindSimilarGroup(ListFerme, ListOuvert->TypeAff[X], Group_cnxname, &taille); 
// 			for( int p=0; p<taille;p++)
// 			{
// 			  ChangeAffinity(composition_copie,compositionfile_temp,Group_cnxname[p],indice);
// 			  ListOuvert->affinity[p]=indice;
// 			}
// 		      }
// 		      else
// 		      {
// 			if(getValAffinity(ListOuvert->TypeAff[X])==AFF_VAR && ListOuvert->affinity[X]==0)
// 			{
// 			  ChangeAffinity(composition_copie,compositionfile_temp,ListOuvert->cnx_name[X],indice);
// 			  ListOuvert->affinity[X]=indice;
// 			}
//  		      }
// 		  }
// // 		  GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
// 		  ListOuvert=ListOuvert->next;
// 	    }*/
// 	  //GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
// 	  
// 	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
// 	  indice=1;
// 	  sortie=false;
// 	    while(ListOuvert !=NULL && indice<nb_cpu &&  cpuload_cur[0]>LoadMax)/// tant que la liste n'est pas vide ou bien  qu'on pas au cpu_0
// 	    {
// 	      
// 		if(sortie){getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);sortie=false;}
// 		for(i=1; i<nb_cpu;i++)/// augmentation de la fr�quence de tous les cpu dont le cpuload_cur[]>LoadMax 80.0
// 		{
// 		    cpu_tmp = AccessToCPU(cpu_access,i);
// 		    if(cpuload_cur[i]>LoadMax)
// 		    {			
// 		      if(TYPE==IS_HYPER_LOW && cpu_tmp->work_frequency<200) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+75); }
// 		      else {
// 			      if(TYPE==IS_LOW && cpu_tmp->work_frequency<250) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+75); }
// 			      else { 
// 				    if(TYPE==IS_MEDIUM && cpu_tmp->work_frequency<250 )SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50); 
// 				    else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25); 
// 				   }
// 			   }
// 			AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;	
// 		    }
// 		    frequence[i]=cpu_tmp->work_frequency;
// 		}
// 		CalculTBC(ListFerme, cpu_access);
// 		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
// 		
// 		///modification seulement de l'affinit� de la liste ! :D
// 		if(cpuload_cur[indice]<LoadMin  && ListOuvert!=NULL && cpuload_cur[0]>LoadMax ) ///si le cpu courant n'est pas assez charg� on lui rajoute des threads
// 		{
// 		 for(uint X=0; X<ListOuvert->nb_input;X++)
// 		 {
// 		      if(getValAffinity(ListOuvert->TypeAff[X])==AFF_GROUP && ListOuvert->affinity[X]==0)/// pour les affinit� en Groupe : type( A,B,C,....Z)
// 		      {
// 			FindSimilarGroup(ListFerme, ListOuvert->TypeAff[X], Group_cnxname, &taille); 
// 			for( int p=0; p<taille;p++)
// 			{
// 			  ChangeAffinity(composition_copie,compositionfile_temp,Group_cnxname[p],indice);
// 			  ListOuvert->affinity[p]=indice;
// 			}
// 		      }
// 		      else
// 		      {
// 			if(getValAffinity(ListOuvert->TypeAff[X])==AFF_VAR && ListOuvert->affinity[X]==0)
// 			{
// 			  ChangeAffinity(composition_copie,compositionfile_temp,ListOuvert->cnx_name[X],indice);
// 			  ListOuvert->affinity[X]=indice;
// 			}
// 		      }
// 		 }
// 		  GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
// 		  ListOuvert=ListOuvert->next;
// 		  sortie=true;    
// 		}
// 		else
// 		{
// 		  indice++;
// 		  //if(indice>nb_cpu) indice=1;
// // 		  if(findnotint(Group_Aff, indice, nb_priority))
// // 		  {
// // 		  }
// // 		  if(sortie) indice++;
// // 		  if(j++<nb_priority){ indice = Group_Aff[j];sortie=false;}
// // 		   else 
// // 		   {
// // 		     if(!sortie)
// // 		      {sortie =true;indice=1;}
// // 		   }
// 		}
// 	    }/// end while
    
//break;

//case MIXTE:
//   coucou();e();
/*	    if(TYPE==IS_HYPER_LOW)
	    {
	       SIZE_MIXTE=2;/// nombre de SLICE/FILTRE par CPU
		    NbMaxCpu =nb_cpu-1;/// nombre de CPU en parall�le
		    offset_frequence=100;//50
	    }
	    else
	    {
		if(TYPE==IS_LOW)
		{
		    SIZE_MIXTE=3;/// nombre de SLICE/FILTRE par CPU
		    NbMaxCpu =nb_cpu/2+1;/// nombre de CPU en parall�le
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
	    }*/
offset_frequence=50;
	    for(i=0; i<nb_cpu ;i++) /// copie des frequences des cpu pour l'�criture  dans les fichiers de sortie
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
	    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	  // if(cpuload_cur[0]<LoadMax){cout<<"cpuLoad_"<<0<<" < "<<LoadMax<<endl;return numerodossier; }
	    /// on va changer l'affinity de NbMaxCpu en parall�le si le ticktimer n'est pas trop �l�v� 
	    ///et le reste se fera de fa�on sequentielle s'il reste encore des  threads
	/*  for(uint t=0;t<=SIZE_MIXTE && ListOuvert !=NULL;t++)
	  {
	    for(uint u=0; u<nb_priority;u++)
	    {
	      indice = Group_Aff[u];
	       for(uint X=0; X<ListOuvert->nb_input;X++)
		  {
		      if(getValAffinity(ListOuvert->TypeAff[X])==AFF_GROUP && ListOuvert->affinity[X]==0)/// pour les affinit� en Groupe : type( A,B,C,....Z)
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
	    
	  }*/
	 // GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);

	    for(uint t=0;t<=SIZE_MIXTE && ListOuvert !=NULL;t++)
	    {
		for(indice=0;indice<NbMaxCpu && ListOuvert !=NULL;indice++)
		{   
		  for(uint X=0; X<ListOuvert->nb_input;X++)/// nombre de branchement par composant (generator, snk...)
		  {
		      if(getValAffinity(ListOuvert->TypeAff[X])==AFF_GROUP && ListOuvert->affinity[X]==0)/// pour les affinit� en Groupe : type( A,B,C,....Z)
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
	    indice=1;
	    cpu_tmp = AccessToCPU(cpu_access,indice);
	    /// fin de la partie parall�le on regarde d'abord s'il n'y plus de threads dans notre liste !
	    if(ListOuvert==NULL)/// si liste vide 
	    {
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		/// maintenant on va v�rifier les cas o� le cpu_0  a un chargement inf�rieur � 5%
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

			for(i=0; i<nb_cpu;i++)/// augementation de la fr�quence de tous les cpu dont le cpuload_cur[]>LoadMax 80.0
			{
			    cpu_tmp = AccessToCPU(cpu_access,i);
			    if(cpuload_cur[i]>LoadMax)
			    {
			      SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25); 
// 				if(TYPE==IS_HYPER_LOW || cpu_tmp->work_frequency<300) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100); }
// 				else
// 				{
// 				    if(TYPE==IS_LOW && cpu_tmp->work_frequency<300) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+75); }
// 				    else { 
// 					if(TYPE==IS_MEDIUM && cpu_tmp->work_frequency<300 )SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50); 
// 					else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25); 
// 					}
// 				}
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
			if(cpuload_cur[indice]<LoadMin  && ListOuvert!=NULL && cpuload_cur[0]>LoadMax) ///si le cpu courant n'est pas assez charg� on lui rajoute des threads
			{
			    for(uint X=0; X<ListOuvert->nb_input;X++)
			    {
				  if(getValAffinity(ListOuvert->TypeAff[X])==AFF_GROUP && ListOuvert->affinity[X]==0)/// pour les affinit� en Groupe : type( A,B,C,....Z)
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
			    indice++;
			}

		    }/// end while
	    }/// end else

//break;

//default:
 //  cout << "partie de d'algo non impl�ment�e " << endl;  break;
    
//}/// fin du Switch

	max=nb_cpu;
	//getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	while(max>0) /// tant qu'il y en aura un cpuload superieur � 83-85%  on augementera la fr�quence 
	{	
	    for(indice=0; indice<nb_cpu && max>0;indice++)/// on regardera tout les niveaux de chargement des CPU qui fonctionnent !
	    {
		if(cpuload_cur[indice]>LoadMax && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency))
		{
		    if(max<=nb_cpu+1) {max++;}
		    cpu_tmp =AccessToCPU(cpu_access,indice);
		   /* if(TYPE==IS_HYPER_LOW) SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
		    if(TYPE==IS_HIGH) SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25);
		    if(TYPE==IS_MEDIUM || TYPE ==IS_LOW) */
		      SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
		    frequence[indice]=cpu_tmp->work_frequency;
		    AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;

		}
		else
		{
		    if(cpuload_cur[indice]>30.0 && cpuload_cur[indice]<LoadMin && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
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
	
 // 	coucou();coucou();e();
	/// maintenant on va v�rifier les cas o� le cpu_0  a un chargement inf�rieur � 40%
	for(i=0;i<nb_cpu-1;i++) { tabcpuload[i]=cpuload_cur[i+1];}
	getMinMaxCpuLoad( tabcpuload,NULL,nb_cpu-1,  0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin); /// recherche min et max  
	if( cpuload_cur[0]<40.0 )
	{
	      cpu_tmp=AccessToCPU(cpu_access,0);
	      FindAndReplaceAffinity(composition_copie,compositionfile_temp,indice_cpuMin+1,0);
	      GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
	      CalculTBC(ListFerme, cpu_access);

	      while(notComprisEntre(cpuload_cur[0],LoadMin,LoadMax) && frequence[0]<(AccessToCPU(cpu_access,0)->end_frequency) && frequence[0]>(AccessToCPU(cpu_access,0)->start_frequency))
	      {
		
		getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		if(cpuload_cur[0]>LoadMax && frequence[0]<=(AccessToCPU(cpu_access,0)->end_frequency))
		  {
		      SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+25);
		      frequence[0]=cpu_tmp->work_frequency;
		      AccessToCPU(cpu_access,0)->work_frequency=cpu_tmp->work_frequency;
		      CalculTBC(ListFerme, cpu_access);

		  }
		  else
		  {
		      if(cpuload_cur[0]>30.0 && cpuload_cur[0]<LoadMin && frequence[0]>(AccessToCPU(cpu_access,0)->start_frequency))
		      {
			  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-25);
			  frequence[0]=cpu_tmp->work_frequency;
			  AccessToCPU(cpu_access,0)->work_frequency=cpu_tmp->work_frequency;
			  CalculTBC(ListFerme, cpu_access);
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
	      GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe,&nb_affinity,&nb_component);
	      CalculTBC(ListFerme, cpu_access);

	      indice=indice_cpuMin;
	      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);

	      while(notComprisEntre(cpuload_cur[indice],LoadMin,LoadMax) && frequence[indice]<(AccessToCPU(cpu_access,indice)->end_frequency) && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
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
		      if(cpuload_cur[indice]>30.0 && cpuload_cur[indice]<LoadMin && frequence[indice]>(AccessToCPU(cpu_access,indice)->start_frequency))
		      {
			  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-25);
			  frequence[indice]=cpu_tmp->work_frequency;
			  AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;

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
	else/// aucun des cas pr�c�dent n'est respect� on quite le programme
	{
	  cout<< "le programme a echou� dans la fonction getSpeedTickTimer(...)\n";
	  cout <<"Raison: dans le fichier "<<input<<" il y a un probl�me de format � la ligne: "<<nb_ligne--<<endl; 
	  exit(0);
	}
      }

}

