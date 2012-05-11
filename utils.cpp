
#include "utils.h"

extern COMPONENTDSP thisComposantsDSP;
extern COMPONENTCPU thisComposantsCPU;
extern CPU thisMesCPU;

using namespace std;


void DownFreqCpu(CPU C, uint delta)
{
  SetWorkFrequencyCPU(C,C->work_frequency-delta);
//   if (C->work_frequency-delta>=C->start_frequency)  SetWorkFrequencyCPU(CPU mon_cpu, uint new_freq)C->work_frequency=C->work_frequency-delta;
//   else cout<<"frequence too low, can not decrease"<<endl;
}

void UpFreqCpu(CPU C, uint delta)
{
    SetWorkFrequencyCPU(C,C->work_frequency+delta);

//   if (C->work_frequency+delta<=C->end_frequency)  C->work_frequency=C->work_frequency+delta;
//   else cout<<"frequence too high, can not increase"<<endl;
}

void getCpuLoad(uint nb_cpu, uint j,char * nomdudossier,float cpuload[])  /// dans cette fonctuion on fait la trace dans un dossier num�roter j 
{				       ///  puis on va lire la valeur du i�me CPU load souhait�e.
  char c[30]; 
  string tmp;
  float loadvalue=0.0f;
    
  sprintf(c,". ./compile.sh a %d",j);
  system(c);/// on aura le % dechargement des cpu
  sprintf(c,"cpuloadfile%d/cpuload.txt",j);
  ifstream in(c);
  ofstream out("historic.txt",ios::app);
  sprintf(nomdudossier,"cpuloadfile%d/",j);
  while(getline(in,tmp)) out<<tmp<<endl;
  out<<"*****\n";
  ifstream in2(c);
for(uint i=0; i<nb_cpu;i++)
 {
    in2>>tmp;//cout<<tmp;
    in2>>tmp;//cout<<tmp;
    in2>> cpuload[i];//cout<<loadvalue<<endl;
 }  
}

void RegenerateCpuFile(string includeListe[], uint nb_component)
{
  string tmp;
  uint i=0,indice=0;
  CPU cpu_tmp=NULL;
   while(i<nb_component)
  {
    tmp= includeListe[i].substr(0,includeListe[i].size()-4);
    indice=atoi(includeListe[i].substr(tmp.size()-1,tmp.size()).c_str());
    tmp.clear();
    tmp= includeListe[i].substr(0,includeListe[i].size()-10);
    tmp = "inputfile/"+tmp+".txt";
    cpu_tmp = AccessToCPU(thisMesCPU,indice);
    GenerateCpuFile(includeListe[i],tmp,cpu_tmp,"_comp","_behaviour","_timing_characs");
    tmp.clear();
    i++; 
  }
  
}


void CopieCompositionFile(string file, string destination)
{
  ifstream in(file.c_str());
  string tmp; 
  tmp= destination+"compositon.txt";
  ofstream out(tmp.c_str());
  
  while(getline(in,tmp)) out<<tmp<<endl;
}