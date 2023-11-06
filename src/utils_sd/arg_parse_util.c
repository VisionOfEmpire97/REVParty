#include <stdio.h>
#include <stdlib.h>
#include <arg_parse_util.h>

void begin_to_log(const char *filename) // will check if filename exists, and open it in write
{
    FILE *file;
    if (filename != NULL)
    {
        file = fopen(filename, "wt");
    }
    else
    {
        file = stdout;
    }
    // something should happen here, dunno what tho
    //probably should add stdout and stderr to file 
}

void check_compatibility(int *tab, int len_tab)
{
    for (int i = 0; i < len_tab; i++)
    {
        if (tab[i] == 'i' || tab[i] == 'd')
        {
            printf("%sLes balises i et d ne sont pas compatibles, merci de n'utiliser qu'une seule occurence de -i ou -d%s\n", RED, END_COLOR);
            exit(EXIT_FAILURE);
        };
    }
}

void lancer_methode(char *methode)
{
    int methode_id = 0;
    for (methode_id; methode_id < 7; methode_id++)
    {
        if (*methode == valid_methods[methode_id]) //strcmp ?
            break;
    }
    switch (methode_id)
    {
    case 0: // uninominale à un tour
        // fonction qui appelle la méthode de vote
        break;
    case 1: // uninominale à deux tours
        // fonction qui appelle la méthode de vote
        break;
    case 2: // Condorcet + minimax
        // fonction qui appelle la méthode de vote
        break;
    case 3: // Condorcet + paires
        // fonction qui appelle la méthode de vote
        break;
    case 4: // Condorcet + Schulze
        // fonction qui appelle la méthode de vote
        break;
    case 5: // jugement majoritaire
        // fonction qui appelle la méthode de vote
        break;
    case 6: //toutes le méthodes
        // fonction qui appelle TOUT
        break;
    default:
        printf("%sargument de méthode invalide%s\n", RED, END_COLOR);
        exit(EXIT_FAILURE);
    }
};