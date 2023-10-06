#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "sha256.h"
#define LONGEUR_MAX 60

/* Programme principal - Vérif my vote :)  */


int main(int argc, char* argv[])
{   
    char* nom;
    char* prenom;
    int code;

    if (argc>1)
    {
        nom = argv[1];
        prenom = argv[2];
        code = atoi(argv[3]);
    }
    
    char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
	char * item = malloc(STRLONG*sizeof(char)); // contiendra la chaîne à hasher
    strcat(item, nom);
    strcat(item, prenom);
    printf("Affichage du nom prénom concaténer %s \n" , item );
    sha256ofString((BYTE *)item,hashRes); // hashRes contient maintenant le hash de l'item^
    printf("Affichage du ^Résultat de sha %s \n" , hashRes );
}