

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "fonctionsUtils.h"
#include "generatefile.h"
#include "regularisation.h"



using namespace std;

extern CPU thisMesCPU;
extern uint TSIZE;
string BufferFreqHisto;

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
 output<<", 85 with lines linecolor rgb \"red\"  title \"Max\", 70 with lines linecolor rgb \"red\" title \"Min\";\npause -1 \n";
}

int main (int argc,char* argv[])
{
  uint nb_component=0,nb_cpu;
  string includeListe[TSIZE], componentListe[TSIZE];    
ostringstream convert;
  time_t start,end;
  double dif;

    if (argc == 4 && strcmp(argv[1],"DSE")==0)
    {  
	time (&start);
	string buffer;
	 size_t pos;	
	 ReadCompositionFile(argv[2]);
	ifstream in_compositionfile(argv[3]);
	if(in_compositionfile)
	{
	ofstream out_compositionfile("composition.txt",ios::trunc); 
	ofstream out_composition_tmp("composition_temp.txt",ios::trunc); 
	buffer="include main.txt;\ninclude slice.txt;\ninclude filter.txt;\ninclude write_buffer.txt;\n\n";
	out_composition_tmp<<buffer;
	 while(getline(in_compositionfile,buffer))
	 {
	    out_compositionfile<<buffer<<endl;
	    pos=buffer.find("include");
	    if (pos==-1) out_composition_tmp<<buffer<<endl;
	    
	 }
	nb_cpu=NB_CPU(CloneCPU(thisMesCPU));
	
	nb_component = GenerateCompCpuFile("composition_temp.txt","composition_copie.txt",includeListe,componentListe);
 	RegenerateCpuFile(thisMesCPU,includeListe,componentListe,nb_component); 
	buffer = ". ./get_monocpuload.sh a  \"cnx_write_buffer -cpu ";
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
// 	  if(cpuload[i]>0.0) 
	    histogram<<cpuload[i]<< "  ";
// 	  else histogram<< "0.5  ";
	}
	histogram<< "\n";
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



