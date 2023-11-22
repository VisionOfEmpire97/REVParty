#include <stdio.h>
#include "../../jugement.h"

int main (int argc, char** argv)
{
    char* nom_csv = argv[1];
    printf("**************** DEBUT DU TEST ***************\n");
    
    methode_jugement(nom_csv);
    
    printf("**************** FIN DU TEST ***************\n");
    return 0;
}
