/**
 * @file jugement.h
 * @author ROSET Nathan (nathroset97@gmail.com)
 * @brief déclaration de la méthode de jugement majoritaire
 * @version 1
 * @date 04-12-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __JUGEMENT_H__
#define __JUGEMENT_H__
#include "utils_sd/matrice.h"

/**
 * @brief méthode qui retourne le gagnant d'un scrutin par jugement majoritaire
 * dans le fichier de log si ce dernier à été spécifié
 * @param mat matrice dérivée du CSV contenant les ballots 
 */
void methode_jugement(t_mat_char_star_dyn *mat);
#endif