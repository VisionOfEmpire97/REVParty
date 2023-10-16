/// \author Equipe 001
/// \date 23 Septembre 2023
/// \file le fichier lecture_csv devrait prendre un fichier CSV 
///       et retourner une matrice de type t_mat_char_star_dyn ????

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lecture_csv.h"
#include "../utils_sd/matrice/code/matrice.h"

#define SEPARATEUR ","

char* data;



t_mat_char_star_dyn *lecture_par_ligne(FILE* file ){

    void *mat = creer_matrice(1, 6);
    char* tok;
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    
    tok = strtok(buffer, SEPARATEUR);
    inserer_matrice_char(tok, mat);
    tok = strtok(NULL, SEPARATEUR); 
    while (tok!=NULL)
    {
    inserer_matrice_char(tok, mat);
    tok = strtok(NULL, SEPARATEUR);    
    }
    afficher_matrice_char(mat);  
    return mat;
}





int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port", argv[0]);
        exit(1);
    }
    
    FILE* file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Echec ouverture fichier");
        exit(2);
    }



    while (!feof(file))
    {
        lecture_par_ligne(file);
    }
    
    

    printf("===================================================\n");



    fclose(file);
    


    
    


    return 0;
}
