#include <stdlib.h>
#include "../matrice.h"
#include "../graph.h"
#include "../../CSV/lecture_csv.h"
int main(int argc, char *argv[])
{

    t_mat_char_star_dyn *m;
    t_mat_int_dyn *mat_duel;
    graph *g, *newG;
    m = lecture_fichier(argv[1]);
    printf("----------------------------------------\n");
    printf("TEST CREATION GRAPH DE MATRICE DE CHAINE\n");
    g = creer_graphe_de_matrice_char(m);
    mat_duel=construire_mat_duel(m);
    afficher_matrice_int(mat_duel);
    afficher_graph(g);
    

    // mat_duel = construire_mat_duel(m);
    // afficher_matrice_int(mat_duel);
    // printf("TEST OK!\n");
    // printf("Affichage Graph!\n");
    // afficher_graph(g);
    // enlever_arc(g, g->arcs[0]);
    // afficher_graph(g);
    // printf("TEST OK!\n");
    // liberer_graph(g);
    // supprimer_matrice_char(m);
    return 0;
}