#ifndef __JUGEMENT_H__
#define __JUGEMENT_H__
#include "utils_sd/matrice.h"

/**
 * @brief méthode qui retourne le gagnant d'un scrutin apr jugement majoritaire
 * 
 * @param mat matrice dérivée du CSV contenant les ballots 
 */
void methode_jugement(t_mat_char_star_dyn *mat);
#endif