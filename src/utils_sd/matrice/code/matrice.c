#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"

typedef struct t_mat_char
{
    int ligne;
    int col;
    int nbelem;
    char ***matrice;
} t_mat_char_star_dyn;

t_mat_char_star_dyn *creer_matrice(int ligne, int colonne)
{
    t_mat_char_star_dyn *m = malloc(sizeof(struct t_mat_char));
    m->ligne = ligne;
    m->col = colonne;
    m->nbelem = 0;
    m->matrice = (char ***)malloc(ligne * sizeof(char **));
    for (int i = 0; i < ligne; i++)
    {
        m->matrice[i] = (char **)malloc(colonne * sizeof(char *));
        for (int j = 0; j < colonne; j++)
        {
            m->matrice[i][j] = "";
        }
    }
    return m;
}

t_mat_char_star_dyn *inserer_matrice_char(char *chaine, t_mat_char_star_dyn *mat)
{
    int no = mat->nbelem;
    int ligne = mat->ligne;
    int colonne = mat->col;
    if (no < (ligne) * (colonne))
    {
        // recuperer la case en fonction du nombre d'element
        int l = no / colonne;
        int c = no % colonne;
        mat->matrice[l][c] = chaine;
        (mat->nbelem)++;
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