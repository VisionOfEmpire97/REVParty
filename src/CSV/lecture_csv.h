/** 
 * \author Équipe 001 (ZERKANI Yanis)
 * \date 16 Octobre 2023
 * \brief Programme permettant de lire un fichier CSV (Comma Separated Value) et de renvoyer son contenu sous forme de matrice.
 * La matrice est de type t_mat_char_star_dyn.
 * \file
 */
#include <stdio.h>
#include "../utils_sd/matrice/matrice.h"

/** \defgroup Programme Lecteur de fichier .csv
 @{
 */

/** \defgroup GetLine Fonctions permettant de récupérer une ligne précise du fichier csv
 @{
 */

/** 
 * \brief Lecture et traduction en matrice de l'entête du fichier csv
 * \param[in] file le fichier à parser
 * \param[out] mat la matrice contenant la premiere ligne du fichier
 */
t_mat_char_star_dyn *lecture_entete(const char *file);

/**
 * \brief Recherche de la ligne contenant le hash
 * \param[in] hash la chaîne de caractères recherchée
 * \param[in] file le fichier à parser
 * \param[out] mat la matrice contenant la ligne dans le fichier (matrice vide si aucune ligne ne correspond)
 */
t_mat_char_star_dyn *recherche_hash(char *hash, const char *file);

/**@}*/
//t_mat_char_star_dyn *recherche_indice(int i_deb, int i_fin, int j_deb, int j_fin);

/** \defgroup UtilityFunctors Fonctions de modification de la matrice
 @{
 */

t_mat_char_star_dyn *lecture_fichier(const char *nom_fichier);

/**
 * \brief Permet d'insérer une ligne entière dans la matrice
 * \param[in] ligne ligne à insérer
 * \param[in] mat matrice destination
 */
void inserer_ligne_matrice(char *ligne, t_mat_char_star_dyn *mat);
/**@}*/
