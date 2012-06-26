

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>


#include "fonctionsUtils.h"
#include "generatefile.h"
#include "utils.h"
#include "regularisation.h"
#define NbBoucle 1

using namespace std;

extern COMPONENTDSP thisComposantsDSP;
extern COMPONENTCPU thisComposantsCPU;
extern CPU thisMesCPU;
extern LISTE_TBC thisTBC;
extern uint TSIZE;
extern float TableTBC[100];
extern uint nbTBC;
char **_argv;
extern float LoadMax;
extern float LoadMin;


int main (int argc,char* argv[])
{
  uint nb_cpu,nb_component=0,indice_cpu,i=0,frequence;
  uint numerodossier=0;
  char folder[100];
  string includeListe[TSIZE], componentListe[TSIZE],tmp;    
  cpu *cpu_tmp=NULL,*cpu_nb=NULL,*access_cpu=NULL;
  
         TBC_InitListe(&thisTBC);/// � faire une seule fois

  time_t start,end;
  char szInput [256];
  double dif;

 
    if (argc == 7 && strcmp(argv[1],"DSE")==0)
    {  
	_argv =argv;
	tmp =  argv[argc-1];
        LoadMax=atof(tmp.c_str()); 
	tmp =  argv[argc-2];
	LoadMin=atof(tmp.c_str());      
	time (&start);
	ReadCompositionFile(argv[2]);
  	nb_cpu=NB_CPU(CloneCPU(thisMesCPU));
 	CPU TabCPU[nb_cpu];
	CopieCompositionFile(argv[3],"inputfile/");//copie qu'on pourra travailler dessus
 	
// 	for(int o=0;o<NbBoucle;o++) 
// 	{ TabCPU[o]=CloneCPU(thisMesCPU); 
// 	}
// 	
 	for(int o=0;o<NbBoucle;o++)
 	{	
	      TabCPU[o]=CloneCPU(thisMesCPU); 
 	      cpu_tmp = TabCPU[o];
	      
	      for (int i=0; i<nb_cpu;i++)
	      {
		FindAndReplaceAffinity("inputfile/composition_copie.txt","composition_temp.txt",i,0);
 		//if(o!=0)
		//  UpFreqCpu(cpu_tmp,100);
		//cpu_tmp=cpu_tmp->next;
	      }
	
	 //RegenerateCpuFile(TabCPU[o],includeListe,componentListe,nb_component); 
	      numerodossier = numerodossier+ setCpuLoadLevel(TabCPU[o],nb_cpu,includeListe,componentListe,numerodossier);
	      
	      GenScriptHistogram(nb_cpu ); 

	     thisMesCPU = TabCPU[o];
	     cout<<"fin setCpuLoadLevel : "<< o<<endl;
// 	    cout<<"wait "<<2<<" sec..."<<endl; sleep(2);
	}
	
	time (&end);
	cout<<"Elapsed time: " << int(difftime(end,start))/60 <<" min "<<int(difftime(end,start))%60<<" sec.\n";


    }
    else 
    {
        cout<<"\noption d'execution : DSE <inputArchi> <inputComposition> <ouput folder name> "<<endl;         
    }
        
        
        return 0;
}

/*
 * 
 * reset
set yrange [0:100]
set xrange [-1:]
set ylabel "Taux de chargement des CPU (%)"
set label "Frequence\n (MHz)"  at -1,-1 rotate by 0   offset character 0,-0.5, 0
set style data histogram
set style histogram cluster gap 4
set style fill solid border -1
set boxwidth 1.0
set xtics border in scale 0,0 nomirror rotate by 90  offset character 1,-1, 0
set xtics  norangelimit font ",7.5"
set xtics ("100\n200\n100\n200\n300" 0, "100\n200\n100\n200\n300" 1,"100\n200\n100\n200\n300" 2, "100\n200\n100\n200\n300" 3, "100\n200\n100\n200\n300" 4,"100\n200\n100\n200\n300" 5,"100\n200\n100\n200\n300" 6)
plot 'all_cpu_hist.dat' using 1  title "cpu_0", '' using 2  title "cpu_1", '' using 3 title "cpu_2", '' using 4 title "cpu_3", '' using 5 title "cpu_4", 85 with lines linecolor rgb "red"  title "Max", 70 with lines linecolor rgb "red" title "Min";

pause -1 
*/

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
extern uint TSIZE;

int main (int argc,char* argv[])
{
  uint i=0,nb_component=0,j=0,k=0,l=1;
  uint nb_cpu,indice_cpu;
  char carac[100],c[100];
  string includeListe[TSIZE],tmp, componentListe[TSIZE];
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

  
