#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>

#include "dynamique.h"



int delay = 10;

//Déclaration des tableaux de bytes
/*
bytes [CHIFFRE][BITS]
deuxPoints [BITS]
*/
char bytes[9][28];
char deuxPoints[28];



int main(int argc, char *argv[]) {
	
	
	//On 
	memset(bytes,'\0',1);
	memset(deuxPoints,'\0',1);
	
	//Initialisation des variables utilisées
	int ligne = 1;
	int image = 0;
	int i;
	int j;
	
	int nombreCaracteres;
	char caractereLu;
	char cheminFichier[128] = "";
	char taille[5];
	
	FILE* deuxPts = NULL;
	FILE* fichier = NULL;
	
	system("clear");
	
	//Traitement de l'argument (argv et argc)
	if (argc==2) //Si un argument a été entré
    {
		delay=atoi(argv[1]); //Conversion de char en int (fonction atoi)
		
    } 
	
	else 
	{
		delay=10;
	}
					
		
		
	ligne=1;
		
		
	for (i=0; i<10; i++) {
		
		snprintf(cheminFichier, sizeof cheminFichier, "heure/%d.pbm", i); //Mettre un int (i) dans une chaine de caractère (cheminFichier) 
		fichier = fopen(cheminFichier, "r+");
			
			
		if (fichier != NULL) {
					
					
			while(ligne < 4 && caractereLu != EOF) //On passe les 3 premières lignes (ne nous interressent pas) ligne<4
			{		
				caractereLu = fgetc(fichier);
				
				if (caractereLu == '\n'){
					ligne++; //Si un retour a la ligne est lu on augmente de 1 la valeur de lignes
				}
			}
				
					
				for (j=0; j<28; j++) { //On lit chaque image correspondante au chiffre 
						
						//on recupère le bit lu dans le tableau
						bytes[i][j] = fgetc(fichier);
						
						if(bytes[i][j] == '\n') { //On annule un retour à la ligne du fichier s'il y en a un
							j=j-1;
						}
						if(bytes[i][j] == ' ') { //On annule un espace s'il y en a un
							j=j-1;
						}
					}
					
					
				}
				
			ligne = 1;
			//On revient à la première ligne et on ferme le fichier
			rewind(fichier);
			fclose(fichier);
			
		}
		
		//On ouvre "deuxPoints.pbm"
		deuxPts = fopen("heure/2pts.pbm", "r+");
			if (deuxPts != NULL) {
					
					
				while(ligne < 4 && caractereLu != EOF){	//On passe les 3 premières lignes (ne nous interressent pas) ligne<4
					
					caractereLu = fgetc(deuxPts);
					if (caractereLu == '\n'){
						ligne++;
					}
				}
				
						
				for (i=0; i<28; i++) {
						deuxPoints[i] = fgetc(deuxPts);
						if(deuxPoints[i] == '\n') { //On annule un retour à la ligne du fichier s'il y en a un
							i=i-1;
						}
						if(deuxPoints[i] == ' ') { //On annule un espace s'il y en a un
							i=i-1;
						}
					}
				}
			
			rewind(deuxPts);
			fclose(deuxPts);
		
		ligne = 1;
		
		//On commence le compteur
		compteur();
		
	
	system("clear");
	return 0;
}
