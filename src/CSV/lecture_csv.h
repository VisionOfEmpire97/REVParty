/*Paramètre :*/
/*lecture_csv(../fichier/*.csv (voir sr2 aussi)*/
/*FILE * fich = NULL
    fopen...*/
/* ========================================== */
/*inserer(____, mot)*/
/*BALISES DOXYGEN*/


#include <stdio.h>
#include "../utils_sd/matrice/matrice.h" 


t_mat_char_star_dyn *lecture_par_ligne(FILE* file );


t_mat_char_star_dyn *recherche_hash(char * hash, FILE* file); //regarder config.c sr2
t_mat_char_star_dyn *recherche_indice(int i_deb, int i_fin, int j_deb, int j_fin);

void inserer_chaine_matrice(char * chaine, t_mat_char_star_dyn *mat);