
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

void getAllCpuLoad(uint nb_cpu, int numerodossier,char * nomdudossier,float cpuload[], int frequence[])  /// dans cette fonctuion on fait la trace dans un dossier numéroter j 
{				       ///  puis on va lire la valeur du ième CPU load souhaitée.
  char c[100]; 
  string tmp;
  float loadvalue=0.0f;
  int i=0;
    
  sprintf(c,". ./compile.sh a %d",numerodossier);
  system(c);/// on aura le % dechargement des cpu
  sprintf(c,"cpuloadfile%d/cpuload.txt",numerodossier);
  ifstream in(c);
  ofstream out("historic.txt",ios::app);
  sprintf(nomdudossier,"cpuloadfile%d/",numerodossier);
  out<<"dans le dossier: "<<nomdudossier<<endl;
  while(getline(in,tmp)) out<<tmp<<"\tFrequence du cpu: "<<frequence[i++] <<" Mhz"<<endl;
  out<<"*****\n";
  ifstream in2(c);
for(i=0; i<nb_cpu;i++)
 {
    in2>>tmp;//cout<<tmp;
    in2>>tmp;//cout<<tmp;
    in2>> cpuload[i];//cout<<loadvalue<<endl;
 }
  in.close();
  out.close();
  in2.close();
  tmp.clear();
}

void getMinMaxCpuLoad(float cpuload[], uint except[], uint nb_cpu, uint nb_except, float *Max, float *Min, uint *indice_cpuMax, uint *indice_cpuMin)
{
uint i=0,j=0; 
float monMin=101, monMax=0;
bool inclut;

  for(i=0;i<nb_cpu;i++)
  {
    inclut=true;
    for(j=0;j<nb_except;j++)
    {
      if(i==except[j]) 
      {
	inclut=false;
      } 
    }
    
    if(monMax<cpuload[i] && inclut)
    {
      *Max=cpuload[i];
      monMax=cpuload[i];
      *indice_cpuMax=i;
    }
    if(monMin>cpuload[i])
    {
      *Min=cpuload[i];
      monMin=cpuload[i];
      *indice_cpuMin=i;
    }
    
  }
}

void CopieCompositionFile(string file, string destination)
{
  ifstream in(file.c_str());
  string tmp; 
  tmp= destination+"composition_copie.txt";
  ofstream out(tmp.c_str());
  
  while(getline(in,tmp)) out<<tmp<<endl;
  out.close();
  in.close();
  tmp.clear();
}


 void  tri_bulle( float *tab, int n)
 {
  int i =0;
  float x =0.0;
  while(i<n-1)
  {
    if(tab[i] > tab[i+1])
    {
      x= tab[i];
      tab[i] = tab[i+1];
      tab[i+1] =  x;
      
      if(i!=0) i--;
      else i++;
    }
    else i++;
  }
}

void afficheTBC( float * tab, int longeur)
{
for(int y=0; y<longeur; y++) cout<<" " <<tab[y];
cout<<endl;		
}
  
