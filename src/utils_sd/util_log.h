/// @file src/utils_sd/util_sd.h
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>


/**
 * 
 * @brief Ecriture du fichier de log
 * chaque méthode devrait appeler cette fonction 
 * pour concaténer l'étape de calcul au fichier filename 
 * passé en paramètre et déjà ouvert en écriture
 * PROPOSITION pour format de l'étape de calcul (ce qui sera affiché): 
 * *****************************************
 * 
 * **Début du programme [nom du programme]**
 * [nom du prgm] - étape réalisée 
 * ...
 * **fin du programme [nom du programme]**
 * 
 * *****************************************
 * Le log sera fermé dans le main principal
 * OU ALORS
 * utiliser dup tout simplement ? à voir...
 */


/**
 * @brief Ajoute une nouvelle ligne au fixhier de log ouvert.
 * Cette fonction serait appelée à chaque étape de calcul.
 * @param[in] filename Fichier de log déjà ouvert
 * @param[in] textToLog Journalisation du texte en entrée
 */
void append_to_log_file(const char* textToLog, FILE* logfp);

/**
 * @brief Affiche sur stdout les logs recueillis pendant l'exécution  
 * du programme ou les sauvegarde dans un fichier 
 * Fonction à appeler une seule fois dans le programme principal
 * @param[in] filename nom du fichier ou les logs seront écrit tout au long du programme
 * @param[out] logfp résultat de l'ouverture du fichier, stdout si pas de fichier spécifié
*/
FILE* begin_to_log(const char *filename);


/**
 * @brief Ferme le fichier log s'il a été ouvert.
 * @param[in] logfp Fichier ouvert (Pas d'effet si logfp == stdout)
 * 
*/
void close_log_file(FILE *logfp);

/**
 * COMMENTAIRE PROVISOIRE EN ATTENDANT VALIDATION
 * 
 * Application des idées proposées
 * 
 * Fonction begin_to_log qui retourne un le descripteur logfp
 * logfp == stdout | fopen(logfile) en fonction de la présence ou non de la balise -o
 * 
 * Fonction append_to_log_file qui concatene le fichier de logs a chaque appel, avec le format proposé
 * 
 * 
*/