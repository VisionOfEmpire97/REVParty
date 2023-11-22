#include <stdlib.h>
#include "matrice.h"
#include "graph.h"

sommet *creer_sommet(char *nom)
{
    sommet *s = malloc(sizeof(sommet));
    s->nom = nom;
    s->nbPredecesseur = 0;
    s->nbSuccesseur = 0;
    return s;
}
void liberer_graph(graph *g)
{
    for (int i = 0; i < (g->nbSommet); i++)
    {
        free((g->sommets)[i]);
    }
    for (int i = 0; i < (g->nbArc); i++)
    {
        free((g->arcs)[i]);
    }
    free(g->arcs);
    free(g->sommets);
    free(g);
}

arc *creer_arc(sommet *arrivee, sommet *depart, int poids)
{

    arc *a = malloc(sizeof(arc));
    a->arrivee = arrivee;
    a->depart = depart;
    a->poids = poids;
    return a;
}

graph *creer_graph()
{

    graph *g = malloc(sizeof(graph));
    g->sommets = NULL;
    g->nbSommet = 0;
    g->arcs = NULL;
    g->nbArc = 0;
    return g;
}

int ajouter_sommet(graph *g, sommet *s)
{

    int nbs = (++(g->nbSommet));
    g->sommets = realloc(g->sommets, nbs * sizeof(sommet *));
    g->sommets[nbs - 1] = s;
    return nbs;
}

int ajouter_arc(graph *g, arc *a)
{
    int nba = (++(g->nbArc));

    g->arcs = realloc(g->arcs, nba * sizeof(arc *));
    g->arcs[nba - 1] = a;
    (a->arrivee)->nbPredecesseur++;
    (a->depart)->nbSuccesseur++;
    return nba;
}
void initialiser_sommet(graph *g, char *listeNomSommets[], int nbCandidats)
{

    sommet *s;
    for (int i = 0; i < nbCandidats; i++)
    {

        s = creer_sommet(listeNomSommets[i]);
        ajouter_sommet(g, s);
    }
}

void initialiser_arc(graph *g, t_mat_int_dyn *mat_duel)
{

    int colonne = mat_duel->col;

    int poids, poids2;
    sommet *arrivee, *depart;
    arc *pa;
    for (int i = 0; i < colonne - 1; i++)
    {

        for (int j = i + 1; j < colonne; j++)
        {

            poids = mat_duel->matrice[i][j];
            poids2 = mat_duel->matrice[j][i];
            arrivee = g->sommets[j];
            depart = g->sommets[i];
            if (poids < poids2)
            {
                poids = poids2;
                arrivee = g->sommets[i];
                depart = g->sommets[j];
            }
            pa = creer_arc(arrivee, depart, poids);
            ajouter_arc(g, pa);
        }
    }
}
graph *creer_graphe_de_matrice_duel(t_mat_int_dyn *mat_duel, char **listeNomSommets)
{

    int nbCandidats = mat_duel->col;
    graph *g = creer_graph();
    initialiser_sommet(g, listeNomSommets, nbCandidats);
    initialiser_arc(g, mat_duel);
    return g;
}

graph *creer_graphe_de_matrice_char(t_mat_char_star_dyn *mat)
{
    graph *g;
    char **entete = recuperer_candidats(mat);
    t_mat_int_dyn *mat_duel = construire_mat_duel(mat);
    g = creer_graphe_de_matrice_duel(mat_duel, entete);
    supprimer_matrice_int(mat_duel);
    return g;
}

void afficher_graph(graph *g)
{

    printf("MON GRAPH\n");
    printf("-Sommets\n");
    for (int i = 0; i < (g->nbSommet); i++)
    {
        printf("%s \n", (g->sommets[i])->nom);
    }
    printf("\n");
    printf("-Arcs\n");
    for (int j = 0; j < (g->nbArc); j++)
    {
        printf("(%s) ---%d---> (%s)\n", (((g->arcs[j])->depart)->nom), ((g->arcs[j])->poids), (((g->arcs[j])->arrivee)->nom));
    }
}