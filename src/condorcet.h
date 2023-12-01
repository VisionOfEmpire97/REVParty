/**
 * \author Équipe 001 (ZERKANI Yanis)
 * \date 20 Novembre 2023
 * \brief Programme de tri de votes selon la méthode de Condorcet, 
 * accompagnée des différents solveurs du paradoxe de condorcet,
 * à savoir Condorcet Minimax, Condorcet Schulze, Condorcet Paires.
 * Les trois résolutions de paradoxe implémentés peuvent renvoyer des sommets différents
 * \file condorcet.h
 */

#include <stdlib.h>
#include <stdio.h>
#include "utils_sd/graph.h"

/**
 * \brief Retourne le vainqueur du suffrage selon la méthode de Condorcet. Si vainqueurCondorcet == NULL,
 * on doit faire appel aux fonctions de résolution du paradoxe de Condorcet.
 * 
 * \param[in] matrice Le matrice de char du fichier csv du scrutin, qu'on transformera en graphe
 * \param[out] vainqueur Le vainqueur, s'il existe, selon la méthode Condorcet.
 *
 */
sommet *vainqueurCondorcet(t_mat_char_star_dyn *matrice);

/**
 * \brief Première proposition de résolution du paradoxe de Condorcet: la méthode Minimax.
 * 
 * \details Pour chacun des candidats, on regarde le pire des scores qu’il ferait dans ses
 * différents faces-à-faces, puis on déclare élu celui des candidats dont le pire des scores est le meilleur.
 * 
 * \param[in] matrice Le matrice de char du fichier csv du scrutin, qu'on transformera en graphe
 * \param[out] vainqueur Le vainqueur, selon la méthode Condorcet Minimax.
 */
sommet *vainqueurCondorcetMinimax(t_mat_char_star_dyn *matrice);

/**
 * \brief Seconde proposition de résolution du paradoxe de Condorcet: la méthode Paires.
 * 
 * 
 * \details Pour cette méthode, on devra :
 *   
 * (*) Verifier si un cycle est formé
 * (*) Supprimer l'arc de poids minimal de ce cycle
 * (*) Répeter jusqu'a obtenir un vainqueur de Condorcet (P- == 0)
 * 
 * \param[in] matrice Le matrice de char du fichier csv du scrutin, qu'on transformera en graphe
 * \param[out] vainqueur Le vainqueur, selon la méthode Condorcet Paires.
*/
sommet *vainqueurCondorcetPaires(t_mat_char_star_dyn *matrice);

/**
 * \brief Troisième proposition de résolution du paradoxe de Condorcet: la méthode Schulze.
 * 
 * \details En guise d'explication concise de la méthode Schulze, il est nécessaire de retirer dans le graphe
 * les arcs de poids minimal jusqu'à ce qu'un des sommets gagne tous ses duels (ou n'en perd aucun), est donc
 * se désigne comme vainqueur de Condorcet.
 * 
 * \param[in] matrice Le matrice de char du fichier csv du scrutin, qu'on transformera en graphe
 * \param[out] vainqueur Le vainqueur, selon la méthode Condorcet Schulze.
*/
sommet *vainqueurCondorcetSchulze(t_mat_char_star_dyn *matrice);

/**
 * \brief Fonction permettant de retrouver l'arc de poids minimal d'un graphe.
 * Fonction utile pour le fonctionnement des méthodes Paires et Schulze.
 * 
 * \param[in] graph Le graphe pondéré des duels.
 * \param[out] arcPoidsMin L'arc de poids minimal.
*/
arc *arcDePoidsMinimal(graph *graph);