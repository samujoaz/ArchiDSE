



#include "regularisation.h"
extern LISTE_TBC thisTBC;
//extern CPU thisMesCPU;

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
      
      for(i=0; i<nb_cpu;i++)
      {
	frequence[i]=cpu_tmp->work_frequency;
	cpu_tmp=cpu_tmp->next;
      }

	
 	nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
 	//RegenerateCpuFile(includeListe,componentListe,nb_component);
	numerodossier=num;
	i=0;
	l=0;
	k=0;
	getAllCpuLoad(nb_cpu,numerodossier++,NomDossierCpu,cpuload_cur,frequence);
	CopieCompositionFile(compositionfile,NomDossierCpu); 
	cpu_tmp = AccessToCPU(cpu_access,l);
	ListeName[i++]="main";
	while(copieListeTBC !=NULL )
	{
	  
	  if(cpuload_cur[l]<75  && copieListeTBC!=NULL)
	  {
	    if((copieListeTBC->name.compare("main"))==0)
	    {
	      copieListeTBC=copieListeTBC->next;

	    }
	    else
	    {
	     tmp2 = copieListeTBC->name;
// 	     if(getAffinityOf(composition_copie,tmp2)==0 && !(cpuload_cur[0]>60 && cpuload_cur[0]<80))
	    if(notFindName(ListeName,tmp2,i-1) && !(cpuload_cur[0]>60 && cpuload_cur[0]<85))
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
	     //sleep(2.0);
	     }
	     else 
	     {
	       cout<<"deja fait : "<<tmp2<<endl;
	       k++;
	       //ListeName[i++]=tmp2;
	       copieListeTBC=copieListeTBC->next;
		  // sleep(2.0);
	     }
	    

	    }
	    
	  }
	  else
	  {
	    
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
	
	return numerodossier;
}