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

#define N 10
#define SEPARATEUR ","

char* data;


t_mat_char_star_dyn *lecture_par_ligne(char* buffer,FILE* file ){

    void *mat = creer_matrice(1, 6);

    fgets(buffer, sizeof(char*), file);
    
    printf("%s\n", buffer);
    
    
    char* tok = strtok(buffer, SEPARATEUR);
    inserer_matrice_char(tok, mat);
    tok = strtok(NULL, SEPARATEUR);
    inserer_matrice_char(tok, mat);
    tok = strtok(NULL, SEPARATEUR);
    inserer_matrice_char(tok, mat);
    tok = strtok(NULL, SEPARATEUR);
    inserer_matrice_char(tok, mat);
    // tok = strtok(NULL, SEPARATEUR);
    // inserer_matrice_char(tok, mat);

    printf("test\n");
    afficher_matrice_char(mat);
   
    return mat;
}

t_mat_char_star_dyn *lecture_par_col(char buffer[], FILE* file){
    t_mat_char_star_dyn *mat = creer_matrice(6, 1);
    while (fgets(buffer, sizeof(char*), file)!=NULL)
    {
        char* tok = strtok(buffer, SEPARATEUR);
        printf("%s\n", tok);
        inserer_matrice_char(tok, mat);
        afficher_matrice_char(mat);
    }
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

    char buffer[100];
    lecture_par_ligne(buffer, file);
    printf("===================================================\n");
    // lecture_par_col(buffer, file);
    while (fgets(buffer, sizeof(buffer), file)!=NULL)
    {
        char* tok = strtok(buffer, ",");

        int data;
        sscanf(tok, "%d", &data);
        tok = strtok(NULL, ","); //On passe à la colonne suivante
        tok = strtok(NULL, ",");
        tok = strtok(NULL, ",");
        // tok = strtok(NULL, ",");
        printf("%s\n", tok);
        printf("\n");
        printf("%d\n", data);
    }
    fclose(file);
    


    
    


    return 0;
}
