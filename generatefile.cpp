#include "generatefile.h"
#include <stdio.h>
#include <stdlib.h>



void GenerateCpuFile(string output,string input, COMPONENTCPU C,string S1, string S2,string S3)
{
  ofstream outputfile(output.c_str());/// ios::app pour rajouter en fin du fichier ce qu'on veut ecrire 
  ///si on ne veut pas ecraser le fichier dans le cas où il existe déjà
  string line,mot,indice;
  char c[20]; 
  size_t pos;
  //string slice1("slice_comp"), slice2("slice_behaviour"), 
  string stringtemp;
  uint i=0;
  float T_RWDATA;	//temps passé à lire et écrire des datas
  float T_Inst;  	//temps passé dans les instructions (ms)
  float T_Total; 	//temps total
  float T_OneDATA;  	//ms pour lire ou écrire une data
  float MissPred;	//MissPred
  float Pen_L1;  	//penalité pour un miss L1
  float Pen_L2;  	//penalité pour un miss L2
  ostringstream oss;
  bool sortie=true;
  uint Nb_instr, load, store, instrL1,R_L1_Miss,W_L1_Miss,instrL2,R_L2_Miss,W_L2_Miss;
  sprintf(c,"_cpu_%d",C->CPU_->indice_CPU);
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
		    
		    T_OneDATA=1.0/(C->CPU_->work_frequency*1000.0);
		    Pen_L1=10.0/(C->CPU_->work_frequency*1000.0);
		    Pen_L2=100.0/(C->CPU_->work_frequency*1000.0);
		    
		    T_Inst=Nb_instr/(C->CPU_->work_frequency*C->CPU_->dmips*1000.0)+instrL1*Pen_L1+instrL2*Pen_L2;
		    T_RWDATA=(store+load)*(T_OneDATA)+(R_L2_Miss*Pen_L2+W_L2_Miss*Pen_L2)+(R_L1_Miss*Pen_L1+W_L1_Miss*Pen_L1);
		    MissPred=(77066983.0/(1500*5.0))*C->CPU_->pipeline*T_OneDATA;
		    T_Total=MissPred+T_RWDATA+T_Inst;
		    inputfile>>mot;
		    oss<<T_Total;
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


void GenerateCompCpuFile(string input,string output,string S1)
{
  ofstream outputfile(output.c_str());
  string line,mot,Stmp;
  string main("main.txt"), slice("slice.txt"),main_behaviour("main_behaviour"), carac("timing_characs");

  uint i=0;
  size_t pos;
  string slice_n[3];
  char c[20];
  
  uint Max=0,Maxtemp=0,affinity[3];
//   string main("main.txt"), slice("slice.txt");
//   sprintf(c,"_cpu_%d",C->CPU_->indice_CPU);
//   indice=c;
    if(!outputfile){cout<<"impossible de crée le fichier de sortie"<<output<<endl;exit(1);}

    ifstream in1(input.c_str());
    if(in1)
    {
	while(getline(in1,line)) /// première lecture
	{	    
	  pos=line.find(S1);
	    if (pos!=-1)
	    {/// on  va se repositionner au debut de la ligne
	    /// on va récupérer les caractère: sliceX, X étant le numéro.
	    in1.seekg(-line.size()-1,ios::cur);
	    in1>>Stmp;//cout<<Stmp<<endl;
	    in1>>Stmp;//cout<< Stmp<<endl;
	    in1>>slice_n[i];
	    in1>>Stmp;//cout<<Stmp<<endl;
	    Stmp.clear();
	    i++;
	    }  
	}	
	Max=i;i=0;
	ifstream in2(input.c_str());
	
	  while(getline(in2,line)&& (i!=Max)) /// Deuxième lecture
	  {
	    mot="cnx_"+slice_n[i]+".configure_affinity(";
	    pos=line.find(mot);
	      if (pos!=-1)
	      {/// on va récupérer l'affinity qui est en 3ème position de la chaine de mot
	      in2.seekg(-line.size()-1,ios::cur);
	      in2>>Stmp;
	      in2>>Stmp;
	      in2>>affinity[i];
	      in2>>Stmp;
	      Stmp.clear();
	      i++;
	      }
	  }

	  i=0;
	  ifstream in3(input.c_str());
	  while(getline(in3,line)) /// Troisième lecture
	  {/// on va pouvoir générer le fichier de sortie
		pos=line.find(main);/// recherche de main.txt dans le fichier
		if(pos!=-1) 
		{
		  Stmp = "main_cpu_0.txt";
		  line.replace(pos,main.size(),Stmp);
		  Stmp.clear();
		  
		}
		
		
		pos=line.find(main_behaviour);/// recherche de main_behaviour dans le fichier
		if(pos!=-1) 
		{
		  Stmp = main_behaviour+"_cpu_0";
		  line.replace(pos,main_behaviour.size(),Stmp);
		  Stmp.clear();
		   pos=line.find(carac);
		    if(pos!=-1) 
		    {
		      Stmp = carac+"_cpu_0";
		      line.replace(pos,carac.size(),Stmp);
		      Stmp.clear();
		    }
		}
		Stmp.clear();
		pos=line.find(slice); /// recherche de slice_behaviour sliceX dans le fichier
		if(pos!=-1) 
		{
		  Stmp.clear();
		    for(i=0;i<Max;i++)
		    {
		      sprintf(c,"_cpu_%d",affinity[i]);	  
		      Stmp =Stmp+"include slice"+c+".txt;\n";	 
		    }
		  line.replace(0,line.size(),Stmp);
		  Stmp.clear();
		  
		}
	      
		for(i=0;i<Max; i++)
		{Stmp.clear();
		  mot=S1+" "+slice_n[i];
		  pos=line.find(mot);
		    if (pos!=-1)
		    {
		      sprintf(c,"_cpu_%d",affinity[i]);
		      Stmp=S1+c;
		      line.replace(pos,S1.size(),Stmp);
		      Stmp.clear();
		      pos=line.find(carac);
		      if(pos!=-1) 
		      {
			Stmp = carac+c;
			line.replace(pos,carac.size(),Stmp);
			Stmp.clear();
		      }
		    }
		    
		}
	      outputfile<<line<<endl;/// on ecrit dans le fichier de composition.
	  }
    }
    else {cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<input<<endl;exit(0);}
//   }
//   else {cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<output<<endl;exit(0);} 
     cout<<output<<" \thas been generate"<<endl;

}


void GenerateDspFile(const char *output,string input, COMPONENTDSP C)
{
  ofstream outputfile(output);/// ios::app pour rajouter en fin du fichier ce qu'on veut ecrire 
  ///si on ne veut pas ecraser le fichier dans le cas où il existe déjà
  string line,mot;
  size_t pos;
  uint i=0;
  float T_RWDATA;	//temps passé à lire et écrire des datas
  float T_Inst;  	//temps passé dans les instructions (ms)
  float T_Total; 	//temps total
  float T_OneDATA;  	//ms pour lire ou écrire une data
  float MissPred;	//MissPred
  float Pen_L1;  	//penalité pour un miss L1
  float Pen_L2;  	//penalité pour un miss L2
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


void GenerateCompositionFile(const char* output,const char* input,const char* newmain, const char* newslice, string indice)
{
 ofstream outputfile(output);
  string line;
  size_t pos;
  string main("main.txt"), slice1("slice1.txt"),slice2("slice2.txt"), main_behaviour("main_behaviour"),behaviour("slice_behaviour"), carac("main_timing_characs");
  string stringtemp;
  
  if(outputfile)
  {
    ifstream inputfile(input);
    if(inputfile)
    {
      
      while(getline(inputfile,line)) 
      {
	  
	
	pos=line.find(main);
	  if(pos<=line.size()) line.replace(pos,main.size(),newmain );
	  else
	  {
	      pos=line.find(slice1);
	      if(pos<=line.size()) line.replace(pos,slice1.size(),newslice);
	      else
	      {
		    pos=line.find(behaviour);
		  if(pos<=line.size()) 
		  {	    
		    stringtemp = behaviour + indice;
		    line.replace(pos,behaviour.size(),stringtemp);
		    stringtemp.clear();
		  }
		  else
		  {
		    pos=line.find(main_behaviour);
		    if(pos<=line.size()) 
		    {
// 				      cout<< "cics"<<endl;

		      stringtemp = main_behaviour + indice;
		      line.replace(pos,main_behaviour.size(),stringtemp);
		      stringtemp.clear();
		    }
		  
		    pos=line.find(carac);
		    if(pos<=line.size()) 
		    {
// 		      cout<< "cic"<<endl;
		      stringtemp = carac + indice;
		      line.replace(pos,carac.size(),stringtemp);
		      stringtemp.clear();

		    }
		  }
	      
	      }
	  }
	      
	      
	  outputfile<<line<<endl;
      }
    }
    else cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<input<<endl;
  }
  else cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<output<<endl; 
}

void ReadCompositionFile(char * compositionfile, char * compositionmain)
{
 
  int nb_cpu=0, nb_cache=0, nb_dsp=0,nb_ligne=0;
  string line, filename,tmp; 
  char dir[100];
  char outputcomposition[20];
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
	    cout <<" \n\n ATTENTION ===> Problème à la ligne: "<<nb_ligne<<" dans le fichier: "<<compositionfile<<" <==="<<endl; 
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
  nb_cpu= NB_CPU(MonCpu);
  nb_dsp= NB_DSP(MonDsp);
  nb_cache= NB_CACHE(MesCacheL1);
  nb_cache= NB_CACHE(MesCacheL2);
//   Affiche_COMPONENTDSP(MesComposantsDSP);  
//   Affiche_COMPONENTCPU(MesComposantsCPU);
  uint i=0;
  CompoCPU_temp = MesComposantsCPU;
  while(i<nb_cpu)
  {
    sprintf(dir,"slice_cpu_%d.txt",CompoCPU_temp->CPU_->indice_CPU);
    GenerateCpuFile(dir,"inputfile/slice.txt",CompoCPU_temp,"_comp","_behaviour","_timing_characs");
    if(CompoCPU_temp->CPU_->indice_CPU==0)
       GenerateCpuFile("main_cpu_0.txt","inputfile/main.txt",CompoCPU_temp,"_comp","_behaviour","_timing_characs");
    
/*
    if(CompoCPU_temp->CPU_->indice_CPU==0)
    {
      string indice; 
      sprintf(dir,"_cpu_%d",CompoCPU_temp->CPU_->indice_CPU);
      indice = dir;
      GenerateSliceCpuFile(dir,"inputfile/slice.txt",CompoCPU_temp);
      sprintf(dir,"main_cpu_%d.txt",CompoCPU_temp->CPU_->indice_CPU);
      GenerateCpuFile(dir,"inputfile/main.txt",CompoCPU_temp,indice);
      
      sprintf(dir,"slice_cpu_%d.txt",CompoCPU_temp->CPU_->indice_CPU);
      sprintf(outputcomposition,"composition_cpu_%d.txt",CompoCPU_temp->CPU_->indice_CPU);
      GenerateCompositionFile(outputcomposition,compositionmain,"main_cpu_0.txt",dir,indice);
    }
    else
    {
      
    }
    */
    
    CompoCPU_temp=CompoCPU_temp->next;
    i++; 
  } 
        GenerateCompCpuFile(compositionmain,"composition.txt","slice_behaviour");


  
  /*
  i=0;
  CompoDSP_temp = MesComposantsDSP;
  while(i<nb_dsp)
  {
    sprintf(dir, "outputfile/slice_dsp_%d.txt",CompoDSP_temp->DSP_->indice_DSP);
    GenerateDspFile(dir,"slice.txt",CompoDSP_temp);
    if(CompoDSP_temp->DSP_->indice_DSP==0)
    {
      sprintf(dir, "outputfile/main_dsp_%d.txt",CompoDSP_temp->DSP_->indice_DSP);
      GenerateDspFile(dir,"main.txt",CompoDSP_temp);
    }
    CompoDSP_temp=CompoDSP_temp->next;
    i++;
  }*/
}

