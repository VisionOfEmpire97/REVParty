#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "SHA256/sha256.h"
#include "SHA256/sha256_utils.h"
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice/matrice.h"
#define STRLONG 120

/**
 * @fn formate et affiche le résultat de la recherche
 * @param entete
 * @param result
**/
void affichage_resultat(t_mat_char_star_dyn *entete, t_mat_char_star_dyn *result)
{
    char *entete_valeur = NULL;
    char *result_valeur = NULL;
    for (int i = 4; i < recuperer_nb_colonnes(result); i++)
    {
        entete_valeur = valeur_matrice_char_indice(entete, 0, i);
        result_valeur = valeur_matrice_char_indice(result, 0, i);
        printf("%-40s%3s \n", entete_valeur, result_valeur);
    }
}

/** 
 * Fonction met en majuscule pour le nom 
 * \brief Fonction verification majuscule pour le nom
 * \param[in] On récupere le nom
**/

void Majuscule(char *chaine)
{
    for (int i = 0; chaine[i] != '\0'; i++)
    {
        if (islower(chaine[i]))
        {
            chaine[i] = toupper(chaine[i]); // Convertir la lettre minuscule en majuscule
        }
    }
}
/**
 *Fonction met en minuscule pour le prenom 
 * \brief Fonction passe en minuscule le prenom et sa première lettre en majuscule
 * \remarks on commence au deuxième caractere comme le premier doit être une majuscule
 * \param[in] On récupere le prenom
 */
void Minuscules(char *chaine)
{
    if (chaine[0] != '\0')
    {
        chaine[0] = toupper(chaine[0]); // Mettre en majuscule la première lettre
    }

    for (int i = 1; chaine[i] != '\0'; i++)
    {
        if (isupper(chaine[i]))
        {
            chaine[i] = tolower(chaine[i]); // Convertir les lettres majuscules en minuscules
        }
    }
}

/** Programme principal - Vérif my vote :) 
 * \brief Fonction main verif vote
 * \author Antoine Vallat
 * \date 13 octobre 2023
 * \fn On récupere le nom , prenom , le code et le nom du csv dans argv
 * \param[in] nom
 * \param[in] prénom
 * \param[in] CodePersonnel
 * \param[in] nom_csv
**/
int main(int argc, char *argv[])
{
    char *nom;
    char *prenom;
    char *code;
    char *nom_csv;
    t_mat_char_star_dyn *ligne;
    if (argc == 5)
    {
        nom = argv[1];
        prenom = argv[2];
        code = argv[3];
        nom_csv = argv[4];
    }
    else
    {
        fprintf(stderr, "usage :./bin/verify_my_vote nom prenom code nom_csv\n");
        exit(1);
    }

    /* Passage en maj/min du nom et du prenom  */
    /// \brief Partie verif du nom/prenom du main

    Majuscule(nom);
    Minuscules(prenom);

    /* On fait le hash du code  */
    /// \brief Partie hash du code personnel
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashresult[bufferSize * 2 + 1];            /**< contiendra le hash en hexadécimal */
    char *stringtohash = malloc(STRLONG * sizeof(char));  /**< contiendra la chaîne à hasher */

    sprintf(stringtohash,"%s %s%s",nom,prenom,code);

    sha256ofString((BYTE *)stringtohash, hashresult); /**< hashresult contient maintenant le hash du code avec le nom , prenom et code */
    /// \param[out] hashresult le résultat qui contient le hash de nom , prenom et code

    t_mat_char_star_dyn *entete;
    t_mat_char_star_dyn *result;
    
    /// \brief appel du lecteur csv , affichage de l'entete et la correspondance du hash et fin de main
    entete = lecture_entete(nom_csv);
    /// \param[out] entête entête du CSV lu
    result = recherche_hash(hashresult, nom_csv);
    /// \param[out] result ligne du CSV contenant hashresult si elle existe
    affichage_resultat(entete, result);
    /// \param[out] affichage des résultats uniquement la colonne 4 de l'entête et de la ligne de vote recherchée
    free(stringtohash);
    return 0;
}
