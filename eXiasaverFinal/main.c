#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "fonction.h"

int main(int argc, char *argv[], char *envp[])
{
// lanceur du eXiasaver

    srand(time(NULL));
    int modechoisi;
    modechoisi = choixMode();
    int imagestatique=0;
    imagestatique = choisirImage();
    system("clear");
    sauvegardeInfos(modechoisi);
    char command[100];

    if (argc==2 && strcmp(argv[1],"-stat")==0) // lance le menu si est seulement si on lance l'application avec ./main -stat
    {
        menustat();
    }

    else
    {
        //execution des modes
        switch (modechoisi)
        {
        case 1:  // mode statique
            printf("%s",command);
            char buffer[100];
            sprintf(buffer, "(cd LanceurStatique ; ./statique %d)", imagestatique);
            system(buffer);
            break;

        case 2: // mode dynamique
            printf("%s",command);
            char buffer2[100];
            sprintf(buffer2, "(cd LanceurDynamique ; ./dynamique)");
            system(buffer2);
            break;

        case 3: // mode interactif
        printf("Le mode interactif n'étant pas programmer, il n'est pas possible de le lancer.\n");
            break;

        default:
            printf("Erreur\n");
            break;
        }
    }

    system("wait");
    return 0;
}
