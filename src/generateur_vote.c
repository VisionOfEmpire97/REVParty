#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// Fonction pour générer une lettre majuscule aléatoire
char randomUppercaseLetter() {
    return 'A' + rand() % 26;
    printf("majuscule \n ");
}

// Fonction pour générer une lettre minuscule aléatoire
char randomLowercaseLetter() {
    return 'a' + rand() % 26;
    printf("minuscule \n ");
}

// Fonction pour générer un nom en majuscules et un prénom en minuscules
void generateName(char *name, char *firstName) {
    for (int i = 0; i < 5; i++) {
        name[i] = randomUppercaseLetter();
        firstName[i] = randomLowercaseLetter();
    }
    name[5] = '\0';
    firstName[5] = '\0';
}

// Fonction pour générer une chaîne de caractères aléatoire
char *generateRandomString(int length) {
    char *randomString = (char *)malloc(length + 1);
    if (randomString == NULL) {
        return NULL;
    }

    for (int i = 0; i < length; i++) {
        randomString[i] = 'A' + rand() % 26; // Génère une lettre majuscule aléatoire
    }
    randomString[length] = '\0';

    return randomString;
}

int main() {

    srand(time(NULL));
    char name[6];
    char firstName[6];
    generateName(name, firstName);

    printf("Nom: %s\n", name);
    printf("Prénom: %s\n", firstName);

    int stringLength = 10;
    char *randomStr = generateRandomString(stringLength);
    printf("Chaine aléatoire: %s\n", randomStr);

    free(randomStr); // N'oubliez pas de libérer la mémoire allouée dynamiquement
    return 0;
}
