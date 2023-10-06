#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "SHA256/sha256.h"
#include "SHA256/sha256_utils.h"
//#include "lecture_csv"
#define STRLONG 60



/*Fonction met en majuscule pour le nom */
/// \brief Fonction verification majuscule pour le nom
/// \param[in] On récupere le nom

int Majuscule(char *chaine) {
    for (int i = 0; chaine[i] != '\0'; i++) {
        if (islower(chaine[i])) {
            chaine[i] = toupper(chaine[i]); // Convertir la lettre minuscule en majuscule
        }
    }
    return 1; // La chaîne est maintenant en majuscules
}
/*Fonction met en minuscule pour le prenom */
/// \brief Fonction passe en minuscule le prenom et sa première lettre en majuscule
/// \remarks on commence au deuxieme caractere comme le premier doit etre une majuscule
/// \param[in] On récupere le prenom

int Minuscules(char *chaine) {
    if (chaine[0] != '\0') {
        chaine[0] = toupper(chaine[0]); // Mettre en majuscule la première lettre
    }

    for (int i = 1; chaine[i] != '\0'; i++) {
        if (isupper(chaine[i])) {
            chaine[i] = tolower(chaine[i]); // Convertir les lettres majuscules en minuscules
        }
    }
    return 1; // La chaîne a été convertie en minuscules, sauf la première lettre
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
    char* code;
    char* nom_csv ;
    char * ligne ;
    if (argc==5)
    {
        nom = argv[1];
        prenom = argv[2];
        code = argv[3];
        nom_csv = argv[4];
    }
    else
    {
        fprintf(stderr,"Veuillez mettre tout les parametres \n");
        exit(1);
    }

    /* Passage en maj/min du nom et du prenom  */
    /// \brief Partie verif du nom/prenom du main

    nom=Majuscule(nom);
    prenom=Minuscules(prenom);


    /* On fait le hash du code  */
    /// \brief Partie hash du code client
    int bufferSize = SHA256_BLOCK_SIZE;
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
	char * item = malloc(STRLONG*sizeof(char)); // contiendra la chaîne à hasher
    strcat(item, nom);
    strcat(item, prenom);
    strcat(item, code);
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
