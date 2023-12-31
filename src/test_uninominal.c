#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice.h"
#include "uninominal.h"
#include "utils_sd/util_log.h"

int main(int argc, char *argv[])
{
    char *nom = argv[1];
    t_mat_char_star_dyn *mat = lecture_fichier(nom);

    FILE *log_file = begin_to_log("log/test_uninom.txt");

    printf("Test méthode uninominal à 1 tours : \n");
    traitement_uninominal(mat, 1);
    printf("Test méthode uninominal à 2 tours : \n");
    traitement_uninominal(mat, 2);
    supprimer_matrice_char(mat);
    close_log_file();
}