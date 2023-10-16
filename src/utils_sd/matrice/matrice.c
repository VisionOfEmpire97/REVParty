#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

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

    return m;
}

t_mat_char_star_dyn *inserer_matrice_char(char *chaine, t_mat_char_star_dyn *mat)
{
    int no = mat->nb_elem;
    int ligne = mat->ligne;
    int colonne = mat->col;
   
    if(ligne==1){
         mat->col++;
         colonne = mat->col;
        realloc(mat->matrice[0],colonne * sizeof(char *));

    }

    if (no < (ligne) * (colonne))
    {
        // recuperer la case en fonction du nombre d'element
        int l = no / colonne;
        int c = no % colonne;
        mat->matrice[l][c] = chaine;
        (mat->nb_elem)++;
    }      
    

    return mat;
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
    int L = mat->ligne;
    int C = mat->col;
    for (int i = 0; i < L; i++)
    {
        free(M[i]);
    }
    free(M);
    free(mat);
}
t_mat_char_star_dyn *ajouter_ligne(t_mat_char_star_dyn *mat){
    mat->ligne++;
    realloc(mat->matrice,((mat->ligne)* sizeof(char **)));
    return mat;
}