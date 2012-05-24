#include "generatefile.h"
#include <stdio.h>
#include <stdlib.h>
#include "fonctionsUtils.h"



uint nb_fichier_include=100;
float TableTBC[100];
uint nbTBC=0;
COMPONENTDSP thisComposantsDSP=NULL;
COMPONENTCPU thisComposantsCPU=NULL;
CPU thisMesCPU;
DSP thisMesDSP;
LISTE_TBC thisTBC;
bool once =true;


bool TBC_estVide(LISTE_TBC L){
         if(L == NULL){
                 return true;
              }
         else{
                 return false;
              }             
     } 
void TBC_InitListe(LISTE_TBC *L){
        if(!TBC_estVide(*L)){
             TBC_InitListe(&((*L)->next));
             *L = NULL;
         }      
     }             
   
void TBC_Ajouter(LISTE_TBC *L,string name,uint affinity,float valeur){
       Liste_TBC *tmp = *L;
       Liste_TBC *nouveau =new Liste_TBC;
       if(nouveau == NULL){
                  exit(1);
             }
       nouveau->valeur = valeur;
       nouveau->name = name;
       nouveau->affinity =affinity;
       nouveau->next = NULL;
       if(TBC_estVide(*L)){
            *L = nouveau;           
       }
       else{
            tmp = *L;
            while(tmp->next != NULL){
                 tmp = tmp->next;   
            }
            tmp->next = nouveau;
       }
     }
  
 void TBC_Trier(LISTE_TBC *L){
       Liste_TBC *tmp1, *tmp2;
       Liste_TBC *Min;
       float valeur_temp;
       string name_temp;
       int affinity_temp;
       tmp1 = *L;
       cout<<"\ntri de liste : "<<endl;
       while(tmp1 != NULL){
             Min = tmp1;
             tmp2 = tmp1;
             while(tmp2 != NULL){
                 if(Min->valeur > tmp2->valeur)
		 {
		   Min = tmp2;
		 }
                 tmp2 = tmp2->next;       
             }
             valeur_temp   =  tmp1->valeur;
	     name_temp     =  tmp1->name;
	     affinity_temp = tmp1->affinity;
	     
             tmp1->valeur   = Min->valeur;
	     tmp1->name     = Min->name;
	     tmp1->affinity = Min->affinity;
	     
             Min->valeur   = valeur_temp;
	     Min->name     = name_temp;
	     Min->affinity = affinity_temp;
             
             tmp1=tmp1->next;     
       }
  }     

LISTE_TBC CloneListeTBC(LISTE_TBC mon_tbc)
{
  Liste_TBC *clone = new Liste_TBC;
  memcpy(&clone,&mon_tbc,sizeof(LISTE_TBC));
  return clone;
}
void TBC_Afficher(LISTE_TBC L){
         Liste_TBC *tmp;
         if(TBC_estVide(L)){
            cout<<"!la liste est vide!" <<endl;           
         }
         else{
           tmp = L;
           while(tmp != NULL){
                cout<<"(val :"<<tmp->valeur<<") (aff :"<<tmp->affinity<<") name :"<<tmp->name<<endl; 
                tmp = tmp->next;    
           }  
           cout<<endl;
         }
      }


void GenerateCpuFile(string output,string input,CPU C,string name,string S1, string S2,string S3)
{
  ofstream outputfile(output.c_str());/// ios::app pour rajouter en fin du fichier ce qu'on veut ecrire 
  ///si on ne veut pas ecraser le fichier dans le cas o� il existe d�j�
  string line,mot,indice;
  char c[100]; 
  size_t pos;
  //string slice1("slice_comp"), slice2("slice_behaviour"), 
  string stringtemp;
  uint i=0;
  float T_RWDATA;	//temps pass� � lire et �crire des datas
  float T_Inst;  	//temps pass� dans les instructions (ms)
  float T_Total; 	//temps total
  float T_OneDATA;  	//ms pour lire ou �crire une data
  float MissPred;	//MissPred
  float Pen_L1;  	//penalit� pour un miss L1
  float Pen_L2;  	//penalit� pour un miss L2
  ostringstream oss;
  bool sortie=true;
  uint Nb_instr, load, store, instrL1,R_L1_Miss,W_L1_Miss,instrL2,R_L2_Miss,W_L2_Miss;
  sprintf(c,"_cpu_%d",C->indice_CPU);
  indice=c;
  if(outputfile)
  {
    ifstream inputfile(input.c_str());
    if(inputfile)
    {
      while(getline(inputfile,line)) 
      {	  	
	/// si besoin de remplacer une autre chaine rajouter la dans le definition de la fonction 
	///et utiliser le if ci-dessous pour faire le remplacement. 
		  pos=line.find(S1);
		  if(pos<=line.size()) 
		  {	    
		    stringtemp =S1+indice;
		    line.replace(pos,S1.size(),stringtemp);
		    stringtemp.clear();
		  }
		   pos=line.find(S2);
		  if(pos<=line.size()) 
		  {	    
		    stringtemp =S2+indice;
		    line.replace(pos,S2.size(),stringtemp);
		    stringtemp.clear();
		  }
		  pos=line.find(S3);
		  if(pos<=line.size()) 
		  {	    
		    stringtemp =S3+indice;
		    line.replace(pos,S3.size(),stringtemp);
		    stringtemp.clear();
		  }
	  pos=line.find("TBC");
	  if (pos!=-1)
	  {/// on  va se repositionner au debut de la ligne
	    inputfile.seekg(-line.size(),ios::cur);
	   while(inputfile>>mot && sortie) 
	    {
		if((mot.compare("TBC"))==0)
		{
		  i=0;
		  while(mot!="["){inputfile>>mot; if(++i>10){cout<<--i <<" iterations no '[' found incorrect file or format in : "<<input<<endl; return;}} 
		  while(mot!="]"&&sortie)
		  {
		    inputfile>>Nb_instr;	inputfile>>load;  		inputfile>>store;
		    inputfile>>instrL1;		inputfile>>R_L1_Miss;		inputfile>>W_L1_Miss;
		    inputfile>>instrL2;		inputfile>>R_L2_Miss;		inputfile>>W_L2_Miss;
		    
		    T_OneDATA=1.0/(C->work_frequency*1000.0);
		    Pen_L1=10.0/(C->work_frequency*1000.0);
		    Pen_L2=100.0/(C->work_frequency*1000.0);
		    
		    T_Inst=Nb_instr/(C->work_frequency*C->dmips*1000.0)+instrL1*Pen_L1+instrL2*Pen_L2;
		    T_RWDATA=(store+load)*(T_OneDATA)+(R_L2_Miss*Pen_L2+W_L2_Miss*Pen_L2)+(R_L1_Miss*Pen_L1+W_L1_Miss*Pen_L1);
		    MissPred=(77066983.0/(1500*5.0))*C->pipeline*T_OneDATA;
		    T_Total=MissPred+T_RWDATA+T_Inst;
		    //cout<<"TBC = "<<T_Total<<" pour  "<<input<<endl;
		    TableTBC[nbTBC++]=T_Total;
		    inputfile>>mot;
		    oss<<T_Total;
		    if(once)TBC_Ajouter(&thisTBC,name,C->indice_CPU,T_Total);
		  }
		  if(pos<=line.size()){ line.replace(pos,3, oss.str());}
		  oss.str(""); oss.clear();
		  sortie=false;
		}
	    }
	    inputfile.seekg(-3*mot.size()+2,ios::cur);	    
	    sortie=true;
	  }	  
	  outputfile<<line<<endl;
      }
    inputfile.close();
    }
    else {cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<input<<endl;exit(0);}
    
  }
  else {cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<output<<endl;exit(0);} 
 // cout<<"fichier d'entr�e "<<input<<endl;
//       cout<<output<<" \thas been generate"<<endl;

    outputfile.close();

}



/// on g�nr�rer le fichier composition 
/// savoir les includes � mettre on lira les mot apr�s le include.
/// cette focntion doit retourner n fichier a g�n�rer
uint GenerateCompCpuFile(string input,string output,string includeListe[], string componentListe[] )
{
  ofstream outputfile(output.c_str());
  string line,mot,Stmp,component_type[nb_fichier_include]; string ListeFileToGenerate[nb_fichier_include];
  string behaviour("_behaviour"), carac("_timing_characs");
  uint i=0,j=0, fin=0, nb_include=0, nb_component=0;
  string include("include"), S2,S3;
  size_t pos;
  string component_n[100];
  char c[100];
  uint nb_affinity=0,affinity[100];

    if(!outputfile){cout<<"impossible de cr�e le fichier de sortie"<<output<<endl;exit(1);}
    ifstream in1(input.c_str());
    if(in1)
    {
      i=0;
      /// lecture des includes pour savoir les fichiers a ouvrir
      	while(getline(in1,line) && fin<10) /// si au out de 15 it�rations on ne trouve plus d'include on arrete de chercher
	{	    
	  pos=line.find(include);
	    if (pos!=-1)
	    {/// on  va se repositionner au debut de la ligne
	    /// on va r�cup�rer les caract�re: sliceX, X �tant le num�ro.
	    in1.seekg(-line.size()-1,ios::cur);
	    in1>>Stmp;
	    in1>>Stmp;
	    pos=line.find(include);
	    if (pos!=-1)
	    ListeFileToGenerate[i] = Stmp.substr(0,Stmp.size()-1);
	    Stmp.clear();
	    i++;
	    }
	    else fin++;
	}
	in1.close();
	  nb_include=i;
	  fin=0;
	  i=0;
	  for(j=0; j<nb_include;j++)
	  {
	    
	    S2=ListeFileToGenerate[j].substr(0,ListeFileToGenerate[j].size()-4)+behaviour;
	    ifstream in2(input.c_str());
	      while(getline(in2,line)) 
	      {	    
		pos=line.find(S2);
		  if (pos!=-1)
		  {/// on  va se repositionner au debut de la ligne
		  /// on va r�cup�rer les caract�re: sliceX, X �tant le num�ro.
		  in2.seekg(-line.size()-1,ios::cur);
		  in2>>Stmp;//cout<<Stmp<<endl;
		  in2>>Stmp;//cout<< Stmp<<endl;
		  in2>>component_n[i];//cout<<"con : "<<component_n[i]<<endl;
		  componentListe[i]=component_n[i];
		  in2>>Stmp;//cout<<Stmp<<endl;
		  Stmp.clear();
		  i++;
		  } 
	      }
	      in2.close();
	  }
	  nb_affinity=i;i=0;
		for(i;i<nb_affinity;i++)
		{
		  	  ifstream in3(input.c_str());

	      while(getline(in3,line) && i<nb_affinity) /// Deuxi�me lecture
	      {
		
		mot="cnx_"+component_n[i]+".configure_affinity(";
		pos=line.find(mot);
		  if (pos!=-1)
		  {/// on va r�cup�rer l'affinity qui est en 3�me position de la chaine de mot		
		  in3.seekg(-line.size()-1,ios::cur);
		  in3>>Stmp;
		  in3>>Stmp;
		  in3>>affinity[i];//cout<<affinity[i]<<endl;
		  in3>>Stmp;
		  Stmp.clear();
		  }
	      }
	     in3.close(); 
	  }
	  Stmp.clear();

	   /// maintenant rajoutons les extensions..
	   i=0;
	   fin=1;
	   ifstream in4(input.c_str());
	  
	      	   fin=1;
	      while(getline(in4,line)&&fin) ///  lecture
	      {	for(j=0;j<nb_include;j++)
		{
		    pos=line.find(ListeFileToGenerate[i]);
		      if(pos!=-1) 
		      {
			for(i=j;i<nb_affinity;i++)
			{
			  S2=ListeFileToGenerate[j].substr(0,ListeFileToGenerate[j].size()-4);
			  S3=component_n[i].substr(0,S2.size());
			    if(S3.compare(S2)==0)
			    {
			      component_type[i]=S2;
			      sprintf(c,"_cpu_%d",affinity[i]);
			      includeListe[i]=S2+c+".txt";
			      Stmp =Stmp+"include "+S2+c+".txt;\n";
			    }
			 }
			 fin=0;
		      line.replace(0,line.size(),Stmp);
		      Stmp.clear();
		      outputfile<<line<<endl;
		    }
		   
		    
	      }
	  }
	  in4.close();
	  i=0;
	  fin=1;
	  ifstream in5(input.c_str());
	  while(getline(in5,line)){
	   fin=1;
	    pos=line.find("component_instance");
	    if (pos!=-1)
	    {
	      for(i=0;i<nb_affinity && fin;i++)
	      {
	      S2=component_n[i]+" "+component_type[i]+carac;
	      pos=line.find(S2);
		      if (pos!=-1)
		      {
			sprintf(c,"_cpu_%d",affinity[i]);
			Stmp= S2+c;
			line.replace(pos,S2.size(),Stmp);
			Stmp.clear();
			S2=component_type[i]+behaviour;
			pos=line.find(S2);
			    if (pos!=-1)
			    {
			      sprintf(c,"_cpu_%d",affinity[i]);
			      Stmp= S2+c;
			      line.replace(pos,S2.size(),Stmp);
			      Stmp.clear();
			      fin=0;
			    }
		      }
	      }
	      outputfile<<line<<endl;

	    }
	    else
	    {
	      pos=line.find(include);
	      if (pos==-1)  outputfile<<line<<endl;
	      
	    } 
	  }
	  in5.close();

      //cout<<nb_include<<" include(s) dans le fichier : "<<input<<endl;
      cout<<nb_affinity<<" fichier(s) � cr�er."<<endl;
    }
    else {cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<input<<endl;exit(0);}
    
//      cout<<output<<" \thas been generate"<<endl;
     ifstream ii(input.c_str());
     ofstream o("copiecomposition.txt");
     while(getline(ii,line)) o<<line<<endl;
     
     o.close();
     ii.close();
    // sleep(1.0);
     return nb_affinity;
     
}


void GenerateDspFile(const char *output,string input, COMPONENTDSP C)
{
  ofstream outputfile(output);/// ios::app pour rajouter en fin du fichier ce qu'on veut ecrire 
  ///si on ne veut pas ecraser le fichier dans le cas o� il existe d�j�
  string line,mot;
  size_t pos;
  uint i=0;
  float T_RWDATA;	//temps pass� � lire et �crire des datas
  float T_Inst;  	//temps pass� dans les instructions (ms)
  float T_Total; 	//temps total
  float T_OneDATA;  	//ms pour lire ou �crire une data
  float MissPred;	//MissPred
  float Pen_L1;  	//penalit� pour un miss L1
  float Pen_L2;  	//penalit� pour un miss L2
  ostringstream oss;
  bool sortie=true;
  uint Nb_instr, load, store, instrL1,R_L1_Miss,W_L1_Miss,instrL2,R_L2_Miss,W_L2_Miss;
  
  if(outputfile)
  {
    ifstream inputfile(input.c_str());
    if(inputfile)
    {
      while(getline(inputfile,line)) 
      {
	  pos=line.find("TBC");
	  if (pos!=-1)
	  {/// on  va se repositionner au debut de la ligne
	    inputfile.seekg(-line.size(),ios::cur);
	   while(inputfile>>mot && sortie) 
	    {
		if((mot.compare("TBC"))==0)
		{
		  i=0;
		  while(mot!="["){inputfile>>mot; if(++i>10){cout<<--i <<" iterations no '[' found incorrect file or format in : "<<input<<endl; return;}} 
		  while(mot!="]")
		  {
		    inputfile>>Nb_instr;// nombre di'nstruction
		    inputfile>>load; // nombre de D-Read
		    inputfile>>store;// nombre de D-Write
		    inputfile>>instrL1;//
		    inputfile>>R_L1_Miss;
		    inputfile>>W_L1_Miss;
		    inputfile>>instrL2;
		    inputfile>>R_L2_Miss;
		    inputfile>>W_L2_Miss;
		    
		    T_OneDATA=1.0/(C->DSP_->work_frequency*1000.0);
		    Pen_L1=10.0/(C->DSP_->work_frequency*1000.0);
		    Pen_L2=100.0/(C->DSP_->work_frequency*1000.0);
		    
		    T_Inst=Nb_instr/(C->DSP_->work_frequency*C->DSP_->dmips*1000.0)+instrL1*Pen_L1+instrL2*Pen_L2;
		    T_RWDATA=(store+load)*(T_OneDATA)+(R_L2_Miss*Pen_L2+W_L2_Miss*Pen_L2)+(R_L1_Miss*Pen_L1+W_L1_Miss*Pen_L1);
		    MissPred=(77066983.0/(1500*5.0))*C->DSP_->pipeline*T_OneDATA;
		    T_Total=MissPred+T_RWDATA+T_Inst;
		    inputfile>>mot;
		     oss<<T_Total;
// 		    cout<<"dsp_"<<C->DSP_->indice_DSP<<" ("<<i++<<") T_Total: "<<T_Total<<endl;
		  }
		  if(pos<=line.size()){ line.replace(pos,3, oss.str());}
		  oss.str(""); oss.clear();
		  sortie=false;
		}
	    }
	    inputfile.seekg(-3*mot.size()+2,ios::cur);	    
	    sortie=true;
	  }	  
	  outputfile<<line<<endl;
      }
    
    }
    else {cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<input<<endl;exit(0);}
  }
  else {cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<output<<endl;exit(0);} 
  cout<<output<<" \thas been generate"<<endl;
 }



// void ReadCompositionFile(char * compositionfile, char * compositionmain, CPU MonCpu,DSP MonDsp,COMPONENTCPU MesComposantsCPU, COMPONENTDSP MesComposantsDSP, CACHE MesCacheL1,CACHE MesCacheL2)
void ReadCompositionFile(char * compositionfile)
{
 
//   int nb_cpu=0, nb_cache=0, nb_dsp=0;
  uint nb_ligne=0,nb_file=0;
  string line, filename,tmp; 
//   string listeinclude[nb_fichier_include];
//   uint indice=0;

  char dir[100];
  char outputcomposition[100];
  CPU MonCpu=NULL,cpu_tmp=NULL;
  DSP MonDsp=NULL,dsp_tmp=NULL;
  CACHE MesCacheL1=NULL,MesCacheL2=NULL,cacheL1_tmp=NULL,cacheL2_tmp=NULL;
  COMPONENTCPU MesComposantsCPU=NULL,CompoCPU_temp=NULL;
  COMPONENTDSP MesComposantsDSP=NULL,CompoDSP_temp=NULL;  
  
  ifstream listing_file(compositionfile);   
 
  if(listing_file)
  {
    
    uint freq=0, taille=0,assoc=0,bpl=0;
    uint indice_cpu=0,indice_cacheL1=0,indice_cacheL2=0,indice_dsp=0;
    
    while(listing_file>>line){ /// on lit mot par mot le fichier et on instantie les composants
      
      nb_ligne++;
      if(line == "component") 
      {
	listing_file>>line;
	if(line=="PU")
	{
	    listing_file>>line;
	    listing_file>>filename;
	    listing_file>>freq;
	    MonCpu=ADD_CPU(MonCpu,filename,freq);
	}
	else{
	    if(line=="CACHE")
	    {
	      listing_file>>line;
	      tmp = line.substr(0,line.size()-2);	      	      
	      listing_file>>taille;
	      listing_file>>assoc;
	      listing_file>>bpl;
	      if(tmp =="L1") MesCacheL1=ADD_CACHE(MesCacheL1,taille,assoc,bpl);
	      else {if(tmp =="L2") MesCacheL2=ADD_CACHE(MesCacheL2,taille,assoc,bpl);}
	    }
	    else{
	      if(line =="DSP")
	      {
		listing_file>>line;
		listing_file>>filename;
		listing_file>>freq;
		MonDsp=ADD_DSP(MonDsp,filename,freq);
	      }
	    }
	}
	
      }/// end if component
      else{
	  if(line =="connection")
	  {
	      listing_file>>line;
	      tmp = line.substr(0,line.size()-1);
	      if(tmp =="CPU")
	      {
		indice_cpu=atoi(line.substr(tmp.size(),line.size()).c_str());
		listing_file>>line;
		listing_file>>line;
		tmp=line.substr(0,line.size()-1);
		if(tmp=="L1_")
		{
		  indice_cacheL1=atoi(line.substr(tmp.size(),line.size()).c_str());
		  MesComposantsCPU = ADD_COMPONENTCPU(MesComposantsCPU,AccessToCPU(MonCpu,indice_cpu),AccessToCACHE(MesCacheL1,indice_cacheL1),indice_cacheL1,indice_cpu,"cpu");
		  
		  //thisComposantsCPU = ADD_COMPONENTCPU(thisComposantsCPU,AccessToCPU(MonCpu,indice_cpu),AccessToCACHE(MesCacheL1,indice_cacheL1),indice_cacheL1,indice_cpu,"cpu");
		}
	      }
	      else {
		if(tmp =="DSP")
		{
		    indice_dsp=atoi(line.substr(tmp.size(),line.size()).c_str());
		    listing_file>>line;
		    listing_file>>line;
		    tmp=line.substr(0,line.size()-1);
		      if(tmp=="L1_")
		      {			
			indice_cacheL1=atoi(line.substr(tmp.size(),line.size()).c_str());
			MesComposantsDSP = ADD_COMPONENTDSP(MesComposantsDSP,AccessToDSP(MonDsp,indice_dsp),AccessToCACHE(MesCacheL1,indice_cacheL1),indice_cacheL1,indice_dsp,"dsp");
		      }
		}
	      else{
		if(tmp=="L1_")
		{
		  indice_cacheL1=atoi(line.substr(tmp.size(),line.size()).c_str());
		  listing_file>>line;
		  listing_file>>line;
		  tmp=line.substr(0,line.size()-1);
		  if(tmp=="L2_")
		  {
		      indice_cacheL2=atoi(line.substr(tmp.size(),line.size()).c_str());
		      cacheL1_tmp=AccessToCACHE(MesCacheL1,indice_cacheL1);
		      cacheL2_tmp=AccessToCACHE(MesCacheL2,indice_cacheL2);
		      
		      if(GetNamelinkCache(cacheL1_tmp) =="dsp"){
		      CompoDSP_temp=AccessToCOMPONENTDSP(MesComposantsDSP,GetLinkCacheL1DSP(MesComposantsDSP,indice_cacheL1));
		      ADD_CACHE_L2_TO_COMPONENTDSP(CompoDSP_temp,cacheL2_tmp);
		      }
		      else{
			if(GetNamelinkCache(cacheL1_tmp) =="cpu"){
			CompoCPU_temp=AccessToCOMPONENTCPU(MesComposantsCPU,GetLinkCacheL1CPU(MesComposantsCPU,indice_cacheL1));
			ADD_CACHE_L2_TO_COMPONENTCPU(CompoCPU_temp,cacheL2_tmp);
			}
		      }
		  }
		}
	      
	      }
	    }
	  }
	   else 
	   {
	    nb_ligne--;
	    cout <<" \n\n ATTENTION ===> Probl�me � la ligne: "<<nb_ligne<<" dans le fichier: "<<compositionfile<<" <==="<<endl; 
	    listing_file.seekg(-listing_file.tellg(),ios::cur);
	    while(nb_ligne>0){getline(listing_file,line);nb_ligne--;}
	    cout<<line <<" :Cette ligne n'est pas correcte \n \n"<<endl;
	    
	      if(line.substr(0,9)=="component")
	      {
		if(line.substr(10,2)=="PU"){
		  cout<<" Required format CPU :";
		  cout<<" component PU CPUX inputfile/file_name.txt freq "<<endl;
		  cout<<" X : cpu number"<<endl;
		  cout<<" file_name.txt : architecture decription texte file"<<endl;
		  cout<<" freq: cpu working frequency"<<endl;
		  cout<<" Example: component PU CPU0 inputfile/cortexA8.txt 200\n"<<endl;
		  exit(0);
		}
	      else
	      {
		  if(line.substr(10,5)=="CACHE")
		  {
		    cout<<" Required format cache memory :";
		    cout<<" component CACHE LX_Y A B C "<<endl; 
		    cout<<" X : cache type 1 or 2"<<endl;
		    cout<<" Y : cache number"<<endl;
		    cout<<" A : cache size "<<endl;
		    cout<<" B : cache associativity "<<endl;
		    cout<<" C : cache nb byte/line "<<endl;
		    cout<<" Example: component CACHE L1_2 32 32 32\n"<<endl;
		    exit(1);
		  }
		else
		{
		  if(line.substr(10,3)=="DSP"){
		  cout<<" Required format DSP :";
		  cout<<" component DSP DSPX inputfile/file_name.txt freq "<<endl;
		  cout<<" X : dsp number"<<endl;
		  cout<<" file_name.txt : architecture decription texte file"<<endl;
		  cout<<" freq: dsp working frequency"<<endl;
		  cout<<" Example: component DSP DSP1 inputfile/dsp3.txt 200\n"<<endl;
		  exit(0);
		}
		}
	      }
	      }
	      else{
		if(line.substr(0,10) =="connection")
		{
		cout<<" Required format connection :";
		cout<<" component CX -> CY"<<endl; 
		cout<<" CX : can be  a PU or a cache memory or RAM ,X mean the component number"<<endl;
		cout<<" CY : only RAM or cache memory ,Y mean the component number"<<endl;
		cout<<" Example: \n\tconnection L1_0 -> L2_0 (link a cache L1 to a cache L2) \n \t";
		cout<<"connection CPU1 -> L1_1 (link a PU to a cache L2)\n"<<endl;
		exit(2);
		}
	      }
	   }
	  

      }
	
      }///end while(listing_file>>line)
    }///end if(listing_file)
  else{
    cout<<"ERREUR: Impossible d'ouvrir le fichier: "<<compositionfile<<endl;
    exit(0);
  }
  
  listing_file.close();


    thisComposantsCPU= MesComposantsCPU;
    thisComposantsDSP= MesComposantsDSP;
    thisMesCPU=MonCpu;
    thisMesDSP=MonDsp;


}

void ChangeAffinity(string compositionfile, string compositionfile_temp,string component,uint NewAffinity) 
{
  string line,tmp;
  size_t pos=-1;
  ostringstream convert;   // stream used for the conversion
  
  
  ofstream outputfile(compositionfile_temp.c_str());   
  if(!outputfile)
  {
    cout<<"impossible de cr�e le fichier de sortie: "<<compositionfile_temp<<endl;
    exit(1);
  }


  ifstream readingfile(compositionfile.c_str());   
  if(readingfile)
  {
    
    while(getline(readingfile,line)) 
      {
	 tmp="cnx_"+component+".configure_affinity(";
	  pos=line.find(tmp);
	  if (pos!=-1)
	  {
	    convert.str(""); convert.clear();
	    convert<<NewAffinity; 
	    line.replace(pos+tmp.size()+1,convert.str().size(),convert.str());
	    outputfile<<line<<endl;
	  }
	  else 
	  {
	    outputfile<<line<<endl;
	  }
	
      }
    
  }
  else 
  {
    cout <<"no such file: "<<compositionfile<<endl; 
    
  }
  
    /// on ferme les  fichiers puis on fait une recopie
  outputfile.close(); 
  readingfile.close();
  
  ofstream write(compositionfile.c_str());   
  ifstream read(compositionfile_temp.c_str());
  while(getline(read,line))
  {
    write<<line<<endl;
  }
  write.close();
  read.close();
}


int getAffinityOf(string inputfile, string componentname) 
{
  string line,tmp;
  size_t pos=-1;
  int ret=-1;
  ifstream read(inputfile.c_str());   
  if(read)
  {
      while(getline(read,line)) 
      {
	tmp = "cnx_"+componentname+".configure_affinity(";
	pos=line.find(tmp);
	  if (pos!=-1)
	  {
	    read.seekg(-line.size()-1,ios::cur);
	    read>>tmp;
	    read>>tmp;
	    read>>ret;
	    read>>tmp;
	    tmp.clear();
	    return ret;
	  }
      }
  }
  else 
  {
    //error
    return -1;
  }
  
}


void FindAndReplaceAffinity(string compositionfile, string compositionfile_temp,uint OldAffinity,uint NewAffinity)
{
  
   string line,tmp;
  size_t pos=-1;
  ostringstream convert;
  ofstream outputfile(compositionfile_temp.c_str());   
  if(!outputfile)
  {
    cout<<"impossible de cr�e le fichier de sortie: "<<compositionfile_temp<<endl;
    exit(1);
  }

  ifstream readingfile(compositionfile.c_str());   
  if(readingfile)
  {
    while(getline(readingfile,line)) 
      {
	convert.str(""); convert.clear();
	 convert<<OldAffinity; 
	 tmp="configure_affinity( "+convert.str();
	  pos=line.find(tmp);
	  if (pos!=-1)
	  {
// 	    cout<<"trouv�\n old : ";
// 	    cout<<line<<endl;
// 	    cout<<pos<<endl;
	    convert.str(""); convert.clear();
	    convert<<NewAffinity; 
	    line.replace(pos+tmp.size()-1,convert.str().size(),convert.str());
	    outputfile<<line<<endl;
/*	    cout<<"new : "<<line<<endl;*/
	  }
	  else 
	  {
	    outputfile<<line<<endl;
	  }
	
      }
    
  }
  else 
  {
    cout <<"no such file: "<<compositionfile<<endl; 
    
  }
  
    /// on ferme les  fichiers puis on fait une recopie
  outputfile.close(); 
  readingfile.close();
  
  ofstream write(compositionfile.c_str());   
  ifstream read(compositionfile_temp.c_str());
  while(getline(read,line))
  {
    write<<line<<endl;
  }
  read.close(); 
  write.close();
  tmp.clear();
  
}

void RegenerateCpuFile(string includeListe[],string componentListe[], uint nb_component)
{
  string tmp;
  uint i=0,indice=0, indice_prec=20, nb_cpu=0,n=0;
  CPU cpu_tmp=NULL,cpu_access=NULL;
  cpu_access = CloneCPU(thisMesCPU);
  nb_cpu=NB_CPU(cpu_access);
  once=true;
  while(i<nb_component)
  {
    //cout<<componentListe[i]<<endl;
      tmp= includeListe[i].substr(0,includeListe[i].size()-4);
      indice=atoi(includeListe[i].substr(tmp.size()-1,tmp.size()).c_str());
      tmp.clear();
      tmp= includeListe[i].substr(0,includeListe[i].size()-10);
      tmp = "inputfile/"+tmp+".txt";
      cpu_tmp = AccessToCPU(cpu_access,indice);
      GenerateCpuFile(includeListe[i],tmp,cpu_tmp, componentListe[i],"_comp","_behaviour","_timing_characs");
      tmp.clear();
      i++;     
  }
  once=false;
  //delete(cpu_access);
 // delete(cpu_tmp);
}


