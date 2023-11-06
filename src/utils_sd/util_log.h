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
 * **début du programme [nom du programme]**
 * [nom du prgm] - étape réalisée 
 * **fin du programme [nom du programme]**
 * 
 * @param filename le fichier de log déjà ouvert
 */
void to_log_file(char* filename);