/**
 * \author Équipe 001 (ZERKANI Yanis)
 * \date 16 Octobre 2023
 * \brief Programme permettant de lire un fichier CSV (Comma Separated Value) et de renvoyer son contenu sous forme de matrice.
 * La matrice est de type t_mat_char_star_dyn.
 * \file lecture_csv.h
 */
#include <stdio.h>
#include "../utils_sd/matrice.h"

/** \defgroup CSV Lecteur de fichier csv
 \{
 * \brief Programme permettant de lire un fichier CSV (Comma Separated Value) et de renvoyer son contenu sous forme de matrice. 
 * La matrice est de type t_mat_char_star_dyn
 */

/** \defgroup GetLine Fonctions permettant de récupérer le fichier csv entier ou une ligne précise.
 @{
 * \brief Trois fonctions seront proposées ici: une fonction de lecture de l'entête, une fonction de récupération d'une ligne précise
 * contenant le hash demandé, et une fonction qui retourne le fichier dans son intégrité.
 */

/**
 * \brief Lecture et traduction en matrice de l'entête du fichier csv
 * \param[in] file Le fichier à parser.
 * \returns La matrice de char contenant la premiere ligne du fichier.
 */
t_mat_char_star_dyn *lecture_entete(const char *file);

/**
 * \brief Lecture et traduction en matrice de l'entête du fichier csv
 * \param[in] file Le fichier à parser.
 * \returns La matrice de char contenant le fichier.
 */

t_mat_char_star_dyn *lecture_fichier(const char *nom_fichier);

/**
 * \brief Recherche de la ligne contenant le hash
 * \param[in] hash La chaîne de caractères recherchée.
 * \param[in] file Le fichier à parser.
 * \returns La matrice de char contenant la ligne dans le fichier (matrice vide si aucune ligne ne correspond).
 */
t_mat_char_star_dyn *recherche_hash(char *hash, const char *file);

/**@}*/
