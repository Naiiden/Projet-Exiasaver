#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>

/**
**/
int choixMode()
{
    int mode;
    mode = rand()%(4-1) +1; //Genere un nombre aleatoire entre 1,2 et 3.
    return mode; // Renvoie le nombre aleatoire obtenu.
}

/**
**/
int choisirImage()
{
    int nombre = 0;
    srand(time(NULL));
    nombre = (rand()%(6-1) +1);// Genere un nombre aleatoire entre 1,2,3,4 et 5.
    return nombre;
}

/**
@param int mode : mode choisis
**/
void sauvegardeInfos (int mode)
{
    const char* NomMois[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"};
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime); // permet de capturer l'horloge de l'OS.
    timeinfo = localtime (&rawtime); // permet d'ecrire sans avoir le nombre de seconde depuis le 01/01/1900

    FILE *ft=NULL; //permet de controler les flux d 'information de fopen et fclose
    ft = fopen("stat.txt","a");

    fprintf(ft,"%02u/%s/%04u", timeinfo->tm_mday, NomMois[timeinfo->tm_mon], 1900 + timeinfo->tm_year);
    fprintf(ft," %02u:%02u:%02u;", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    fprintf(ft,"%d;",mode);
    fprintf(ft,"\n");
    fclose(ft);
}

/**
**/
void afficherInfo()
{
    system("cat stat.txt");
}

/**
**/
void afficherfinInfo()
{
    system("tail stat.txt");
}

/**
**/
void trierinfo()
{
    int modestatique=0, modedynamique=0, modeinteractif=0;
    char modelu;
    FILE* ft=NULL;
    char chaine[22];
    ft = fopen("stat.txt","r");
    while(fgets(chaine,22,ft) != NULL)// On lit ligne par ligne
    {
        modelu = chaine[20]; // on capture le 20e caractere
        if (modelu=='1')
        {
            modestatique++;
        }
        else if (modelu=='2')
        {
            modedynamique++;
        }
        else if (modelu=='3')
        {
            modeinteractif++;
        }
    }
    printf("Le mode statique a ete lance %d fois\n", modestatique/2);
    printf("Le mode dynamique a ete lance %d fois\n", modedynamique/2);
    printf("Le mode interactif a ete lance %d fois\n", modeinteractif/2);

    fclose(ft);
}

/**
**/
void menustat()
{
    char menu='0';
    char choixmenustat;
    while (menu=='0')
    {
        choixmenustat = '0';
        printf("\n\n\n   Bienvenue dans le menu statistique du eXiasaver");
        printf("\n Pour lire le log en entier taper 1");
        printf("\n Pour lire les dix dernieres lignes du log taper 2");
        printf("\n Pour trier les informations qui se trouvent dans le log taper 3");
        printf("\n Que voulez-vous faire ? :");
        fflush(stdin); // permet de refaire un scanf a chaque while
        scanf(" %c",&choixmenustat);

        if (choixmenustat=='1')
        {
            afficherInfo();
        }

        else if (choixmenustat=='2')
        {
            afficherfinInfo();
        }

        else if (choixmenustat=='3')
        {
            trierinfo();
        }

        else
        {
            printf ("Vous avez insere un mauvais caractere\n");
        }

        menu=0;
        printf("\n Pour revenir au menu principal taper 0, sinon taper quelque chose d'autre pour quitter le programme :");
        fflush(stdin);
        scanf(" %c",&menu);
    }
}

