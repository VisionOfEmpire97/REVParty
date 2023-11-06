/**
 * @file arg_parse_util.h
 * @author ROSET Nathan
 * @brief 
 * @version 1
 * @date 2023-11-05
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * @addtogroup scrutin
 * 
 *\{
 */

/**
 *@defgroup arg_parse Utilitaire d'extraction d'arguments
 * \{
 */
/**
 * \var char* RED 
 * Variables qui changent la couleur de stdout en rouge
 * 
 * \var char* GREEN 
 * Variables qui changent la couleur de stdout en vert
 * 
 * \var char* END_COLOR 
 * Variables qui réinitialise la couleur de stdout
 * 
 * \var char** valid_methods 
 * liste des méthodes de votes acceptées par -m
 */ 
char *RED = "\033[1;31m";
char *GREEN = "\033[1;32m";
char *END_COLOR = "\e[00m";
char *valid_methods[7] = {"uni1", "uni2", "cm", "cp", "cs", "jm", "all"};

/**
 * @brief Vérifie que seul -i ou -d est présent lors de l'appel 
 * 
 * @param[in] tab liste des balises déjà traitées
 * @param[in] len_tab longueur du tableau de balises
*/
void check_compatibility(int *tab, int len_tab);

/**
 * @brief Appelle la méthode de scrutin passée en paramètres 
 * 
 * @param[in] methode nom du paramètre associé à la méthode à appeler
*/
void lancer_methode(char *methode);
/**\}*/
/**\}*/