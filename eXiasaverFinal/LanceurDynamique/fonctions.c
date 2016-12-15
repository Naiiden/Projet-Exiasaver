#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <time.h>
#include "dynamique.h"

extern int delay;

extern char bytes[10][28];
extern char deuxPoints[28];


/**
Fonction de delay de l'ecran (attente)
@param int i : nombre de secondes de delay
**/
void my_delay(int i)
{
        clock_t start,end;
        start=clock();
        while(((end=clock())-start)<=i*CLOCKS_PER_SEC);
}



/**
Centre l'image verticalement en fonction de la taille de la console et de l'image
@param int hauteur : hauteur de l'image
**/
void centrerImageVertical(int hauteur) {
	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w); //fonction systeme qui récupère la taille de la console
	int n;
	for (n=0; n<(w.ws_row-hauteur)/2; n++){ //ws_row : nombre de lignes de la console
			printf("\n");
		}

}


/**
Fonction qui centre une ligne au milieu de la console
@param int largeur : largeur en caractère du texte/image
**/
void centrerImageHorizontal(int largeur) {

	struct winsize w;
	ioctl(0, TIOCGWINSZ, &w); //Fonction système pour récupérer la valeur de la console
	int n;
	for (n=0; n<(w.ws_col-largeur)/2; n++){ //ws_col : nombre de colonnes de la console
			putchar(' ');
		}


}


/**
Fonction qui affiche récupère l'heure système et l'affiche dans la console
**/
int afficherHeure() {


	//Initisation des variables pour la fonction
	int chiffre=0;
	char heureTotal[8];
	char caractere;
	int i, j, k, depart;
	depart=0;

	time_t now = time(NULL);

    //On la convertit en heure local
    struct tm tm_now = *localtime(&now);

    //On creer 3 chaine HH MM et SS
    char s_heure[sizeof "HH"];
    char s_minute[sizeof "MM"];
    char s_seconde[sizeof "SS"];


	//Met au format d'heure
    strftime(s_heure, sizeof s_heure, "%H", &tm_now);
    strftime(s_minute, sizeof s_minute, "%M", &tm_now);
    strftime(s_seconde, sizeof s_seconde, "%S", &tm_now);




	//concaténation des 3 chaines de caractères de l'heure dans "heureTotal"
	strcat(heureTotal,s_heure);
	strcat(heureTotal,":");
	strcat(heureTotal,s_minute);
	strcat(heureTotal,":");
	strcat(heureTotal,s_seconde);

	//Centrer le début de l'heure au milieu de la console (les images font 7 de hauteur)
	centrerImageVertical(7);

	//Boucle pour les lignes (7 lignes pour afficher l'heure)
	for(i=0;i<7;i++) {

		//On centre la ligne (39 caractères)
		centrerImageHorizontal(39);

		//Boucle pour chaque ligne de l'heure (8 caractères)
		/*
		Pour afficher l'heure entière on affiche 4bits par 4bits de chaque image
		*/
		for(j=0;j<8;j++) {

			//Si c'est deux-points
			if (heureTotal[chiffre]==':') {

				//On affiche les deux-points
				for(k=0;k<4;k++) {

					caractere = deuxPoints[k+depart];

					if (caractere=='0') {
						printf(" ");
					}

					if (caractere=='1') {
						printf("\xe2\x96\x86");
					}
				}
			}
			else {

				//Boucle pour afficher les lignes de l'image "deux points" (4 caractères/image)
				for(k=0;k<4;k++) {
					caractere = bytes[heureTotal[chiffre] - '0'][k+depart];

					if (caractere=='0') {
						printf(" ");
					}
					if (caractere=='1') {
						printf("\xe2\x96\x86");
					}
				}


			}

			chiffre++;
			printf(" ");

		}

		printf("\n");
		chiffre=0;

		//On incremente le depart de 4 à chaque fin de ligne
		depart = depart+4;
	}
}


/**
Fonction de compteur, elle compte au bout de combien de temps l'heure s'actualise et attend
**/
int compteur()

{   while(1)
	{
        int valeur = 0;

        system("clear");
        afficherHeure();
		setvbuf(stdout, NULL, _IONBF, 0);
		printf("\n");
		centrerImageHorizontal(49); //centrage du texte suivant (49 caractères)
        printf("Actualisation de l'heure dans %d seconde(s) : ", delay);

		//Boucle tant que le nombre de seconde est inférieur au temps rentré en paramètre
		while(valeur < delay)
			{
				printf(".");
				my_delay(1); //on attend 1sec
				valeur ++;
			}
	}
}




