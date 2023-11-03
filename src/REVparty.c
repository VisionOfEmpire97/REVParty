/**
 \mainpage
  \section Project Projet REVParty
  \subsection Objectifs Objectifs du Projet :
   - Implémentation de différentes méthodes de scrutins
   - Vérification des résultats du scrutin grâce à SHA256
   \subsection Modules Liste des modules du programme
   - Programme \ref VMV
   - Programme principal REVParty
 */

/**
 * \author Équipe 001
 * \date 23 Septembre 2023
 * \file le fichier REVparty s'occupe d'analyser les balises et les paramètres,
 *       appelle la méthode de scrutin appropriée, et crée un fichier de vote anonymisé
 */
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#define NAMELENGHT 60

// Variables Couleurs
char *RED = "\033[1;31m";
char *GREEN = "\033[1;32m";
char *END_COLOR = "\e[00m";

//méthodes
enum methodes{uni1,uni2,cm,cp,cs,jm,all};

void check_compatibility(int *tab, int len_tab)
{
    for (int i = 0; i < len_tab; i++)
    {
        if (tab[i] == 'i' || tab[i] == 'd')
        {
            printf("%sLes balises i et d ne sont pas compatibles, merci de n'utiliser qu'une seule occurence de -i ou -d%s\n", RED, END_COLOR);
            exit(EXIT_FAILURE);
        };
    }
}

int main(int argc, char **argv)
{
    int balise[5], n = 0;
    char *nom_csv;
    char *nom_log = stdout;
    char *methode;
    while ((balise[n] = getopt(argc, argc, "i:d:o:m:")) != -1)
    {
        switch (balise[n])
        {
        case 'i': /*i and d are mutually exclusive  */
            check_compatibility(balise, n);
            nom_csv = optarg;
            n++;
            break;
        case 'd':
            check_compatibility(balise, n);
            nom_csv = optarg;
            printf("%sAttention, la balise -d désactive l'emploi des arguments uni1 et uni2%s\n", RED, END_COLOR);
            n++;
            break;
        case 'o':
            nom_log = optarg;
            n++;
            break;
        case 'm': //ne prend qu'un argument ?
            methode = optarg;
            n++;
            break;
        default:
            printf("usage : ./REVparty -i/d [nom_du_csv] -o [nom_du_log] -m [méthodes]\n");
            exit(EXIT_FAILURE);
        }
    };
    // getopt();
    return 0;
}