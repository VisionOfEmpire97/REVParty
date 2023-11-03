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
#define NAMELENGHT 60

int main(int argc, char **argv)
{
    int balise;
    char *nom_csv;
    char *nom_log;
    while (balise = getopt(argc, argc, "i:d:o:m:"))
    {
        switch (balise)
        {
        case 'i' || 'd': /*those should be mutually exclusive ??*/
            nom_csv = optarg;
            break;
        case 'o':
            nom_log = optarg;
            break;
        case 'm':
            break;
        default:
            printf("usage : ./REVparty -i/d [nom_du_csv] -o [nom_du_log] -m [méthodes]\n");
        }
    };
    // getopt();
    return 0;
}