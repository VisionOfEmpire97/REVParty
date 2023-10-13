/// \author Equipe 001
/// \date 23 Septembre 2023
/// \file le fichier lecture_csv devrait prendre un fichier CSV 
///       et retourner une matrice de type t_mat_char_star_dyn ????

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lecture_csv.h"

#define N 10
#define SEPARATEUR ","

char data[N], data2[N], data3[N], data4[N], data5[N];

char** lecture_par_ligne(char buffer[],FILE* file ){

    fgets(buffer, sizeof(buffer), file);
    printf("%s", buffer);
    char* tok = strtok(buffer, SEPARATEUR);
    tok = strcat(tok,strtok(NULL, SEPARATEUR));
    tok = strcat(tok,strtok(NULL, SEPARATEUR));
    tok = strcat(tok,strtok(NULL, SEPARATEUR));
    tok = strcat(tok,strtok(NULL, SEPARATEUR));
    sscanf(tok, "%s", data); 
    printf("%s\n", data);
    return data;
}

char** lecture_par_col(char buffer[], FILE* file){
    while (fgets(buffer, sizeof(buffer), file)!=NULL)
    {
        printf("%s\n", buffer);
        char* tok = strtok(buffer, SEPARATEUR);
        sscanf(tok, "%s", data); 
        printf("%s\n", data);
    }
    return data;

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

    

        
    // printf("%s",lecture_par_ligne(buffer, file));



    // sscanf(tok, "%s", data); 
    // printf("%s\n", data); 
    
    // lecture_par_col(buffer, file);
    
    fclose(file);
    


    
    


    return 0;
}
