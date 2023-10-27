/** Programme principal - Vérif my vote :) 
 *
 *
 * @brief Programme principal de vérification de vote
 * @author Antoine Vallat
 * @date 13 octobre 2023
 */
/// \file verif_my_vote

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "SHA256/sha256.h"
#include "SHA256/sha256_utils.h"
#include "CSV/lecture_csv.h"
#include "utils_sd/matrice/matrice.h"
#define STRLONG 120


/**
 * \defgroup VMV Documentation du main de verif_my_vote
 Documentation du verif_my_vote avec ses fonctions 
 * @{
 *
 */

/**     
 * Fonction pour l'affichage des résultats 
 * \brief Fonction pour l'affichage des résultats 
 * \param[in] On récupere la matrice de l'entete et du résultat de la recherche
 * \param[out] On affiche le résultat 
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
 * \brief Fonction verification majuscule pour le nom
 * \param[in] On récupere le nom
 * \param[out] On renvoie le nom en majuscule
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
 * \brief Fonction passe en minuscule le prenom et sa première lettre en majuscule
 * \remarks on commence au deuxième caractere comme le premier doit être une majuscule
 * \param[in] On récupere le prenom
 * \param[out] On renvoie le prénom en minuscule et la première lettre en majuscule
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

/**
 * \brief Fonction principale Main 
 * \remarks on commence au deuxième caractere comme le premier doit être une majuscule
 * \param[in] argc Le nombre d'arguments de la ligne de commande.
 * \param[in] argv	Les arguments de la ligne de commande.
 */
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
    /// \brief Partie-1 , Correction du nom/prenom donne en parametre 

    Majuscule(nom);
    Minuscules(prenom);

    /* On fait le hash du code  */
    /// \brief Partie-2 , Hash le code 
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashresult[bufferSize * 2 + 1];            /**< contiendra le hash en hexadécimal */
    char *stringtohash = malloc(STRLONG * sizeof(char));  /**< contiendra la chaîne à hasher */

    sprintf(stringtohash,"%s %s%s",nom,prenom,code);

    sha256ofString((BYTE *)stringtohash, hashresult); /**< hashresult contient maintenant le hash du code avec le nom , prenom et code */
    /// \param[out] hashresult est le résultat qui contient le hash de nom , prenom et code

    t_mat_char_star_dyn *entete;
    t_mat_char_star_dyn *result;
    
    /// \brief Partie-3 , appel du lecteur csv , affichage de l'entete et la correspondance du hash et fin de main
    entete = lecture_entete(nom_csv);
    /// \param[out] entête entête du CSV lu
    result = recherche_hash(hashresult, nom_csv);
    /// \param[out] result ligne du CSV contenant hashresult si elle existe
    if (!est_matrice_vide(result)) 
    {
        affichage_resultat(entete, result);
    }else
    {
        printf("Aucune correspondance n'a été retrouvée pour les données fournies. . . . . . :)  \n");
    }
    /// \param[out] affichage des résultats uniquement la colonne 4 de l'entête et de la ligne de vote recherchée
    free(stringtohash);
    return 0;
}
