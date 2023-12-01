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
    sommet *s, *t;
    m = lecture_fichier(argv[1]);
    printf("----------------------------------------\n");
    printf("TEST CREATION GRAPH DE MATRICE DE CHAINE\n");
    g = creer_graphe_de_matrice_char(m);

    
    printf("TEST OK!\n");
    printf("Affichage Graph!\n");
    afficher_graph(g);
    printf("TEST OK!\n");

    
    printf("\n\n***************(TEST CONDORCET)****************\n\n");
    s = vainqueurCondorcet(m);
    printf("Candidat vainqueur selon Condorcet : %s\n", s->nom);
    printf("\n\n****************(VERIFICATION)*****************\n\n");
    printf("Nombre de predecesseurs (defaites) du candidat %s : %d\n", s->nom, s->nbPredecesseur);
    printf("Nombre de victoires de %s : %d, nombre de candidats : %d\n", s->nom, s->nbSuccesseur, creer_graphe_de_matrice_char(m)->nbSommet);
    
    
    
    printf("\n\n***************(TEST CONDORCET_MINIMAX)****************\n\n");
    t = vainqueurCondorcetMinimax(m);
    printf("Candidat vainqueur selon Condorcet Minimax : %s\n", t->nom);
    printf("\n\n****************(VERIFICATION)****************************\n\n");
    printf("Nombre de predecesseurs (defaites) du candidat %s : %d\n", t->nom, t->nbPredecesseur);
    printf("Nombre de victoires de %s : %d, nombre de candidats : %d\n", t->nom, t->nbSuccesseur, creer_graphe_de_matrice_char(m)->nbSommet);
    
    
    return 0;
}