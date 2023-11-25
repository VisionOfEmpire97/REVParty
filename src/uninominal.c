#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice.h"
#include "uninominal.h"
#include "utils_sd/util_log.h"

char buffer[CHARMAX];

void electionUninominal(int votes[], char *candidats[], int n, int nombreDeVotes, t_mat_char_star_dyn *mat, int tours)
{
    int premierTour[n];
    for (int i = 0; i < n; i++)
    {
        premierTour[i] = 0;
    }
    for (int i = 0; i < nombreDeVotes; i++)
    {
        int vote = votes[i];
        if (vote < 1 || vote > n)
        {
            printf("Vote invalide pour l'électeur %d : numéro de candidat non valide.\n", i + 1);
            continue;
        }
        premierTour[vote - 1]++;
    } 

    for (int i = 0; i < n; i++){
        sprintf(buffer, "Le Candidat %s à eu %d votes au premier tours \n", valeur_matrice_char_indice(mat, 0, 4+i), premierTour[i]);
        append_to_log_file(buffer);
    }
    int premierGagnant = 0;
    int deuxiemeGagnant = -1; // Initialisation à une valeur non valide

    for (int i = 1; i < n; i++)
    {
        if (premierTour[i] > premierTour[premierGagnant])
        {
            deuxiemeGagnant = premierGagnant;
            premierGagnant = i;
        }
        else if (deuxiemeGagnant == -1 || premierTour[i] > premierTour[deuxiemeGagnant])
        {
            deuxiemeGagnant = i;
        }
    }
    int pourcentagePremierGagnant = (premierTour[premierGagnant] * 100) / nombreDeVotes;
    printf("Mode de scrutin : uninominal à %d tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2d%%\n", tours, n, nombreDeVotes, candidats[premierGagnant], pourcentagePremierGagnant);
    if (pourcentagePremierGagnant <= 50 && tours == 2)
    {

        int deuxiemeTourVotes[2] = {0, 0};
        int deuxiemeTourGagnant = -1;
        int compteur = 0; // Traite en vote blanc les égalités
        for (int ligne = 1; ligne < nombreDeVotes + 1; ligne++)
        {
            if (atoi(valeur_matrice_char_indice(mat, ligne, premierGagnant + 4)) < atoi(valeur_matrice_char_indice(mat, ligne, deuxiemeGagnant + 4)))
            {
                sprintf(buffer, "Le votant %d à voter pour %s au deuxieme tours \n", ligne , valeur_matrice_char_indice(mat, 0, premierGagnant+4));
                append_to_log_file(buffer);
                deuxiemeTourVotes[0]++;
                compteur++;
            }
            else if (atoi(valeur_matrice_char_indice(mat, ligne, premierGagnant + 4)) > atoi(valeur_matrice_char_indice(mat, ligne, deuxiemeGagnant + 4)))
            {
                sprintf(buffer, "Le votant %d à voter pour %s au deuxieme tours \n", ligne, valeur_matrice_char_indice(mat, 0, deuxiemeGagnant+4));
                append_to_log_file(buffer);
                deuxiemeTourVotes[1]++;
                compteur++;
            }else{
                sprintf(buffer, "Le votant %d à voter blanc au deuxieme tours \n", ligne);
                append_to_log_file(buffer);
            }
        }

        int IndiceVainqueur = 0;

        sprintf(buffer, "Le Candidat %s à eu %d votes au deuxieme tours \n ", valeur_matrice_char_indice(mat, 0, premierGagnant+4), deuxiemeTourVotes[0]);
        append_to_log_file(buffer);
        sprintf(buffer, "Le Candidat %s à eu %d votes au deuxieme tours \n ", valeur_matrice_char_indice(mat, 0, deuxiemeGagnant+4), deuxiemeTourVotes[1]);
        append_to_log_file(buffer);

        if (deuxiemeTourVotes[0] >= deuxiemeTourVotes[1])
        {
            deuxiemeTourGagnant = premierGagnant;
            IndiceVainqueur = 0;
        }
        else
        {
            deuxiemeTourGagnant = deuxiemeGagnant;
            IndiceVainqueur = 1;
        }
        int pourcentageDeuxiemeTourGagnant = (deuxiemeTourVotes[IndiceVainqueur] * 100) / compteur;

        printf("Mode de scrutin : uninominal à deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s, score = %.2d%%\n", nombreDeVotes, candidats[deuxiemeTourGagnant], pourcentageDeuxiemeTourGagnant);
    }
}

int recupere_numeroCandidat(t_mat_char_star_dyn *mat, int num_ligne)
{
    for (int z = 1; z < 9; z++)
    {
        for (int i = 4; i < recuperer_nb_colonnes(mat); i++)
        {
            if (atoi(valeur_matrice_char_indice(mat, num_ligne, i)) == z)
            {
                return i - 3;
            }
        }
    }
    printf("Errreur encore \n");
    return -1;
}

void traitement_uninominal(t_mat_char_star_dyn *mat, int tours) // 1 == 1 tours , 2 == 2 tours
{

    int nombrecandidat = recuperer_nb_colonnes(mat) - 4;
    int nombreVotant = recuperer_nb_lignes(mat) - 1;
    char **candidats = recuperer_candidats(mat);
    int votes[nombreVotant];
    int vote_numéro = 0;


    for (int num = 1; num < nombreVotant + 1; num++)
    {
        vote_numéro = recupere_numeroCandidat(mat, num);
        sprintf(buffer, "Le votant %d à voter pour %s au premier tours \n", num, valeur_matrice_char_indice(mat, 0, vote_numéro+3));
        append_to_log_file(buffer);
        votes[num - 1] = vote_numéro;
        buffer[0] = '\0';
    }
    /*for (int i = 0; i < 10; i++) {
        printf("Vote %d : %d \n ",i,votes[i]);
    }*/
    electionUninominal(votes, candidats, nombrecandidat, nombreVotant, mat, tours);

}
