#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lecture_csv.h"
#include "../utils_sd/matrice/matrice.h"

#define SEPARATEUR ","
#define BUFF_SIZE 300


t_mat_char_star_dyn *lecture_par_ligne(const char *nom_fichier ){

    FILE *file = fopen(nom_fichier, "r");  
    t_mat_char_star_dyn *mat = creer_matrice(); 
    char* tok;
    char buffer[300];

    fgets(buffer, sizeof(buffer), file);
    ajouter_ligne(mat);
    inserer_chaine_matrice(buffer,mat);
    afficher_matrice_char(mat); 
    fclose(file); 
    return mat;

}

void inserer_chaine_matrice(char * chaine, t_mat_char_star_dyn *mat){
    char chaine2[600];    /*Free???*/
    strcpy(chaine2, chaine);
    char*  tok = strtok(chaine2, SEPARATEUR);
    inserer_matrice_char(tok, mat);
    tok = strtok(NULL, SEPARATEUR); 
    while (tok!=NULL)
    {
    inserer_matrice_char(tok, mat);
    tok = strtok(NULL, SEPARATEUR);    
    }
    
}

t_mat_char_star_dyn *recherche_hash(char * hash, const char *nom_fichier){
    
    FILE* file = fopen(nom_fichier, "r");
    
    t_mat_char_star_dyn *mat = creer_matrice();
    char buffer[BUFF_SIZE];
    char buffer2[BUFF_SIZE]; 
    int found=0;
    

     while (fgets(buffer, sizeof(buffer), file)!=NULL&& !found)
    {   
        strcpy(buffer2,buffer);
        char* tok = strtok(buffer, SEPARATEUR);
        tok = strtok(NULL, SEPARATEUR);
        tok = strtok(NULL, SEPARATEUR);
        tok = strtok(NULL, SEPARATEUR);
         if (!strcmp(tok, hash))
        {   
            ajouter_ligne(mat);
            inserer_chaine_matrice(buffer2,mat);
            found=1; 
        }

    }
    printf("%s\n\n",found?"Hash retrouvé!":"Votre hash ne correspond pas.");

    fclose(file);
    return mat;
}
