#ifndef __MATRICE_H__
#define __MATRICE_H__

/// \brief structure de donnee matrice
/// \struct t_mat_char_star_dyn une structure de matrice de chaine dynamique
typedef struct t_mat_char t_mat_char_star_dyn;

/// \brief creation d'une matrice vide
/// \param ligne nombre de ligne de la matrice
/// \param colonne nombre de colonne de la matrice
/// \return une matrice de charactere bien initialisee avec la chaine vide

t_mat_char_star_dyn *creer_matrice(int ligne, int colonne);

/// \brief insertion dans une machine
/// \param chaine l'element a inserer
/// \param mat la matrice dans laquelle on va inserer l'element
/// \return la nouvelle matrice avec l'element place dans la matrice
t_mat_char_star_dyn *inserer_matrice_char(char *chaine, t_mat_char_star_dyn *mat);

/// \brief faire l'affichage d'une matrice
/// \param mat la matrice a afficher
void afficher_matrice_char(t_mat_char_star_dyn *mat);

/// \brief liberer la memoire alloué a la structure
/// \param mat la structure a liberer
void supprimer_matrice_char(t_mat_char_star_dyn *mat);

#endif