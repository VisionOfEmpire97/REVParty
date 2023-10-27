/**
 * \author Equipe 001 (JOSEPH REMY)
 * \date 16 Octobre 2023
 * \brief Fichier de definition de la structure de donnée
 */
#ifndef __MATRICE_H__
#define __MATRICE_H__
#include "stdbool.h"
#include "stdbool.h"
#define MAX_CHAR 500

/** \defgroup ADTMatrice Matrice
 Documentation de l'implémentation de la structure de données Matrice
 *@{
 *
 */

/**
 * \defgroup Type Type de données Matrice de chaines
 *@{
 * \brief Structure de donnee matrice.
 * \struct t_mat_char_star_dyn une structure de matrice de chaine dynamique
 */

typedef struct t_mat_char t_mat_char_star_dyn;
/**@}*/

/** \defgroup Constructeur Constructeurs et destructeurs de matrice
 *@{
 * \brief Creation d'une matrice vide.
 * \return Une matrice de charactere vide
 */
t_mat_char_star_dyn *creer_matrice();

/**
 * \brief Insertion dans une matrice de chaine
 * \param chaine L'element a inserer
 * \param mat La matrice dans laquelle on va inserer l'element
 * \return 0 si la valeur a bien été inséré -1 sinon
 */
int inserer_matrice_char(char *chaine, t_mat_char_star_dyn *mat);

/**
 * \brief Faire l'affichage d'une matrice sur stdout.
 * \param mat La matrice a afficher
 */
void afficher_matrice_char(t_mat_char_star_dyn *mat);

/**
 * \brief Supprime et libere la memoire allouée a la structure
 * \param mat La structure à liberer
 */
void supprimer_matrice_char(t_mat_char_star_dyn *mat);

/**
 * \brief Ajouter une ligne a la matrice
 * \param mat
 * \return La matrice en entree avec une ligne ajoutée
 */

t_mat_char_star_dyn *ajouter_ligne(t_mat_char_star_dyn *mat);

/**
 * \brief Renvoie si la matrice est vide ou non
 * \param mat
 * \return true si la matrice est vide
 * \return false si il y a au moins un element dans la matrice
 */
bool est_matrice_vide(t_mat_char_star_dyn *mat);

/**
 * \brief Récuperer la valeur a une case precise de la matrice
 * \param mat
 * \param ligne La ligne a laquelle on veut accéder
 * \param colonne La colonne a laquelle on veut accéder
 * \return La valeur a la case donnée ou NULL si l'indice est incorrecte
 */
char *valeur_matrice_char_indice(t_mat_char_star_dyn *mat, int ligne, int colonne);

/**
 * \brief Récuperer le nombre de colonne de la matrice
 * \param mat
 * \return Le nombre de colonnes de la matrice
 */
int recuperer_nb_colonnes(t_mat_char_star_dyn *mat);
/**@}*/
/**@*/
#endif