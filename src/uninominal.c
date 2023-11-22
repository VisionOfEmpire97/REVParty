#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
void electionUninominalDeuxTours(int votes[], char *candidats[], int n, int nombreDeVotes,t_mat_char_star_dyn *mat) { // n nombre de candidats 
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
    printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %.2d%%\n", n, nombreDeVotes, candidats[premierGagnant], pourcentagePremierGagnant);
    if (pourcentagePremierGagnant <= 50) {

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

char *recupere_1(t_mat_char_star_dyn *entete, t_mat_char_star_dyn *mat , int num_ligne )
{
    for(int z = 1; z < 9 ; z++)
    {
        for (int i = 4; i < recuperer_nb_colonnes(mat); i++){
            if (atoi(valeur_matrice_char_indice(mat,num_ligne, i))==z) // On parcourt i colonne a partir de la colonne 4 
            {
                return valeur_matrice_char_indice(entete, 0, i);
            }
        }
    }
    printf("Errreur encore \n");
    return NULL;
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
    printf("Errreur encore \n");
    return NULL;
}
void recupere_candidat(t_mat_char_star_dyn *entete,char *liste_candidat[])
{   
    int nbColonne = recuperer_nb_colonnes(entete);
    for (int i = 4; i < nbColonne; i++){
      liste_candidat[i-4]=valeur_matrice_char_indice(entete, 0, i);
    }

}
int changement(char*liste_candidat[] , char *vote , int nombreCandidat)
{    
    for(int i = 0 ; i<nombreCandidat ; i++)
    {
        if (liste_candidat[i]==vote)
        {
            return i+1;
        }
    }
    printf("Retour -1 \n");
    return -1 ;
}
void traitement_uninominal_1tours(t_mat_char_star_dyn *mat,t_mat_char_star_dyn *entete) 
{
    int nombrecandidat = recuperer_nb_colonnes(entete)-4;
    int nombreVotant = recuperer_nb_lignes(mat)-1;
    char *candidats[nombrecandidat] ; 
    recupere_candidat(entete,candidats);
    int votes[nombreVotant];
    char *vote ; 
    int vote_final = 0 ;
   
    for (int num=1 ;  num<nombreVotant+1 ; num++ )
    {
        vote = recupere_1(entete, mat , num );
        vote_final = changement(candidats , vote ,nombrecandidat); // le premier candidat est le candidat 1 = 1  , candidat 2 = 2 , . . .
        
        votes[num-1]=vote_final;

    }
 
    /*for (int i = 0; i < 10; i++) {
        printf("Vote %d : %d \n ",i,votes[i]);
    }*/
    electionUninominale(votes, candidats, nombrecandidat , nombreVotant );
}
void traitement_uninominal_2tours(t_mat_char_star_dyn *mat,t_mat_char_star_dyn *entete) 
{
    int nombrecandidat = recuperer_nb_colonnes(entete)-4;
    int nombreVotant = recuperer_nb_lignes(mat)-1;
    char *candidats[nombrecandidat];
    recupere_candidat(entete,candidats);
    int votes[nombreVotant];
    char *vote;
    int vote_final = 0 ;
    for (int num=1 ;  num<nombreVotant+1 ; num++ )
    {
        vote = recupere_1(entete, mat , num );
        vote_final = changement(candidats , vote ,nombrecandidat);
        votes[num-1]=vote_final;
    }
    /*
    for (int i = 0; i < 10; i++) {
        printf("Vote %d : %d \n ",i,votes[i]);
    }
    for (int i = 0; i < 10; i++) {
        printf("Vote deux %d : %d \n ",i,votes_deux[i]);
    }*/
    electionUninominalDeuxTours(votes, candidats, nombrecandidat , nombreVotant ,mat);
}
int main(int argc, char *argv[])
{   
    char *nom = argv[1]; 
    t_mat_char_star_dyn *mat  = lecture_fichier(nom);

    t_mat_char_star_dyn *entete  = lecture_entete(nom);

    int votes[] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 3};
    int votes_deux[] = {1, 1, 2, 1, 1, 2, 3, 3, 1, 3};
    char *candidats[] = {"Candidat 1", "Candidat 2", "Candidat 3"};
    int nombrecandidat = 3;
    int nombreVotant = 10 ;

    char*teste = valeur_matrice_char_indice(mat, 1, 4);
    //printf("Teste %s  \n" , teste);
    traitement_uninominal_1tours(mat,entete);
    traitement_uninominal_2tours(mat,entete);
    //electionUninominale(votes, candidats, nombrecandidat , nombreVotant );
    //electionUninominalDeuxTours(votes, candidats, nombrecandidat , nombreVotant ,votes_deux);
}