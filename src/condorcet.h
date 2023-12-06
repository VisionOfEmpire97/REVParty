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
 \{
 */

/** \defgroup Methods Vainqueurs de Condorcet
 @{
 */
/**
 * \brief Retourne le vainqueur du suffrage selon la méthode de Condorcet. Si vainqueurCondorcet == NULL,
 * on doit faire appel aux fonctions de résolution du paradoxe de Condorcet.
 * 
 * \param[in] matrice Le matrice de char du fichier csv du scrutin, qu'on transformera en graphe
 * \param[out] vainqueur Le vainqueur, s'il existe, selon la méthode Condorcet.
 *
 */
void vainqueurCondorcet(t_mat_int_dyn *matrice, char **entete, int nbElecteurs);

/**
 * \brief Première proposition de résolution du paradoxe de Condorcet: la méthode Minimax.
 * 
 * \details Pour chacun des candidats, on regarde le pire des scores qu’il ferait dans ses
 * différents faces-à-faces, puis on déclare élu celui des candidats dont le pire des scores est le meilleur.
 * 
 * \param[in] matrice Le matrice de char du fichier csv du scrutin, qu'on transformera en graphe
 * \param[out] vainqueur Le vainqueur, selon la méthode Condorcet Minimax.
 */
char *vainqueurCondorcetMinimax(t_mat_int_dyn *matrice, char **entete);

/**
 * \brief Seconde proposition de résolution du paradoxe de Condorcet: la méthode Paires.
 * 
 * 
 * \details Pour cette méthode, on devra :
 * 
 *   
 * \details (*) Verifier si un cycle est formé 
 * \details (*) Supprimer l'arc de poids minimal de ce cycle
 * \details (*) Répeter jusqu'a obtenir un vainqueur de Condorcet (P- == 0)
 * 
 * 
 * \param[in] matrice Le matrice de char du fichier csv du scrutin, qu'on transformera en graphe
 * \param[out] vainqueur Le vainqueur, selon la méthode Condorcet Paires.
*/
sommet *vainqueurCondorcetPaires(t_mat_int_dyn *matrice, char **entete);

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
char *vainqueurCondorcetSchulzeSimpl(t_mat_int_dyn *matrice, char **entete);
/**@}*/

/** \defgroup UtilsCondorcet Fonctions utilitaires
 \{
 */
/**
 * \brief Fonction permettant de retrouver l'arc de poids minimal d'un graphe.
 * Fonction utile pour le fonctionnement des méthodes Paires et Schulze.
 * 
 * \param[in] graph Le graphe pondéré des duels.
 * \returns L'arc de poids minimal du graphe.
*/
arc *arcDePoidsMinimal(graph *graphe);


/**
 * \brief Fonction permettant de voir si un sommet appartient ou non à un ensemble de Schwartz
 * Fonction utile pour le fonctionnement de la méthode Schulze.
 * 
 * \details Pour un graphe des duels donné, l’ensemble de Schwartz est défini formellement de la façon suivante :
 *
 * \details(*) Un groupe de tête est un ensemble non-vide E de candidats n’ayant perdu aucune confrontation avec un candidat hors de E ;
 * \details(*) Un groupe de tête minimal est un groupe de tête qui ne contient pas de groupe de tête strictement plus petit ;
 * \details(*) L'ensemble de Schwartz est constitué de tous les candidats appartenant à au moins un groupe de tête minimal.
 * 
 * \param[in] candidat Le sommet à vérifier.
 * \param[in] groupeDeTete L'ensemble des candidats n'ayant perdu aucune confrontation avec un candidat en dehors du groupe.
 * \param[in] tailleGroupeDeTete La taille du groupe de tête.
 * \returns res 1 si le sommet appartient à un ensemble de Scwhartz, 0 sinon.
*/
int appartientEnsembleDeSchwartz(sommet *candidat, sommet **groupeDeTete, int tailleGroupeDeTete);


/**
 * \brief Fonction permettant de retrouver et renvoyer l'ensemble de Schwartz dans un graphe donné
 * 
 * \param[in] 
 * 
*/
sommet **ensembleDeSchwartz(graph *graphe, int *tailleEnsemble);


void printLogsVote(t_mat_int_dyn *matrice, char **entete);
/**@}*/