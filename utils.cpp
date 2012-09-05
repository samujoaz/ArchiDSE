#include <list>
#include <vector>
#include "utils.h"
extern list <pair < string,double> > selected_connections;

extern COMPONENTDSP thisComposantsDSP;
extern COMPONENTCPU thisComposantsCPU;
extern CPU thisMesCPU;
extern char **_argv;
extern double LoadMax;
extern double LoadMin;

using namespace std;

string BufferFreqHisto; /// on mettera toutes les fequences des cpu a chaque itération 
			///  on utilera pour ecrire le script de l'histogramme!

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

void getAllCpuLoad(uint nb_cpu, int numerodossier, double cpuload[], int frequence[])  /// dans cette fonctuion on fait la trace dans un dossier numéroter j 
{				       ///  puis on va lire la valeur du ième CPU load souhaitée.
    char c[256],nomdudossier[100];
    string buffer,line,cmd, cnx_name_file;
    ostringstream convert;

    int i=0;
    size_t pos;
    for (list < pair < string, double > >::iterator iter = selected_connections.begin(); iter != selected_connections.end(); iter++) 
    {
      cnx_name_file += iter->first + " ";
    }
//     cmd =  "./get_allcpuload.sh a  \"cnx_write_buffe " 
    sprintf(c,"./get_allcpuload.sh a  \" cnx_write_buffer -cpu 0 CPU0 \" %d",numerodossier);
    cmd=c;/// par défaut!
    
    
    if(numerodossier>0)
    {
      cmd.clear();
      cmd = "./get_allcpuload.sh a  \"cnx_write_buffer " + cnx_name_file + " -cpu";

      for(i=0; i<nb_cpu;i++)  
      {
	sprintf(c,"  %d CPU%d ",i,i);
	cmd = cmd+ c;
      }

      sprintf(c," \" %d",numerodossier);
      cmd = cmd+ c;
//       cout<< cmd <<endl;  exit(0);
    }
   
    i=0;
    system(cmd.c_str());/// execution d'une ligne de commade :: on aura le % chargement des cpu
    sprintf(c,"cpuloadfile%d/cpuload.txt",numerodossier);
    
    ifstream in(c);
   
    
    /// écriture d'un fichier historic.txt qui contient tout les cpuload et les fréquences de fonctionement des cpu!
    ofstream out("historic.txt",ios::app); /// ecriture de l'historique des cpuloads
    sprintf(nomdudossier,"cpuloadfile%d/",numerodossier);
    out<<"dans le dossier: "<<nomdudossier<<endl;
     BufferFreqHisto=BufferFreqHisto+" \"";
     line.clear();
    while(getline(in,buffer))
    {
      convert.str(""); convert.clear();
      convert<<frequence[i];
      //strcat (BufferFreqHisto,convert.str()+"\\n");

      line=line+convert.str()+"\\n";
      out<<buffer<<"\tFrequence du cpu: "<<frequence[i++] <<" Mhz"<<endl;
    }
    convert.str(""); convert.clear();
    convert<<numerodossier;
    BufferFreqHisto=BufferFreqHisto+line+"\" "+convert.str()+", ";
    out<<"*****\n";
    /// fin historic.txt
    ifstream in2(c); /// ouverture du fichier créer par format_trace.cpp  on va récupérer les valeurs des cpuload 
    
    char c2[256];
    sprintf(c2,"cpuloadfile%d/pie.dat",numerodossier);
     ofstream out2(c2);
    for(i=0; i<nb_cpu;i++)
    {
	in2>>buffer;cout<<buffer;
	in2>>buffer;cout<<buffer;
	in2>> cpuload[i];cout<<cpuload[i]<<endl; 
	out2<<buffer<<"("<<cpuload[i]<<") "<<cpuload[i]<<endl;
	
	
    }
    
  /// copie du fichier Software
    CopieCompositionFile("composition.txt",nomdudossier);
    buffer.clear();

  /// copie du fichier HArdware !  en rajoutant la fréquence de fonctionnnement actuelle du cpu courant !
  
    sprintf(c,"cpuloadfile%d/compositionarchi.txt",numerodossier);
    ofstream outHDW(c);
    if(!outHDW)/// si défaut mémoire ou fichier non créé on quitte le programme 
    {
      cout<<"ERREUR exit("<<404<<")impossible de crée le fichier de sortie: "<<c<<endl;
      cout<<"voir fonction : getAllCpuLoad(,,,) "<<endl;
      exit(404);
    }
    i=0;
    string ttmp = string(_argv[2])+string(_argv[3]);
    ifstream fichierHDW(ttmp.c_str());/// fichier d'entrée qu'on va copier !
    line.clear();
    if(fichierHDW)
    {
      i=0;
      while(getline(fichierHDW,line) &&line.size()>5) 
      {
	pos=line.find("component");
	if(pos!=-1)
	{
	pos=line.find("PU");
	  if(pos!=-1)
	  {
	      buffer=".txt ";
	      pos=line.find(buffer);
	      if (pos!=-1)
	      {
		convert.str(""); convert.clear();
		convert<<frequence[i++];/// rajout de la fréquence de fonctionnement actuelle du cpu
		line.replace(pos+buffer.size(),convert.str().size(),convert.str());
		outHDW<<line<<endl;
		  
	      }
	  }
	  else
	   outHDW<<line<<endl;
	  
	}
	  else
	  { 
	    outHDW<<line<<endl; 
	  }
      }
    }
    else 
    {
	cout<<"ERREUR exit("<<405<<"): Impossible d'ouvrir le fichier:"<<_argv[2]<<endl;
	cout<<"voir fonction : getAllCpuLoad(,,,) "<<endl;
	exit(405);
    }
    write_Data_histogram(cpuload,nb_cpu);
//     if (numerodossier==2) { GenScriptHistogram(nb_cpu); exit(0);}
    /// fermeture des fichiers !  pas obligatoire mais bon !
    in.close();
    out.close();
    in2.close();
   fichierHDW.close();
   outHDW.close();
   /*
     sprintf(c,"cpuloadfile%d",numerodossier);
     buffer = c;
     buffer = buffer+"/includeliste.txt";
     ofstream out_includefile(buffer.c_str()); 
    for(int u=0; u<nb_component;u++)/// on va recopier tout les fichiers de l'application (main, slife, filter, generator...)
    {
//       string cp;
//       cp = "cp  "+includeListe[u] + "  "+ c;
//       system(cp.c_str());
      out_includefile<<includeListe[u]<<endl;
    }
    out_includefile.close();
    
     sprintf(c,"cpuloadfile%d",numerodossier);
     buffer = c;
     buffer = buffer+"/origine.txt";
     ofstream pp(buffer.c_str()); 
     ifstream  tt("composition.txt");
     while(getline(tt,buffer))pp<<buffer<<endl;
    */
}

void getMinMaxCpuLoad(double cpuload[], uint except[], uint nb_cpu, uint nb_except, double *Max, double *Min, uint *indice_cpuMax, uint *indice_cpuMin)
{/// pour avoir le Min et MAx ainsi  que les indices des cpu correspondantes
uint i=0,j=0; 
double monMin=101, monMax=0;
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
    if(monMin>cpuload[i] && cpuload[i]>0.0)
    {
      *Min=cpuload[i];
      monMin=cpuload[i];
      *indice_cpuMin=i;
    }
    
  }
}

void CopieCompositionFile(string file, string destination)
{/// copie de quelconque fichier en rajoutant l'extension _copie.txt
  ifstream in(file.c_str());
  string buffer; 
  buffer= destination+"composition_copie.txt";
  ofstream out(buffer.c_str());
  
  while(getline(in,buffer)) out<<buffer<<endl;
  out.close();
  in.close();
}


 void  tri_bulle( double *tab, int n)
 {
  int i =0;
  double x =0.0;
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

void afficheTBC( double * tab, int longeur)
{
for(int y=0; y<longeur; y++) cout<<" " <<tab[y];
cout<<endl;		
}
  

void coucou()
{cout<<" Free egg : ^_^ coucou @_@ "<<endl;}
void write_Data_histogram(double cpuload[], int nb_cpu)
{
    ofstream histogram("all_cpu_hist.dat",ios::app);

  for(int i=0; i<nb_cpu;i++)  
  {
    //if(cpuload[i]>0.0)
   // {
      histogram<<cpuload[i]<< "  ";
//       histogram<<" ";
//     }
//     else
//     { 
//       histogram<< "0.5  ";
//     }
  }
  histogram<< "\n";
}


void GenScriptHistogram(uint nb_cpu)
{
 ofstream output("hist_all_archi.gnu",ios::trunc);
 output<<"reset\nset yrange [0:100]\nset xrange [-1:]\nset ylabel \"Taux de chargement des CPU (%)\"\n";
 output<<"set label \"Frequence\\n (MHz)\"  at -1,-1 rotate by 0   offset character 0,-0.5, 0\n";
 output<<"set style data histogram\nset style histogram cluster gap 4 \nset style fill solid border -1\nset boxwidth 1.0 \n";
 output<<"set xtics border in scale 0,0 nomirror rotate by 90  offset character 1.7,-1, 0\nset xtics  norangelimit font \",9\"\n set xtics ( ";
 BufferFreqHisto = BufferFreqHisto.substr(0,BufferFreqHisto.size()-2);
 output<<BufferFreqHisto<<")";
 output<<"\nplot 'all_cpu_hist.dat' using 1 title \"cpu_0\"";
 for(int i=1; i<nb_cpu;i++)
 output<<", '' using "<<i+1<<" title \"cpu_"<<i<<"\"";
 output<<", "<<LoadMax<<" with lines linecolor rgb \"red\"  title \"Max\", "<<LoadMin<<"  with lines linecolor rgb \"red\" title \"Min\";\npause -1 \n";
}