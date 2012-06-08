



#include "regularisation.h"
#include <time.h>
extern LISTE_TBC thisTBC;
extern CPU thisMesCPU;
extern uint NbMaxCpu;

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
/*
uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num)
{
      uint i=0,nb_component=0,numerodossier,k=0,l=0,indice=0;
      int frequence[nb_cpu];
      char c[100],NomDossierCpu[100];
      string  tmp2,component,output, input,name;
      float cpuload_cur[nb_cpu];
      string ListeName[100];
      string compositionfile="composition.txt", composition_copie="inputfile/composition_copie.txt",compositionfile_temp="composition_temp.txt";
      CPU cpu_tmp=NULL,cpu_access=NULL;
      LISTE_TBC copieListeTBC=NULL;
      cpu_tmp = CloneCPU(MesCPU);
      cpu_access=CloneCPU(MesCPU);
      uint listeIndice[NbMaxCpu];
      
      bool sortie=true;
      cout<<"fonction : setCpuLoadLevel"<<endl;      
      nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
      
      RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);  
      TBC_Trier(&thisTBC);/// parce que la frequence avait changée!
      TBC_Afficher(thisTBC);
      for(i=0;i<NbMaxCpu;i++)
      {
	listeIndice[i]=i;
      }
      copieListeTBC=CloneListeTBC(thisTBC);

      for(i=0; i<nb_cpu;i++)
      {
	frequence[i]=cpu_tmp->work_frequency;
	cpu_tmp=cpu_tmp->next;
      }
	numerodossier=num;
	i=0;
	l=0;
	k=0;
	//getAllCpuLoad(nb_cpu,numerodossier++,NomDossierCpu,cpuload_cur,frequence);
	//CopieCompositionFile(compositionfile,NomDossierCpu); 
	while(copieListeTBC !=NULL)
	{
	  cpu_tmp=NULL;
	  cpu_access= NULL;
	  cpu_tmp = CloneCPU(MesCPU);
	  cpu_access=CloneCPU(MesCPU);
	  
	  for(i=0;i<NbMaxCpu && copieListeTBC !=NULL;i++)
	  {
	    int o=0;
	    l=listeIndice[i];
	    if (l!=509)
	    {
	     
	    name= copieListeTBC->name;
	    ChangeAffinity(composition_copie,compositionfile_temp,name,l);
	    while((componentListe[o++].compare(name))!=0);
	    o--;
	    component= includeListe[o].substr(0,includeListe[o].size()-10);
	    sprintf(c,"_cpu_%d.txt",l);
	    output= component+c;
	    input ="inputfile/"+component+".txt";
	    cpu_tmp = AccessToCPU(cpu_access,l);
	    GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
	    copieListeTBC=copieListeTBC->next;
	    }
	  }
	  
	  nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
// 	  RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	  getAllCpuLoad(nb_cpu,numerodossier++,NomDossierCpu,cpuload_cur,frequence);
	  CopieCompositionFile(compositionfile,NomDossierCpu);  
	  for(i=0;i<NbMaxCpu;i++)
	  {
 	    if(cpuload_cur[listeIndice[i]]<75.0)
	    {
	      listeIndice[i]=i;
	    }
	    else{
		if(cpuload_cur[listeIndice[i]]>75.0&& nb_cpu>NbMaxCpu && NbMaxCpu+i<nb_cpu)
		{
		   if(!notComprisEntre(cpuload_cur[listeIndice[i]],82.0,97.0)) 
		   {
		     MesCPU=AccessToCPU(MesCPU,listeIndice[i]);
		     UpFreqCpu(MesCPU,100);		    
		   }
		  listeIndice[i]=NbMaxCpu+i;
		}
	      else
	      {
		listeIndice[i]=509;/// valeur pour éviter les cas déja fait ou bien complet 
	      }
	      
	    }
	  }
	  
		    
		     for(i=0; i<nb_cpu-1;i++)
		      {
			frequence[i]=AccessToCPU(MesCPU,i)->work_frequency;
			cout<<"i is: "<<i<<endl;
		      }
		      
		      cout<<"out"<<endl;


		
// 		   if(cpuload_cur[l]<75 && copieListeTBC!=NULL )
// 		   {
// 			
// 		      int o=0;
// 		      tmp2 = copieListeTBC->name;
// 		      ChangeAffinity(composition_copie,compositionfile_temp,tmp2,l);
// 		      nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
// 		      while((componentListe[o++].compare(tmp2))!=0);o--;
// 		      component= includeListe[o].substr(0,includeListe[o].size()-10);
// 		      sprintf(c,"_cpu_%d.txt",l);
// 		      output= component+c;
// 		      input ="inputfile/"+component+".txt";
// 		      cpu_tmp = AccessToCPU(cpu_access,l);
// 		      GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
// 		      input.clear();
// 		      component.clear();
// 		      output.clear();
// 		      copieListeTBC=copieListeTBC->next;
// 		   }
// 		   else {l++;
// 		   		      copieListeTBC=copieListeTBC->next;
// 		   }
		
// 		      getAllCpuLoad(nb_cpu,numerodossier++,NomDossierCpu,cpuload_cur,frequence);
// 		      CopieCompositionFile(compositionfile,NomDossierCpu);  
// 		        		      copieListeTBC=copieListeTBC->next;
// 
// 			if(l>nb_cpu)
// 			{
// 			   l=0;
// 			}

	  
	  
	}
	
	getAllCpuLoad(nb_cpu,numerodossier++,NomDossierCpu,cpuload_cur,frequence);
	if(cpuload_cur[0]<10.0 && cpuload_cur[nb_cpu-1]<75.0)
	{
	  FindAndReplaceAffinity(composition_copie,compositionfile_temp,nb_cpu-1,0);
	  nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
	  RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);
	  getAllCpuLoad(nb_cpu,numerodossier++,NomDossierCpu,cpuload_cur,frequence);

	}
	return numerodossier;
}
*/


uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num)
{
      uint i=0,nb_component=0,numerodossier,k=0,l=0,indice=0;
      int frequence[nb_cpu];
      char c[100],NomDossierCpu[100];
      string  tmp2,component,output, input;
      float cpuload_cur[nb_cpu];
      string ListeName[100];
      string compositionfile="composition.txt", composition_copie="inputfile/composition_copie.txt",compositionfile_temp="composition_temp.txt";
      CPU cpu_tmp=NULL,cpu_access=NULL;
      LISTE_TBC copieListeTBC=NULL;
      cpu_tmp = CloneCPU(MesCPU);
      cpu_access=CloneCPU(MesCPU);
      
      bool sortie=true;
      nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
      RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);  
      TBC_Trier(&thisTBC);/// parce que la frequence avait changée!
      TBC_Afficher(thisTBC);
      copieListeTBC=CloneListeTBC(thisTBC);
      for(i=0; i<nb_cpu;i++)
      {
	if(cpu_tmp->work_frequency<200)
	{
	SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
	AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
	}
	frequence[i]=cpu_tmp->work_frequency;
	cpu_tmp=cpu_tmp->next;
      }
	numerodossier=num;
	i=0;
	k=0;

	if(nb_cpu>NbMaxCpu+1)
	{
	  for(uint t=0;t<=NbMaxCpu;t++)
	  {
	    for(l=1;l<=NbMaxCpu && copieListeTBC !=NULL;l++)
	    {
	      if(nb_cpu>l)/// :d petite précaution
	      {
		int o=0;
		tmp2= copieListeTBC->name;
		ChangeAffinity(composition_copie,compositionfile_temp,tmp2,l);
		nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
		while((componentListe[o++].compare(tmp2))!=0);
		o--;
		component= includeListe[o].substr(0,includeListe[o].size()-10);
		sprintf(c,"_cpu_%d.txt",l);
		output= component+c;
		input ="inputfile/"+component+".txt";
		cpu_tmp = AccessToCPU(cpu_access,l);
		GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
		copieListeTBC=copieListeTBC->next;
	      }
	    }/// fin parallèle
	  }
	  l=1;
	cpu_tmp = AccessToCPU(cpu_access,l);
	}
	
	if(copieListeTBC==NULL)
	{
	  sortie = false;
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	  int max=nb_cpu-1;
	  while(max>0)
	  {
	   
	      for(i=1; i<nb_cpu && max>0;i++)
	      {
		
		  if(cpuload_cur[i]>83.0)
		  {
		    if(max<nb_cpu-1)max++;
		  cpu_tmp = AccessToCPU(cpu_access,i);
		  if(cpu_tmp->work_frequency<400)SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
		  else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
		  frequence[i]=cpu_tmp->work_frequency;
		  AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
		  RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
		  }
		  else if(max>1)max--;
// 		  cout <<" cpu_"<<i<<" : "<<cpuload_cur[i]<<endl;
// 		  cout << " max "<< max<<endl;
// 		  sleep(1.0);
	      }
	       if(max>0)
	       {
		 getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
		 max--;
	       }
	  }
	  float MaxCpuload,MinCpuload, tabcpuload[nb_cpu-1];
	  uint indice_cpuMax, indice_cpuMin;

	  for(i=0;i<nb_cpu-1;i++)
	  {
	  
	    tabcpuload[i]=cpuload_cur[i+1];
// 	     cout <<" cpu_"<<i<<" : "<< tabcpuload[i]<<endl;
	    
	  }
	  getMinMaxCpuLoad( tabcpuload,NULL,nb_cpu-1,  0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin);
	  
// 	  cout <<" Max : "<< MaxCpuload << " cpu_"<<indice_cpuMax<<endl;
// 	  cout <<" Min : "<< MinCpuload << " cpu_"<<indice_cpuMin<<endl;
// 	  exit(0);
	  if(cpuload_cur[0]<5.0 && cpuload_cur[indice_cpuMin+1]<80.0)
	  {
	  cpu_tmp=AccessToCPU(cpu_access,0);
	  FindAndReplaceAffinity(composition_copie,compositionfile_temp,indice_cpuMin+1,0);
	  nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
	  RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);

	  }
	}
	
	while(copieListeTBC !=NULL && sortie)
	{
	  for(i=1; i<nb_cpu;i++)
	  {
	    cpu_tmp = AccessToCPU(cpu_access,i);
	    if(cpuload_cur[i]>83.0)
	    {
	      if(cpu_tmp->work_frequency<400)SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
	      else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
		AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
		RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	    }
	    frequence[i]=cpu_tmp->work_frequency;
	  }

	  cpu_tmp = AccessToCPU(cpu_access,l);
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);

	  if(cpuload_cur[l]<70.0  && copieListeTBC!=NULL )
	  {

	    tmp2 = copieListeTBC->name;
	    int o=0;
	    ChangeAffinity(composition_copie,compositionfile_temp,tmp2,l);
	    nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
	    while((componentListe[o++].compare(tmp2))!=0);
	      o--;
	    component= includeListe[o].substr(0,includeListe[o].size()-10);
	    cout<<"name :"<<tmp2<<endl;
	    cout<<"component :"<<component<<endl;
	    sprintf(c,"_cpu_%d.txt",l);
	    output= component+c;
	    input ="inputfile/"+component+".txt";
	    GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
	    copieListeTBC=copieListeTBC->next;
	
	    
	  }
	  else
	  {
	      
		if(l<nb_cpu)
		{
	      if(cpuload_cur[l]>85.0)
		{
		  if(cpu_tmp->work_frequency<400)SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
		  else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
		  frequence[l]=cpu_tmp->work_frequency;
		  AccessToCPU(cpu_access,l)->work_frequency=cpu_tmp->work_frequency;
		}
		 else{ l++;
		  if(l>=nb_cpu){ l=0;sortie=false;}
		 }
		  
		}
		
	      cout<<"cpu_"<< l<<endl;
	  }
	  
	}/// end while
	/*
	//getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	if(cpuload_cur[0]<5.0 && cpuload_cur[nb_cpu-1]<82.0)
	{
	  cpu_tmp=AccessToCPU(cpu_access,0);
	  FindAndReplaceAffinity(composition_copie,compositionfile_temp,l,0);
	  nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
	  RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);

	}else
	{
	  */
	  l=0;
	  cout<<"zetre while"<<endl;
	  while(cpuload_cur[l]>85.0)
	  {
	    cpu_tmp =AccessToCPU(cpu_access,l);
	  if(cpu_tmp->work_frequency<200)SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
	  else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
	  frequence[l]=cpu_tmp->work_frequency;
	  AccessToCPU(cpu_access,l)->work_frequency=cpu_tmp->work_frequency;
	  RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	  }
	thisMesCPU=NULL;

	
	return numerodossier;
}


/**
uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num)
{
      uint i=0,nb_component=0,numerodossier,k=0,l=0,indice=0;
      int frequence[nb_cpu];
      char c[100],NomDossierCpu[100];
      string tmp, tmp2,component,include;
      float cpuload_cur[nb_cpu];
      string ListeName[100];
      string compositionfile="composition.txt", composition_copie="inputfile/composition_copie.txt",compositionfile_temp="composition_temp.txt";
      CPU cpu_tmp=NULL,cpu_access=NULL;
      LISTE_TBC copieListeTBC=NULL;
      cpu_tmp = CloneCPU(MesCPU);
      cpu_access=CloneCPU(MesCPU);
      copieListeTBC=CloneListeTBC(thisTBC);
      bool sortie=true;
      
      
      nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
      RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);  
      for(i=0; i<nb_cpu;i++)
      {
	frequence[i]=cpu_tmp->work_frequency;
	cpu_tmp=cpu_tmp->next;
      }
	numerodossier=num;
	i=0;
	l=0;
	k=0;
	getAllCpuLoad(nb_cpu,numerodossier++,NomDossierCpu,cpuload_cur,frequence);
	CopieCompositionFile(compositionfile,NomDossierCpu); 
	cpu_tmp = AccessToCPU(cpu_access,l);
	ListeName[i++]="main";
	while(copieListeTBC !=NULL && sortie)
	{
	  
	  if(cpuload_cur[l]<75  && copieListeTBC!=NULL )
	  {
		if((copieListeTBC->name.compare("main"))==0)
		{
		  copieListeTBC=copieListeTBC->next;

		}
		else
		{
		tmp2 = copieListeTBC->name;
		      if(notFindName(ListeName,tmp2,i-1)&&!(cpuload_cur[0]>60 && cpuload_cur[0]<80))
		      {
		      ChangeAffinity(composition_copie,compositionfile_temp,tmp2,l);
		      nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
		      component= tmp2.substr(0,tmp2.size()-1);
		      cout<<"name :"<<tmp2<<endl;
		      cout<<"component :"<<component<<endl;
		      sprintf(c,"_cpu_%d.txt",l);
		      include= component+c;
		      tmp ="inputfile/"+component+".txt";
		      GenerateCpuFile(include,tmp,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
		      tmp.clear();
		      component.clear();
		      include.clear();
		      copieListeTBC=copieListeTBC->next;
		      getAllCpuLoad(nb_cpu,numerodossier++,NomDossierCpu,cpuload_cur,frequence);
		      CopieCompositionFile(compositionfile,NomDossierCpu);  
		      ListeName[i++]=tmp2;
		      }
		      else 
		      {
			cout<<"deja fait : "<<tmp2<<endl;
			k++;
			copieListeTBC=copieListeTBC->next;
		      }
		

		}
	    
	  }
	  else
	  {
	     if(cpuload_cur[nb_cpu-1]>75)  sortie=false;
	      if(l<nb_cpu)
	      {
		l++;
		if(cpu_tmp->next!=NULL){cpu_tmp=cpu_tmp->next;}
		else {l=0;cpu_tmp = AccessToCPU(cpu_access,l);}
		
	      }
	      else 
	      {
		l=0;
		cpu_tmp = AccessToCPU(cpu_access,l);
	      }
	     
	      cout<<"cpu_"<< l<<endl;

	  }
	  
	}
	
	cout<<k<<" deja fait\n restant de la liste "<<endl;
	
	//for(int o=0;o<i;o++)cout<<"ListeName["<<o<<"] "<<ListeName[o]<<endl;
	///TBC_Afficher(thisTBC); 
	delete(thisTBC);
	thisTBC=NULL;
	return numerodossier;
}
**/
