/// \author Equipe 001 (ZERKANI Yanis)
/// \date 16 Octobre 2023
/// \brief Programme permettant de lire un fichier CSV et de renvoyer son contenu sous forme de matrice de type t_mat_char_star_dyn

#include <stdio.h>
#include "../utils_sd/matrice/matrice.h" 

/// \brief Lecture et traduction en matrice du fichier csv ligne par ligne
/// \param[in] file le fichier à parser
/// \param[out] mat la matrice contenant la premiere ligne du fichier
/// \note Appeler la fonction n fois pour lire n lignes
t_mat_char_star_dyn *lecture_par_ligne(const char *file);

/// \brief Recherche de la ligne contenant le hash
/// \param hash la chaine de caractères recherchée
/// \param file le fichier à parser
/// \param[out] mat la matrice contenant la ligne dans le fichier (matrice vide si aucune ligne ne correspond)
t_mat_char_star_dyn *recherche_hash(char * hash, const char *file);

t_mat_char_star_dyn *recherche_indice(int i_deb, int i_fin, int j_deb, int j_fin);

/// \brief Permet d'inserer une chaine dans la matrice
/// \param chaine chaine à insérer
/// \param mat matrice destination

void inserer_chaine_matrice(char * chaine, t_mat_char_star_dyn *mat);