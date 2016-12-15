#include "statique.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <time.h>



/** Permet de centrer l'image verticalement
 * @brief centrerImageVertical
 * @param largeur
 * @param hauteur
 **/

void centrerImageVertical(int largeur, int hauteur)//Declaration de la fonction centrerImageVertical
{
   struct winsize w;//Strcuture déclaré dans les librairies
    ioctl(0, TIOCGWINSZ, &w);//Appelle système contrôle entré/sortie
    int n;
    for (n=0; n<(w.ws_row-hauteur)/2; n++)

    {
        printf("\n");
    }

}

/** Permet de centrer l'image horizontalement
 * @brief centrerImage
 * @param largeur
 * @param hauteur
 **/

void centrerImageHorizontal(int largeur, int hauteur)//Déclaration de la fonction centrerImage
{
    struct winsize w;//Strcuture déclaré dans les librairies
    ioctl(0, TIOCGWINSZ, &w);//Appelle système contrôle entré/sortie
    int n;
    for (n=0; n<(w.ws_col-largeur)/2; n++)

    {
        putchar(' ');
    }
}


int choisirImage()
{
	int nombre = 0;
	srand(time(NULL));
	nombre = (rand()%(6-1)+1);
	return nombre;
}
