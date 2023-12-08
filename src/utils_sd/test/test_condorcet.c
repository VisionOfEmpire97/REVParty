#include <stdlib.h>
#include "../matrice.h"
#include "../graph.h"
#include "../../CSV/lecture_csv.h"
#include "../../condorcet.h"
#include "../util_log.h"
#include "../arg_parse_util.h"

int main(int argc, char *argv[])
{
    // begin_to_log(NULL);
    

    t_mat_char_star_dyn *m;
    graph *g;
    t_mat_int_dyn *mat_duels;
    m = lecture_fichier(argv[1]);
    int nbElecteurs = recuperer_nb_colonnes(m);
    char **candidats= recuperer_candidats(m, 1);
    mat_duels = construire_mat_duel(m);
    // printf("----------------------------------------\n");
    // printf("TEST CREATION GRAPH DE MATRICE DE CHAINE\n");
    // g = creer_graphe_de_matrice_char(m);
    afficher_matrice_int(mat_duels);
    g = creer_graphe_de_matrice_duel(mat_duels, recuperer_candidats(m, 1));
    afficher_graph(g);

    
    // printf("TEST OK!\n");
    // printf("Affichage Graph!\n");
    // afficher_graph(g);
    // printf("TEST OK!\n");    

    printf("--------------------------------------------------\n");

    
    // close_log_file();
    
    
    printf("\n***************(TEST CONDORCET_MINIMAX)**********\n\n");
    // condorcet_minimax(mat_duels, candidats, nbElecteurs);

    
    printf("\n***************(TEST CONDORCET_SCHULZE)**********\n\n");

    printf("--------------------------------------------------\n");

    
    printf("\n***************(TEST_LOGS)***********************\n\n");
    printLogsVote(mat_duels, candidats);

    liberer_graph(g);
    supprimer_matrice_int(mat_duels);
    supprimer_matrice_char(m);
    
    return 0;
}