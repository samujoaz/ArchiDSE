
#include "fonctionsUtils.h"


/**
 * ajout en queue de la liste 
 * CACHE ADD_CACHE(CACHE ma_cache,uint taille, uint bpl,uint assoc,uint indice)
 * 
 * parametres : CACHE (liste de tous les éléments CACHE)  
 *		taille : la taille 
 * 		bpl   : nombre le ligne par byte
 * 		assoc: l'associatitivé
 * 		indice: indice  de la cache
 * 
 * Return : une nouvelle liste est retournée avec
 * 
 * */
CACHE ADD_CACHE(CACHE ma_cache,uint taille, uint bpl, uint assoc,uint indice)
{
    cache *newcache = new cache;
    /// on assigne les parametres du nouveau cache
    newcache-> taille=taille;
    newcache->associativity =assoc; 
    newcache->bpl = bpl;
    newcache->indice_cache = indice;
    newcache->next = NULL;
    if(ma_cache==NULL){ return newcache;}
    else 
    {
      cache *cache_temp=ma_cache; 
      while(cache_temp->next!=NULL) cache_temp = cache_temp->next;
  
      cache_temp->next= newcache;
      return ma_cache;
    }
}


/** acces à la CACHE en fonction de l'indice : 
 * cette fonction fonction comme FindCACHE() suite à des modification au niveau des fonction de lectures de fichier
 * */
  CACHE AccessToCACHE(CACHE ma_cache, uint indice)
  {
      for(uint i=0; i<indice && ma_cache!=NULL;i++) ma_cache=ma_cache->next;
      if(ma_cache==NULL) return NULL;
      else return ma_cache;
  }

/**
 *       Ajout d'un nouveau (élément) CPU
 * cette fonction prend en paramètre : 
 * CPu mon_cpu : une liste type cpu, 
 * string name correspond au nom du fichier comportant les caractéristiques du processeur
 * exemple du contenu de fichier qui sera ouvert 
 * 					start_frequency: 100
					end_frequency: 1000
					dmips: 2.5
					pipeline: 8
* uint freq : la frequence lu dans le fichier architecture qui correspond à la frequence de  focntionnement du cpu
* uint indice : l'indice du cpu en question
*   
* focntionnement : on teste l'ouverture du fichier (name) si tout se passe correctement on récupère alors les caractéristiques vu précédemment (fréquences, dmips, pipeline)
* dans le cas contraire on arrete le programme et on indique qu'il y a un problème soit dans le fichier (manquant ou impossibilité d'ouverture)
* 
* Erreur:  possibilité d'erreurs dans lors de la lecture du fichier: 
* --> frequence de fonctionnement hors des frequences autorisées par le constructeur
* --> le format définit n'est pas respecté
* 
* 
* Return : la fonction retourne une liste CPU
**/
CPU ADD_CPU(CPU mon_cpu, string name,uint freq, uint indice)
{
  cpu *newcpu = new cpu;
  int nb_ligne=0;
  string line, tmp;
  ifstream cpu_file(name.c_str());
  /// on assigne les parametres du nouveau cpu
  if(cpu_file)
  {
    newcpu->name_cpu=name;
    newcpu->indice_CPU= indice;
     while(cpu_file>>line ){ /// on lit mot par mot le fichier et on instantie les composants
      nb_ligne++;
      cpu_file>>tmp;
       if(line=="start_frequency:") newcpu->start_frequency =atoi(tmp.c_str());
       else{
	  if(line=="end_frequency:") newcpu->end_frequency =atoi(tmp.c_str());
	  else{
	    if(line=="dmips:") newcpu->dmips =atof(tmp.c_str());
	    else{
	      if(line=="pipeline:") newcpu->pipeline =atoi(tmp.c_str());
	      else{
		    nb_ligne--;
		    cout <<" \n\n ATTENTION  dans le fichier ===>"<<name<<"<=== Problème à la ligne: "<<nb_ligne<<endl; 
		    cout<<"\nRequired format for "<<name<<endl;
		    cout<<" start_frequency:  W, (W is a uint) "<<endl;
		    cout<<" end_frequency:    X, (X is a uint)"<<endl;
		    cout<<" dmips:            Y, (Y is a flaot) "<<endl;
		    cout<<" pipeline:         Z, (Z is a uint) "<<endl;
		    cout<<" \nExample cortexA8.txt \n\tstart_frequency: 100\n\tend_frequency: 500\n\tdmips: 1.98\n\tpipeline: 11 \n"<<endl;
		    exit(3);
	      }
	    } 
	  }
       }
    }/// end while()..
  }
  else {cout<<"\nERREUR: Impossible d'ouvrir: "<<name<<endl<<endl;exit(0);}
  
  if(!(freq>=newcpu->start_frequency && freq<=newcpu->end_frequency)) 
  {cout<<"pour le "<<name<<" la plage frequentielle doit être compris entre :["<<newcpu->start_frequency<<","<<newcpu->end_frequency<<"]"<<endl; exit(3);}
  else newcpu->work_frequency = freq;
  cpu_file.close();
  newcpu->next = NULL;
  if(mon_cpu==NULL)return newcpu;
  else 
  {
    cpu *cpu_temp=mon_cpu; 
    while(cpu_temp->next!=NULL) cpu_temp = cpu_temp->next;
    cpu_temp->next= newcpu;
    return mon_cpu;
  }
}

/**
 * permet  de savoir  quel cpu est connecté à telle cache en fonction de l'indice (cache) en paramètre
 * 
 * **/

uint GetLinkCacheL1CPU(COMPONENTCPU my_component,uint indice)
{
    componentcpu *tmp=my_component;
    while(tmp!=NULL)
    {
      if(tmp->CPU_->indice_cache_L1==indice){return tmp->CPU_->indice_CPU;}        
      tmp = tmp->next;
    }
    return NULL;
}
 
/// pour avoir acces au i-ème composant CPU
  CPU AccessToCPU(CPU mon_cpu, uint indice)
  {
      cpu *tmp_cpu=new cpu;
      tmp_cpu= CloneCPU(mon_cpu);
//       for(uint i=0; i<indice && tmp_cpu!=NULL;i++)
      while(tmp_cpu->indice_CPU!=indice && tmp_cpu!=NULL)
      {
	tmp_cpu=tmp_cpu->next;
      }
      if(tmp_cpu==NULL)
      {
	return NULL;
      }
      else 
      {
	return tmp_cpu;
      }
  }
/// trouver les cpu en fonction de  son indice
  CPU FindCPU(CPU mon_cpu, uint indice)
  {
      while(mon_cpu->indice_CPU!=indice && mon_cpu!=NULL) mon_cpu=mon_cpu->next;
      if(mon_cpu==NULL) return NULL;
      else return mon_cpu;
  }
/// trouver les CACHE en fonction de  son indice
  CACHE FindCACHE(CACHE ma_cache, uint indice)
  {
      while(ma_cache->indice_cache!=indice && ma_cache!=NULL) ma_cache=ma_cache->next;
      if(ma_cache==NULL) return NULL;
      else return ma_cache;
  }
  
  /**
   * renvoie le nom du lien d'un cache ainsi on sait si la cace est connecté à un cpu, un dsp ou une autre cache
   * 
   * */
string GetNamelinkCache(CACHE ma_cache){if(ma_cache!=NULL) return ma_cache->namelink;}


 /** Modification de la fréquence des cpu en respectant les bornes
  *  
  * **/

void SetWorkFrequencyCPU(CPU mon_cpu, uint new_freq)
{
 
  if(!(new_freq>=mon_cpu->start_frequency && new_freq<=mon_cpu->end_frequency)) 
  {
    cout<<" la plage frequentielle du cpu doit être compris entre :[";
    cout<<mon_cpu->start_frequency<<","<<mon_cpu->end_frequency<<"]"<<endl; 
    
  }
  else 
  {
    
    mon_cpu->work_frequency = new_freq;
    cout<<"nouvelle fréquence du cpu_"<<mon_cpu->indice_CPU<<" freq: "<<mon_cpu->work_frequency<<endl;
  }
}

/**
 * pour cloner un cpu
 * il faut différencier clone et copie 
 * car la copie garde un pointeur  sur l'element et donc toutes modifications affecteront les copies et l'originale
 * alors le clone detient une nouvelle adresse et on peut le modifier sans conséquance sur l'originale
 **/
  CPU CloneCPU(CPU mon_cpu)
  {
      cpu *clone= new cpu;
      memcpy(&clone,&mon_cpu,sizeof(CPU));
      return clone;
  }

/**
 * pour Effacer la liste des cpu
 **/
  void DeleteCPUList(CPU mon_cpu)
  {
  delete(mon_cpu); 
  }
  
  
/** ajout d'un nouveau DSP 
 * fonciton tester avec les fichiers des cpu, comme le profiling n'est pas encore alors  on a gardé ce modèle.
 * */

DSP ADD_DSP(DSP mon_dsp, string name,uint freq, uint indice)
{
  dsp *newdsp = new dsp;
  int nb_ligne=0;;
  string line, tmp;
  ifstream dsp_file(name.c_str());
  /// on assigne les parametres du nouveau dsp
  if(dsp_file)
  {
     while(dsp_file>>line ){ /// on lit mot par mot le fichier et on instantie les composants
      nb_ligne++;
      dsp_file>>tmp;
       if(line=="start_frequency:") newdsp->start_frequency =atoi(tmp.c_str());
       else{
	  if(line=="end_frequency:") newdsp->end_frequency =atoi(tmp.c_str());
	  else{
	    if(line=="dmips:") newdsp->dmips =atof(tmp.c_str());
	    else{
	      if(line=="pipeline:") newdsp->pipeline =atoi(tmp.c_str());
	      else{
		    nb_ligne--;
		    cout <<" \n\n ATTENTION  dans le fichier ===>"<<name<<"<=== Problème à la ligne: "<<nb_ligne<<endl; 
		    cout<<"\nRequired format for "<<name<<endl;
		    cout<<" start_frequency:  W, (W is a uint) "<<endl;
		    cout<<" end_frequency:    X, (X is a uint)"<<endl;
		    cout<<" dmips:            Y, (Y is a flaot) "<<endl;
		    cout<<" pipeline:         Z, (Z is a uint) "<<endl;
		    cout<<" \nExample dspX.txt \n\tstart_frequency: 100\n\tend_frequency: 500\n\tdmips: 1.98\n\tpipeline: 11 \n"<<endl;
		    exit(3);
	      }
	    } 
	  }
       }
    }/// end while()..
  }
  else {cout<<"\nERREUR: Impossible d'ouvrir: "<<name<<endl<<endl;exit(0);}
  
  if(!(freq>=newdsp->start_frequency && freq<=newdsp->end_frequency)) 
  {cout<<"pour le "<<name<<" la plage frequentielle doit être compris entre :["<<newdsp->start_frequency<<","<<newdsp->end_frequency<<"]"<<endl; exit(3);}
   else newdsp->work_frequency = freq;
   newdsp->indice_DSP = indice;
  dsp_file.close();
  newdsp->next = NULL;
  if(mon_dsp==NULL)return newdsp;
  else 
  {
    dsp *dsp_temp=mon_dsp; 
    while(dsp_temp->next!=NULL) dsp_temp = dsp_temp->next;
    dsp_temp->next= newdsp;
    return mon_dsp;
  }
}




/** ajout d'un nouveau cpu et cache à une archi+
 * ***/

COMPONENTCPU ADD_COMPONENTCPU(COMPONENTCPU my_component,CPU mon_cpu,CACHE ma_cache,uint indice_cache,uint indice_cpu, string link)
{
    componentcpu *new_component= new componentcpu;
    new_component->CPU_=mon_cpu;
    new_component->L1_=ma_cache;
    ma_cache->namelink=link;
    mon_cpu->indice_cache_L1= indice_cache;
    mon_cpu->indice_CPU= indice_cpu;
    new_component->next = NULL;
    if(my_component==NULL) { return new_component;}
    else
    {
	componentcpu *compo_tmp=my_component;
	while(compo_tmp->next!=NULL)compo_tmp=compo_tmp->next;
	
	compo_tmp->next = new_component;
	return my_component;
    }
}


COMPONENTDSP ADD_COMPONENTDSP(COMPONENTDSP my_component,DSP mon_dsp,CACHE ma_cache, uint indice_cache,uint indice_dsp, string link)
{
    componentdsp *new_component= new componentdsp;
    new_component->DSP_=mon_dsp;
    new_component->L1_=ma_cache;
    mon_dsp->indice_cache_L1= indice_cache;
    mon_dsp->indice_DSP= indice_dsp;  
    ma_cache->namelink=link;
    new_component->next = NULL;
    if(my_component==NULL) { return new_component;}
    else
    {
      componentdsp *compo_tmp=my_component;
      while(compo_tmp->next!=NULL)compo_tmp=compo_tmp->next;

      compo_tmp->next = new_component;
      return my_component;
    }
}


void ADD_CACHE_L2_TO_COMPONENTCPU(COMPONENTCPU my_component,CACHE L2){my_component->L2_=L2;}
void ADD_CACHE_L2_TO_COMPONENTDSP(COMPONENTDSP my_component,CACHE L2){my_component->L2_=L2;}

uint GetLinkCacheL1DSP(COMPONENTDSP my_component,uint indice)
{
    componentdsp *tmp=my_component;
    while(tmp!=NULL)
    {
      if(tmp->DSP_->indice_cache_L1==indice){return tmp->DSP_->indice_DSP;}        
      tmp = tmp->next;
    }
    return NULL;
}




  
  DSP FindDSP(DSP mon_dsp, uint indice)
  {
      while(mon_dsp->indice_DSP!=indice && mon_dsp!=NULL) mon_dsp=mon_dsp->next;
      if(mon_dsp==NULL) return NULL;
      else return mon_dsp;
  }
  
  DSP AccessToDSP(DSP mon_dsp, uint indice)
  {
      for(uint i=0; i<indice && mon_dsp!=NULL;i++) mon_dsp=mon_dsp->next;
      if(mon_dsp==NULL) return NULL;
      else return mon_dsp;
  }


  
  COMPONENTCPU AccessToCOMPONENTCPU(COMPONENTCPU my_component, uint indice)
  {
      while(my_component->CPU_->indice_CPU!=indice && my_component!=NULL) my_component=my_component->next;
//       for(uint i=0; i<indice && my_component!=NULL;i++) my_component=my_component->next; /// problème si l'indice est plus grand que le nombre de cpu
      if(my_component==NULL) return NULL;
      else return my_component;
  }
  
  COMPONENTDSP AccessToCOMPONENTDSP(COMPONENTDSP my_component, uint indice)
  {
      for(uint i=0; i<indice && my_component!=NULL;i++) my_component=my_component->next;
      if(my_component==NULL) return NULL;
      else return my_component;
  }


/** fonctions pour copter les élémentes d'une liste **/
int NB_CPU(CPU A){if(A == NULL) return 0; return NB_CPU(A->next)+1;}
int NB_DSP(DSP A){if(A == NULL) return 0; return NB_DSP(A->next)+1;}
int NB_CACHE(CACHE A){if(A == NULL) return 0;return NB_CACHE(A->next)+1; }
int NB_COMPONENTCPU(COMPONENTCPU A){if(A == NULL) return 0; return NB_COMPONENTCPU(A->next)+1; }
int NB_COMPONENTDSP(COMPONENTDSP A){if(A == NULL) return 0; return NB_COMPONENTDSP(A->next)+1; }



/**
 * Fonction pour faires les différentes affichages.
 **/
void Affiche_CPU(CPU A)
{
    cpu *tmp = new cpu; 
    tmp = CloneCPU(A);
    while(tmp!=NULL)
    {     
      cout<<"cpu_"<<tmp->indice_CPU<<": "<<tmp->name_cpu<<endl;
      cout<<"start_frequency: "<<tmp->start_frequency<<endl;
      cout<<"working_frequency: "<<tmp->work_frequency<<endl;
      cout<<"end_frequency: "<<tmp->end_frequency<<endl;
      cout<<"dmips: "<<tmp->dmips<<endl;
      cout<<"pipeline: "<<tmp->pipeline<<endl;
      tmp=tmp->next;
      cout<<endl;
      
    }
    //delete(tmp);
}

void Affiche_CACHE(CACHE A)
{
    cache *tmp = A;    
    while(tmp!=NULL)
    {      
      cout<<"taille: "<<tmp->taille<<endl;
      cout<<"associativity: "<<tmp->associativity<<endl;
      cout<<"nb byte per line: "<<tmp->bpl<<endl;
      tmp=tmp->next;
      cout<<endl;
    }
}


void Affiche_COMPONENTCPU(COMPONENTCPU A)
{
  uint i=0;
  componentcpu *tmp=A;
  while(tmp!=NULL)
  {
   cout<<endl;
   cout<<"cpu_"<<tmp->CPU_->indice_CPU<<": "<<tmp->CPU_->name_cpu<<endl;
   cout<<"\tstart_frequency: "<<tmp->CPU_->start_frequency<<endl;
   cout<<"\tworking_frequency: "<<tmp->CPU_->work_frequency<<endl;
   cout<<"\tend_frequency: "<<tmp->CPU_->end_frequency<<endl;
   cout<<"\tdmips: "<<tmp->CPU_->dmips<<endl;
   cout<<"\tpipeline: "<<tmp->CPU_->pipeline<<endl;
   cout<<"cache L1"<<endl;
   cout<<"\ttaille: "<<tmp->L1_->taille<<endl;
   cout<<"\tassociativity: "<<tmp->L1_->associativity<<endl;
   cout<<"\tnb byte per line: "<<tmp->L1_->bpl<<endl;
   cout<<"cache L2"<<endl;
   cout<<"\ttaille: "<<tmp->L2_->taille<<endl;
   cout<<"\tassociativity: "<<tmp->L2_->associativity<<endl;
   cout<<"\tnb byte per line: "<<tmp->L2_->bpl<<endl;
   cout<<endl;
   tmp=tmp->next;   
  }
 
}
  
void Affiche_COMPONENTDSP(COMPONENTDSP A)
{
  uint i=0;
  componentdsp *tmp=A;
  while(tmp!=NULL)
  {
   cout<<endl;
   cout<<"dsp_"<<tmp->DSP_->indice_DSP<<": "<<endl;
   cout<<"\tstart_frequency: "<<tmp->DSP_->start_frequency<<endl;
   cout<<"\tworking_frequency: "<<tmp->DSP_->work_frequency<<endl;
   cout<<"\tend_frequency: "<<tmp->DSP_->end_frequency<<endl;
   cout<<"\tdmips: "<<tmp->DSP_->dmips<<endl;
   cout<<"\tpipeline: "<<tmp->DSP_->pipeline<<endl;
   cout<<"cache L1"<<endl;
   cout<<"\ttaille: "<<tmp->L1_->taille<<endl;
   cout<<"\tassociativity: "<<tmp->L1_->associativity<<endl;
   cout<<"\tnb byte per line: "<<tmp->L1_->bpl<<endl;
   cout<<"cache L2"<<endl;
   cout<<"\ttaille: "<<tmp->L2_->taille<<endl;
   cout<<"\tassociativity: "<<tmp->L2_->associativity<<endl;
   cout<<"\tnb byte per line: "<<tmp->L2_->bpl<<endl;
   cout<<endl;
   tmp=tmp->next; 
  }
 
}
  