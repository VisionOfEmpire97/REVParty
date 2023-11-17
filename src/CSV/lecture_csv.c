#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lecture_csv.h"

#define SEPARATEUR ","
#define BUFF_SIZE 500

t_mat_char_star_dyn *lecture_entete(const char *nom_fichier)
{

    FILE *file = fopen(nom_fichier, "r");
    t_mat_char_star_dyn *mat = creer_matrice_char();
    char buffer[BUFF_SIZE];

    fgets(buffer, sizeof(buffer), file);
    ajouter_ligne(mat);
    inserer_ligne_matrice(buffer, mat);
    fclose(file);
    return mat;
}

t_mat_char_star_dyn *lecture_fichier(const char *nom_fichier)
{

    FILE *file = fopen(nom_fichier, "r");
    t_mat_char_star_dyn *mat = creer_matrice_char();
    char buffer[BUFF_SIZE];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        ajouter_ligne(mat);
        inserer_ligne_matrice(buffer, mat);
    }
    fclose(file);
    return mat;
}

void inserer_ligne_matrice(char *ligne, t_mat_char_star_dyn *mat)
{
    char chaine[BUFF_SIZE];
    strcpy(chaine, ligne);
    size_t length = strlen(chaine);
    if (chaine[length - 1] == '\n')
        chaine[--length] = '\0';

    char *tok = strtok(chaine, SEPARATEUR);
    while (tok != NULL)
    {
        inserer_matrice_char(tok, mat);
        tok = strtok(NULL, SEPARATEUR);
    }
}

t_mat_char_star_dyn *recherche_hash(char *hash, const char *nom_fichier)
{

    FILE *file = fopen(nom_fichier, "r");

    t_mat_char_star_dyn *mat = creer_matrice_char();
    char buffer[BUFF_SIZE];
    char buffer2[BUFF_SIZE];
    int found = 0;

    while (fgets(buffer, sizeof(buffer), file) != NULL && !found)
    {
        strcpy(buffer2, buffer);
        char *tok = strtok(buffer, SEPARATEUR);
        tok = strtok(NULL, SEPARATEUR);
        tok = strtok(NULL, SEPARATEUR);
        tok = strtok(NULL, SEPARATEUR);

        if (!strcmp(tok, hash))
        {
            ajouter_ligne(mat);
            inserer_ligne_matrice(buffer2, mat);
            found = 1;
        }
    }
    fclose(file);
    return mat;
}
