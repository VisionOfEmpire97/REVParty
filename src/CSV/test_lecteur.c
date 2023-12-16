#include <stdlib.h>
#include "lecture_csv.h"

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }
    printf("\033[1;31mAffichage de l'entête de la matrice\e[00m\n");
    afficher_matrice_char(lecture_entete(argv[1]));
    printf("\033[1;31mAffichage d'une ligne de la matrice\e[00m\n");
    afficher_matrice_char(recherche_hash("fa5fd9ce659e1f97807b8785846790d9c739f532ae0ee07801f91e996debaea6", argv[1]));
    printf("\033[1;31mAffichage du fichier complet\e[00m\n");
    afficher_matrice_char(lecture_fichier(argv[1]));

    return 0;
}
