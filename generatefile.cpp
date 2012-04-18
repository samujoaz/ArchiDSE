#include "generatefile.h"


void GenerateCpuFile(char *output,string input, COMPONENTCPU C)
{
  ofstream outputfile(output);/// ios::app pour rajouter en fin du fichier ce qu'on veut ecrire 
  ///si on ne veut pas ecraser le fichier dans le cas où il existe déjà
  string line,mot;
  size_t pos;
  float TBC=0.0;
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
		  while(mot!="[" && sortie) inputfile>>mot;
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
		    
		    T_OneDATA=1.0/(C->CPU_->work_frequency*1000.0);
		    Pen_L1=10.0/(C->CPU_->work_frequency*1000.0);
		    Pen_L2=100.0/(C->CPU_->work_frequency*1000.0);
		    
		    T_Inst=Nb_instr/(C->CPU_->work_frequency*C->CPU_->dmips*1000.0)+instrL1*Pen_L1+instrL2*Pen_L2;
		    T_RWDATA=(store+load)*(T_OneDATA)+(R_L2_Miss*Pen_L2+W_L2_Miss*Pen_L2)+(R_L1_Miss*Pen_L1+W_L1_Miss*Pen_L1);
		    MissPred=(77066983.0/(1500*5.0))*C->CPU_->pipeline*T_OneDATA;
		    T_Total=MissPred+T_RWDATA+T_Inst;
		    inputfile>>mot;
		     oss<<T_Total;
		    cout<<"T_Total: "<<T_Total<<endl;
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
}


void GenerateDspFile(char *output,string input, COMPONENTDSP C)
{
  ofstream outputfile(output);/// ios::app pour rajouter en fin du fichier ce qu'on veut ecrire 
  ///si on ne veut pas ecraser le fichier dans le cas où il existe déjà
  string line,mot;
  size_t pos;
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
		  while(mot!="[" && sortie) inputfile>>mot;
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
		    cout<<"T_Total: "<<T_Total<<endl;
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
}

