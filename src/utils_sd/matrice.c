#include <stdio.h>
#include <stdlib.h>
#include "matrice.h"
#include "stdbool.h"
#include "string.h"

//------------------MATRICE CHAR------------------------
typedef char ***t_matrice;
typedef struct t_mat_char
{
    int ligne;
    int col;
    int nb_elem;
    t_matrice matrice;
} t_mat_char_star_dyn;

t_mat_char_star_dyn *creer_matrice_char()
{

    t_mat_char_star_dyn *m = malloc(sizeof(struct t_mat_char));
    m->ligne = 0;
    m->col = 0;
    m->nb_elem = 0;
    m->matrice = NULL;
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
    t_matrice M = mat->matrice;
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

    (mat->matrice) = (t_matrice)realloc((mat->matrice), ((mat->ligne) * sizeof(char **)));
    if ((mat->ligne) == 1)
    {
        mat->matrice[(mat->ligne) - 1] = NULL;
    }
    else
    {
        mat->matrice[(mat->ligne) - 1] = malloc((mat->col) * sizeof(char *));
    }
    return mat;
}
char *valeur_matrice_char_indice(t_mat_char_star_dyn *mat, int ligne, int colonne)
{
    if ((ligne >= 0 && ligne < (mat->ligne)) && (colonne >= 0 && colonne < (mat->col)))

    {
        return mat->matrice[ligne][colonne];
    }
    return NULL;
}
int recuperer_nb_colonnes(t_mat_char_star_dyn *mat)
{
    return mat->col;
}
int recuperer_nb_lignes(t_mat_char_star_dyn *mat)
{
    return mat->ligne;
}
bool est_matrice_vide(t_mat_char_star_dyn *mat)
{
    return mat->nb_elem == 0;
}

char **recuperer_candidats(t_mat_char_star_dyn *mat)
{
    return mat->matrice[0] + 4;
}
//--------------------------MATRICE INT----------------------------

t_mat_int_dyn *creer_matrice_int(int ligne, int colonne)
{
    t_mat_int_dyn *m = malloc(sizeof(struct t_mat_int));
    m->ligne = ligne;
    m->col = colonne;
    m->matrice = (int **)malloc(ligne * sizeof(int *));
    for (int i = 0; i < ligne; i++)
    {
        m->matrice[i] = calloc(colonne, sizeof(int));
    }
    return m;
}

t_mat_int_dyn *construire_mat_duel(t_mat_char_star_dyn *mat)
{

    int ligne = mat->ligne;
    int colonne = mat->col, val1, val2;
    t_mat_int_dyn *mat_duel = creer_matrice_int(colonne - 4, colonne - 4);
    if (!est_matrice_vide(mat))
    {
        for (int i = 1; i < ligne; i++)
        {
            for (int j = 4; j < colonne; j++)
            {
                val1 = atoi(mat->matrice[i][j]);
                for (int k = j + 1; k < colonne; k++)
                {
                    val2 = atoi(mat->matrice[i][k]);

                    if (val1 > val2)
                    {
                        mat_duel->matrice[j - 4][k - 4]++;
                    }
                    else if (val1 < val2)
                    {
                        mat_duel->matrice[k - 4][j - 4]++;
                    }
                    else
                    {
                        mat_duel->matrice[k - 4][j - 4]++;
                        mat_duel->matrice[j - 4][k - 4]++;
                    }
                }
            }
        }
    }
    return mat_duel;
}
t_mat_int_dyn *transformer_mat_char_mat_duel(t_mat_char_star_dyn *mat)
{
    int ligne = mat->ligne;
    int colonne = mat->col;
    t_mat_int_dyn *mat_duel = creer_matrice_int(colonne, colonne);
    for (int i = 1; i < ligne; i++)
    {
        for (int j = 0; j < colonne; j++)
        {
            mat_duel->matrice[i][j] = atoi(mat->matrice[i][j]);
        }
    }
    return mat_duel;
}
void afficher_matrice_int(t_mat_int_dyn *mat)
{
    int **M = mat->matrice;
    int L = mat->ligne;
    int C = mat->col;
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < C; j++)
        {
            printf("%5d ", M[i][j]);
        }
        printf("\n");
    }
}
void supprimer_matrice_int(t_mat_int_dyn *mat)
{
    int **M = mat->matrice;
    int lig = mat->ligne;

    for (int i = 0; i < lig; i++)
    {
        {
            free(M[i]);
        }
    }
    free(M);
    free(mat);
}
