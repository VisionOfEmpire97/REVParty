#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg_parse_util.h"
#include "../CSV/lecture_csv.h"
#include "../uninominal.h"
#include "../jugement.h"
#include "../condorcet.h"
#include "matrice.h"

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

void lancer_methode(char *methode, char *nom_csv, char *type_csv)
{
    t_mat_char_star_dyn *matrice_de_vote = lecture_fichier(nom_csv);
    char **entete;
    int nb_electeur = recuperer_nb_lignes(matrice_de_vote) - 1;
    t_mat_int_dyn *mat_duel;
    if (*type_csv == 'd')
    {
        entete = recuperer_candidats(matrice_de_vote, 0); // mat de duel == 0
        mat_duel = transformer_mat_char_mat_duel(matrice_de_vote);
        nb_electeur = mat_duel->matrice[0][1] + mat_duel->matrice[1][0];
    }
    else
    {
        entete = recuperer_candidats(matrice_de_vote, 1); // mat de vote == 1
        mat_duel = construire_mat_duel(matrice_de_vote);
    }
    int methode_id;
    char *valid_methods[7] = {"uni1", "uni2", "cm", "cp",
                              "cs", "jm", "all"};

    for (methode_id = 0; methode_id < 7; methode_id++)
    {
        if (strcmp(methode, valid_methods[methode_id]) == 0)
            break;
    }
    switch (methode_id)
    {
    case 0: // uninominale à un tour
        traitement_uninominal(matrice_de_vote, 1);
        break;
    case 1: // uninominale à deux tours
        traitement_uninominal(matrice_de_vote, 2);
        break;
    case 2: // Condorcet + minimax
        // fonction qui appelle la méthode de vote
        condorcet_minimax(mat_duel, entete, nb_electeur);
        // vainqueur_condorcet prendra en param mat_duel et entete A CHANGER
        break;
    case 3: // Condorcet + paires
        condorcet_paires(mat_duel, entete, nb_electeur);
        // fonction qui appelle la méthode de vote
        break;
    case 4: // Condorcet + Schulze
        condorcet_Schulze(mat_duel, entete, nb_electeur);
        // fonction qui appelle la méthode de vote
        break;
    case 5: // jugement majoritaire
        methode_jugement(matrice_de_vote);
        break;
    case 6: // toutes le méthodes
        // fonction qui appelle TOUT
        // - si -i (vote par classement), alors on lance toutes les méthodes
        // - si -d(matrice de duel), alors on lance toutes les méthodes sauf uni1 et uni2 et jugement
        if (*type_csv == 'i')
        {
            traitement_uninominal(matrice_de_vote, 1);
            traitement_uninominal(matrice_de_vote, 2);
            methode_jugement(matrice_de_vote);
            condorcet_minimax(mat_duel, entete, nb_electeur);
            condorcet_paires(mat_duel, entete, nb_electeur);
            condorcet_Schulze(mat_duel, entete, nb_electeur);
        }
        else
        {
            condorcet_minimax(mat_duel, entete, nb_electeur);
            condorcet_paires(mat_duel, entete, nb_electeur);
            condorcet_Schulze(mat_duel, entete, nb_electeur);
        }
        break;
    default:
        printf("%sargument de méthode invalides, arguments reconnus :\n      ", RED);
        for (int i = 0; i < 7; i++)
        {
            printf("%s ", valid_methods[i]);
        }
        printf("\n      Veuillez réessayer%s\n", END_COLOR);
        exit(EXIT_FAILURE);
    }
    supprimer_matrice_char(matrice_de_vote);
    supprimer_matrice_int(mat_duel);
}

void afficher_res(char *nom_methode, int nb_candidats, int nb_electeurs, char *nom_vainqueur, char *score)
{
    printf("%sMode de scrutin : %s, %d candidats, %d votants%s", GREEN, nom_methode, nb_candidats, nb_electeurs, END_COLOR);
    if (nom_vainqueur != NULL)
    {
        printf("%s, vainqueur = %s%s", GREEN, nom_vainqueur, END_COLOR);
    }
    else
    {
        printf("%s, vainqueur = pas de vainqueur%s",RED, END_COLOR);
    }
    if (score != NULL)
    {
        printf("%s, score = %s%s", GREEN, score, END_COLOR);
    }
    printf("\n");
};