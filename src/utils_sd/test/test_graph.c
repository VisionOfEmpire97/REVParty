#include <stdlib.h>
#include "../matrice.h"
#include "../graph.h"
#include "../../CSV/lecture_csv.h"
int main(int argc, char *argv[])
{

    t_mat_char_star_dyn *m;
    t_mat_int_dyn *mat_duel;
    char **entete;
    graph *g, *newG;
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s NOM DU FICHIER  TYPE du fichier 1 duel 0 vote\n", argv[0]);
        exit(0);
    }

    m = lecture_fichier(argv[1]);
    int type = atoi(argv[2]);

    printf("----------------------------------------\n");
    if (type == 1)
    {
        printf("TEST CREATION GRAPH MATRICE DE DUEL \n");
        entete = recuperer_candidats(m, 0);
        mat_duel = transformer_mat_char_mat_duel(m);
        g = creer_graphe_de_matrice_duel(mat_duel, entete);
    }
    else
    {
        printf("TEST CREATION GRAPH MATRICE DE VOTE\n");
        mat_duel = construire_mat_duel(m);
        g = creer_graphe_de_matrice_char(m);
    }
    afficher_matrice_int(mat_duel);
    printf("TEST OK!\n");
    printf("-----------Affichage Graph--------------\n");
    afficher_graph(g);
    printf("TEST OK!\n");
    printf("-----------TEST ENLEVER ARC!--------------\n");
    enlever_arc(g, g->arcs[0]);
    afficher_graph(g);
    printf("TEST OK!\n");
    liberer_graph(g);
    supprimer_matrice_char(m);
    printf("FIN!\n");
    return 0;
}