#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>

#include "statique.h"

int main(int argc, char *argv[]) {
    // INIT
    int ligne = 1;
    int image = 0;
    int nombreCaracteres;
    char caractereLu;
    int imageSize = 0;
    int tailleImage = 0;
    int largeurImage = 0;
    int hauteurImage = 0;

    char separateur[1] = " ";
    char * pch;


    char taille[10];//Création d'un tableau de caractère

    int i= 0;
    int j =0;// i -> compteur de tour, j -> retour a la ligne
    FILE* fichier = NULL;//Initialisation du pointeur fichier a NULL

    int nbLine = 0;
    char cheminFichier[128] = "";

	if (argc==2)
{
	strcat(cheminFichier,"images/");
	strcat(cheminFichier,argv[1]);
	strcat(cheminFichier,".pbm");
	fichier = fopen(cheminFichier, "r+");
}
	else
{
	image = choisirImage();
	snprintf(cheminFichier, sizeof cheminFichier, "images/%d.pbm", image);//Snprintf permet de stocker une variable int dans une chaine de caractere
	fichier = fopen(cheminFichier, "r+");//Ouverture de l'image
}

    // CODE
    system("clear");


    if (fichier != NULL) { //Si l'image est bien ouverte


    int c;
    while((c=fgetc(fichier)) != EOF){ //On compte le nombre de caractère que contient le fichier pour savoir sa taille en octet
        imageSize++;
    }


    rewind(fichier);

    int bytes[imageSize]; //tableau avec la taille du fichier
    memset(bytes,'\0',imageSize); // mettre toutes les cases du tableau à NULLE




    while(ligne < 3 && caractereLu != EOF){ //On passe les 2 premières lignes (ne nous interressent pas) ligne<3
            caractereLu = fgetc(fichier);
            if(caractereLu=='\n') {
                ligne++;
            }
    }

    fgets(taille, 10, fichier);




    pch = strtok (taille," ");
    while (pch != NULL)
    {

     sscanf(pch, "%d", &largeurImage);
     pch = strtok (NULL, " ");

    sscanf(pch, "%d", &hauteurImage);
     break;
    }

    rewind(fichier);//Remonter au début du fichier
    ligne = 1;

        while(ligne < 4 && caractereLu != EOF){ //On passe les 3 premières lignes (ne nous interressent pas) ligne<4
            caractereLu = fgetc(fichier);

            if (caractereLu == '\n'){
                ligne++;
            }
        }

        for (i = 0; i < imageSize; i++) { // Boucle qui va parcourir tous les bytes de l'image et les stocker dans le tableau bytes
            bytes[i] = fgetc(fichier);

            if(bytes[i] == '\n') { //On annule un retour à la ligne du fichier s'il y en a un
                i=i-1;

            }
        }


        centrerImageVertical(largeurImage, hauteurImage);
        centrerImageHorizontal(largeurImage, hauteurImage);

        for (i = 0; i < imageSize+1; i++){ //Boucle qui va afficher tous les 0 et 1 dans la console


            if (j == largeurImage) { //Au bout de 80, il y a un retour à la ligne dans la console (pour garder le format 80x24)
                printf("\n"); //retour a la ligne
                j = 0;
                nbLine++;
                centrerImageHorizontal(largeurImage, hauteurImage);
            }



                    if (bytes[i] == '0'){ //Si le bit est un 0, on affiche un espace
                        printf(" ");
                    }
                    if (bytes[i] == '1'){ //Si le bit est un 1 on affiche un carré rempli
                        printf("\xe2\x96\x96");
                    }



            j++;
        }
        fclose(fichier); //On ferme le fichier
        printf("\n");

    system("/bin/stty raw");
        getchar();
        system("/bin/stty cooked");
    }

    system("clear");
    return 0;
}
