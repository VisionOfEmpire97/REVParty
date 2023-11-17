/**
 * \author Équipe 001 (VALLAT ANTOINE)
 * \date 13 Novembre 2023
 * \brief Fichier des méthodes uninominals
 * \file uninominal.h
 */

#ifndef __UNINOMINALS_H__
#define __UNINOMINALS_H__


/**
 * \brief Effectue le vote uninominal à 1 tours
 * \param Votes
 * \param Candidats
 * \param nombreDecandidats
 * \param nombreDeVotes
 * \return 
 */
void electionUninominale(int votes[], char *candidats[], int n , int nombreDeVotes );
/**
 * \brief Effectue le vote uninominal à 2 tours
 * \param Votes
 * \param Candidats
 * \param nombreDecandidats
 * \param nombreDeVotes
 * \return 
 */
void electionUninominalDeuxTours(int votes[], char *candidats[], int n, int nombreDeVotes);
/**
 * \brief Effectue le traitement des informations pour le vote uninominal à 1 tours
 * \param mat
 * \param entete
 * \return 
 */
void traitement_uninominal_1tours(t_mat_char_star_dyn *mat,t_mat_char_star_dyn *entete);
/**
 * \brief Effectue le traitement des informations pour le vote uninominal à 2 tours
 * \param mat
 * \param entete
 * \return 
 */
void traitement_uninominal_2tours(t_mat_char_star_dyn *mat,t_mat_char_star_dyn *entete) ;
/**@}*/
#endif