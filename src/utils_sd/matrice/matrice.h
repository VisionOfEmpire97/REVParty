#ifndef __MATRICE_H__
#define __MATRICE_H__
#include "stdbool.h"
#include "stdbool.h"
#define MAX_CHAR 500
/// \brief structure de donnee matrice
/// \struct t_mat_char_star_dyn une structure de matrice de chaine dynamique
typedef struct t_mat_char t_mat_char_star_dyn;

/// \brief creation d'une matrice vide
/// \param ligne nombre de ligne de la matrice
/// \param colonne nombre de colonne de la matrice
/// \return une matrice de charactere bien initialisee avec la chaine vide

t_mat_char_star_dyn *creer_matrice();
t_mat_char_star_dyn *creer_matrice();
/// \brief insertion dans une matrice
/// \param chaine l'element a inserer
/// \param mat la matrice dans laquelle on va inserer l'element
/// \return 0 si la valeur a bien été inséré -1 sinon

int inserer_matrice_char(char *chaine, t_mat_char_star_dyn *mat);

/// \brief faire l'affichage d'une matrice
/// \param mat la matrice a afficher
void afficher_matrice_char(t_mat_char_star_dyn *mat);

/// \brief liberer la memoire alloué a la structure
/// \param mat la structure a liberer
void supprimer_matrice_char(t_mat_char_star_dyn *mat);

/// \brief ajouter une ligne a la matrice
/// \param mat
/// \return la matyrice en entree avec une ligne ajouté
t_mat_char_star_dyn *ajouter_ligne(t_mat_char_star_dyn *mat);

/// \brief renvoie si la matrice est vide ou non
/// \param mat
bool est_matrice_vide(t_mat_char_star_dyn *mat);

/// \brief ajouter une ligne a la matrice
/// \param mat
/// \return la matyrice en entree avec une ligne ajouté
t_mat_char_star_dyn *ajouter_ligne(t_mat_char_star_dyn *mat);

/// \brief récuperer la valeur a une case precise de la matrice
/// \param mat
/// \param ligne la ligne a laquelle on veut acceder
/// \param colonne la colonne a laquelle on veut acceder
/// \return la valeur a la case donnée ou NULL si l'indice est incorrecte
char * valeur_matrice_char_indice(t_mat_char_star_dyn *mat,int ligne,int colonne);
#endif