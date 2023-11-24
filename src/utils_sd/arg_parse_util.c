#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg_parse_util.h"
#include "../CSV/lecture_csv.h"
#include "../uninominal.h"

void check_compatibility(int *tab, int len_tab)
{   
    for (int i = 0; i < len_tab; i++)
    {
        if (tab[i] == 'i' || tab[i] == 'd')
        {
            printf("\033[1;31mLes balises i et d ne sont pas compatibles, merci de n'utiliser qu'une seule occurence de -i ou -d\e[00m\n");
            exit(EXIT_FAILURE);
        };
    }
}

void lancer_methode(char *methode, char *nom_csv)
{   
    t_mat_char_star_dyn *mat  = lecture_fichier(nom_csv);
    t_mat_char_star_dyn *entete  = lecture_entete(nom_csv);
    int methode_id;
    char *valid_methods[7] = {"uni1", "uni2", "cm", "cp", "cs", "jm", "all"};

    for (methode_id = 0; methode_id < 7; methode_id++)
    {
        if (strcmp(methode, valid_methods[methode_id]) == 0)
            break;
    }
    switch (methode_id)
    {
    case 0: // uninominale à un tour
        traitement_uninominal(mat, 1);
        break;
    case 1: // uninominale à deux tours
        traitement_uninominal(mat, 2);
        break;
    case 2: // Condorcet + minimax
        // fonction qui appelle la méthode de vote
        break;
    case 3: // Condorcet + paires
        // fonction qui appelle la méthode de vote
        break;
    case 4: // Condorcet + Schulze
        // fonction qui appelle la méthode de vote
        break;
    case 5: // jugement majoritaire
        // fonction qui appelle la méthode de vote
        break;
    case 6: // toutes le méthodes
        // fonction qui appelle TOUT
        // - si -i (vote par classement), alors on lance toutes les méthodes 
        // - si -d(matrice de duel), alors on lance toutes les méthodes sauf uni1 et uni2
        break;
    default:
        printf("\033[1;31margument de méthode invalide, arguments reconnus :\n      ");
        for (int i = 0; i < 7; i++) {
            printf("%s ",valid_methods[i]);
        }
        printf("\n      Veuillez réessayer\e[00m\n");
        exit(EXIT_FAILURE);
    }
};