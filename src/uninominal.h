/**
 * \author Équipe 001 (VALLAT ANTOINE)
 * \date 13 Novembre 2023
 * \brief Fichier des méthodes uninominals
 * \file uninominal.h
 */
#ifndef __UNINOMINAL_H__
#define __UNINOMINAL_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice.h"

/**
 * \defgroup ADTMethodeVote Uninominal
 * @brief Documentation de l'implémentation de la méthode de vote uninominal
 * @{
 */

/**
 * @brief Fonction qui prend en paramètre une liste de candidats et une liste de votes, elle applique la méthode uninominal à un tour ou deux tours et affiche le vainqueur.
 *  Dans le cadre de la lecture de Matrice du fichier csv , la méthode uninominal prends en compte le vote le plus favorable d'un electeur et pour un éventuelle deuxieme tours
 * on prends le vote le plus favorable entre les deux candidats vainqueur du premier tours (une égalité est traité comme un vote blanc)
 * @param Votes Tableau des votes
 * @param Candidats Tableau des noms des candidats
 * @param n Nombre de candidats
 * @param nombreDeVotes Nombre total de votes
 * @param mat Matrice du vote
 * @param tours Nombre de tours (1 ou 2)
 * @return Affiche le vainqueur
 */
void electionUninominal(int votes[], char *candidats[], int n, int nombreDeVotes, t_mat_char_star_dyn *mat, int tours);
/**
 * @brief Fonction qui cherche le vote le plus favorable d'un électeur pour un candidat dans une ligne de la matrice et retourne le nom du candidat en question.
 * @param mat Matrice de votes
 * @param num_ligne Numéro de ligne
 * @return Numéro du candidat
 */
int recupere_numeroCandidat(t_mat_char_star_dyn *mat, int num_ligne);
/**
 * @brief Récupère les matrices de votes, les traite pour pouvoir appeler la méthode uninominal à un ou deux tours, et fait l'appel de la méthode.
 *
 * @param mat Matrice de votes
 * @param tours choix de la méthode 1 tours ou 2 tours
 */
void traitement_uninominal(t_mat_char_star_dyn *mat, int tours);
/** @} */
#endif