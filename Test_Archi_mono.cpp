

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "fonctionsUtils.h"
#include "generatefile.h"
// #include "regularisation.h"
 float LoadMax;
 float LoadMin;

 

using namespace std;

extern CPU thisMesCPU;
extern uint TSIZE;
string BufferFreqHisto;
extern GROUP_TBC GroupAffinity;
extern bool once;
char **_argv;

void coucou()
{cout<<" Free egg : ^_^ coucou @_@ "<<endl;}
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


void GenScriptHistogram(uint nb_cpu)
{
 ofstream output("hist_mono_archi.gnu",ios::trunc);
 output<<"reset\nset yrange [0:100]\nset xrange [-1:]\nset ylabel \"Taux de chargement des CPU (%)\"\n";
 output<<"set label \"Frequence\\n (MHz)\"  at -1,-1 rotate by 0   offset character 0,0,0\n";
 output<<"set style data histogram\nset style histogram cluster gap 5\nset style fill solid border 0.5\nset boxwidth 1.0 \n";
 output<<"set xtics border in scale 0,0 nomirror rotate by 0  offset character 0,0, 0\nset xtics  norangelimit font \",10\"\n";
 
 //output<<;
 output<<"\nplot 'mono_archi_hist.dat' using 1:xticlabels(\""<<BufferFreqHisto<<"\") title \"cpu_0\"";
 for(int i=1; i<nb_cpu;i++)
 output<<", '' using "<<i+1<<" title \"cpu_"<<i<<"\"";
 output<<", "<<LoadMax<<" with lines linecolor rgb \"red\"  title \"Max\", "<<LoadMin<<"  with lines linecolor rgb \"red\" title \"Min\";\npause -1 \n";
}

int main (int argc,char* argv[])
{
  uint nb_component=0,nb_cpu,nb_affinity;
  string includeListe[TSIZE], componentListe[TSIZE],tmp,line;    
  ostringstream convert;
  time_t start,end;
  CPU cpu_tmp=NULL;
   GROUP_TBC ListFerme=NULL;
  double dif;
  G_TBC_InitListe(&GroupAffinity);
    if (argc == 8 && strcmp(argv[1],"DSE")==0)
    {  
	_argv =argv;
	tmp =  argv[argc-1];
        LoadMax=atof(tmp.c_str()); 
	tmp =  argv[argc-2];
	LoadMin=atof(tmp.c_str());      
	time (&start);
	tmp =  string(argv[3])+string(argv[4]);
	ReadCompositionFile(tmp);
	string buffer;
	size_t pos;	
	tmp = string(argv[3])+string(argv[5]);
	ifstream in_compositionfile(tmp.c_str());
	tmp = "listeinclude.txt";
	ifstream cp_include(tmp.c_str());
	int i=0;
	if(in_compositionfile)
	{
	ofstream out_compositionfile("composition_temp.txt"); 
	while(getline(in_compositionfile,line))
	{
	  pos=line.find("include");
 	    if (pos!=-1  && i==0)
	    {
	      while(getline(cp_include,buffer))
	      {
	      out_compositionfile<<"include " << buffer<<";"<<endl;
	      }
	      i=111;
	    }
	    else {
	      if(pos==-1)out_compositionfile<<line<<endl;
	    }
	    
	}

	nb_cpu=NB_CPU(CloneCPU(thisMesCPU));
	once=true;
  	GenerateCompCpuFile("composition_temp.txt","composition.txt",includeListe,componentListe,&nb_affinity,&nb_component);
	CalculTBC(GroupAffinity, CloneCPU(thisMesCPU));	
	once=false;
	
	
	tmp = string(argv[3])+ string(argv[5]);
 	ifstream in_compo(tmp.c_str());
	ofstream out_compo("composition.txt");
 	while(getline(in_compo,buffer)) out_compo<<buffer<<endl;
 	
	buffer = "./get_monocpuload.sh a  \"cnx_write_buffer -cpu ";
	char c[256];
	for(int i=0; i<nb_cpu;i++)  
	{
	  sprintf(c," %d CPU%d ",i,i);
	  buffer = buffer+ c;

	  convert.str(""); convert.clear();
	  convert<<thisMesCPU->work_frequency;

	  thisMesCPU=thisMesCPU->next;
	  BufferFreqHisto=BufferFreqHisto+convert.str()+"  ";
	}
    
	GenScriptHistogram(nb_cpu); 
	sprintf(c," \" %s","Mono");
	buffer = buffer+ c;
	system(buffer.c_str());/// execution d'une ligne de commade :: on aura le % chargement des cpu
	sprintf(c,"cpuloadfile%s/cpuload.txt","Mono");
	ofstream histogram("mono_archi_hist.dat");
	ifstream in(c); 
	float cpuload[nb_cpu];
	for(uint i=0; i<nb_cpu;i++)
	{
	  in>>buffer;
	  in>>buffer;
	  in>> cpuload[i];
	  histogram<<cpuload[i]<< "  ";
	}
	histogram<< "\n";
    }

	time (&end);
	cout<<"Elapsed time: " << int(difftime(end,start))/60 <<" min "<<int(difftime(end,start))%60<<" sec.\n";

    }
    else 
    {
        cout<<"\noption d'execution : ./exec_mono_archi.sh <dossier des fichiers avec TBC> <numero du dossier cpuload  à tester> "<<endl;         
    }
        
  return 0;
}



