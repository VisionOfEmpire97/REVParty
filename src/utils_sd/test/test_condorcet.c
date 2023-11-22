#include <stdlib.h>
#include "../matrice.h"
#include "../graph.h"
#include "../../CSV/lecture_csv.h"
#include "../../condorcet.h"

int main(int argc, char *argv[])
{

    t_mat_char_star_dyn *m;
    t_mat_int_dyn *mat_duel;
    graph *g;
    m = lecture_fichier(argv[1]);
    printf("----------------------------------------\n");
    printf("TEST CREATION GRAPH DE MATRICE DE CHAINE\n");
    g = creer_graphe_de_matrice_char(m);

    printf("TEST OK!\n");
    printf("Affichage Graph!\n");
    afficher_graph(g);
    printf("TEST OK!\n");
    return 0;
}