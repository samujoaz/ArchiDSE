//2012-08-18  thiack  <thiack@thiackPC>

 
#ifndef DEF_REGRESSION
#define DEF_REGRESSION

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
#include <iostream>
#include <fstream>
#include <sstream>


/**
 * Pour pouvoir calculer les Coefficients d'un polynome du second degre
 * P(x) = ax²+bx+c
 * ce programme permet de calculer a,b et c, en lui donnant quelques points de la courbe
 * 
 * on procède par regression linéaire d'ordre 2 (parabole des moindres carres)  cette meme methode peut etre vu comme les 
 * polynomes de Lagrange: (interpolation polynomiale)
 * 
 * 
 * */

using namespace std;
/// Decomposition LU 
int matrix_lu_double (double* M,size_t* idx,double* d,size_t n);
/// backSubstitution
void matrix_lub_double (double* b,double* M,size_t *idx,size_t n);

/// Inversion Matricielle
///Y: matrix(n,n) inverse.
///    M: matrix(n,n) Ã  inverser 

int matrix_inv_double (double* Y,double* M,size_t n);

/// calcul les coeffient a,b,c des l'equation;
void compute_coeff(double *Tab_Freq, double *Tab_Conso, int nb_points, double coeff[3]);

/// lecture du fichier de conso, comportant les points de la courbe
void  ReadFileConso(string inputname, int *nb_points, int *nb_col);

vector < vector <  double> > compute_regression(string consofilename);
void affiche_regression(vector < vector <  double> > myvector);
#endif