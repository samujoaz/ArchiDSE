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
 * ATTENTION le moèdele développé prend en compte le second degré;
 * il serait mieux d'apporter des modifications pour avoir une puissance dynamique en tout pour avoir une meilleure estimation 
 * ou pour mieux extrapoler la courbe il faudrait avoir une puissance largement supérieur à 2
 * des parties du codes sont déjà faites en prévsion  du modèle dynamique, c'est le cas des fonctions de: 
 * 
 * --->int matrix_inv_double (double* Y,double* M,size_t n)
 * ---> int	matrix_lu_double (double* M,size_t* idx,double* d,size_t n)
 * --->void matrix_lub_double (double* b,double* M,size_t *idx,size_t n)
 * void ReadFileConso(string inputname, int *nb_points, int *nb_col)
 * 
 * elles n'auront pas besoin de modification sauf dans le cas où l'on souhait rajouter une colonne de paramètre dans le fichier des consommation
 * il faudra dans ce cas mmodifier parmi toutes les fonctions ci-dessus seulement void ReadFileConso(string inputname, int *nb_points, int *nb_col)
 * les autres resteronst telles quelles
 * 
 * cependant rien n'empêche d'améliorer  tout le code. 
 * */

using namespace std;
/// Decomposition LU 
int matrix_lu_double (double* M,size_t* idx,double* d,size_t n);
/// backSubstitution
void matrix_lub_double (double* b,double* M,size_t *idx,size_t n);

/** Inversion Matricielle
* Y: matrix(n,n) inverse.
* M: matrix(n,n) Ã  inverser 
* Pour inverser une matrice de taille n
 **/
int matrix_inv_double (double* Y,double* M,size_t n);

/// calcul les coeffient a,b,c des l'equation;
void compute_coeff(double *Tab_Freq, double *Tab_Conso, int nb_points, double coeff[3]);

/// lecture du fichier de conso, comportant les points de la courbe
void  ReadFileConso(string inputname, int *nb_points, int *nb_col);


/** pour la calcul des coefficients de l'equation qu'on chercher à extrapoler. 
 * cette fonction prend en parametre seulement un string, représentant le nom du fichier de texte contenant les valeurs des consommations.
 * cette fonction retourne un vecteur de vecteur contenant les coefficients constants de l'équation
 **/
vector < vector <  double> > compute_regression(string consofilename);

/** pour afficher les resultats de la regression. Affichages sous formes d'équation
 **/ 
void affiche_regression(vector < vector <  double> > myvector);
#endif