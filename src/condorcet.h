/**
 * \author Équipe 001 (ZERKANI Yanis)
 * \date 20 Novembre 2023
 * \brief Programme de tri de votes selon la méthode de Condorcet, 
 * accompagnée des différents solveurs du paradoxe de condorcet,
 * à savoir Condorcet Minimax, Condorcet Schulze, Condorcet Paires.
 * Les trois résolutions de paradoxe implémentés peuvent renvoyer des sommets différents
 * \file condorcet.h
 */
#ifndef __CONDORCET_H__
#define __CONDORCET_H__
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
 * Si plusieurs vainqueurs ont le meme score de pire défaite, on les fait s'affronter en duel deux à deux,
 * avec le graphe d'origine comme référentiel.
 * 
 * \param[in] matrice Le matrice de duels du fichier csv du scrutin, qu'on transformera en graphe.
 * \param[in] entete La partie de l'entete du fichier csv, où l'on retrouvera les candidats.
 * \param[in] nbElecteurs Le nombre d'electeurs ayant participé au scrutin.
 */
void condorcet_minimax(t_mat_int_dyn *matrice, char **entete, int nbElecteurs);

/**
 * \brief Seconde proposition de résolution du paradoxe de Condorcet: la méthode des paires par ordre croissant.
 * 
 * 
 * \details 
 * 
 * Chaque électeur range les candidats par ordre de préférence. 
 * Comme dans toute méthode Condorcet, toutes les confrontations par paires sont organisées. 
 * On établit alors un graphe orienté pondéré :
 * 
 * On classe chaque arc par poids décroissant, selon un ordre strict (sans ex-aequo).
 * 
 * Puis on parcourt le graphe, par ordre décroissant du poids attribué, en recherchant systématiquement les cycles, 
 * et en "confirmant" les arcs qui n'en créent pas (à l'inverse, on élimine les arcs qui créent un cycle avec les arcs déjà confirmés).
 * Au terme des opérations on obtient un graphe sans cycles. 
 * Le gagnant est le sommet vers lequel n'arrive aucune flèche (c'est-à-dire : qui gagne tous les duels "confirmés").
 *
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
 * les arcs de poids minimal jusqu'à ce qu'un des sommets gagne tous ses duels (ou n'en perd aucun), et donc
 * se désigne comme vainqueur de Condorcet. Cette methode implémente l'heuristique de Schwartz de manière simplifiée.
 * 
 * \param[in] matrice Le matrice de duels du fichier csv du scrutin, qu'on transformera en graphe.
 * \param[in] entete La partie de l'entete du fichier csv, où l'on retrouvera les candidats.
 * \param[in] nbElecteurs Le nombre d'electeurs ayant participé au scrutin.
*/
void condorcet_Schulze(t_mat_int_dyn *matrice, char **entete, int nbElecteurs);
/**@}*/
#endif