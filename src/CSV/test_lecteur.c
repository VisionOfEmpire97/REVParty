#include <stdlib.h>
#include "lecture_csv.h"
#include "../utils_sd/matrice/matrice.h"


int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port", argv[0]);
        exit(1);
    }
    lecture_entete(argv[1]);
    afficher_matrice_char(recherche_hash("fa5fd9ce659e1f97807b8785846790d9c739f532ae0ee07801f91e996debaea6", argv[1]));
    

    
    return 0;
}
