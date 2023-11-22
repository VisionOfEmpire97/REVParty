
/**
 * \author Équipe 001 (JOSEPH REMY)
 * \date 16 Octobre 2023
 * \brief Fichier de definition de la structure de donnée
 * \file matrice.h
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
 * \defgroup Type Type de données
 * Types de données utilisés afin de manipuler des matrices
 *@{
 */
/**
 * \brief Structure de donnée matrice de chaîne dynamique
 * \struct t_mat_char_star_dyn une structure
 * Matrice de n lignes , m colonnes de taille non statique
 */
/**
 * \defgroup Matrice de chaine de charactere
 * @{
 */

typedef struct t_mat_char t_mat_char_star_dyn;

/** \defgroup Constructeur Constructeurs et destructeurs de matrice
 *@{


 * \brief Creation d'une matrice vide.
 * \return Une matrice de caractères vide
 */
t_mat_char_star_dyn *creer_matrice_char();

/**
 * \brief Insertion dans une matrice de chaîne
 * \param chaine L'element a insérer
 * \param mat La matrice dans laquelle on va insérer l'element
 * \return 0 si la valeur a bien été inséré -1 sinon
 */
int inserer_matrice_char(char *chaine, t_mat_char_star_dyn *mat);

/**
 * \brief Faire l'affichage d'une matrice sur stdout.
 * \param mat La matrice a afficher
 */
void afficher_matrice_char(t_mat_char_star_dyn *mat);

/**
 * \brief Supprime la matrice et libère la mémoire allouée
 * \param mat La structure à libérer
 */
void supprimer_matrice_char(t_mat_char_star_dyn *mat);

char **recuperer_candidats(t_mat_char_star_dyn *mat);
/**
 * \brief Ajoute une ligne a la matrice
 * \param mat
 * \return La matrice en entree avec une ligne ajoutée
 */

t_mat_char_star_dyn *ajouter_ligne(t_mat_char_star_dyn *mat);

/**
 * \brief Indique si la matrice est vide ou non
 * \param mat
 * \return true si la matrice est vide
 * \return false si il y a au moins un element dans la matrice
 */
bool est_matrice_vide(t_mat_char_star_dyn *mat);

/**
 * \brief Récupérer la valeur a une position precise de la matrice
 * \param mat
 * \param ligne La ligne a laquelle on veut accéder
 * \param colonne La colonne a laquelle on veut accéder
 * \return La valeur a la case donnée ou NULL si l'indice est incorrecte
 */
char *valeur_matrice_char_indice(t_mat_char_star_dyn *mat, int ligne, int colonne);

/**
 * \brief Récupérer le nombre de colonne de la matrice
 * \param mat
 * \return Le nombre de colonnes de la matrice
 */
int recuperer_nb_colonnes(t_mat_char_star_dyn *mat);

/**
 * \brief Récupérer le nombre de colonne de la matrice
 * \param mat
 * \return Le nombre de lignes de la matrice
 */
int recuperer_nb_lignes(t_mat_char_star_dyn *mat);
/**@}*/

/**
 * \defgroup Matrice de d'entier
 * @{
 */

typedef struct t_mat_int
{
    int ligne;
    int col;
    int **matrice;
} t_mat_int_dyn;

/**
 * @brief crée une matrice d'entier
 * 
 * @param ligne 
 * @param colonne 
 * @return t_mat_int_dyn* 
 */
t_mat_int_dyn *creer_matrice_int(int ligne, int colonne);

/**
 * \brief Transforme une matrice de chaine lu du CSV en matrice de duel
 *
 * \param mat
 * \return t_mat_int_dyn* Une matrice de duel
 * */

t_mat_int_dyn *construire_mat_duel(t_mat_char_star_dyn *mat);

/**
 * \brief Affiche une matrice d'entiers
 *
 * @param mat
 */
void afficher_matrice_int(t_mat_int_dyn *mat);
int recuperer_nb_colonnes_int(t_mat_int_dyn *mat);
/**
 * @brief supprime une matrice et libere la memoire occupee par celle ci
 *
 * @param mat
 */
void supprimer_matrice_int(t_mat_int_dyn *mat);
/** @} */

/**@}*/
#endif