#include <stdlib.h>
#include "../matrice.h"
#include "../graph.h"
#include "../../CSV/lecture_csv.h"
#include "../../condorcet.h"
#include "../util_log.h"

int main(int argc, char *argv[])
{
    // begin_to_log(NULL);
    

    t_mat_char_star_dyn *m;
    graph *g;
    t_mat_int_dyn *mat_duels;
    m = lecture_fichier(argv[1]);
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

    printf("----------------------------------------\n");

    
    // close_log_file();
    printf("\n***************(TEST CONDORCET)****************\n\n");
    
    printf("Candidat vainqueur selon Condorcet : %s\n", vainqueurCondorcet(mat_duels, candidats));

    
    
    printf("\n***************(TEST CONDORCET_MINIMAX)****************\n\n");
    printf("Candidat vainqueur selon Condorcet Minimax : %s\n", vainqueurCondorcetMinimax(mat_duels, candidats));

    
    printf("\n***************(TEST CONDORCET_SCHULZE)****************\n\n");
    printf("Candidat vainqueur selon Condorcet Schulze : %s\n", vainqueurCondorcetSchulzeSimpl(mat_duels, candidats));

    printf("----------------------------------------\n");

    printf("\n***************(Arc de poids minimal)***********\n\n");
    printf("Sommet de depart de l'arc de poids minimal: %s\n", arcDePoidsMinimal(g)->depart->nom);
    printf("Sommet d'arrivée de l'arc de poids minimal: %s\n", arcDePoidsMinimal(g)->arrivee->nom);
    printf("Poids de l'arc de poids minimal: %d\n", arcDePoidsMinimal(g)->poids);
    printf("----------------------------------------\n");
    printf("\n\n***************(Fin des tests)***********\n\n");

    liberer_graph(g);
    supprimer_matrice_int(mat_duels);
    supprimer_matrice_char(m);
    
    return 0;
}