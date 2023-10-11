/// \author Equipe 001
/// \date 23 Septembre 2023
/// \file le fichier lecture_csv devrait prendre un fichier CSV 
///       et retourner une matrice de type t_mat_char_star_dyn ????

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

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

    while (fgets(buffer, sizeof(buffer), file)!=NULL)
    {
        char* tok = strtok(buffer, ",");

        int data;
        sscanf(tok, "%d", &data);
        // tok = strtok(NULL, ","); //On passe à la colonne suivante
        // tok = strtok(NULL, ",");
        // tok = strtok(NULL, ",");
        // tok = strtok(NULL, ",");
        // printf("%s\n", tok);
        printf("\n");
        printf("%d\n", data);

    }
    
    fclose(file);


    
    


    return 0;
}
