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
 * @brief Fonction qui prend en paramètre une liste de candidats et une liste de votes, elle applique la méthode uninominal à un tour et affiche le vainqueur.
 *  Dans le cadre de la lecture de Matrice du fichier csv , la méthode à un tours prends en compte le vote le plus favorable d'un electeur
 * @param Votes Tableau des votes
 * @param Candidats Tableau des noms des candidats
 * @param n Nombre de candidats
 * @param nombreDeVotes Nombre total de votes
 * @return Affiche le vainqueur
 */
void electionUninominale(int votes[], char *candidats[], int n, int nombreDeVotes);

/**
 * @brief Fonction qui prend en paramètre une liste de candidats et deux listes de votes, elle applique la méthode uninominal à deux tours et retourne le vainqueur. 
 * Dans le cadre de la lecture de Matrice du fichier csv , le premier tours prends en compte le vote le plus favorable d'un electeur et pour un éventuelle deuxieme tours 
 * on prends le vote le plus favorable entre les deux candidats vainqueur du premier tours (une égalité est traité comme un vote blanc)
 *
 * @param Votes Tableau des votes
 * @param Candidats Tableau des noms des candidats
 * @param n Nombre de candidats
 * @param nombreDeVotes Nombre total de votes
 * @param votes_deux Tableau des votes deux
 * @return Affiche le vainqueur des premier et deuxième tours si nécessaire
 */
void electionUninominalDeuxTours(int votes[], char *candidats[], int n, int nombreDeVotes,t_mat_char_star_dyn *mat)

/**
 * @brief Fonction qui cherche le vote le plus favorable d'un électeur pour un candidat dans une ligne de la matrice et retourne le nom du candidat en question.
 *
 * @param entete Matrice d'entête
 * @param mat Matrice de votes
 * @param num_ligne Numéro de ligne
 * @return Nom du candidat
 */
char *recupere_1(t_mat_char_star_dyn *entete, t_mat_char_star_dyn *mat, int num_ligne);

/**
 * @brief Fonction qui récupère le nom des candidats présents dans l'entête et les range dans une liste.
 *
 * @param entete Matrice d'entête
 * @param liste_candidat Tableau pour stocker les noms des candidats
 */
void recupere_candidat(t_mat_char_star_dyn *entete, char *liste_candidat[]);

/**
 * @brief Fonction qui transforme un vote du nom du candidat en un vote sous forme de son Indice dans la liste de candidats. (ex : "candidat 1" -> 0 premier candidat de la liste)
 *
 * @param liste_candidat Tableau des noms des candidats
 * @param vote Vote sous forme du nom du candidat
 * @param nombreCandidat Nombre total de candidats
 * @return Numéro correspondant au candidat
 */
int changement(char *liste_candidat[], char *vote, int nombreCandidat);

/**
 * @brief Récupère les matrices de votes, les traite pour pouvoir appeler la méthode uninominal à un tour, et fait l'appel de la méthode.
 *
 * @param mat Matrice de votes
 * @param entete Matrice d'entête
 */
void traitement_uninominal_1tours(t_mat_char_star_dyn *mat, t_mat_char_star_dyn *entete);

/**
 * @brief Récupère les matrices de votes, les traite pour pouvoir appeler la méthode uninominal à deux tours, et fait l'appel de la méthode.
 *
 * @param mat Matrice de votes
 * @param entete Matrice d'entête
 */
void traitement_uninominal_2tours(t_mat_char_star_dyn *mat, t_mat_char_star_dyn *entete);

/**
 * @brief Fonction main de test de la méthode uninominal.
 *
 * @param argc Nombre d'arguments
 * @param argv Tableau des arguments
 * @return Résultat de l'exécution
 */
int main(int argc, char *argv[]);

/** @} */
#endif