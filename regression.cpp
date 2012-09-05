//2012-08-18  thiack  <thiack@thiackPC>



#include "regression.h"
/**enleve le commentaire si on veut utilise le main dans ce fichier
 // ne pas oublie de commenter le  #include "regression.h" ci dessus si on veut tester le main
#include <list>
#include <vector>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
**/
using namespace std;

list < double > list_of_conso;
int	matrix_lu_double (double* M,size_t* idx,double* d,size_t n)
{
	size_t i,imax,j,k;
	double big,dum,sum,temp;
	double* v = (double*)malloc(n*sizeof(double));
	*d = 1.0;
	for (i=0;i<n;i++)
	{
		big = 0.0;
		for (j=0;j<n;j++)
			if ((temp=fabs(M[i+j*n])) > big)
				big = temp;
		if (fabs(big) < 1E-10) {
			free (v);
			return 0;
		}
		v[i] = 1.0/big;
	}
	for (j=0;j<n;j++)
	{
		for (i=0;i<j;i++)
		{
			sum = M[i+j*n];
			for (k=0;k<i;k++)
				sum -= M[i+k*n]*M[k+j*n];
			M[i+j*n] = sum;
		}
		big = 0.0;
		imax = 0;
		for (i=j;i<n;i++)
		{
			sum = M[i+j*n];
			for (k=0;k<j;k++)
				sum -= M[i+k*n]*M[k+j*n];
			M[i+j*n] = sum;
			if ((dum=v[i]*fabs(sum)) >= big)
			{
				big = dum;
				imax = i;
			}
		}
		if (j != imax)
		{
			for (k=0;k<n;k++)
			{
				dum = M[imax+k*n];
				M[imax+k*n] = M[j+k*n];
				M[j+k*n] = dum;
			}
			*d = -(*d);
			v[imax] = v[j];
		}
		idx[j] = imax;
		if (M[j+j*n] == 0.0) M[j+j*n] = 1E-10;
		if (j != n)
		{
			dum = 1.0/M[j+j*n];
			for (i=j+1;i<n;i++)
				M[i+j*n] *= dum;
		}
	}
	free (v);
	return 1;
}
void matrix_lub_double (double* b,double* M,size_t *idx,size_t n)
{
	int i,ii=-1,ip,j;
	double sum;
	for (i=0;i<n;i++)
	{
		ip = idx[i];
		sum = b[ip];
		b[ip] = b[i];
		if (ii >= 0)
		{
			for (j=ii;j<i;j++)
				sum -= M[i+j*n]*b[j];
		}
		else if (fabs(sum) > 1E-10)
			ii = i;
		b[i] = sum;
	}
	for (i=n-1;i>=0;i--)
	{
		sum = b[i];
		for (j=i+1;j<n;j++)
			sum -= M[i+j*n]*b[j];
		b[i] = sum/M[i+i*n];
	}
}

///Y: matrix(n,n) inverse.
///    M: matrix(n,n) Ã  inverser 

int matrix_inv_double (double* Y,double* M,size_t n)
{
	double d;
	size_t i,j;
	size_t* idx = (size_t*)malloc(n*sizeof(size_t));
	if (!matrix_lu_double (M,idx,&d,n)) {
		free (idx);
		return 0;
	}
	double* c = (double*)malloc(n*sizeof(double));
	for (j=0;j<n;j++)
	{
		for (i=0;i<n;i++)
			c[i] = 0.0;
		c[j] = 1.0;
		matrix_lub_double (c,M,idx,n);
		for (i=0;i<n;i++)
			Y[i+j*n] = c[i];
	}
	free (idx);
	free (c);
	return 1;
}

/**
 * On utlise une matrice 3x3
 * Voici la forme de la matrice : 
 * 		On fait une somme (SUM) sur N: i allant de 0 à N-1
 * 		|SUM[Xi^4]  SUM[Xi^3]  SUM[Xi^2] |
 * 		|				 |
 * 	A=	|SUM[Xi^3]  SUM[Xi^2]  SUM[Xi^1] |
 * 		|				 |
 * 		|SUM[Xi^2]  SUM[Xi^1]  N         |
 * 
 * 		| SUM[Xi^2*Yi] 	 |
 * 	B= 	|	|
 * 		| SUM[Xi*Yi]	 |		
 * 		|	|
 * 		| SUM[Yi]	 |
 * 
 * */
void compute_coeff(double *Tab_Freq, double *Tab_Conso, int nb_points, double coeff[3])
{
	double *Ainv, *MatrixA,*VectorB;
	Ainv = new double[9];
	MatrixA = new double[9];
	VectorB =new double[3];
	
	/// calcul de la matrice A 
	for(int i=0; i<9;i++){ MatrixA[i] = 0.0; Ainv[i]=0.0; }
	for(int i=0; i<3;i++)VectorB[i] = 0.0;

	for(int j=0;j<nb_points;j++)
	{
		MatrixA[0] += pow(Tab_Freq[j],4.0);
		MatrixA[1] += pow(Tab_Freq[j],3.0);
		MatrixA[2] += pow(Tab_Freq[j],2.0);
		MatrixA[3] += pow(Tab_Freq[j],3.0);
		MatrixA[4] += pow(Tab_Freq[j],2.0);
		MatrixA[5] += Tab_Freq[j];
		MatrixA[6] += pow(Tab_Freq[j],2.0);
		MatrixA[7] += Tab_Freq[j];
		
		VectorB[0] += pow(Tab_Freq[j],2.0)*Tab_Conso[j];
		VectorB[1] += Tab_Freq[j]*Tab_Conso[j];
		VectorB[2] += Tab_Conso[j];
	}	
		
	MatrixA[8]=nb_points;
// 		for(int i=0; i<9; i++) cout<<"MatrixA "<<MatrixA[i]<<endl; 

	matrix_inv_double(Ainv,MatrixA,3);
// 	for(int i=0; i<9; i++) cout<<"Ainv "<<Ainv[i]<<endl; 
// 	cout<<endl;
// 	for(int i =0; i<3; i++)
	for(int i =0; i<3; i++)
	{
	  coeff[i]=0.0;
		
	  for(int j=0;j<3;j++)
	  {
	      coeff[i]+=Ainv[i*3+j]*VectorB[j];
		  
	  }
	}
}

void ReadFileConso(string inputname, int *nb_points, int *nb_col)
{
  uint nb_colonne=0,nb_element_par_colonne=0;
  double valeur=0.0;
  double temp_freq[100],temp_conso[100]; 
  string line;
  ifstream listing_file(inputname.c_str());   
  bool end_read = true, first_line=true;
 
  if(listing_file)
  {
    while(end_read){ /// on lit mot par mot le fichier et on instantie les composants

	  if(first_line)/// pour lire la première ligne une seule fois o/
	  {
	    /** dans cette partie on lit la première ligne, 
	    * Si on a besoin de rajouter une nouvelle ligne  de conso 
	    * il faut proceder comme suit: 
	    * 
	    * 		listing_file >> s;
	    *  		if (s != "Nom_de_la_colonne_de_conso") { cerr << "Error 1 : Nom_de_la_colonne_de_conso missing" << endl; exit(1); }
	    * 		nb_colonne++; 
	    * 
	    *        nb_colonne c'est pour savoir à la fin le nombre de colonnes qu'on aura, ce qui nous donnera le  nombre d'equations
	    * 
	    * */
  ///    FREQ 	L2 	L1 	CPU 	LEACKAGE [plus autre colonne si besoin]
	      string s;
	      listing_file >> s;
	      if (s != "FREQ") { cerr << "Error 1 : FREQ missing" << endl; exit(1); }
	      nb_colonne++;

	      listing_file >> s;
	      if (s != "L2") { cerr << "Error 2 : L2 missing" << endl; exit(1); }
	      nb_colonne++;
	      
	      listing_file >> s;
	      if (s != "L1") { cerr << "Error 3 : L1 missing" << endl; exit(1); }
	      nb_colonne++;
	      
	      listing_file >> s;
	      if (s != "CPU") { cerr << "Error 4 : CPU missing" << endl; exit(1); }
	      nb_colonne++;

	      listing_file >> s;
	      if (s != "LEACKAGE") { cerr << "Error 5 : LEACKAGE missing" << endl; exit(1); }
	      nb_colonne++;
	      /** 
	      *  Espace pour les colonnes supplementaires 
	      */
	      first_line=false;
	  }
	  
	  for (int i=0 ; i<nb_colonne && end_read; i++)
	  {
	    if((listing_file>>valeur )!=NULL){ list_of_conso.push_back(valeur);}
	    else end_read=false;
	  
	  }
	  nb_element_par_colonne++;
	 	   
	}
 }
 else 
 {
   cout<<" Dans la fonction void ReadFileConso(...) "<<endl;
   cout<<"impossible d'ouvrir le fichier: " <<inputname<<endl; exit(0);
 }
 *nb_points=nb_element_par_colonne-1;
 *nb_col=nb_colonne;
}
    

vector < vector <  double> > compute_regression(string consofilename)
{
	int nb_points,nb_colonne;
	ReadFileConso(consofilename, &nb_points, &nb_colonne);
	double coeff[3];
	double Freq[nb_points];
	double Conso[nb_colonne-1][nb_points];
	vector < vector <  double> > vector_coeff;
	int j=0;
	
// 	cout<< " le tableau des conso est : \n";
	 while (!list_of_conso.empty())
	 {
	    
	    Freq[j] = list_of_conso.front();
	    list_of_conso.pop_front();
 	    //cout<<Freq[j]<< ": ";
	    for(int i=0; i<nb_colonne-1;i++)
	    {
	      Conso[i][j] = list_of_conso.front();
	      list_of_conso.pop_front();
 	      //cout<< Conso[i][j]<< " ";
	    }
	    //cout<<endl;
	    j++;

	}
	
	for(int i=0; i<nb_colonne-1;i++)
	{
	  double conso_temp[nb_points];
	  vector < double > tmp_vect ;
	  for(int k=0; k<nb_points;k++)
	  conso_temp[k] = Conso[i][k];
	  compute_coeff(Freq,conso_temp,nb_points,coeff);
	for (int i=0; i<3;i++) cout<<"coeff " <<coeff[i]<<endl; cout<<endl;
	
	tmp_vect.push_back(coeff[0]);
	tmp_vect.push_back(coeff[1]);
	tmp_vect.push_back(coeff[2]);
	
	vector_coeff.push_back(tmp_vect);
	}
	return vector_coeff;
}
/*
int main()
{
  vector < vector <  double> > vector_coeff;
  vector_coeff = compute_regression("consoleak.txt");
//       for (list < string >::iterator iter = selected_cpus.begin(); iter != selected_cpus.end(); iter++) {
int i=0;
  for(vector < vector < double > >::iterator iter1 = vector_coeff.begin(); iter1 != vector_coeff.end(); iter1++)
  {
    cout <<"\n l'équation n°: "<<i<< " est : ";
    int j=0; 
  for(vector < double  >::iterator iter2 = vector_coeff[i].begin(); iter2 != vector_coeff[i].end(); iter2++)
  {
    
    if(j==0) 
     cout<<"("<<*iter2<<")"<<"*X² + ";
    if(j==1)
      cout<<"("<<*iter2<<")"<<"*X + ";
    if(j==2)
      cout<<"("<<*iter2<<")"<<endl;
    j++;
//     cout<<vector_coeff[0][0]<<endl;
//     cout<<vector_coeff[1][0]<<endl;
//     cout<<vector_coeff[2][0];
  }
  i++;
  }
  return 0;
}
 */

void affiche_regression(vector < vector <  double> > myvector)
{
int i=0;
ofstream visuel_regression("visuel_regr.gnu");
ostringstream convert; 
string buffer;
bool first_time=true;
visuel_regression <<"set title \"COURBE DES CONSOMMATIONS\" \nset xlabel \"FREQUENCE EN  MHz\" \nset ylabel \"CONSO\" "<<endl;
  for(vector < vector < double > >::iterator iter1 = myvector.begin(); iter1 != myvector.end(); iter1++)
  {
    cout <<"\n l'équation n°: "<<i<< " est : ";
    int j=0; 
    buffer.clear();
    
  for(vector < double  >::iterator iter2 = myvector[i].begin(); iter2 != myvector[i].end(); iter2++)
  {
    
    if(j==0) 
    {
     cout<<"("<<*iter2<<")"<<"*X² + ";
      convert.str(""); convert.clear();
     convert<<*iter2;
     if(first_time)
     buffer  = "plot [0 :800 ] [0 : 0.25]" + convert.str()+ "*x**2 ";
     else buffer  = "replot " + convert.str()+ "*x**2 ";
     first_time=false;
    }
    if(j==1)
    {
      cout<<"("<<*iter2<<")"<<"*X + ";
       convert.str(""); convert.clear();
      convert<<*iter2;
     buffer  += " + (" + convert.str() + ")*x "; 
    }
    if(j==2)
    {
      cout<<"("<<*iter2<<")"<<endl;
       convert.str(""); convert.clear();
      convert<<*iter2;
      buffer += "+ (" + convert.str()+ ")";
      switch (i)
      {
	  case 0: 
	  buffer += " title \"Conso L2(nJ)\""; break;
	  case 1: 
	  buffer += " title \"Conso L1(nJ)\""; break;
	  case 2: 
	  buffer += " title \"Conso CPU(nJ)\""; break;
	  case 3: 
	  buffer += " title \"Conso Leackage(Watts)\""; break;
	 
      }
    }
    j++;

  }
  visuel_regression<<buffer<<endl;
  i++;
  }
  visuel_regression<<"pause -1"<<endl;
  
}