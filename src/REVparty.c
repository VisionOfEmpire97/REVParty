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
#include <arg_parse_util.h>
#define NAMELENGHT 60

int main(int argc, char **argv)
{
    int balise[5], n = 0;
    char *nom_csv;
    char *nom_log;
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
        case 'm': // ne prend qu'un argument ?
            methode = optarg;
            n++;
            break;
        default:
            printf("usage : ./REVparty -i/-d [nom_du_csv] -o [nom_du_log] -m [méthodes]\n");
            exit(EXIT_FAILURE);
        }
    };
    begin_to_log(nom_log);

    lancer_methode(methode);
    //more things here 

    if (nom_log != NULL) fclose(nom_log);
    return 0;
}