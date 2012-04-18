Exemple d'architecture réalisable avec le code qu'on a implémenter. 


	 ________	 _______	 ______		 ______
	| CPU0   |	| DSP1  |	| CPU1 |	| CPU2 |
	|________|	|_______|	|______|	|______|
	    |		    |		    |		    |
	 ___|______	____|_____	____|_____     _____|____
	| Cache L1 |   | Cache L1 |    | Cache L1 |   | Cache L1 |
	|__________|   |__________|    |__________|   |__________
	    |                |		    |		     |						
	     \		    /		    \		    /
	      \		   /		     \		   /
	       \	  /    		      \		  /
	        \	 /		       \	 /
	       __|_______|_____		     __|_________|___
	      |	Cache L2       |	    |	Cache L2     |
	      |________________|	    |________________|
	             |				     |
	             |				     |
	      _______|_______________________________|_______
	     |                                               |	     
	     |                       RAM                     |
	     |_______________________________________________| \o/
	     
	     	     
	     


le mot clé: component, permet de définit des composants type PU, DSP ou CACHE. 
Pour définir un processeur exmeple un cortex il faut définir le numéro  du PU ie.  (CPU1) 
ensuite le nom du fichier de texte decrivant l'architecture du PU puis la fréquence de fonctionnement
Voici un exmple de définition d'un composant: 
--TYPE Processor
component PU  CPU1 cortexA8.txt 800 
   (1)    (2)  (3)   (4)        (5)    

(1): on veut définir un composant 
(2): type du composant : PU  dans notre cas le cortexA8/9
(3): on numéro notre composant CPX, X: est le numéro index du composant PU
(4): le nom du fichier texte dans lequel on a la déscription du CPU 
(5): la fréquence de fonctionnement de notre cpu

/***********

exemple de fichier (3) pour le cortex: 

    start_frequency: 100
    end_frequency: 800 
    dmips: 1.98 
    pipeline: 13 

*************/

--TYPE Cache
component CACHE L1_0 16 64 4
   (1)    (2)   (3)   (4)       

(1): on veut définir un composant 
(2): type du composant : mémoire cache
(3): définition du cache LX_Y avec  X: qui peut valoir 1 ou 2, indiquant s'il s'agit d'une cache L1 ou L2
                                    Y: le numéro index de la cache
                                    
(4):A B C, sont les paramètres de la mémoire cache: dans l'ordre
		A: la taille de la cache
		B: l'associativitié de la cache
		C: lenombre de bit par ligne de la cache


ensuite après avoir définit les composants il faut les connetés entre eux,
La connection se fait par le mot clé: connection
			    ATTENTION
ATTENTION **** connecter d'abord tout les caches L1. **** ATTENTION
			    ATTENTION

ensuite la connnection aux caches L2 peut se faire dans n'importe quel ordre

on utilise "->" pour établir la connection entre les composants 
(utile car même syntaxe en dot, visualisation facile)
*
*
*
Exemple:  
connection CPU1 -> L1_0 : on a connecté le Cpu d'index_1 à  une cache de type L1 indexé 0
pareil on peut connecter deux caches entre elles ou deux caches L1 à une cache L2. voici l'exemple ci-dessous.
connection L1_2 -> L2_1
connection L1_3 -> L2_1


:q