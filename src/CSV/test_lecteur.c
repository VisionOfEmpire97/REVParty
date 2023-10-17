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
    
    afficher_matrice_char(recherche_hash("83020643a5c92bb5b6ee269146c64a9b989bf203f0fc1348f1479bc637469056", argv[1]));
    

    
    return 0;
}
