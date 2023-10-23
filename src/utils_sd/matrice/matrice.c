#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include "stdbool.h"
#include "string.h"

typedef struct t_mat_char
{
    int ligne;
    int col;
    int nb_elem;
    char ***matrice;
} t_mat_char_star_dyn;

t_mat_char_star_dyn *creer_matrice()
{
    t_mat_char_star_dyn *m = malloc(sizeof(struct t_mat_char));
    m->ligne = 0;
    m->col = 0;
    m->nb_elem = 0;
    m->matrice = (char ***)malloc(sizeof(char **));
    m->matrice[0] = (char **)malloc(sizeof(char *));
    return m;
}

int inserer_matrice_char(char *chaine, t_mat_char_star_dyn *mat)
{
    int no = mat->nb_elem;

    if ((mat->ligne) == 1)
    {

        mat->col++;

        mat->matrice[0] = (char **)realloc(mat->matrice[0], (mat->col) * sizeof(char *));
    }
    int ligne = mat->ligne;
    int colonne = mat->col;

    if (no < (ligne) * (colonne))
    {
        // recuperer la case en fonction du nombre d'element
        int l = no / colonne;
        int c = no % colonne;
        char *element;
        element = (char *)malloc(MAX_CHAR);
        strcpy(element, chaine);
        mat->matrice[l][c] = element;
        (mat->nb_elem)++;
    }
    else
    {
        return -1;
    }

    return 0;
}

void afficher_matrice_char(t_mat_char_star_dyn *mat)
{
    char ***M = mat->matrice;
    int L = mat->ligne;
    int C = mat->col;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("%5s ", M[i][j]);
        }
        printf("\n");
    }
}

void supprimer_matrice_char(t_mat_char_star_dyn *mat)
{
    char ***M = mat->matrice;
    int lig = mat->ligne;
    int col = mat->col;
    for (int i = 0; i < lig; i++)
    {
        for (int j = 0; j < col; j++)
        {
            free(M[i][j]);
        }
        free(M[i]);
    }
    free(M);
    free(mat);
}

t_mat_char_star_dyn *ajouter_ligne(t_mat_char_star_dyn *mat)
{
    (mat->ligne)++;

    (mat->matrice) = (char ***)realloc((mat->matrice), ((mat->ligne) * sizeof(char **)));
    for (int i = 1; i < (mat->ligne); i++)
    {
        mat->matrice[i] = (char **)malloc((mat->col) * sizeof(char *));
        for (int j = 0; j < (mat->col); j++)
        {
            mat->matrice[i][j] = "";
        }
    }
    return mat;
}
char * valeur_matrice_char_indice(t_mat_char_star_dyn *mat,int ligne,int colonne){
    if ((ligne>=0 && ligne<(mat->ligne))&&(colonne>=0 && colonne<(mat->col))){
        return mat->matrice[ligne][colonne];
    }
    return NULL;
}
int recuperer_nb_colonnes(t_mat_char_star_dyn *mat){
    return mat->col;
}

bool est_matrice_vide(t_mat_char_star_dyn *mat)
{
    return mat->nb_elem == 0;
}