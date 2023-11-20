#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SHA256/sha256.h"
#include "SHA256/sha256_utils.h"
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice.h"
<<<<<<< Updated upstream:src/uninominal_invasion_cd.c
=======

>>>>>>> Stashed changes:src/uninominal.c
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
    for(int z = 1; z < 9 ; z++)
    {
        printf("Probleme 9  \n");
        for (int i = 4; i < recuperer_nb_colonnes(mat); i++){
            printf("Probleme num %d \n",num_ligne);
            if (atoi(valeur_matrice_char_indice(mat,num_ligne, i))==z) // On parcourt i colonne a partir de la colonne 4 
            {
                printf("Probleme 10  \n");
                return valeur_matrice_char_indice(entete, 0, i);
            }
        }
    }
    printf("Errreur encore \n");
}
char *recupere_2(t_mat_char_star_dyn *entete, t_mat_char_star_dyn *mat , int num_ligne )
{
    int premier_1 = 0 ;
    
    for(int z = 1; z < 9 ; z++)
    {
        for (int i = 4; i < recuperer_nb_colonnes(mat); i++){
            if (atoi(valeur_matrice_char_indice(mat,num_ligne, i))==z && premier_1==1 ) // On parcourt i colonne a partir de la colonne 4 
            {
                    return valeur_matrice_char_indice(entete, 0, i);
            }
            else if (atoi(valeur_matrice_char_indice(mat,num_ligne, i))==z && premier_1==0 )
            {
                premier_1++;
            }
        }
    /*for (int i = 4; i < recuperer_nb_colonnes(mat); i++){
        if (atoi(valeur_matrice_char_indice(mat, num_ligne, i))==2)
        {

            return valeur_matrice_char_indice(entete, 0, i);
        }
    }
    printf("Pas de 2 trouver dans la ligne ") ;*/
    }
}
void recupere_candidat(t_mat_char_star_dyn *entete,int nbColonne,char *liste_candidat[])
{   

    for (int i = 0; i < nbColonne; i++){
      liste_candidat[i]=valeur_matrice_char_indice(entete, 0, i);
    }

}
int changement(char*liste_candidat[] , char *vote , int nombreCandidat)
{    printf("Probleme 12  \n");
    for(int i = 0 ; i<nombreCandidat ; i++)
    {
        printf("Probleme 13  \n");
        if (strcmp(liste_candidat[i],vote)==0)
        {
            return i+1 ;
        }
        printf("Probleme 14 \n");
    }
    return -1 ;
}
void traitement_uninominal_1tours(t_mat_char_star_dyn *mat,t_mat_char_star_dyn *entete) 
{
    printf("Probleme 2  \n");
    int nombrecandidat = recuperer_nb_colonnes(entete)-4;
    int nombreVotant = recuperer_nb_lignes(mat)-1;
    printf("Probleme 3  \n");
    char *candidats[nombrecandidat] ; 
    recupere_candidat(entete,nombrecandidat,candidats);
    printf("Probleme 4 \n");
    int votes[nombreVotant];
    char *vote ; 
    int vote_final = 0 ;
    printf("Probleme 6  \n");
    for (int num=1 ;  num<nombreVotant ; num++ )
    {
        printf("Probleme boucle numéro i %d \n"  , num );
        vote = recupere_1(entete, mat , num );
        printf("Probleme 7  \n");
        printf("vote : %s  \n", vote);
         printf("Probleme seg  \n");
        vote_final = changement(candidats , vote ,nombrecandidat); // le premier candidat est le candidat 1 = 1  , candidat 2 = 2 , . . .
        printf("Probleme 8  \n");
        vote[num-1]=vote_final;
        printf("Probleme 9 \n");
    }
    printf("Ôk on envoie  \n");
    electionUninominale(votes, candidats, nombrecandidat , nombreVotant );
}
void traitement_uninominal_2tours(t_mat_char_star_dyn *mat,t_mat_char_star_dyn *entete) 
{
    int nombrecandidat = recuperer_nb_colonnes(entete)-4;
    int nombreVotant = recuperer_nb_lignes(mat)-1;
    char *candidats[nombrecandidat];
    recupere_candidat(entete,nombrecandidat,candidats);
    int votes[nombreVotant];
    int votes_deux[nombreVotant];
    char *vote;
    int vote_final = 0 ;
    for (int num=1 ;  num<nombreVotant ; num++ )
    {
        vote = recupere_1(entete, mat , num );
        vote_final = changement(candidats , vote ,nombrecandidat);
        vote[num-1]=vote_final;
        vote = recupere_2(entete, mat , num );
        vote_final = changement(candidats , vote ,nombrecandidat);
        votes_deux[num-1]=vote_final;
    }
    electionUninominalDeuxTours(votes, candidats, nombrecandidat , nombreVotant ,votes_deux);
}
int main(int argc, char *argv[])
{
    char *nom = argv[1]; 
    t_mat_char_star_dyn *mat  = lecture_fichier(nom);
    t_mat_char_star_dyn *entete  = lecture_entete(nom);
    printf("Ok pour le moment \n");
    int votes[] = {1, 2, 2, 1, 1, 2, 2, 2, 2, 3};
    int votes_deux[] = {1, 2, 2, 1, 1, 2, 2, 2, 2, 3};
    char *candidats[] = {"Candidat 1", "Candidat 2", "Candidat 3"};
    int nombrecandidat = 3;
    int nombreVotant = 10 ;
    printf("Probleme 1  \n");
    traitement_uninominal_1tours(mat,entete);
    //electionUninominale(votes, candidats, nombrecandidat , nombreVotant );
    //electionUninominalDeuxTours(votes, candidats, nombrecandidat , nombreVotant ,votes_deux);
}