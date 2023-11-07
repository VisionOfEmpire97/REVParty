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
 * PROPOSITION pour format de l'étape de calcul : 
 * *****************************************
 * 
 * **début du programme [nom du programme]**
 * [nom du prgm] - étape réalisée 
 * **fin du programme [nom du programme]**
 * 
 * *****************************************
 * Le log sera fermé dans le main principal
 * 
 * utiliser dup ? à voir...
 * 
 * @param filename le fichier de log déjà ouvert
 */
void append_to_log_file(char* filename);

/**
 * @brief Affiche les logs recueillis tout au long 
 * du programme ou les sauvegarde dans un fichier 
 * 
 * @param[in] filename nom du fichier ou les logs seront écrit tout au long du programme
*/
void begin_to_log(const char *filename);