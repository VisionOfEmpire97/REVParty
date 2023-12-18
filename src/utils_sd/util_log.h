/**
 * \author Équipe 001 (ZERKANI Yanis)
 * \date 06 Novembre 2023
 * \brief Programme permettant de retranscrire les affichages intermédiaires permettant la vérification du vote (le suivi des calculs)
 * dans un fichier de logs si spécifié, sur stdout sinon.
 * \file util_log.h
 */
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>


/** \defgroup UtilsLog Util_log
 \*@{
 * 
 */

/**
 * \brief Affiche sur stdout les logs recueillis pendant l'exécution  
 * du programme ou les sauvegarde dans un fichier 
 * \details Fonction à appeler une seule fois dans le programme principal
 * \param[in] filename nom du fichier ou les logs seront écrit tout au long du programme
 * \param[out] logfp résultat de l'ouverture du fichier, stdout si pas de fichier spécifié
*/
FILE* begin_to_log(const char *filename);


/**
 * \brief Ajoute une nouvelle ligne au fichier de log ouvert.
 * Cette fonction doit être appelée à chaque étape de calcul.
 * \param[in] textToLog Texte à journaliser.
 */
void append_to_log_file(const char* textToLog);

/**
 * \brief Ferme le fichier log s'il a été ouvert.
 * 
 * \details Fonction à appeler une seule fois dans le programme principal
*/
void close_log_file();

/**@}*/