

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>


#include "fonctionsUtils.h"
#include "generatefile.h"
#include "utils.h"

using namespace std;

extern COMPONENTDSP thisComposantsDSP;
extern COMPONENTCPU thisComposantsCPU;
extern CPU thisMesCPU;
extern uint nb_fichier_include;

int main (int argc,char* argv[])
{
  uint i=0,nb_component=0,j=0,k=0,l=1;
  uint nb_cpu,indice_cpu,deltafreq=100,nb_aff=1;
  char carac[100],c[100];
  string includeListe[nb_fichier_include],tmp, componentListe[nb_fichier_include];
  string out;
  bool sortir=true;
  CPU cpu_tmp=NULL;


    if (argc == 5 && strcmp(argv[1],"DSE")==0)
    { 
	ReadCompositionFile(argv[2]);
        nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
	nb_cpu=NB_CPU(thisMesCPU);
	RegenerateCpuFile(includeListe,nb_component);
	float  cpuload_ref=80.0, cpuload_total=0.0, cpuload_cur[nb_cpu], cpuload_err[nb_cpu];
// 	float  cpuload_ref=80.0, cpuload_prec=0.0, cpuload_cur, cpuload_err;
	j=0;
	i=0;
	indice_cpu=0;
	FindAndReplaceAffinity("temp.txt","kiki.txt",componentListe[l++],1,2);

	
	/*
	while(indice_cpu<nb_cpu && sortir)
	{
	  	getCpuLoad(nb_cpu,j++,carac,cpuload_cur);
		while(!(cpuload[indice_cpu]<cpuload_ref-10 && cpuload[indice_cpu]>cpuload_ref-5 ) )
		{
		  
		}
		indice_cpu++;
		

	  
	}*/
	
/*
 while(cpuload_total<90.0)
 {
	getCpuLoad(nb_cpu,j++,carac,cpuload_cur);
	cpuload_total=0.0;
	for(i=0;i<nb_aff;i++)
	{
	
	      cpuload_err[i]= cpuload_ref-cpuload_cur[i];
	      cpu_tmp = AccessToCPU(thisMesCPU,i);
	      cout<<"cpuload_cur["<<i<<"]: "<<cpuload_cur[i]<<endl;
	      cout<<"cpuload_err["<<i<<"]: "<<cpuload_err[i]<<endl;
	      
	      if(cpuload_err[i]< -10.0)
	      {
		  UpFreqCpu(cpu_tmp,deltafreq);
		  nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
		  CopieCompositionFile("composition.txt", carac);
		  RegenerateCpuFile(includeListe,nb_component);
		  cout<<"up frequency"<<endl;
	      
	      }
	      else
	      {
		  if(cpuload_err[i]> 10.0)
		  {
		    DownFreqCpu(cpu_tmp,deltafreq);
		    nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
		    CopieCompositionFile("composition.txt", carac);
		    RegenerateCpuFile(includeListe,nb_component);
		    cout<<"down frequency"<<endl;
		  }
		  else
		  {
		      if(cpuload_err[i]> -10 && cpuload_err[i]<10)
		      {
			if(l>=nb_component)l=0;
			if(k>nb_cpu-1){k=0;nb_aff++;
			  if (nb_aff>nb_cpu) nb_aff=1;
			}
			ChangeAffinity("copiecomposition.txt","newcomposition.txt",componentListe[l++],k++);
			nb_component = GenerateCompCpuFile("newcomposition.txt","composition.txt",includeListe,componentListe);
			CopieCompositionFile("composition.txt", carac);
			RegenerateCpuFile(includeListe,nb_component);
			cout<<"affinity"<<endl;
			//if(cpuload_cur[0]<cpuload_ref-10.0 && cpuload_cur[0]>cpuload_ref+10) nb_aff=2; 
			
		      }
		  }
		  
	      }
	      cpuload_total=cpuload_cur[i]+cpuload_total;
	      cout<<"cpuload_total: "<<cpuload_total<<endl;
	      	      sleep(2.0);

	}
	
}
	*/
	/*
	

      while(indice_cpu<nb_cpu)
      {
	
	 getCpuLoad(indice_cpu,j++,carac,&cpuload_err);

	cpuload_err = cpuload_cur-cpuload_prec;
	cpu_tmp = AccessToCPU(thisMesCPU,indice_cpu);
	i=j;
	sortir=true;
 	k++;
	if(l>=nb_component)l=1;
 	if(k>nb_cpu-1)k=0;
	      while(!(cpuload_cur<cpuload_ref+5 && cpuload_cur>cpuload_ref-5) && j<i+3 && sortir)
	      {
				      cout<<"cpuload_err: "<<cpuload_err<<endl;sleep(2.0);
		  //if(l>=nb_component)l=1;
		  if(cpuload_cur>cpuload_ref && cpuload_err> 5.0)
		  {
		    UpFreqCpu(cpu_tmp,100);    
		    nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
		    CopieCompositionFile("composition.txt", carac);
		    RegenerateCpuFile(includeListe,nb_component);
		    j++;
		    cout<<"up frequency"<<endl;
		  }
		  else
		  {
		    if(cpuload_cur < cpuload_ref && cpuload_err< -5.0)
		    {
		      DownFreqCpu(cpu_tmp,100);    
		      nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
		      CopieCompositionFile("composition.txt", carac);
		      RegenerateCpuFile(includeListe,nb_component);
		      j++;
		    cout<<"down frequency"<<endl;
		      
		    }
		    else
		    {
		      if(cpuload_err> -5 && cpuload_err<5)
		      {
			indice_cpu++;
			//cpuload_ref=10;
			sortir=false;
		      }
		      else
		      {
		  	ChangeAffinity("copiecomposition.txt","newcomposition.txt",componentListe[l++],k);
			nb_component = GenerateCompCpuFile("newcomposition.txt","composition.txt",includeListe,componentListe);
			CopieCompositionFile("composition.txt", carac);

		    	RegenerateCpuFile(includeListe,nb_component);

			cout<<"affinity"<<endl;

		      }
		    }
		  }

// 		

	      cpuload_prec=cpuload_cur;
	      getCpuLoad(indice_cpu,j++,carac,&cpuload_cur);
	      cpuload_err = cpuload_cur-cpuload_prec;
	      sleep(2.0);
	      }
	      //indice_cpu++;
	     // cpuload_ref=100.0-cpuload_prec;
	      ChangeAffinity("copiecomposition.txt","newcomposition.txt",componentListe[l++],k);
	      nb_component = GenerateCompCpuFile("newcomposition.txt","composition.txt",includeListe,componentListe);
	      CopieCompositionFile("composition.txt", carac);
	      RegenerateCpuFile(includeListe,nb_component);
    }
*/

    }
    else 
    {
         cout<<"\noption d'execution : DSE <inputArchi> <inputComposition> "<<endl;         
    }
        
        
        return 0;
}


/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>


#include "fonctionsUtils.h"
#include "generatefile.h"
#include "utils.h"

using namespace std;

extern COMPONENTDSP thisComposantsDSP;
extern COMPONENTCPU thisComposantsCPU;
extern CPU thisMesCPU;
extern uint nb_fichier_include;

int main (int argc,char* argv[])
{
  uint i=0,nb_component=0,j=0,k=0,l=1;
  uint nb_cpu,indice_cpu;
  char carac[100],c[100];
  string includeListe[nb_fichier_include],tmp, componentListe[nb_fichier_include];
  string out;

  CPU cpu_tmp=NULL;


    if (argc == 5 && strcmp(argv[1],"DSE")==0)
    { 
	ReadCompositionFile(argv[2]);
        nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
	nb_cpu=NB_CPU(thisMesCPU);
	float CPULOAD[nb_cpu], cpuload_ref=80.0, cpuload_prec=80.0, cpuload_cur=0.0f, cpuload_err=0.0f;
	
	bool sortir=true;

// 	while(i<nb_component)
// 	{
// 	  tmp= includeListe[i].substr(0,includeListe[i].size()-4);
// 	  indice_cpu=atoi(includeListe[i].substr(tmp.size()-1,tmp.size()).c_str());
// 	  tmp.clear();
// 	  tmp= includeListe[i].substr(0,includeListe[i].size()-10);
// 	  tmp = "inputfile/"+tmp+".txt";
// 	  cpu_tmp = AccessToCPU(thisMesCPU,indice_cpu);
// 	  GenerateCpuFile(includeListe[i],tmp,cpu_tmp,"_comp","_behaviour","_timing_characs");
// 	  tmp.clear();
// 	  i++; 
// 	} 
	RegenerateCpuFile(includeListe,nb_component);

	
	
	/// partie  Asserve.
	j=0;
	i=0;
	indice_cpu=0;
	
// 	while(){
	ChangeAffinity(argv[3],"temp.txt",componentListe[i],l);
        nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
	cpu_tmp = AccessToCPU(thisMesCPU,l);
	SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
	tmp = "inputfile/"+componentListe[i]+".txt";
	sprintf(c,"_cpu_%d.txt",l);
	out=componentListe[i]+c;
	GenerateCpuFile(out,tmp,cpu_tmp,"_comp","_behaviour","_timing_characs");
	
	
// 	}

	


//	sleep(1.0);

      while(indice_cpu<nb_cpu)
      {
	
	cpuload_cur =getCpuLoad(indice_cpu,j++,carac);
	//cout<<carac<<endl;
	//cout<<"load cpu_"<<indice_cpu<<" : "<<cpuload_cur<<endl<<"attente....2s"<<endl;
	//sleep(2.0); 
	cpuload_err = cpuload_cur-cpuload_prec;
	cpu_tmp = AccessToCPU(thisMesCPU,indice_cpu);
	i=j;
	sortir=true;
 	k++;
	if(l>=nb_component)l=1;
 	if(k>nb_cpu-1)k=0;
	      while(!(cpuload_cur<cpuload_ref+5 && cpuload_cur>cpuload_ref-5) && j<i+3 && sortir)
	      {
				      cout<<"cpuload_err: "<<cpuload_err<<endl;sleep(2.0);
		  //if(l>=nb_component)l=1;
		  if(cpuload_cur>cpuload_ref && cpuload_err> 5.0)
		  {
		    UpFreqCpu(cpu_tmp,100);    
		    nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
		    CopieCompositionFile("composition.txt", carac);
		    RegenerateCpuFile(includeListe,nb_component);
		    j++;
		    cout<<"up frequency"<<endl;
		  }
		  else
		  {
		    if(cpuload_cur < cpuload_ref && cpuload_err< -5.0)
		    {
		      DownFreqCpu(cpu_tmp,100);    
		      nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
		      CopieCompositionFile("composition.txt", carac);
		      RegenerateCpuFile(includeListe,nb_component);
		      j++;
		    cout<<"down frequency"<<endl;
		      
		    }
		    else
		    {
		      if(cpuload_err> -5 && cpuload_err<5)
		      {
			indice_cpu++;
			//cpuload_ref=10;
			//sortir=false;
		      }
		      else
		      {
		  	ChangeAffinity("copiecomposition.txt","newcomposition.txt",componentListe[l++],k);
			nb_component = GenerateCompCpuFile("newcomposition.txt","composition.txt",includeListe,componentListe);
			CopieCompositionFile("composition.txt", carac);

		    	RegenerateCpuFile(includeListe,nb_component);

			cout<<"affinity"<<endl;

		      }
		    }
		  }

// 		  if(cpuload_cur>90)/// frequence<500 et %load grande
// 		  {
// 		    UpFreqCpu(cpu_tmp,50);
// 		  // ChangeAffinity(argv[3],"temp.txt",componentListe[l++],0);
// 		    nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
// 		    RegenerateCpuFile(includeListe,nb_component);
// 		  // if(l>=nb_component)l=0;
// 		  }
// 		  if(cpuload_cur<70)/// frequence<500 et %load grande
// 		  {
// 		  //  ChangeAffinity(argv[3],"temp.txt",componentListe[l++],0);
// 		    DownFreqCpu(cpu_tmp,50);
// 		    nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
// 		    RegenerateCpuFile(includeListe,nb_component);		  
// 		  //  if(l>=nb_component)l=0;
// 
// 		  }
// 		  if(cpuload_cur<=0) sortir=false;
		  //else UpFreqCpu(cpu_tmp,100);
		  
// 		cout<<"load cpu_"<<indice_cpu<<" : "<<cpuload_cur<<endl<<"attente....2s"<<endl;
		      //cout<<"cpuload_err: "<<cpuload_err<<endl;sleep(2.0);

	      cpuload_prec=cpuload_cur;
	      cpuload_cur =getCpuLoad(indice_cpu,j++,carac);
	      cpuload_err = cpuload_cur-cpuload_prec;
	      }
	      //indice_cpu++;
	      cpuload_ref=100.0-cpuload_prec;
	      ChangeAffinity("copiecomposition.txt","newcomposition.txt",componentListe[l++],k);
	      nb_component = GenerateCompCpuFile("newcomposition.txt","composition.txt",includeListe,componentListe);
	      CopieCompositionFile("composition.txt", carac);
	      RegenerateCpuFile(includeListe,nb_component);
    }
// 	while(CPULOAD[indice_pcu]>70.0 && j<nb_component)
// 	{
// 	  	//sleep(2.0);
// 	      ifstream in(c);
// 	      in>>tmp;
// 	      in>>tmp;
// 	      in>> CPULOAD[indice_cpu];
// 	      sprintf(c,". ./compile.sh a %d",j);
// 	      system(c);/// on aura le % dechargement des cpu
// 	      sprintf(c,"cpuloadfile%d/cpuload.txt",j);
//  	      
//   	      ChangeAffinity(argv[3],"temp.txt",componentListe[k],l);
// 	      
// 	      cpu_tmp = AccessToCPU(thisMesCPU,0);
// 	      SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-200);
//  	      //nb_component = GenerateCompCpuFile(argv[3],"composition.txt",includeListe,componentListe);
// 	      i=0;
// 	      j++;
// 		while(i<nb_component)
// 	      {
// 		tmp= includeListe[i].substr(0,includeListe[i].size()-4);
// 		indice=atoi(includeListe[i].substr(tmp.size()-1,tmp.size()).c_str());
// 		tmp.clear();
// 		tmp= includeListe[i].substr(0,includeListe[i].size()-10);
// 		tmp = "inputfile/"+tmp+".txt";
// 		cpu_tmp = AccessToCPU(thisMesCPU,indice);
// 		GenerateCpuFile(includeListe[i],tmp,cpu_tmp,"_comp","_behaviour","_timing_characs");
// 		tmp.clear();
// 		i++; 
// 	      }
// 	      sleep(2.0);
// 		
// 	}
// 	Affiche_CPU(thisMesCPU);

	    //sprintf(carac,"%s%d",argv[4],i);
	
	//out = argv[4]+carac;
	//cout<<carac<<endl;
	//SetWorkFrequencyCPU(AccessToCPU(thisComposantsCPU->CPU_,0),700);
	//ifstream in("cpuloadfile0/cpuload.txt");
	//while(getline(in,tmp))cout <<tmp<<endl;
	

    }
    else 
    {
         cout<<"\noption d'execution : DSE <inputArchi> <inputComposition> "<< "\ninput: is a txt file "<<endl;         
    }
        
        
        return 0;
}
  */

  
