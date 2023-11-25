#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice.h"
#include "uninominal.h"
#include "utils_sd/util_log.h"

char buffer[CHARMAX];

void compter_voixCandidats_tour1(int votes[], int nbVotes, int resultat[], int nbCandidats)
{
    int vote;
    for (int i = 0; i < nbCandidats; i++)
        resultat[i] = 0;

    for (int i = 0; i < nbVotes; i++)
    {
        vote = votes[i];
        if (vote < 0 || vote > nbCandidats)
        {
            printf("Vote invalide pour l'électeur %d : numéro de candidat non valide.\n", i + 1);
            continue;
        }
        resultat[vote]++;
    }
}

int compter_voixCandidats_tour2(int resultat[], int nombreDeVotes, t_mat_char_star_dyn *mat, int premierGagnant, int deuxiemeGagnant, char *candidats[])
{
    int compteur = 0; // Traite en vote blanc les égalités
    int valGagnant1, valGagnant2;
    int indice = premierGagnant;
    int i_resultat = 0;
    for (int ligne = 1; ligne < nombreDeVotes + 1; ligne++)
    {
        valGagnant1 = atoi(valeur_matrice_char_indice(mat, ligne, premierGagnant + 4));
        valGagnant2 = atoi(valeur_matrice_char_indice(mat, ligne, deuxiemeGagnant + 4));
        if (valGagnant1 == valGagnant2)
        {
            sprintf(buffer, "Le votant %d à voter blanc au deuxieme tours \n", ligne);
        }
        else
        {
            indice = premierGagnant;
            i_resultat = 0;
            if (valGagnant1 > valGagnant2)
            {
                indice = deuxiemeGagnant;
                i_resultat = 1;
            }
            compteur++;
            resultat[i_resultat]++;
            sprintf(buffer, "Le votant %d à voter pour %s au deuxieme tours \n", ligne, candidats[indice]);
        }

        // append_to_log_file(buffer);
    }
    return compteur;
}

void electionUninominal(int votes[], char *candidats[], int nbCandidats, int nombreDeVotes, t_mat_char_star_dyn *mat, int tours)
{
    int premierTour[nbCandidats];
    int premierGagnant = 0;
    int deuxiemeGagnant = 1;
    int deuxiemeTourVotes[2] = {0, 0};
    int IndiceVainqueur = 0;
    int pourcentagePremierGagnant, pourcentageDeuxiemeTourGagnant, deuxiemeTourGagnant, compteur;

    compter_voixCandidats_tour1(votes, nombreDeVotes, premierTour, nbCandidats);

    /*for (int i = 0; i < n; i++)
    {
        sprintf(buffer, "Le Candidat %s à eu %d votes au premier tours \n", candidats[i], premierTour[i]);
         append_to_log_file(buffer);
    }*/

    for (int i = 1; i < nbCandidats; i++)
    {
        if (premierTour[i] > premierTour[premierGagnant])
        {
            deuxiemeGagnant = premierGagnant;
            premierGagnant = i;
        }
        else if (premierTour[i] > premierTour[deuxiemeGagnant])
        {
            deuxiemeGagnant = i;
        }
    }

    pourcentagePremierGagnant = (premierTour[premierGagnant] * 100) / nombreDeVotes;

    printf("Mode de scrutin : uninominal à %d tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2d%%\n",
           tours, nbCandidats, nombreDeVotes, candidats[premierGagnant], pourcentagePremierGagnant);

    if (pourcentagePremierGagnant <= 50 && tours == 2)
    {
        deuxiemeTourGagnant = premierGagnant;
        compteur = compter_voixCandidats_tour2(deuxiemeTourVotes, nombreDeVotes, mat, premierGagnant, deuxiemeGagnant, candidats);

        /*sprintf(buffer, "Le Candidat %s à eu %d votes au deuxieme tours \n ", candidats[premierGagnant], deuxiemeTourVotes[0]);
        append_to_log_file(buffer);
        sprintf(buffer, "Le Candidat %s à eu %d votes au deuxieme tours \n ", candidats[deuxiemeGagnant], deuxiemeTourVotes[1]);
        append_to_log_file(buffer);*/

        if (deuxiemeTourVotes[0] < deuxiemeTourVotes[1])
        {
            deuxiemeTourGagnant = deuxiemeGagnant;
            IndiceVainqueur = 1;
        }
        pourcentageDeuxiemeTourGagnant = (deuxiemeTourVotes[IndiceVainqueur] * 100) / compteur;

        printf("Mode de scrutin : uninominal à deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s, score = %.2d%%\n",
               compteur, candidats[deuxiemeTourGagnant], pourcentageDeuxiemeTourGagnant);
    }
}

int recupere_numeroCandidat(t_mat_char_star_dyn *mat, int num_ligne)
{
    int nbColonne = recuperer_nb_colonnes(mat);
    int indice_min = 0;
    int min = atoi(valeur_matrice_char_indice(mat, num_ligne, 4));
    int val;
    for (int i = 5; i < nbColonne; i++)
    {
        val = atoi(valeur_matrice_char_indice(mat, num_ligne, i));
        if (val < min)
        {
            min = val;
            indice_min = i - 4;
        }
    }
    return indice_min;
}

void traitement_uninominal(t_mat_char_star_dyn *mat, int tours) // 1 == 1 tours , 2 == 2 tours
{

    int nombrecandidat = recuperer_nb_colonnes(mat) - 4;
    int nombreVotant = recuperer_nb_lignes(mat) - 1;
    char **candidats = recuperer_candidats(mat);
    int votes[nombreVotant];
    int vote_numéro = 0;
    for (int num = 0; num < nombreVotant; num++)
    {
        vote_numéro = recupere_numeroCandidat(mat, num + 1);
        sprintf(buffer, "Le votant %d à voter pour %s au premier tours \n", num + 1, candidats[vote_numéro]);
        // append_to_log_file(buffer);
        votes[num] = vote_numéro;
        buffer[0] = '\0';
    }
    electionUninominal(votes, candidats, nombrecandidat, nombreVotant, mat, tours);
}
