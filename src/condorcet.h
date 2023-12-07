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

/** \defgroup Condorcet Methodes de Condorcet
 *@{
 */


/**
 * \brief Première proposition de résolution du paradoxe de Condorcet: la méthode Minimax.
 * 
 * \details Pour chacun des candidats, on regarde le pire des scores qu’il ferait dans ses
 * différents faces-à-faces, puis on déclare élu celui des candidats dont le pire des scores est le meilleur.
 * 
 * \param[in] matrice Le matrice de duels du fichier csv du scrutin, qu'on transformera en graphe.
 * \param[in] entete La partie de l'entete du fichier csv, où l'on retrouvera les candidats.
 * \param[in] nbElecteurs Le nombre d'electeurs ayant participé au scrutin.
 */
void condorcet_minimax(t_mat_int_dyn *matrice, char **entete, int nbElecteurs);

/**
 * \brief Seconde proposition de résolution du paradoxe de Condorcet: la méthode Paires.
 * 
 * 
 * \details Pour cette méthode, on devra :
 * 
 *   
 * \details (*) Verifier si un cycle est formé 
 * \details (*) Supprimer l'arc de poids minimal de ce cycle
 * \details (*) Répeter jusqu'a obtenir un vainqueur de Condorcet (d- == 0)
 * 
 * \param[in] matrice Le matrice de duels du fichier csv du scrutin, qu'on transformera en graphe.
 * \param[in] entete La partie de l'entete du fichier csv, où l'on retrouvera les candidats.
 * \param[in] nbElecteurs Le nombre d'electeurs ayant participé au scrutin.
*/
void condorcet_paires(t_mat_int_dyn *matrice, char **entete, int nbElecteurs);

/**
 * \brief Troisième proposition de résolution du paradoxe de Condorcet: la méthode Schulze.
 * 
 * \details En guise d'explication concise de la méthode Schulze, il est nécessaire de retirer dans le graphe
 * les arcs de poids minimal jusqu'à ce qu'un des sommets gagne tous ses duels (ou n'en perd aucun), est donc
 * se désigne comme vainqueur de Condorcet.
 * 
 * \param[in] matrice Le matrice de duels du fichier csv du scrutin, qu'on transformera en graphe.
 * \param[in] entete La partie de l'entete du fichier csv, où l'on retrouvera les candidats.
 * \param[in] nbElecteurs Le nombre d'electeurs ayant participé au scrutin.
*/
void condorcet_Schulze(t_mat_int_dyn *matrice, char **entete, int nbElecteurs);

/**@}*/