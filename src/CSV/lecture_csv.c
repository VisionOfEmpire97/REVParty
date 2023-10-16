#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lecture_csv.h"
#include "../utils_sd/matrice/matrice.h"

#define SEPARATEUR ","

char* data;




t_mat_char_star_dyn *lecture_par_ligne(FILE* file ){

    
    if (fopen(file, "r")==NULL)
    { 
        perror("Echec ouverture fichier");
        exit(1);
    }
    
    void *mat = creer_matrice();
    char* tok;
    char buffer[300];
    fgets(buffer, sizeof(buffer), file);
    ajouter_ligne(mat);
    inserer_chaine_matrice(buffer,mat);
    
    // tok = strtok(buffer, SEPARATEUR);
    // inserer_matrice_char(tok, mat);
    // tok = strtok(NULL, SEPARATEUR); 
    // while (tok!=NULL)
    // {
    // inserer_matrice_char(tok, mat);
    // tok = strtok(NULL, SEPARATEUR);    
    // }
    afficher_matrice_char(mat); 
    fclose(file); 
    return mat;

}
void inserer_chaine_matrice(char * chaine, t_mat_char_star_dyn *mat){
    char *chaine2;
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

t_mat_char_star_dyn *recherche_hash(char * hash, FILE* file){
    
    if (fopen(file, "r")==NULL)
    { 
        perror("Echec ouverture fichier");
        exit(1);
    }
    t_mat_char_star_dyn *mat = creer_matrice();

    char buffer[300];
    char buffer2[300]; 
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

    }printf("%s\n",found?"found":"not found");
    fclose(file);
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


   
    

    afficher_matrice_char(recherche_hash("83020643a5c92bb5b6ee269146c64a9b989bf203f0fc1348f1479bc637469056", file));

    

    // lecture_par_ligne(file);



    // while (!feof(file))
    // {
    //     lecture_par_ligne(file);
    // }
    
    

    // printf("===================================================\n");



    fclose(file);
    


    
    


    return 0;
}
