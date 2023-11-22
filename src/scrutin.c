/**
 * \author Équipe 001
 * \date 23 Septembre 2023
 * \brief Programme principal de décompte de voix.
 * \file src/scrutin.c
 * Le fichier scrutin s'occupe d'analyser les balises et les paramètres,
 * appelle la méthode de scrutin appropriée, et crée un fichier de vote anonymisé
 */
/**
 \mainpage
  \section Project Projet REVParty
  \subsection Objectifs Objectifs du Projet :
   - Implémentation de différentes méthodes de scrutins
   - Vérification des résultats du scrutin grâce à SHA256
   \subsection Modules Liste des modules du programme
   - Programme indépendant \ref VMV
   - Programme principal \ref scrutin
   - Lecteur du fichier csv \ref CSV
   - Initialisation des matrices \ref ADTMatrice
 */

/**
 * \defgroup scrutin Programme principal
 * Analyse des balises et arguments passés en paramètre et appel des
 * différentes méthodes de scrutins
 * \{
*/
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include "utils_sd/arg_parse_util.h"
#include "utils_sd/util_log.h"
#include "CSV/lecture_csv.h"
#define NAMELENGHT 60


/**
 * @brief utilise getopt() afin de récupérer les arguments de la ligne de commande
 *
 * @param[in] argc
 * @param[in] argv
 * @return retourne zéro en cas de succès
 */
int main(int argc, char **argv)
{
    int balise[5], n = 0;
    char *nom_csv = NULL;
    char *nom_log = NULL;
    char *methode = NULL;
    while ((balise[n] = getopt(argc, argv, "i:d:o:m:")) != -1)
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
            printf("usage : ./REVparty [-i|d nom_du_csv] [-o nom_du_log] [-m méthodes]\n");
            exit(EXIT_FAILURE);
        }
    }
    if (nom_csv == NULL || methode == NULL)
    {
        printf("usage : ./REVparty [-i|d nom_du_csv] [-o nom_du_log] [-m méthodes]\n");
        exit(EXIT_FAILURE);
    }

    FILE* log_file = begin_to_log(nom_log);

    lancer_methode(methode, nom_csv);
    //more things here
    close_log_file(log_file);
    
    return 0;
}

/**}\*/
