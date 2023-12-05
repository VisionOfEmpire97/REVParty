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
 * @param nom_csv nom du fichier csv passé en argument
 * @param type_csv type du csv passé en argument (i ou d)
 */
void lancer_methode(char *methode, char *nom_csv, char *type_csv);

/**
 * @brief formate la sortie finale
 * 
 * @param nom_methode nom de la méthode
 * @param nb_candidats nombre de candidats
 * @param nb_electeurs nb de votants
 * @param nom_vainqueur nom du vainqueur
 * @param score score du vainqueur
 */
void afficher_res(char* nom_methode, int nb_candidats, int nb_electeurs, char* nom_vainqueur, char *score);

/**\}*/
/**\}*/
#endif