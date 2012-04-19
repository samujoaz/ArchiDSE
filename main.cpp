

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include "fonctionsUtils.h"
#include "generatefile.h"

using namespace std;


int main (int argc,char* argv[])
{

string filename;

        if (argc == 4 && strcmp(argv[1],"DSE")==0)
	{ 
	  ReadCompositionFile(argv[2], argv[3]);
        }
        else {
                cout<<"\noption d'execution : DSE <input>"<< "\ninput: is a txt file "<<endl;         
        }
        
        return 0;
}
  
