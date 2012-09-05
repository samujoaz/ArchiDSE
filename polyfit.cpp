/*
**  $Id: polyfit.c,v 1.3 1999/11/19 00:04:34 frank Exp $
**  polyfit.c	1.0	BSD 4.3	910115	SIO/ODF	fmd
**
**  Orthogonal polynomial curve fitting.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
    
    
    var n,x=new Array(),y=new Array(),a=new Array(11);
    var s=new Array(), w=new Array();
    for (int i=1;i<=11;i++) {a[i]=new Array(12)}    // ----------  déf. d'une matrice a(i,j)
    function mcar()
    {
      int i=0;
	n="";
	n=eval(prompt("Nombre de points à ajuster (<=20) :",n))
	for(i=1;i<=n;i++)
	{
	x[i]="";y[i]="";
	x[i]=eval(prompt("x du point "+i+" = ",x[i]))
	y[i]=eval(prompt("y du point "+i+" = ",y[i]))
	}
	p="";
	p=eval(prompt("Degré du lissage (<=10) :",p))
	for(k=0;k<=2*p;k++)
	{
	s[k]=0;
	for(i=1;i<=n;i++)
	{
	s[k]=s[k]+Math.pow(x[i],k)
	}
	}
	for(k=0;k<=p;k++)
	{
	w[k]=0;
	for(i=1;i<=n;i++)
	{
	w[k]=w[k]+y[i]*Math.pow(x[i],k)
	}
	}
	for(k=0;k<=p;k++)
	{
	a[k+1][p+2]=w[k];
	}
	for(i=1;i<=p+1;i++)
	{
	for(j=1;j<=p+1;j++)
	{
	a[i][j]=s[i+j-2]
	}
	}
	a[1][1]=n;
	n=p+1;                                   // --------  dim du système
	for(k=1;k<=n-1;k++)              // -------------résol par méthode du pivot de Gauss
	{
	v=a[k][k];
	if (v==0) {v=permu(k); if (v==0) {sing();return}}
	for(i=k+1;i<=n;i++)
	{
	for(j=k+1;j<=n+1;j++)
	{
	a[i][j]=a[i][j]-a[i][k]*a[k][j]/v
	}
	}
	}
	if (a[n][n]==0) {sing();return}
	x[n]=a[n][n+1]/a[n][n];
	for (i=n-1;i>=1;i--)
	{sx=0;
	for (j=i+1;j<=n;j++)
	{
	sx=sx+a[i][j]*x[j]
	}
	x[i]=(a[i][n+1]-sx)/a[i][i]
	}

	for(k=1;k<=n;k++){y[k]=x[n-k+1]}
	for(k=1;k<=n;k++){x[k]=y[k]}
	for(i=1;i<=n;i++)
	{
	nmi=n-i;
	alert("a("+nmi+") = "+x[i])
	}

    } // fin pgm principal

    function permu(k)
    {
	q=0;li=k;
      while (a[li][k]==0)
      {
      q++;li=q+k;
      if (li==n+1) {return 0}
      }
      for(int i=1;i<=n+1;i++){aux=a[k][i];a[k][i]=a[li][i];a[li][i]=aux}
      return a[k][k]
    
    }
    
    function sing()
    {
      cout<<"Pas de chance, ce système est singulier..."<<endl;
    }
int  main(void)
{
return 0;
}
// #endif /* FORTRAN */
