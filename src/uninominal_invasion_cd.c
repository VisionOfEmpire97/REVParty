#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SHA256/sha256.h"
#include "SHA256/sha256_utils.h"
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice.h"
void electionUninominale(int votes[], char *candidats[], int n , int nombreDeVotes ) {
    int candidatVotes[n];
    for (int i = 0; i < n; i++) {
        candidatVotes[i] = 0;
    }
    for (int i = 0; i < nombreDeVotes; i++) {
        int vote = votes[i];
        if (vote < 1 || vote > n) {
            printf("Vote invalide pour l'électeur %d \n", i + 1);
            continue;
        }
        candidatVotes[vote - 1]++;
    }
    int gagnant = 0;
    int maxVotes = 0;
    for (int i = 0; i < n; i++) {
        if (candidatVotes[i] > maxVotes) {
            maxVotes = candidatVotes[i];
            gagnant = i;
        }
    }
    
    char *vainqueur = candidats[gagnant];
    int score = ( maxVotes*100) / nombreDeVotes;
    printf("Mode de scrutin : uninominal à un tour, %d candidats, %d votants, vainqueur = %s, score = %.2d%% \n", n, nombreDeVotes, vainqueur, score);
}
void electionUninominalDeuxTours(int votes[], char *candidats[], int n, int nombreDeVotes,int votes_deux[]) {
    int candidatVotes[n];
    for (int i = 0; i < n; i++) {
        candidatVotes[i] = 0;
    }
    for (int i = 0; i < nombreDeVotes; i++) {
        int vote = votes[i];
        if (vote < 1 || vote > n) {
            printf("Vote invalide pour l'électeur %d : numéro de candidat non valide.\n", i + 1);
            continue;
        }
        candidatVotes[vote-1]++;
    }
    int premierTour[n];
    for (int i = 0; i < n; i++) {
        premierTour[i] = candidatVotes[i];
    }
    int premierGagnant = 0;
    int deuxiemeGagnant = 0;
    int totalVotesPremierTour = nombreDeVotes;
    for (int i = 0; i < n; i++) {
        if (premierTour[i] > premierTour[premierGagnant]) {
            deuxiemeGagnant = premierGagnant;
            premierGagnant = i;
        } else if (premierTour[i] > premierTour[deuxiemeGagnant]) {
            deuxiemeGagnant = i;
        }
    }
    int pourcentagePremierGagnant = (premierTour[premierGagnant] * 100) / totalVotesPremierTour;
    printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2d%%\n", n, nombreDeVotes, candidats[premierGagnant], pourcentagePremierGagnant);
    if (pourcentagePremierGagnant <= 50) {
        int deuxiemeTourVotes[2] = {0, 0};
        int deuxiemeTourGagnant = -1;
        for (int i = 0; i < nombreDeVotes; i++) {
            if (votes_deux[i] == premierGagnant) {
                deuxiemeTourVotes[0]++;
            } else if (votes_deux[i] == deuxiemeGagnant) {
                deuxiemeTourVotes[1]++;
            }
        }
        int pourcentageDeuxiemeTourGagnant = (deuxiemeTourVotes[deuxiemeTourGagnant] * 100) / nombreDeVotes;
        printf("Mode de scrutin : uninominal à deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s, score = %.2d%%\n", nombreDeVotes, candidats[deuxiemeTourGagnant], pourcentageDeuxiemeTourGagnant);
    }
}

char *recupere_1(t_mat_char_star_dyn *entete, t_mat_char_star_dyn *mat , int num_ligne )
{
    for (int i = 4; i < recuperer_nb_colonnes(mat); i++){
        if (atoi(valeur_matrice_char_indice(mat,num_ligne, i))==1)
        {
            return valeur_matrice_char_indice(entete, 0, i);
        }
    }
    printf("Pas de 1 trouver dans la ligne ") ;
}
char *recupere_2(t_mat_char_star_dyn *entete, t_mat_char_star_dyn *mat , int num_ligne )
{
    for (int i = 4; i < recuperer_nb_colonnes(mat); i++){
        if (atoi(valeur_matrice_char_indice(mat, num_ligne, i))==2)
        {

            return valeur_matrice_char_indice(entete, 0, i);
        }
    }
    printf("Pas de 2 trouver dans la ligne ") ;
}
char **recupere_candidat(t_mat_char_star_dyn *entete)
{   
    int nbColonne = recuperer_nb_colonnes(entete)-4 ; 
    char *liste_candidat[nbColonne];
    for (int i = 0; i < nbColonne; i++){
      liste_candidat[i]=valeur_matrice_char_indice(entete, 0, i);
    }
    return liste_candidat;
}
int changement(char*liste_candidat[] , char vote , int nombreCandidat)
{   
    for(int i = 0 ; i<nombreCandidat ; i++)
    {
        if (strcmp(liste_candidat[i],vote))
        {
            return i+1 ;
        }
    }
    return -1 ;
}
void traitement_uninominal_1tours(t_mat_char_star_dyn *mat,t_mat_char_star_dyn *entete) // mat on part du principe que c'est sans l'entete
{
    int nombrecandidat = recuperer_nb_colonnes(entete)-4;
    int nombreVotant = recuperer_nb_lignes(mat);
    char *candidats[] = recupere_candidat(entete);
    int votes[nombreVotant];
    char vote ; 
    int vote_final = 0 ;
    for (int num=0 ;  num<nombreVotant ; num++ )
    {
        vote = recupere_1(entete, mat , num );
        vote_final = changement(candidats , vote ,nombrecandidat);
        votes[num]=vote_final;
    }
    electionUninominale(votes, candidats, nombrecandidat , nombreVotant );
}
void traitement_uninominal_2tours(t_mat_char_star_dyn *mat,t_mat_char_star_dyn *entete) 
{
    int nombrecandidat = recuperer_nb_colonnes(entete)-4;
    int nombreVotant = recuperer_nb_lignes(mat);
    char *candidats[] = recupere_candidat(entete);
    int votes[nombreVotant];
    int votes_deux[nombreVotant];
    char vote;
    int vote_final = 0 ;
    for (int num=0 ;  num<nombreVotant ; num++ )
    {
        vote = recupere_1(entete, mat , num );
        vote_final = changement(candidats , vote ,nombrecandidat);
        votes[num]=vote_final;
        vote = recupere_2(entete, mat , num );
        vote_final = changement(candidats , vote ,nombrecandidat);
        votes_deux[num]=vote_final;
    }
    electionUninominalDeuxTours(votes, candidats, nombrecandidat , nombreVotant ,votes_deux);
}
int main ()
{
    int votes[] = {1, 2, 2, 1, 1, 2, 2, 2, 2, 3};
    int votes_deux[] = {1, 2, 2, 1, 1, 2, 2, 2, 2, 3};
    char *candidats[] = {"Candidat 1", "Candidat 2", "Candidat 3"};
    int nombrecandidat = 3;
    int nombreVotant = 10 ;
    electionUninominale(votes, candidats, nombrecandidat , nombreVotant );
    electionUninominalDeuxTours(votes, candidats, nombrecandidat , nombreVotant ,votes_deux);
}