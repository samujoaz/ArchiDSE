#include "generatefile.h"
#include <stdio.h>
#include <stdlib.h>
#include "fonctionsUtils.h"



uint TSIZE=1024;
double TableTBC[100];
COMPONENTDSP thisComposantsDSP=NULL;
COMPONENTCPU thisComposantsCPU=NULL;
CPU thisMesCPU;
DSP thisMesDSP;
GROUP_TBC GroupAffinity;
bool once =true;
extern char **_argv;


/// init liste G_TBC
void G_TBC_InitListe(GROUP_TBC *L)
{
  if(!G_TBC_estVide(*L)){
	    G_TBC_InitListe(&((*L)->next));
	    *L = NULL;
	} 
}


/** verification si la liste est ou pas 
* bool : la liste est vide 
* false: la  liste est non-vide
* */
bool G_TBC_estVide(GROUP_TBC L)
{
if(L == NULL)return true;
else return false;                        
} 

/// pour ajputer un nouveau élément à la liste des TBC
void G_TBC_Ajouter(GROUP_TBC *L,int nb_input,int *Liste_affinity,string include_name,string *input_name,string *component_name, string *cnx_name,string *typeAff)
{
   Group_TBC *tmp = *L;
       Group_TBC *nouveau =new Group_TBC;
       if(nouveau == NULL){
                  exit(1);
             }
             
       nouveau->nb_input = nb_input;
       nouveau->include_name=include_name;
       nouveau->input_name =  new string[nb_input];
       nouveau->component_name = new string[nb_input];
       nouveau->cnx_name = new string[nb_input];
       nouveau->affinity = new int[nb_input];
       nouveau->TypeAff = new string[nb_input];
       for(int p=0; p<nb_input;p++)
       {
       nouveau->input_name[p] = input_name[p];
       nouveau->component_name[p]= component_name[p];
       nouveau->cnx_name[p] = cnx_name[p];
       nouveau->affinity[p] = Liste_affinity[p];
       nouveau->TypeAff[p] = typeAff[p];
       }
       
       nouveau->next = NULL;
       if(G_TBC_estVide(*L)){
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

///fonction d'affichage de la liste des tbc
void G_TBC_Afficher(GROUP_TBC L)
{
 // ofstream fileTBC("listeTBC.txt",ios::app);
  //fileTBC<<"liste des valeurs de TBC N°: "<<toto<<endl;
         Group_TBC *tmp;
         if(G_TBC_estVide(L)){
            cout<<"!la liste est vide!" <<endl;           
         }
         else{
	   
           tmp = CloneG_TBC(L);
           while(tmp != NULL){
	      cout<<tmp->include_name << ".txt avec "<< tmp->nb_input<< " input(s) "<<endl;
	     for(int p=0; p<tmp->nb_input;p++)
	      {
               cout<<"(component_name : "<<tmp->component_name[p]<<")\t (cnx_name : "<<tmp->cnx_name[p]<<")\t (input_name : "<<tmp->input_name[p]<<")\t affinity : "<<tmp->affinity[p]<<" TypeAff : "<<tmp->TypeAff[p]<<endl;
		//fileTBC<<"(val :"<<tmp->valeur<<") (aff :"<<tmp->affinity<<") name :"<<tmp->name<<endl;
	      }
                tmp = tmp->next;    
           }  
           cout<<endl;
         }
     
      // fileTBC<<"fin de la liste des valeurs de TBC N°: "<<toto++<<endl<<endl<<endl;

 }
 
 

 GROUP_TBC CloneG_TBC(GROUP_TBC mon_tbc)
{
  Group_TBC *clone = new Group_TBC;
  memcpy(&clone,&mon_tbc,sizeof(GROUP_TBC));
  return clone;
}


/// ancienne fonction utilisée 
// int getValAffinity(char x)
// {
//   //int res; 
//   if(int('A') <= int(x) && int(x) <= int('Z'))
//    return AFF_GROUP;
//   else
//   {
//      if(48 <= int(x) && int(x) <= 55)
//      return AFF_FIXE;
//      else
//      {
// 	  if(int(x)==int('?'))return AFF_VAR;
// 	  else 
// 	  {
// 	    cout <<"\n Dans la fonction : int getValAffinity(char x)\n erreur(405):\n problème dans la lecture  du fichier de composition" <<endl;
// 	    cout <<" une ou plusieurs lignes définissant l'affinité des cpu est ou sont mal formatée(s)\n voir fichier composition.... \n"<<endl;
// 	    //exit(405);
// 	  }
//      }
//   }
//   
// }


/**
 * cette fonction permet de savoir quel est le type d'une affinité
 * 
 * retour : si l'affinité est VARIABLE ===> AFF_VAR
 * 	    si l'affinité est Groupée ===> AFF_GROUP
 * 	     si l'affinité est Fixe ===> AFF_FIXE
 * 
 * */
int getValAffinity(string x)
{
//   cout<<"envoie : "<<x << " taille : "<<x.size();
  if(x.size()==1)
  {
    char caractere[3];
    sprintf(caractere,"%s",x.c_str());
  if(int('A') <= int(caractere[0]) && int(caractere[0]) <= int('Z'))
  {
//     cout<<" return : GROUP  ==>"<<AFF_GROUP<<endl;
   return AFF_GROUP;
  }
  else
  {
     if(48 <= int(caractere[0]) && int(caractere[0]) <= 57)
     {
//        cout<<" return : FIXE  ==>"<<AFF_FIXE<<endl;
       return AFF_FIXE;}
     else
     {
	  if(int(caractere[0])==int('?')){
// 	    cout<<" return : VAR ==>"<<AFF_VAR<<endl;
	  return AFF_VAR;}
	  else 
	  {
	    cout <<"\n Dans la fonction : int getValAffinity(char x)\n erreur(405):\n problème dans la lecture  du fichier de composition" <<endl;
	    cout <<" une ou plusieurs lignes définissant l'affinité des cpu est ou sont mal formatée(s)\n voir fichier composition.... \n"<<endl;
	    //exit(405);
	  }
     }
  }
  }
  else{
    if(x.size()>1)
    {
      if(10 <= atoi(x.c_str())&& atoi(x.c_str()) <= 1000){
//       cout<<" return : FIXE  ==>"<<AFF_FIXE<<endl;
       return AFF_FIXE;
     }
    }
    
    
  }

}

/**
 * cette fontion permet de calculer le temps d'exécution estimé (TBC) pour un thread
 * ensuite on génere le fichier correspondant au thread. 
 * Elle fait appel à eux autre focntion qui calcule le TBC bdu thread
 * 1) si le composant dont  a une seule Entrée/Sortie  (comme les slices et filters)  on fait appelle à GenerateCpuFile
 * 2) si le compansant à plusieurs Entrées/Sorties (cas de generator ou modulator..) on appelle GenerateCpuFileMultiInput
 *
 * pour se faire on récupère en premier le nom du fichier à ouvrir puis son on genere le nom de fichier qu'il doit avoir et on appelle le calcul de TBC
 * */
void CalculTBC(GROUP_TBC Liste, CPU MesCPU){
      Group_TBC *Liste_tmp;
      string S3;
      string output,cnx_name, input,  include_name,component_name;
      CPU cpu_tmp=NULL;
      char carac[10]; 
      
      if(G_TBC_estVide(Liste))
	{
	cout<<"Pas de calcul de TBC car la liste est vide" <<endl;           
	}
      else
	{
	  Liste_tmp = CloneG_TBC(Liste);
	  while(Liste_tmp != NULL)
	  {
	    if(Liste_tmp->nb_input>1)
	    {
	      
	      include_name = Liste_tmp->include_name;
// 	      cout<<"fct " <<include_name <<endl;
	      
	      S3 = Liste_tmp->component_name[0].substr(include_name.size(),include_name.size());
	      if(S3.size()>0)sprintf(carac,"_%s",S3.c_str());
	      else sprintf(carac,"_%d",0); 
	      input = _argv[2]+include_name+".txt";
	      output=include_name+carac+".txt";
	      
	      GenerateCpuFileMultiInput( output, input,MesCPU, Liste_tmp,carac);
// 	      cout<< "fct " <<Liste_tmp->input_name[0]<<endl;

	    }
	    else
	    {
	      if(Liste_tmp->nb_input==1)/// calcul normal comme poour les cas où, l'on avait que les slices, filters...
	      {/// argv[2] == inputfile/ où le dossier des fichier d'origine
		  
		include_name = Liste_tmp->include_name;
		S3 = Liste_tmp->component_name[0].substr(include_name.size(),include_name.size());
		if(S3.size()>0)sprintf(carac,"_%s",S3.c_str());
		else sprintf(carac,"_%d",0); 
		input = _argv[2]+include_name+".txt";
		output=include_name+carac+".txt";
// 		cnx_name = Liste_tmp->cnx_name[0];
		cpu_tmp = AccessToCPU(MesCPU,Liste_tmp->affinity[0]);
		
		GenerateCpuFile(output,input,cpu_tmp, carac);
// 		sleep(1.0);	     
	      }
	      else { 
		//cout<< "timer output "<<endl;
		include_name = Liste_tmp->include_name;
		//S3 = Liste_tmp->component_name[0].substr(include_name.size(),include_name.size());
		sprintf(carac,"_%d",0); 
		input = _argv[2]+include_name+".txt";
		output=include_name+carac+".txt";
// 		cnx_name = Liste_tmp->cnx_name[0];
		cpu_tmp = AccessToCPU(MesCPU,0);
		GenerateCpuFile(output,input,cpu_tmp, carac);
	      }
	    }
	   
	    Liste_tmp = Liste_tmp->next;    
	  }  
	  
	}
  }

/**
 * calcul du TBC ( temps estimé d'exécution d'un threads) 
 * ici c'est le cas des composants qui ont plusieurs entrées/sorties.
 * on utilise les equation estimation et les caractéristiques des processeurs et du profiling pour le calcul 
 * dans la generation du nouveau fichier on prend soin de ne pas écrire  le  "Alfa et Branch_Miss" car la trace n'en aura pas besoin 
 * et ils ne sont pas necéssaire à part dans ce calcul ( pour le moement ) 
 * 
 * 
 * Gestion des erreurs : 
 * le programme s'arrete s'il y a un problème d'ouverture du fichier ou bien s'il y a une ligne qui n'est  pas correcte
 * le numero de la ligne d'erreur et le nom de la fonction seront affichés
 * */

  void GenerateCpuFileMultiInput(string output,string input,CPU MesCPU,GROUP_TBC Liste,char *indice){
  ofstream outputfile(output.c_str(),ios::trunc);/// ios::app pour rajouter en fin du fichier ce qu'on veut ecrire 
  ///si on ne veut pas ecraser le fichier dans le cas où il existe déjà
  string line,mot;
  string input_name;
  string S1="_comp",S2="_behaviour",S3="_timing_characs";
  size_t pos;
  string stringtemp;
  uint i=0, fin=1;
  double T_RWDATA;	//temps passé à lire et écrire des datas
  double T_Inst;  	//temps passé dans les instructions (ms)
  double T_Total; 	//temps total
  double T_OneDATA;  	//ms pour lire ou écrire une data
  double MissPred;	//MissPred
  double Pen_L1;  	//penalité pour un miss L1
  double Pen_L2;  	//penalité pour un miss L2
  ostringstream oss;
  bool sortie=true;
  uint Nb_instr, load, store, instrL1,R_L1_Miss,W_L1_Miss,instrL2,R_L2_Miss,W_L2_Miss;
  uint Alfa, Branch_Miss;

  CPU Cpu=NULL;

  if(outputfile)
  {
    ifstream inputfile(input.c_str());
    if(inputfile)
    {
      string ListeName[TSIZE];
     
     
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
		  fin=0;
		  pos=line.find("input");
		 if(pos!=-1) fin=1;
		  for(int p=0; p < Liste->nb_input && fin ;p++)
		  {
		    input_name = Liste->input_name[p];
		    pos=line.find(input_name);
// 		    cout<<Liste->component_name[0]<<endl;
// 		    cout<< Liste->input_name[0]<<endl;
		    
		    if(pos!=-1 )
		    {
		      
			outputfile<<line<<endl;
			getline(inputfile,line); 
			outputfile<<line<<endl;
			getline(inputfile,line);
			pos=line.find("TBC");
			    while (pos!=-1 &&fin)
			    {/// on  va se repositionner au debut de la ligne
				inputfile.seekg((int)(-line.size()),ios::cur);
				fin=0;

				while(inputfile>>mot && sortie) 
				{
				/// pour les mutli input
				if((mot.compare("TBC"))==0)
				{
				i=0;
				while(mot!="[")
				{
				inputfile>>mot;
				if(++i>100){/// si au bout du 100ème caractère lu on ne trouve pas le  crochet on qui l'exécution
				cout<<--i <<" iterations no '[' found incorrect file or format in : "<<input<<endl; 
				cout<<"voir fonction : GenerateCpuFileMultiInput(,,,)  exit("<<13<<")"<<endl;
				exit(13);

				}

				} 
				while(mot!="]"&&sortie)
				{
// 				  cout<<"indice : "<<Liste->affinity[p]<<endl;
				Cpu=AccessToCPU(MesCPU,Liste->affinity[p]);
				inputfile>>Alfa;
				inputfile>>Nb_instr;	inputfile>>load;  		inputfile>>store;
				inputfile>>instrL1;		inputfile>>R_L1_Miss;		inputfile>>W_L1_Miss;
				inputfile>>instrL2;		inputfile>>R_L2_Miss;		inputfile>>W_L2_Miss;
				inputfile>>Branch_Miss;

				T_OneDATA=1.0/(Cpu->work_frequency*1000.0);
				Pen_L1=10.0/(Cpu->work_frequency*1000.0);
				Pen_L2=100.0/(Cpu->work_frequency*1000.0);
				T_Inst=(Alfa/100.0)*Nb_instr/(Cpu->work_frequency*Cpu->dmips*1000.0)+instrL1*Pen_L1+instrL2*Pen_L2;
// 				T_Inst=Nb_instr/(Cpu->work_frequency*Cpu->dmips*1000.0)+instrL1*Pen_L1+instrL2*Pen_L2;
				T_RWDATA=(store+load)*(T_OneDATA)+(R_L2_Miss*Pen_L2+W_L2_Miss*Pen_L2)+(R_L1_Miss*Pen_L1+W_L1_Miss*Pen_L1);
// 				MissPred=(77066983.0/(1500*5.0))*Cpu->pipeline*T_OneDATA;/// ancienne méthode :D
				MissPred=1.0*Branch_Miss*Cpu->pipeline*T_OneDATA;
				T_Total=MissPred+T_RWDATA+T_Inst;
				//cout<<"TBC = "<<T_Total<<" pour  "<<input<<endl;
			      
				inputfile>>mot;
				if(mot!="]") 
				{
				  cout <<endl<<"EXECUTION : FAIL !!"<<endl;
				  cout<<"Arret dans la fonction : \n void GenerateCpuFileMultiInput(string output,string input,CPU MesCPU,GROUP_TBC Liste,char *indice)" <<endl;
				  cout <<"Que faire ? "<<endl<<"ERROR(13.01) voir le fichier: "<<input<< endl; 
				  cout <<"la ligne suivante n'est pas correcte: \n"<<line<<endl<<endl; 
				  exit(13);
				}
				oss<<T_Total;

				}		    

				if(pos<=line.size()){ line.replace(pos,3, oss.str());}
				oss.str(""); oss.clear();
				sortie=false;
// 				cout<<line<<endl;
				 pos=line.find("[");
				 if(pos !=-1)
				  {
				    
				    oss << "[ " << Nb_instr <<" "<<load<<" "<<store<<" "<<instrL1<<" "<<R_L1_Miss<<" "<<W_L1_Miss<<" "<<instrL2<<" "<<R_L2_Miss<<" "<<W_L2_Miss<<" ]           ";//<<endl;
				    line.replace(pos,oss.str().size(), oss.str());
				  }
// 				  cout<<"fichier "<<input<<endl;
// 				  cout<<line<<endl;
				  oss.str(""); oss.clear();
				}

				}
				inputfile.seekg((int)(-3*mot.size())+2,ios::cur);	    
				sortie=true;
				stringtemp = line;
				getline(inputfile,line);
				pos=line.find("TBC");
				if(pos!=-1 ) 
				{
				  fin=1;
				}
				outputfile<<stringtemp<<endl;
				
				  
		    
			    }
			    
		    }
		    
		  }
		  
	  outputfile<<line<<endl;
      }
    inputfile.close();
    }
    else {
      cout<<"ERREUR exit("<<11<<"): Impossible d'ouvrir le fichier:"<<input<<endl;
      cout<<"voir fonction : GenerateCpuFileMultiInput(,,,) "<<endl;
      exit(11);
      
    }
    
  }
  else {
    cout<<"ERREUR exit("<<12<<"): Impossible d'ouvrir le fichier:"<<output<<endl;
      cout<<"voir fonction : GenerateCpuFileMultiInput(,,,) "<<endl;
    exit(12);
    
  } 
//    cout<<"fichier d'entrée "<<input<<endl;
//         cout<<output<<" \thas been generate2"<<endl;
      
   outputfile.close();


}

/**
 *
 * pour le commentaire voir  ceux de la fonction GenerateCpuFileMultiInput(...) 
 * on utilise la même méthode c'est juste qu'on dispose de composant mono E/S
 * 
 * */
  
void GenerateCpuFile(string output,string input,CPU C,char *indice){
  ofstream outputfile(output.c_str(),ios::trunc);/// ios::app pour rajouter en fin du fichier ce qu'on veut ecrire 
  ///si on ne veut pas ecraser le fichier dans le cas où il existe déjà
  string line,mot;
  size_t pos;
  string S1="_comp",S2="_behaviour",S3="_timing_characs";
  string stringtemp;
  uint i=0;
  double T_RWDATA;	//temps passé à lire et écrire des datas
  double T_Inst;  	//temps passé dans les instructions (ms)
  double T_Total; 	//temps total
  double T_OneDATA;  	//ms pour lire ou écrire une data
  double MissPred;	//MissPred
  double Pen_L1;  	//penalité pour un miss L1
  double Pen_L2;  	//penalité pour un miss L2
  ostringstream oss;
  bool sortie=true;
  uint Nb_instr, load, store, instrL1,R_L1_Miss,W_L1_Miss,instrL2,R_L2_Miss,W_L2_Miss;
  uint Alfa, Branch_Miss;
  

  if(outputfile)
  {
    ifstream inputfile(input.c_str());
    
    if(inputfile)
    {
      string ListeName[TSIZE];
      int o =0;
      ListeName[o++]="blabla";/// juste pour init le tableau
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
	    inputfile.seekg((int)(-line.size()),ios::cur);
	    
	   while(inputfile>>mot && sortie) 
	    {
		if((mot.compare("TBC"))==0)
		{
		  i=0;
		  while(mot!="[")
		  {
		    inputfile>>mot;
		    if(++i>100){/// si au bout du 100ème caractère lu on ne trouve pas le  crochet on qui l'exécution
		      cout<<--i <<" iterations no '[' found incorrect file or format in : "<<input<<endl; 
		      cout<<"voir fonction : GenerateCpuFile(,,,)  exit("<<13<<")"<<endl;
		      exit(13);
		      
		    }
		    
		  } 
		  i=0;
		  while(mot!="]"&&sortie )
		  {
 		    inputfile>>Alfa;
		    inputfile>>Nb_instr;	inputfile>>load;  		inputfile>>store;
		    inputfile>>instrL1;		inputfile>>R_L1_Miss;		inputfile>>W_L1_Miss;
		    inputfile>>instrL2;		inputfile>>R_L2_Miss;		inputfile>>W_L2_Miss;
 		    inputfile>>Branch_Miss;

		    T_OneDATA=1.0/(C->work_frequency*1000.0);
		    Pen_L1=10.0/(C->work_frequency*1000.0);
		    Pen_L2=100.0/(C->work_frequency*1000.0);
		    T_Inst=(Alfa/100.0)* Nb_instr/(C->work_frequency*C->dmips*1000.0)+instrL1*Pen_L1+instrL2*Pen_L2;
// 		    T_Inst=Nb_instr/(C->work_frequency*C->dmips*1000.0)+instrL1*Pen_L1+instrL2*Pen_L2;
		    T_RWDATA=(store+load)*(T_OneDATA)+(R_L2_Miss*Pen_L2+W_L2_Miss*Pen_L2)+(R_L1_Miss*Pen_L1+W_L1_Miss*Pen_L1);
// 		    MissPred=(77066983.0/(1500*5.0))*C->pipeline*T_OneDATA;
		    MissPred=1.0*Branch_Miss*C->pipeline*T_OneDATA;
		    T_Total=MissPred+T_RWDATA+T_Inst;
		    //cout<<"TBC = "<<T_Total<<" pour  "<<input<<endl;
		    //TableTBC[nbTBC++]=T_Total;
		    //cout <<" T_Total " <<T_Total<<endl;
		    //e();
		    inputfile>>mot;
		    if(mot!="]") 
				{
				  cout <<endl<<"EXECUTION : FAIL !!"<<endl;
				  cout<<"Arret dans la fonction : \n void GenerateCpuFile(string output,string input,CPU C,char *indice)" <<endl;
				  cout <<"Que faire ? "<<endl<<"ERROR(13.01) voir le fichier: "<<input<< endl; 
				  cout <<"la ligne suivante n'est pas correcte: \n"<<line<<endl<<endl; 
				  exit(13);
				}
		    		    
		    oss<<T_Total;
// 		    ListeName[o++]=name;
		    //if(once && notFindName(ListeName,name,o-1)  )
		    //  { 
			//nbTBC++;
		     // TBC_Ajouter(&thisTBC,name,C->indice_CPU,T_Total);
		    //cout <<name<<endl;
		  //  sleep(1.0);
		    //  }
		  }		    

		  if(pos<=line.size()){ line.replace(pos,3, oss.str());}
		  
		  oss.str(""); oss.clear();
		  sortie=false;
		   pos=line.find("[");
// 		   cout<<line<<endl;
		   if(pos !=-1)
		   {
		    
		     oss << "[ " << Nb_instr <<" "<<load<<" "<<store<<" "<<instrL1<<" "<<R_L1_Miss<<" "<<W_L1_Miss<<" "<<instrL2<<" "<<R_L2_Miss<<" "<<W_L2_Miss<<" ]             ";//   "<<endl;
		     line.replace(pos,oss.str().size(), oss.str());
		   }
// 		  cout<<"fichier "<<input<<endl;
// 		  cout<<line<<endl;
		  oss.str(""); oss.clear();
// 		  e();
		}
	    }
	    inputfile.seekg((int)(-3*mot.size())+2,ios::cur);	    
	    sortie=true;
	  }	  
	  outputfile<<line<<endl;
      }
    inputfile.close();
    }
    else {
      cout<<"ERREUR exit("<<11<<"): Impossible d'ouvrir le fichier:"<<input<<endl;
      cout<<"voir fonction : GenerateCpuFile(,,,) "<<endl;
      exit(11);
      
    }
    
  }
  else {
    cout<<"ERREUR exit("<<12<<"): Impossible d'ouvrir le fichier:"<<output<<endl;
      cout<<"voir fonction : GenerateCpuFile(,,,) "<<endl;
    exit(12);
    
  } 
//   cout<<"fichier d'entrée "<<input<<endl;
//        cout<<output<<" \thas been generate"<<endl;
//       sleep(1.0);
   outputfile.close();
}



/**
 * Fonction principale de l'explorateur : qui génére le nouveau fichier de composition pour l'exécution de la trace
 * dans un premier temps on  ne lit que les include : pour avoir le nom de composant à ouvrir, on crée donc une liste de composants dans un tableau
 * ensuite on regarde les composants qu'on instancie pour recuperer leur nom.  et grace aux noms et au mot clé "configure_affinity" on recupere les 
 * affinités,  leur type et caractéristiques on créer alors la liste des affinités et grace G_TBC_Ajouter() nous creer cette liste
 * 
 * ensuite vient l'etape de la generation du nouveau fichier avec les modification des behaviour et characteristics
 * un #include sera ecrit pour chaque fichier instancier
 * pour les composants  qui sont instanciés une seule fois nous rajoutons l'estension " _0 " behaviour_0 et characteristics_0
 * pour ceux instancier plusieurs fois nous recuperons et leur donnons leur indice de declaration 
 * les affinités de type AFF_GROUP(A-Z) ou AFF_VAR (?) sont remplacer par la valeur par defaut de ZERo ( c'est à cause de cela qu'on ne prend par en compte la première
 * boucle de l'explration. les affinités fixes restent telles quelles.  
 * 
 * 
 * un fichier composition.txt sera créer dans le même repertoire que l'exécutable.
 * 
 * s'il y a des erreurs il y aura arret du programme et un retour de la ligne d'erreur
 * 
 * */
void GenerateCompCpuFile(string input,string output,string includeListe[], string componentListe[],  uint* N_affinity,uint* NB_COMPONENT)
{
  ofstream outputfile(output.c_str());
  string ListeFileToGenerate[TSIZE], component_type[TSIZE],component_inst[TSIZE];
  string line,mot,Stmp,S2,S3, behaviour("_behaviour"), carac("_timing_characs"),tmp;
  uint i=0,j=0, fin=0, nb_include=0, nb_component=0,nb_affinity=0,affinity[TSIZE],count=0;
  size_t pos;
  bool  go=true;
  char c[TSIZE];
   

    if(!outputfile){
      cout<<"ERREUR exit("<<9<<") impossible de crée le fichier de sortie"<<output<<endl;
      cout<<"voir fonction : GenerateCompCpuFile(,,,)"<<endl;
      exit(9);
      
    }
    ifstream in1(input.c_str());
    if(in1)
      
    {
      for(int r=0 ; r<TSIZE; r++) affinity[r]=0;
      i=0;
      /// lecture des includes pour savoir les fichiers à ouvrir
      	while(getline(in1,line)) 
	{	    
	  pos=line.find("include");
	    if (pos!=-1)
	    {/// on  va se repositionner au debut de la ligne.
	    in1.seekg((int)(-line.size()-1),ios::cur);
	    in1>>Stmp;
	    in1>>Stmp;
	    pos=line.find("include");
	    if (pos!=-1)
	    ListeFileToGenerate[i] = Stmp.substr(0,Stmp.size()-1);

	    Stmp.clear();
	    i++;
	    }
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
		  /// on va récupérer les caractère: sliceX, X étant le numéro.
		  in2.seekg((int)(-line.size()-1),ios::cur);
		  in2>>Stmp;//cout<<Stmp<<endl;
		  in2>>Stmp;//cout<< Stmp<<endl;
		  in2>>component_inst[i];//cout<<"component : "<<component_inst[i]<<endl;
		  componentListe[i]=component_inst[i];
		  in2>>Stmp;//cout<<Stmp<<endl;
		  Stmp.clear();
		  i++;
		  } 
	      }
	      
	      in2.close();
	  }
	   string ListeName[TSIZE], inputName[TSIZE]; string typeAffinity[TSIZE];
	   uint incr=0;

	  nb_component=i;i=0; /// penser à changer nb_aff en nb_fichier a créér
	  *NB_COMPONENT=nb_component;
	  j=0;
	 
	  ifstream in3(input.c_str());uint o=0;

	    go=true;
	    S2="cnx_";
	    ListeName[o++]="init";
	    while(getline(in3,line) && go ) /// Deuxième lecture
	      {
		pos=line.find("connection");
		if (int(pos)!=-1)
		{

		      mot=".input";
		      pos=line.find(mot);
		       if(int(pos)!=-1)
		       {
			  in3.seekg((int)(-line.size()-1),ios::cur);
			  in3>>Stmp;
			  in3>>Stmp;
			  in3>>Stmp;
			  in3>>Stmp;
			  in3>>Stmp;
			  in3>>Stmp;
			  ListeName[o++]=Stmp;
			  if( notFindName(ListeName,Stmp,o-1))
			  {
			    inputName[incr++]=Stmp.substr(0,(int)(Stmp.size()-1));
			  }
		       }
		      
		    }
		  
		    mot=".configure_affinity(";
		    pos=line.find(mot);
		      if (int(pos)!=-1)
		      {/// on va récupérer l'affinity qui est en 3ème position de la chaine de mot	
		      in3.seekg((int)(-line.size()-1),ios::cur);
		      in3>>Stmp;
		      in3>>Stmp;
		      string carac_temp; 
		      
		      S3=Stmp.substr(int(S2.size()),int(Stmp.size()-S2.size()-mot.size()));
		      in3>>carac_temp;
		      Stmp=carac_temp;
		      if(getValAffinity(carac_temp)==AFF_FIXE) affinity[j]=atoi(Stmp.c_str());
			else affinity[j]=0;
		      
		      ListeName[o++]=S3;
		      if( notFindName(ListeName,S3,o-1))
		      {
			typeAffinity[j]=carac_temp;
			component_type[j]=S3; //cout<<component_type[j]<<endl;
			j++;
		      }
		      in3>>Stmp;
		      		      
		      }
		      

		  pos=line.find("start.run");
		  if(pos !=-1) 
		  {
		    in3.seekg(int(0),ios::beg);
		    go =false;
		  }
	      }
	  in3.close();
	  nb_affinity=j;
	  if(once)/// cette partie est faite une seule fois, tout au début de l'algo.
	  {
	 /// construction de la liste des affinités, utilisation de component_type, affinity, inputName
	    for(i=0;i<nb_component;i++)
	    {
	      int nb_input=0,Liste_affinity[TSIZE];
	      string include_name,input_name[TSIZE],cnx_name[TSIZE],component_name[TSIZE]; string typeAffinity_[TSIZE];
	      fin=1;
	      for(j=0; j<nb_include && fin;j++)
		{
		  S2=ListeFileToGenerate[j].substr(0,ListeFileToGenerate[j].size()-4);
		  S3=component_inst[i].substr(0,S2.size()); 
		  if(S3.compare(S2)==0){fin=0; include_name=S2;}
		}
	      
	      for(int p = 0; p<incr  ;p++)
	      {
	      
		S3=inputName[p].substr(0,component_inst[i].size());/// on enlève le .inputXXX
		if(S3.compare(component_inst[i])==0  )
		{
		S2=inputName[p].substr((int)(component_inst[i].size()+1),(int)(inputName[p].size())); 
		pos=S2.find(".");/// pour eviter les cas déjà fait ou pas correct 
		if(pos==-1)
		{
		  input_name[nb_input]=S2;
		  cnx_name[nb_input]=component_type[p];
		  Liste_affinity[nb_input]=affinity[p];
		  typeAffinity_[nb_input]=typeAffinity[p];
		  component_name[nb_input]=S3;
		  nb_input++;
		}		
		}
			
	      }
	      G_TBC_Ajouter(&GroupAffinity,nb_input,Liste_affinity,include_name,input_name,component_name,cnx_name,typeAffinity_);
	      }
	  }
	  Stmp.clear();
	   /// maintenant rajoutons les extensions.. pour les includes : 
	  i=0;
	  ifstream in4(input.c_str());
	  fin=1;
	  while(getline(in4,line)&&fin) ///  lecture des qu'on arrive au premier include
	  {
		
	      if(line.find("component")!=-1){fin=0;}
	      for(j=0;j<nb_include && fin;j++)
	      {
		 uint o=0;
		      S2=ListeFileToGenerate[j].substr(0,ListeFileToGenerate[j].size()-4);
		      pos=line.find(S2);
		      if(pos!=-1) 
		      {
			  for(i=0;i<nb_component && fin ;i++)
			  {
			    S3=component_inst[i].substr(0,S2.size());
			    if(S3.compare(S2)==0 )
			    {
				S3 = component_inst[i].substr(S2.size(),S2.size());
				if(S3.size()>0)sprintf(c,"_%s.txt",S3.c_str());
				else sprintf(c,"_%d.txt",0);

				includeListe[i]=S2+c;
				count++;

				Stmp =Stmp+"include "+S2+c+";\n";
			      
			    }
			  }
			 
			  
			    
			  if((int)(Stmp.size())>1)
			  {
			    Stmp= Stmp.substr(0,(int)(Stmp.size()-1));
			    outputfile<<Stmp<<endl;  /// on ecrit dans le fichier composition de sortie
			  }
			  else {/*coucou()*/; cout<<line<<endl;}
			  Stmp.clear();	
		      }
	      } 
	  }
/// on va ecrire la suite du fichier de composition de sortie 
	  in4.close();
	  i=0;
	  fin=1;
	  j=0;
	  int l_prec=0;
	  ifstream in5(input.c_str());
	  while(getline(in5,line) ){
	    
	    pos=line.find("component_instance");
	    if (pos!=-1)
	    {
	     pos=line.find("Timer_impl");if (pos!=-1 ){  outputfile<<line<<endl;fin=0;}
	      for(int  l=0;l<nb_include &&fin;l++)
	      {
		  tmp=ListeFileToGenerate[l].substr(0,ListeFileToGenerate[l].size()-4);
		  for(i=0;i<nb_component;i++)
		  {
		      S2=component_inst[i]+ " " +tmp+carac;
		      pos=line.find(S2);
		      if (pos!=-1)
		      {
			S3 = component_inst[i].substr(tmp.size(),tmp.size());
			if(S3.size()>0)sprintf(c,"_%s",S3.c_str());
			else sprintf(c,"_%d",0);
			Stmp= S2+c;
			S3= line;
			S3.replace(pos,S2.size(),Stmp);
			S2=tmp+behaviour;
			pos=line.find(S2);
			if (pos!=-1)
			{
			  Stmp= S2+c;
			  S3.replace(pos,S2.size(),Stmp);
			  outputfile<<S3<<endl;
			}
		      }
		  }// for(i=0;i<nb_component;i++)
	      }// end for(int  l=0;l<nb_include;l++) ///
	      
	      fin=1;
 	    }// end if  pos=line.find("component_instance");  if (pos!=-1)
	    else
	    {	      
	      S2="configure_affinity(";
	      pos=line.find(S2);
	      if (pos!=-1)
	      {	
		  in5.seekg((int)(-line.size()-1),ios::cur);
		  in5>>Stmp;
		  in5>>Stmp;
		  string carac;
		  in5>>carac;
		  if(getValAffinity(carac)!=AFF_FIXE){
		    line.replace((int)(pos+S2.size()+1),1,"0");
		  }
		  outputfile<<line<<endl;
		  in5>>Stmp;
		  in5.seekg((int)(1),ios::cur);	/// repositionnement fin de ligne;	    
	      }
	      else
	      {
		pos=line.find("include");
		if (pos==-1){  outputfile<<line<<endl; }
	      }
	    } 
	  }
	  in5.close();

//        cout<<nb_include<<" include(s) dans le fichier : "<<input<<endl;
//        cout<<nb_affinity<<" fichier(s) à créer."<<endl;
    }
    else {
      cout<<"ERREUR exit("<<10<<"): Impossible d'ouvrir le fichier:"<<input<<endl;
      cout<<"voir fonction : GenerateCompCpuFile(,,,)"<<endl;
      exit(10);}
    
//       cout<<output<<" \thas been generate"<<endl;
  *N_affinity =nb_affinity;
}



void GenerateDspFile(const char *output,string input, COMPONENTDSP C)
{
  ofstream outputfile(output);/// ios::app pour rajouter en fin du fichier ce qu'on veut ecrire 
  ///si on ne veut pas ecraser le fichier dans le cas où il existe déjà
  string line,mot;
  size_t pos;
  uint i=0;
  double T_RWDATA;	//temps passé à lire et écrire des datas
  double T_Inst;  	//temps passé dans les instructions (ms)
  double T_Total; 	//temps total
  double T_OneDATA;  	//ms pour lire ou écrire une data
  double MissPred;	//MissPred
  double Pen_L1;  	//penalité pour un miss L1
  double Pen_L2;  	//penalité pour un miss L2
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
	    inputfile.seekg((int)(-line.size()),ios::cur);
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
	    inputfile.seekg((int)(-3*mot.size())+2,ios::cur);	    
	    sortie=true;
	  }	  
	  outputfile<<line<<endl;
      }
    
    }
    else {cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<input<<endl;exit(0);}
  }
  else {cout<<"ERREUR: Impossible d'ouvrir le fichier:"<<output<<endl;exit(0);} 
  //cout<<output<<" \thas been generate"<<endl;
 }



/**
 * Cette fonction est celle qui lit la fichier de la description matérielle  souvent "compositionarchi.txt"
 * si l'ouverture du fichie n'echoue pas alors on regarde si l'on trouve le mot clé "component"
 * si celui est retrouvé on cherche alors les mots clé "cache, PU, DSP" une fois trouver,  on recupère leurs caractéristique 
 * et on les ajoute dans  la liste chainées par type de composants: 
 * pour les caches on les a directement :  taille, bpl, association
 * pour les processeurs on appelle la fonction ADD_CPU(..) en lui passant le nom du fichier à ouvrir et la fréquence de fonctionnement du processeur
 * (Idem pour le DSP) 
 * 
 * ensuite quand on voit le mot clé "connection " 
 * si le prochain mot clé est "CPU" alors on cherchera une cache L1 ou L2
 * si le prochain mot clé est "CACHE" alors on cherchera une cache L2 seulement
 * ADD_COMPONENTCPU() permet de creer un objet contenant un cpu et les 2 caches
 * 
 * ensuite pour les erreurs de format on aura l'arret du programme ,  le numero de la ligne à l'origine de l'erreur
 *  le fichier dans lequel s'est produit l'erreur et une affichage exemple correcte pour la correction au cas où 
 * **/
void ReadCompositionFile(string compositionfile)
{
  
  uint nb_ligne=0,nb_file=0;
  string line, filename,tmp,tmp2; 

  char dir[100];
  char outputcomposition[100];
  CPU MonCpu=NULL,cpu_tmp=NULL;
  DSP MonDsp=NULL,dsp_tmp=NULL;
  CACHE MesCacheL1=NULL,MesCacheL2=NULL,cacheL1_tmp=NULL,cacheL2_tmp=NULL;
  COMPONENTCPU MesComposantsCPU=NULL,CompoCPU_temp=NULL;
  COMPONENTDSP MesComposantsDSP=NULL,CompoDSP_temp=NULL;  
  
  ifstream listing_file(compositionfile.c_str());   
 
  if(listing_file)
  {
    
    uint freq=0, taille=0,assoc=0,bpl=0;
    uint indice_cpu=0,indice_cacheL1=0,indice_cacheL2=0,indice_dsp=0,indice;
    
    while(listing_file>>line){ /// on lit mot par mot le fichier et on instantie les composants
      
      nb_ligne++;
      if(line == "component") 
      {
	listing_file>>line;
	if(line=="PU")
	{
	    listing_file>>line;
	    tmp= line.substr(3,line.size());
//   	    cout<<"cpu"<<tmp<<endl;
	    indice_cpu = atoi(tmp.c_str());
	    listing_file>>filename;
	    listing_file>>freq;
	    MonCpu=ADD_CPU(MonCpu,filename,freq,indice_cpu);
	}
	else{
	    if(line=="CACHE")
	    {
	      listing_file>>line;
	      tmp = line.substr(0,2);/// les 2 premières caractères 
// 	      cout<<tmp<<endl;
	      tmp2= line.substr(3,line.size());/// tout le reste de la chaine à partir du 3ième caractère
// 	      cout<<tmp2<<endl;
	      indice= atoi(tmp2.c_str());
	      listing_file>>taille;
	      listing_file>>bpl;
	      listing_file>>assoc;
	      if(tmp =="L1") MesCacheL1=ADD_CACHE(MesCacheL1,taille,bpl,assoc,indice);
	      else {if(tmp =="L2") MesCacheL2=ADD_CACHE(MesCacheL2,taille,bpl,assoc,indice);}
	     
	    }
	    else{
	      if(line =="DSP")
	      {
		listing_file>>line;
		tmp= line.substr(line.size()-1,line.size());
		indice_dsp = atoi(tmp.c_str());
		listing_file>>filename;
		listing_file>>freq;
		MonDsp=ADD_DSP(MonDsp,filename,freq,indice_dsp);
	      }
	    }
	}
	
      }/// end if component 
      
      else{
	
	  if(line =="connection")
	  { 
	      listing_file>>line;
	      tmp = line.substr(0,3);
	     
	      if(tmp =="CPU")
	      {
		
		indice_cpu=atoi(line.substr(tmp.size(),line.size()).c_str());
// 		 cout<<" V2 : cpu"<<indice_cpu<<endl;
		listing_file>>line; /// lecture du "->"
		listing_file>>line; /// lecture du deuxième composant à connecter
		tmp=line.substr(0,3);
		if(tmp=="L1_")
		{
		  indice_cacheL1=atoi(line.substr(tmp.size(),line.size()).c_str());
		  cacheL1_tmp = FindCACHE(MesCacheL1,indice_cacheL1);
		  cpu_tmp = FindCPU(MonCpu,indice_cpu);
		  MesComposantsCPU = ADD_COMPONENTCPU(MesComposantsCPU,cpu_tmp,cacheL1_tmp,cacheL1_tmp->indice_cache,cpu_tmp->indice_CPU,"cpu");
		  //thisComposantsCPU = ADD_COMPONENTCPU(thisComposantsCPU,AccessToCPU(MonCpu,indice_cpu),AccessToCACHE(MesCacheL1,indice_cacheL1),indice_cacheL1,indice_cpu,"cpu");
		}
	      }
	      else {
		if(tmp =="DSP")
		{
		    indice_dsp=atoi(line.substr(tmp.size(),line.size()).c_str());
		    listing_file>>line;
		    listing_file>>line;
		    tmp=line.substr(0,3);
		      if(tmp=="L1_")
		      {				
			indice_cacheL1=atoi(line.substr(tmp.size(),line.size()).c_str());
			dsp_tmp = FindDSP(MonDsp,indice_dsp);
			cacheL1_tmp = FindCACHE(MesCacheL1,indice_cacheL1);
			MesComposantsDSP = ADD_COMPONENTDSP(MesComposantsDSP,dsp_tmp,cacheL1_tmp,cacheL1_tmp->indice_cache,dsp_tmp->indice_DSP,"dsp");
		      }
		}
	      else{
		if(tmp=="L1_")
		{ 
		  indice_cacheL1=atoi(line.substr(tmp.size(),line.size()).c_str());
// 		  cout<<"indice_cacheL1 : "<<indice_cacheL1<<endl;
		  listing_file>>line;
		  listing_file>>line;
		  tmp=line.substr(0,3);
		  if(tmp=="L2_")
		  {
		      indice_cacheL2=atoi(line.substr(tmp.size(),line.size()).c_str());
// 		      		     cout<<"indice_cacheL2 : "<<indice_cacheL2<<endl;  

		      cacheL1_tmp=FindCACHE(MesCacheL1,indice_cacheL1);
		      cacheL2_tmp=FindCACHE(MesCacheL2,indice_cacheL2);
// 		     Affiche_CACHE(cacheL2_tmp);e();
		      if(GetNamelinkCache(cacheL1_tmp) =="dsp"){
		      CompoDSP_temp=AccessToCOMPONENTDSP(MesComposantsDSP,GetLinkCacheL1DSP(MesComposantsDSP,cacheL1_tmp->indice_cache));
		      ADD_CACHE_L2_TO_COMPONENTDSP(CompoDSP_temp,cacheL2_tmp);
		      
		      }
		      else{
			if(GetNamelinkCache(cacheL1_tmp) =="cpu"){
			CompoCPU_temp=AccessToCOMPONENTCPU(MesComposantsCPU,GetLinkCacheL1CPU(MesComposantsCPU,cacheL1_tmp->indice_cache));
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
	    listing_file.seekg((int)(-listing_file.tellg()),ios::cur);
	    while(nb_ligne>0){getline(listing_file,line);nb_ligne--;}
	    cout<<line <<" :Cette ligne n'est pas correcte \n \n"<<endl;
	    
	      if(line.substr(0,9)=="component")
	      {
		if(line.substr(10,2)=="PU"){
		  cout<<" Required format CPU :";
		  cout<<" component PU CPUX "<<_argv[2]<<"file_name.txt freq "<<endl;
		  cout<<" X : cpu number"<<endl;
		  cout<<" file_name.txt : architecture decription texte file"<<endl;
		  cout<<" freq: cpu working frequency"<<endl;
		  cout<<" Example: component PU CPU0 "<<_argv[2]<<"cortexA8.txt 200\n"<<endl;
		  cout<<"ERREUR exit("<<1<<") de format dans le fichier: "<<compositionfile<<"\nvoir fonction : ReadCompositionFile(,,,) "<<endl;
		  exit(1);
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
		    
		    cout<<"ERREUR exit("<<2<<") de format dans le fichier: "<<compositionfile<<"\nvoir fonction : ReadCompositionFile(,,,) "<<endl;
		    exit(2);
		  }
		else
		{
		  if(line.substr(10,3)=="DSP"){
		  cout<<" Required format DSP :";
		  cout<<" component DSP DSPX "<<_argv[2]<<"file_name.txt freq "<<endl;
		  cout<<" X : dsp number"<<endl;
		  cout<<" file_name.txt : architecture decription texte file"<<endl;
		  cout<<" freq: dsp working frequency"<<endl;
		  cout<<" Example: component DSP DSP1 "<<_argv[2]<<"dsp3.txt 200\n"<<endl;
		  
		  
		  cout<<"ERREUR exit("<<3<<") de format dans le fichier: "<<compositionfile<<"\nvoir fonction : ReadCompositionFile(,,,) "<<endl;
		  exit(3);
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
		
		
		cout<<"ERREUR exit("<<4<<") de format dans le fichier: "<<compositionfile<<"\nvoir fonction : ReadCompositionFile(,,,) "<<endl;
		exit(4);
		}
	      }
	   }
	
      }
	
      }///end while(listing_file>>line)
    }///end if(listing_file)
  else{
    cout<<"ERREUR exit("<<0<<") : Impossible d'ouvrir le fichier: "<<compositionfile<<endl;
    cout<<"voir fonction : ReadCompositionFile(,,,) "<<endl;
    exit(0);
  }
  
  listing_file.close();
  thisComposantsCPU= MesComposantsCPU;
  thisComposantsDSP= MesComposantsDSP;
  thisMesCPU=MonCpu;
  thisMesDSP=MonDsp;

}


/**
 * pour trouver tout le composants qui sont du même groupe d'affinité var définit par les lettre Maj. (A-Z)
 * */
void FindSimilarGroup(GROUP_TBC Liste, string Type, string Group_cnxname[], int *taille)
{
  Group_TBC *Liste_tmp;
  Liste_tmp = CloneG_TBC(Liste);
  int i=0;
  *taille=0;
  while(Liste_tmp->next!=NULL)
  {
    for(int p=0; p< Liste_tmp->nb_input;p++)
    {
      if(Liste_tmp->TypeAff[p]==Type)
      {
	Group_cnxname[i++]= Liste_tmp->cnx_name[p];
      }
    }
    Liste_tmp=Liste_tmp->next;
  }
  *taille =i;
}

bool findnotint(int *list, int index, int taille)
{
  
for(int i=0;i<taille;i++) 
  if(list[i]==index)return false;
    
  return true;
}

/**
 * pour trouver le tout les composants qui ont une affinité fixe. 
 * */
void FindGroupCpuFix(GROUP_TBC Liste, int Group_Aff[], int *taille)
{
  Group_TBC *Liste_tmp;
  Liste_tmp = CloneG_TBC(Liste);
  int i=0;
  *taille=0;
  while(Liste_tmp!=NULL)
  {
    for(int p=0; p< Liste_tmp->nb_input;p++)
    {
//       cout<<Liste_tmp->TypeAff[p] << endl;
	if(getValAffinity(Liste_tmp->TypeAff[p])==AFF_FIXE   && findnotint(Group_Aff,Liste_tmp->affinity[p],i))
      {
	Group_Aff[i++]= Liste_tmp->affinity[p];
//  	cout << "group " <<Group_Aff[i-1] <<endl;
      }
    }
    Liste_tmp=Liste_tmp->next;
  }
  *taille =i;
}

/**
 * /// cette fonction remplace l'affinité du debut de l'exploration par la nouvelle en paramètre (NewAffinity) 
 * pour un composant dont le nom est passé en paramètre "component"
 * un nouveau fichier de composition.txt et composition_temp.txt sont à la suite genérés
 * 
 * si le fichier est mal fomarté on arret le programme et son indique dans quelle fonction s'est arrêté le programme
 * 
 * **/

void ChangeAffinity(string compositionfile, string compositionfile_temp,string component,uint NewAffinity) 
{
  string line,tmp;
  size_t pos=-1;
  ostringstream convert;   // stream used for the conversion
  
  
  ofstream outputfile(compositionfile_temp.c_str(),ios::trunc);   
  if(!outputfile)
  {
    cout<<"ERREUR exit("<<7<<")impossible de crée le fichier de sortie: "<<compositionfile_temp<<endl;
    cout<<"voir fonction : ChangeAffinity(,,,) "<<endl;
    exit(7);
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
    cout<<"ERREUR exit("<<8<<")fichier inexistant ou ouverture impossible: "<<compositionfile<<endl;
    cout<<"voir fonction : ChangeAffinity(,,,) "<<endl;
    exit(8);
  }
  
    /// on ferme les  fichiers puis on fait une recopie
  outputfile.close(); 
  readingfile.close();
  
  ofstream write(compositionfile.c_str(),ios::trunc);   
  ifstream read(compositionfile_temp.c_str());
  while(getline(read,line))
  {
    write<<line<<endl;
  }
  write.close();
  read.close();
}


/**
 * pour avoir l'affinité dans un fichier de composition d'une composant via son nom
 * retourne 61 s'il y a un problème dans le fichier de composition. sinon retourne la  valeur de l'affinité.
 * */
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
	    read.seekg((int)(-line.size()-1),ios::cur);
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
    return -1;
  }
  
}

/**
 * /// cette fonction change toutes les affinités d'une certaine valeur (Oldaffinity) par la nouvelle en paramètre (NewAffinity) 
 * un nouveau fichier de composition.txt est à la suite genéré
 * 
 * **/

void FindAndReplaceAffinity(string compositionfile, string compositionfile_temp,uint OldAffinity,uint NewAffinity)
{
  
   string line,tmp;
  size_t pos=-1;
  ostringstream convert;
  ofstream outputfile(compositionfile_temp.c_str(),ios::trunc);   
  if(!outputfile)
  {
    cout<<"ERREUR exit("<<5<<")impossible de crée le fichier: "<<compositionfile_temp<<endl;
    cout<<"voir fonction : FindAndReplaceAffinity(,,,) "<<endl;
    exit(5);
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
// 	    cout<<"trouvé\n old : ";
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
    cout<<"ERREUR exit("<<6<<")fichier inexistant ou ouverture impossible: "<<compositionfile<<endl;
    cout<<"voir fonction : FindAndReplaceAffinity(,,,) "<<endl;
    exit(6);
    
  }
  
    /// on ferme les  fichiers puis on fait une recopie
  outputfile.close(); 
  readingfile.close();
  
  ofstream write(compositionfile.c_str(),ios::trunc);   
  ifstream read(compositionfile_temp.c_str());
  while(getline(read,line))
  {
    write<<line<<endl;
  }
  read.close(); 
  write.close();
  tmp.clear();
  
}

/**
 * /// cette fonction change une seule affinité d'une certaine valeur (Oldaffinity) par la nouvelle en paramètre (NewAffinity) 
 * un nouveau fichier de composition.txt est à la suite genéré
 * 
 * **/

void FindAndReplaceOneAffinity(string compositionfile, string compositionfile_temp,uint OldAffinity,uint NewAffinity)
{/// cette fonction change une seule affinité
  
  string line,tmp;
  size_t pos=-1;
  ostringstream convert;
  ofstream outputfile(compositionfile_temp.c_str(),ios::trunc);   
  bool found =true;
  if(!outputfile)
  {
    cout<<"ERREUR exit("<<5<<")impossible de crée le fichier: "<<compositionfile_temp<<endl;
    cout<<"voir fonction : FindAndReplaceOneAffinity(,,,) "<<endl;
    exit(5);
  }

  ifstream readingfile(compositionfile.c_str());   
  if(readingfile)
  {
    while(getline(readingfile,line)) 
      {
// 	cout<< " .............. avant   "<< line<<endl;
	convert.str(""); convert.clear();
	 convert<<OldAffinity; 
	 tmp="configure_affinity( "+convert.str();
	  pos=line.find(tmp);
	  if (pos!=-1  &&found)
	  {
	    convert.str(""); convert.clear();
	    convert<<NewAffinity; 
	    line.replace(pos+tmp.size()-1,convert.str().size(),convert.str());
	    outputfile<<line<<endl;
	    found= false;
	  }
	  else 
	  {
	    outputfile<<line<<endl;
	  }
// 	cout<<line<<endl;
      }
    
  }
  else 
  {
    cout<<"ERREUR exit("<<6<<")fichier inexistant ou ouverture impossible: "<<compositionfile<<endl;
    cout<<"voir fonction : FindAndReplaceOneAffinity(,,,) "<<endl;
    exit(6);
    
  }
  
    /// on ferme les  fichiers puis on fait une recopie
  outputfile.close(); 
  readingfile.close();
  
  ofstream write(compositionfile.c_str(),ios::trunc);   
  ifstream read(compositionfile_temp.c_str());
  while(getline(read,line))
  {
    write<<line<<endl;
  }
  read.close(); 
  write.close();
  tmp.clear();
  
}

