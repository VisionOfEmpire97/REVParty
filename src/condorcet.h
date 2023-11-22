/**
 * \author Équipe 001 (ZERKANI Yanis)
 * \date 20 Novembre 2023
 * \brief Programme de tri de votes selon la méthode de Condorcet, accompagnée des différents solveurs du paradoxe de condorcet,
 * à savoir Condorcet Minimax, Condorcet Schulze, Condorcet Paires
 * \file condorcet.h
 */

#include <stdlib.h>
#include <stdio.h>
#include "utils_sd/graph.h"

/**
 * \brief Retourne le vainqueur du suffrage selon la méthode de Condorcet. Si vainqueurCondorcet == NULL,
 * on doit faire appel aux fonctions de résolution du paradoxe de Condorcet.
 *
 * \param[in] graph La matrice de duels sous forme de graph.
 * \param[out] vainqueur Le vainqueur, s'il existe, selon la méthode Condorcet.
 *
 */
sommet *vainqueurCondorcet(graph *graph);

/**
 * \brief Première proposition de résolution du paradoxe de Condorcet: la méthode Minimax.
 * Pour chacun des candidats, on regarde le pire des scores qu’il ferait dans ses
 * différents faces-à-faces, puis on déclare élu celui des candidats dont le pire des scores est le meilleur.
 * \param[in] graph La matrice de duels sous forme de graph.
 * \param[out] vainqueur Le vainqueur, selon la méthode Condorcet Minimax.
 */
sommet *vainqueurCondorcetMinimax(graph *graph);

/**
 * \brief Seconde proposition de résolution du paradoxe de Condorcet: la méthode Paires.

 * \param[in] graph La matrice de duels sous forme de graph.
 * \param[out] vainqueur Le vainqueur, selon la méthode Condorcet Paires.
*/
sommet *vainqueurCondorcetPaires(graph *graph);

/**
 * \brief Seconde proposition de résolution du paradoxe de Condorcet: la méthode Schulze.

 * \param[in] graph La matrice de duels sous forme de graph.
 * \param[out] vainqueur Le vainqueur, selon la méthode Condorcet Schulze.
*/
sommet *vainqueurCondorcetSchulze(graph *graph);
