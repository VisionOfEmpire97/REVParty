/*Paramètre :*/
/*lecture_csv(../fichier/*.csv (voir sr2 aussi)*/
/*FILE * fich = NULL
    fopen...*/
/* ========================================== */
/*inserer(____, mot)*/
/*BALISES DOXYGEN*/


#include <stdio.h>
#include "../utils_sd/matrice/code/matrice.h"


t_mat_char_star_dyn *lecture_par_ligne(char buffer[],FILE* file );
t_mat_char_star_dyn *lecture_par_col(char buffer[], FILE* file);

char** recherche_mot(char * mot, FILE csv); //regarder config.c sr2
char** recherche_indice(int i_deb, int i_fin, int j_deb, int j_fin);