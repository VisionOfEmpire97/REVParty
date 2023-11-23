#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice.h"

int main(int argc, char *argv[])
{   
    char *nom = argv[1]; 
    t_mat_char_star_dyn *mat  = lecture_fichier(nom);
    t_mat_char_star_dyn *entete  = lecture_entete(nom);

    printf("Teste méthode uninominal à 1 tours : \n" );
    traitement_uninominal(mat,entete,1);
    printf("Teste méthode uninominal à 2 tours : \n" );
    traitement_uninominal(mat,entete,2);
    
}