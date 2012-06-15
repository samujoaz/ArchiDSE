



#include "regularisation.h"
#include <time.h>
extern LISTE_TBC thisTBC;
extern CPU thisMesCPU;
extern uint NbMaxCpu;
extern uint nbTBC;
float LoadMax=80.0;
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

uint setCpuLoadLevel(CPU MesCPU,uint nb_cpu,string includeListe[],string componentListe[],uint num)
{
  uint i=0,o,nb_component=0,numerodossier,indice=0;
  int frequence[nb_cpu],_nbTBC;
  char c[100];
  string  name,component,output, input;
  float cpuload_cur[nb_cpu];
  float MaxCpuload,MinCpuload, tabcpuload[nb_cpu-1];
  uint indice_cpuMax, indice_cpuMin;
  bool sortie=true;
  string compositionfile="composition.txt", composition_copie="inputfile/composition_copie.txt",compositionfile_temp="composition_temp.txt";
  CPU cpu_tmp=NULL,cpu_access=NULL;
  LISTE_TBC copieListeTBC=NULL;
  cpu_tmp = CloneCPU(MesCPU);
  cpu_access=CloneCPU(MesCPU);
  
  nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
  RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);  
  TBC_Trier(&thisTBC);/// parce que la frequence avait changée!
  TBC_Afficher(thisTBC);
  copieListeTBC=CloneListeTBC(thisTBC);/// on fait un clone pour pouvoir modifier les valeurs sans modifier l'originale (pointeur)
  _nbTBC = nbTBC;
  //sortie= getLevelTickTimer(compositionfile);
  for(i=0; i<nb_cpu ;i++) /// copie des frequences des cpu pour l'écriture  dans les fichiers de sortie
  {
    if(cpu_tmp->work_frequency<200 )
    {
    SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
    AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
    }
    frequence[i]=cpu_tmp->work_frequency;
    cpu_tmp=cpu_tmp->next;
  }
    numerodossier=num;
    i=0;
   // sortie=true;
   // getLevelTickTimer(compositionfile);
  
    getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
    
    if(cpuload_cur[0]<LoadMax){return numerodossier; }
    if(nb_cpu>NbMaxCpu+1 && getLevelTickTimer(compositionfile))/// on va changer l'affinity de NbMaxCpu en parallèle si le ticktimer n'est pas trop élévé 
    {			///et le reste se fera de façon sequentielle s'il reste encore des  threads
      for(uint t=0;t<=NbMaxCpu;t++)
      {
	for(indice=1;indice<=NbMaxCpu && copieListeTBC !=NULL;indice++)
	{
	  if(nb_cpu>indice)/// :d petite précaution
	  {
	    o=0;
	    name= copieListeTBC->name;
	    ChangeAffinity(composition_copie,compositionfile_temp,name,indice);
	    nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
	    while((componentListe[o++].compare(name))!=0);
	    o--;
	    component= includeListe[o].substr(0,includeListe[o].size()-10);
	    sprintf(c,"_cpu_%d.txt",indice);
	    output= component+c;
	    input ="inputfile/"+component+".txt";
	    cpu_tmp = AccessToCPU(cpu_access,indice);
	    GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
	    copieListeTBC=copieListeTBC->next;
	  }
	}
      }
      indice=1;
    cpu_tmp = AccessToCPU(cpu_access,indice);
     getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);

    }
    else
    {
      cpu_tmp = AccessToCPU(cpu_access,1);
      sprintf(c,"_cpu_%d.txt",1);

      for(indice=1;indice<=2*NbMaxCpu && copieListeTBC !=NULL;indice++)
	{
	  
	    o=0;
	    name= copieListeTBC->name;
	    ChangeAffinity(composition_copie,compositionfile_temp,name,1);
	    nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
	    while((componentListe[o++].compare(name))!=0);
	    o--;
	    component= includeListe[o].substr(0,includeListe[o].size()-10);
	    output= component+c;
	    input ="inputfile/"+component+".txt";
	    GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
	    copieListeTBC=copieListeTBC->next;
	  
	}
    }
    /// fin de la partie parallèle on regarde d'abord s'il n'y plus de threads dans notre liste !
    if(copieListeTBC==NULL)
    {
    
      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
      int max=nb_cpu-1;
      while(max>0) /// tant qu'il y en aura un cpuload superieur à 83-85%  on augementera la fréquence 
      {	
	  for(i=1; i<nb_cpu && max>0;i++)/// on regardera tout les niveaux de chargement des CPU qui fonctionnent !
	  {
	    if(cpuload_cur[i]>LoadMax)
	    {
	      if(max<nb_cpu-1){ max++; }
	      
	      cpu_tmp = AccessToCPU(cpu_access,i);
	      if(cpu_tmp->work_frequency<300){ SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100); }
	      else {  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50); }
	      frequence[i]=cpu_tmp->work_frequency;
	      AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
	      RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	    }
	    else 
	      if(max>1){ max--; }
	  }
	    if(max>0)
	    {
	      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	      //write_Data_histogram(cpuload_cur,nb_cpu);
	      max--;
	    }
      }
    
/// maintenant on va vérifier les cas où le cpu_0  a un chargement inférieur à 5%
      for(i=0;i<nb_cpu-1;i++) { tabcpuload[i]=cpuload_cur[i+1];}
      getMinMaxCpuLoad( tabcpuload,NULL,nb_cpu-1,  0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin); /// recherche min et max  
// 	  cout <<" Max : "<< MaxCpuload << " cpu_"<<indice_cpuMax+1<<endl;
// 	  cout <<" Min : "<< MinCpuload << " cpu_"<<indice_cpuMin+1<<endl;
// 	  exit(0);
      if(cpuload_cur[0]<5.0 && cpuload_cur[indice_cpuMin+1]<LoadMax)
      {
	cpu_tmp=AccessToCPU(cpu_access,0);
	FindAndReplaceAffinity(composition_copie,compositionfile_temp,indice_cpuMin+1,0);
	nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
	RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	//write_Data_histogram(cpuload_cur,nb_cpu);
      }
 }
 else/// sinon on sait que la liste des threads n'est pas encore vide !
 {
    indice=1;
    sortie = true;
    while(copieListeTBC !=NULL && indice<nb_cpu &&  !ComprisEntre(cpuload_cur[0],LoadMax-10.0,LoadMax+5.0 ))/// tant que la liste n'est pas vide ou bien  qu'on npas au cpu_0
    {
      
	if(sortie)
	{
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	  //write_Data_histogram(cpuload_cur,nb_cpu);	    
	  sortie=false;	 
	}
	
	for(i=0; i<nb_cpu;i++)/// augementation de la fréquence de tous les cpu dont le cpuload_cur[]>LoadMax 80.0
	{
	  cpu_tmp = AccessToCPU(cpu_access,i);
	    if(cpuload_cur[i]>(LoadMax+5.0))
	    {
	      if(cpu_tmp->work_frequency<300) { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100); }
	      else { SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50); }
		
	      AccessToCPU(cpu_access,i)->work_frequency=cpu_tmp->work_frequency;
	      RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);
	      sortie=true;
	    }
	    
	  frequence[i]=cpu_tmp->work_frequency;
	}
	
	if(sortie) 
	{
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	  //write_Data_histogram(cpuload_cur,nb_cpu);
	  sortie=false;	 
	}
	
	if(cpuload_cur[indice]<LoadMax-10.0  && copieListeTBC!=NULL ) ///si le cpu courant n'est pas assez chargé on lui rajoute des threads
	{
	   o=0;
	  cpu_tmp = AccessToCPU(cpu_access,indice);
	  name = copieListeTBC->name;
	  ChangeAffinity(composition_copie,compositionfile_temp,name,indice);
	  nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);  
	  while((componentListe[o++].compare(name))!=0);
	  o--;///  \o/
	  component= includeListe[o].substr(0,includeListe[o].size()-10);
	  cout<<"name :"<<name<<endl;
	  cout<<"component :"<<component<<endl;
	  sprintf(c,"_cpu_%d.txt",indice);
	  output= component+c;
	  input ="inputfile/"+component+".txt";
	  GenerateCpuFile(output,input,cpu_tmp,component,"_comp","_behaviour","_timing_characs");
	  copieListeTBC=copieListeTBC->next;	
	  sortie = true;
	}
	else
	{
	  indice++;
	}
      
    }/// end while
}/// end else
/*      o=0;
      for(i=0;i<nb_cpu;i++)
      {
	if(cpuload_cur[i]<5.0 && cpuload_cur[i]>0.1) 
	 {
	    tabcpuload[i]=cpuload_cur[i];
	    o++;
	 }
      }
*/
      
      for(i=1;i<nb_cpu;i++)tabcpuload[i-1]=cpuload_cur[i];
      getMinMaxCpuLoad(tabcpuload,NULL,nb_cpu-1, 0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin);
      
      if(cpuload_cur[0]<5.0 && cpuload_cur[indice_cpuMin+1]<LoadMax-5.0)/// on change la frequence des
      {
	cpu_tmp=AccessToCPU(cpu_access,0);
	FindAndReplaceAffinity(composition_copie,compositionfile_temp,0,indice_cpuMin+1);
	nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
	RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	//write_Data_histogram(cpuload_cur,nb_cpu);
      }
      else
      {
	  indice=0;
	  while(cpuload_cur[indice]>LoadMax+5.0) /// sinon tant que le cpu_0  a une charge > à 85.6  on augmente la frequence de fonctionnement 
	{
	  cpu_tmp =AccessToCPU(cpu_access,indice);
	if(cpu_tmp->work_frequency<400)SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
	else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
	frequence[indice]=cpu_tmp->work_frequency;
	AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
	RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	//write_Data_histogram(cpuload_cur,nb_cpu);
	}
      }
      
      
      for(indice=0;indice<nb_cpu;)/// diminution de la frequence pour les cpu qui ont une charge inféieur à 70!!!
      {
	if(cpuload_cur[indice]>30.0 && cpuload_cur[indice]<LoadMax-10.0 && frequence[indice]>100)
	{
	  cpu_tmp =AccessToCPU(cpu_access,indice);
	  SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency-25);
	  frequence[indice]=cpu_tmp->work_frequency;
	  AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
	  RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	  getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	}
	else indice++;
      }
      
      
      
      if(cpuload_cur[0]<5.0)
      {
	 o=0;
	for(i=1;i<nb_cpu;i++) 
	{
	  if(cpuload_cur[i]>30.0) 
	  {
	    tabcpuload[i-1]=cpuload_cur[i];
	    o++;
	  }
	}
      getMinMaxCpuLoad(tabcpuload,NULL,o-1, 0,&MaxCpuload, &MinCpuload,&indice_cpuMax, &indice_cpuMin);
      cpu_tmp=AccessToCPU(cpu_access,0);
      FindAndReplaceAffinity(composition_copie,compositionfile_temp,0,indice_cpuMin+1);
      nb_component = GenerateCompCpuFile(composition_copie,compositionfile,includeListe,componentListe);
      RegenerateCpuFile(cpu_tmp,includeListe,componentListe,nb_component);
      getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
      /*indice=0;
       while(cpuload_cur[indice]<LoadMax) /// sinon tant que le cpu_0  a une charge > à 85.6  on augmente la frequence de fonctionnement 
	{
	  cpu_tmp =AccessToCPU(cpu_access,indice);
	if(cpu_tmp->work_frequency<400)SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+100);
	else SetWorkFrequencyCPU(cpu_tmp,cpu_tmp->work_frequency+50);
	frequence[indice]=cpu_tmp->work_frequency;
	AccessToCPU(cpu_access,indice)->work_frequency=cpu_tmp->work_frequency;
	RegenerateCpuFile(cpu_access,includeListe,componentListe,nb_component);  
	getAllCpuLoad(nb_cpu,numerodossier++,cpuload_cur,frequence);
	//write_Data_histogram(cpuload_cur,nb_cpu);
	}*/
      }
//       write_Data_histogram(cpuload_cur,nb_cpu);
      thisMesCPU=NULL;
    coucou();
    return numerodossier;
}


bool getLevelTickTimer(string input)
{
  string line,mot,S1="configure_timerspec_and_sched_fifo"; 
  size_t pos;
  int i=0,seconde=0,nanoseconde;
  bool high = false, low=true;
  ifstream inputfile(input.c_str());
   while(getline(inputfile,line) && i<9 ) 
      {	  	
	pos=line.find(S1);
	if (pos!=-1)
	{/// on  va se repositionner au debut de la ligne
// 	cout<<line<<endl;
	    inputfile.seekg(-line.size()-1,ios::cur);
	    inputfile>>mot; 
// 	    cout<<mot<<endl;
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
      if(seconde>0) return high;
      else
      {
	if(nanoseconde>500000000) return high;
	  else return low;
      }

}
