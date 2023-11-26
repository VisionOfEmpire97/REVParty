/**
 * @file arg_parse_util.h
 * @author ROSET Nathan
 * @brief 
 * @version 1
 * @date 2023-11-05
 */
 #ifndef __ARG_PARSE_UTILS_H__
 #define __ARG_PARSE_UTILS_H__
#include <stdio.h>
#include <stdlib.h>


/**
 * @addtogroup scrutin
 * 
 *\{
 * @defgroup arg_parse Utilitaire d'extraction d'arguments
 * \{
 * \var char* RED 
 * Variable qui change la couleur de stdout en rouge
 * 
 * \var char* GREEN 
 * Variable qui change la couleur de stdout en vert
 * 
 * \var char* END_COLOR 
 * Variable qui réinitialise la couleur de stdout
 * 
 */ 

extern char *RED;
extern char *GREEN;
extern char *END_COLOR;

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
void lancer_methode(char *methode, char *nom_csv);
/**\}*/
/**\}*/
#endif