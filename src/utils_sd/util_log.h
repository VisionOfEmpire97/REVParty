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
 * @brief Ajoute une nouvelle ligne au fixhier de log ouvert
 * Cette fonction serait appelée à chaque étape de calcul
 * Peut prendre plus de paramètres, à toi de voir comment tu gères l'implémentation
 * @param[in] filename le fichier de log déjà ouvert
 */
void append_to_log_file(char* filename);

/**
 * @brief Affiche sur stdout les logs recueillis pendant l'exécution  
 * du programme ou les sauvegarde dans un fichier 
 * Fonction à appeler une seule fois dans le programme principal
 * @param[in] filename nom du fichier ou les logs seront écrit tout au long du programme
*/
void begin_to_log(const char *filename);