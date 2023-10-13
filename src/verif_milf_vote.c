#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "SHA256/sha256.h"
#include "SHA256/sha256_utils.h"
//#include "lecture_csv"
#define STRLONG 60

#define LONGEUR_MAX 60


/*Fonction verification majuscule pour le nom */
/// \brief Fonction verification majuscule pour le nom
/// \param[in] On récupere le nom

int Majuscule(const char *chaine) {
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (!isupper(chaine[i])) {
            return 0; // Au moins un caractère n'est pas en majuscule
        }
    }
    return 1; // Tous les caractères sont en majuscules
}

/*Fonction verification minuscule pour le prenom */
/// \brief Fonction verification minuscule pour le prenom
/// \remarks on commence au deuxieme caractere comme le premier doit etre une majuscule
/// \param[in] On récupere le prenom

int Minuscules(const char *chaine) {
    for (int i = 1; chaine[i] != '\0'; i++) {
        if (!islower(chaine[i])) {
            return 0; // Au moins un caractère n'est pas en minuscule
        }
    }
    return 1; // Tous les caractères sont en minuscules
}

/*Fonction lecture de la ligne du retour csv */
/// \brief Fonction lecture de la ligne du retour csv
/// \param[in] On récupere la ligne a afficher avec le résultat 

void affichage_ligne (char*ligne)
{   
    printf("Le vote qui correspond à mon code est : \n ");
    int longeur = strlen(ligne);
    for(int i=0;i<longeur;i++)
    {
        printf("%d \t",ligne[i]);
    }
}

/* Programme principal - Vérif my vote :)  */
/// \brief Fonction main verif vote
/// \author Antoine Vallat
/// \date 13 octobre 2023
/// \param[in] On récupere le nom , prenom , le code et le nom du csv dans argv

int main(int argc, char* argv[])
{   
    char* nom;
    char* prenom;
    int code;
    char* nom_csv ;
    char * ligne ; 
    if (argc>1)
    {
        nom = argv[1];
        prenom = argv[2];
        code = atoi(argv[3]);
        nom_csv = argv[4];
    }

    /* vérification du nom et du prenom  */
    /// \brief Partie verif du nom/prenom du main
    
    while (Majuscule(nom) == 0) {
        printf("Le nom n'est pas en majuscules. Veuillez réessayer : ");
        scanf("%s", nom);
    }
 
    while (Minuscules(prenom) == 0 || islower(prenom[0])) {
        printf("Le Prenom n'est pas en minuscule ou la première lettre n'est pas en majuscule. Veuillez réessayer : ");
        scanf("%s", prenom);
    }

    /* On fait le hash du code  */
    /// \brief Partie hash du code client 
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
	char * item = malloc(STRLONG*sizeof(char)); // contiendra la chaîne à hasher
    char * chaine_code = malloc(STRLONG*sizeof(char));// contiendra le code à hasher
    sprintf(chaine_code, "%d", code);
    strcat(item, nom);
    strcat(item, prenom);
    strcat(item, chaine_code);
    printf("Affichage du nom prénom code concaténer %s \n" , item );
    sha256ofString((BYTE *)item,hashRes); // hashRes contient maintenant le hash du code avec le nom , prenom et code
    /// \param[out] on récupere le hashRes qui contient le hash de nom , prenom et code  
    printf("Affichage du Résultat de sha %s \n" , hashRes );
    

    /* On appelle la fonction du lecteur_csv  */
    /// \brief appelle du lecteur csv , affichage et fin de main 

    //ligne = recherche_csv (hashRes,nom_csv);
    /// \param[out] on récupere la ligne qui contient notre hash 
    affichage_ligne (ligne);
    free(item);
    printf(" Fin du programme de vérification  \n" );
}