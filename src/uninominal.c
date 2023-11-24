#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice.h"

void electionUninominal(int votes[], char *candidats[], int n, int nombreDeVotes,t_mat_char_star_dyn *mat , int tours) { 
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
    int deuxiemeGagnant = -1; // Initialisation à une valeur non valide

    for (int i = 1; i < n; i++) {
    if (premierTour[i] > premierTour[premierGagnant]) {
        deuxiemeGagnant = premierGagnant;
        premierGagnant = i;
    } else if (deuxiemeGagnant == -1 || premierTour[i] > premierTour[deuxiemeGagnant]) {
        deuxiemeGagnant = i;
        }
    }
    int pourcentagePremierGagnant = (premierTour[premierGagnant] * 100) / nombreDeVotes;
    printf("Mode de scrutin : uninominal à %d tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2d%%\n", tours , n, nombreDeVotes, candidats[premierGagnant], pourcentagePremierGagnant);
    if (pourcentagePremierGagnant <= 50 && tours == 2 ) {

        int deuxiemeTourVotes[2] = {0, 0};
        int deuxiemeTourGagnant = -1 ;
    	int compteur = 0 ; // Traite en vote blanc les égalités 
        for (int ligne=1 ;  ligne<nombreDeVotes+1 ; ligne++){
            if (atoi(valeur_matrice_char_indice(mat,ligne,premierGagnant+4))<atoi(valeur_matrice_char_indice(mat,ligne,deuxiemeGagnant+4)))
            {
                deuxiemeTourVotes[0]++;
                compteur++;
            }else if (atoi(valeur_matrice_char_indice(mat,ligne,premierGagnant+4))>atoi(valeur_matrice_char_indice(mat,ligne,deuxiemeGagnant+4))){
                deuxiemeTourVotes[1]++;
                compteur++; 
            }
       }

        int IndiceVainqueur = 0 ; 
    	
        if (deuxiemeTourVotes[0]>= deuxiemeTourVotes[1]){
            deuxiemeTourGagnant = premierGagnant;
            IndiceVainqueur = 0 ;
        }
        else{
            deuxiemeTourGagnant = deuxiemeGagnant;
            IndiceVainqueur = 1 ;
        }
        int  pourcentageDeuxiemeTourGagnant = (deuxiemeTourVotes[IndiceVainqueur] * 100)/compteur;

        printf("Mode de scrutin : uninominal à deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s, score = %.2d%%\n", nombreDeVotes, candidats[deuxiemeTourGagnant], pourcentageDeuxiemeTourGagnant);

    }
}

int recupere_numeroCandidat(t_mat_char_star_dyn *entete, t_mat_char_star_dyn *mat , int num_ligne )
{
    for(int z = 1; z < 9 ; z++)
    {
        for (int i = 4; i < recuperer_nb_colonnes(mat); i++){
            if (atoi(valeur_matrice_char_indice(mat,num_ligne, i))==z){
                return i-3;
            }
        }
    }
    printf("Errreur encore \n");
    return -1;
}

void recupere_candidat(t_mat_char_star_dyn *entete,char *liste_candidat[])
{   
    int nbColonne = recuperer_nb_colonnes(entete);
    for (int i = 4; i < nbColonne; i++){
      liste_candidat[i-4]=valeur_matrice_char_indice(entete, 0, i);
    }

}
 
void traitement_uninominal(t_mat_char_star_dyn *mat,t_mat_char_star_dyn *entete,int tours ) // 1 == 1 tours , 2 == 2 tours 
{
    int nombrecandidat = recuperer_nb_colonnes(entete)-4;
    int nombreVotant = recuperer_nb_lignes(mat)-1;
    char *candidats[nombrecandidat] ; 
    recupere_candidat(entete,candidats);
    int votes[nombreVotant];
    int vote_numéro = 0 ;
   
    for (int num=1 ;  num<nombreVotant+1 ; num++ )
    {
        vote_numéro = recupere_numeroCandidat(entete, mat , num );        
        votes[num-1]=vote_numéro;
    }
 
    /*for (int i = 0; i < 10; i++) {
        printf("Vote %d : %d \n ",i,votes[i]);
    }*/
    electionUninominal(votes, candidats, nombrecandidat , nombreVotant ,mat , tours );
}
