#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdlib.h>
#include <stdio.h>
#include "matrice.h"

typedef struct t_sommet
{
    char *nom;
    int nbSuccesseur;
    int nbPredecesseur;

} sommet;

typedef struct t_arc
{
    sommet *depart;
    sommet *arrivee;
    int poids;
} arc;

typedef struct t_graph
{
    sommet **sommets;
    int nbSommet;
    arc **arcs;
    int nbArc;
} graph;

sommet *creer_sommet(char *nom);

arc *creer_arc(sommet *arrivee, sommet *depart, int poids);

graph *creer_graph();

int ajouter_sommet(graph *g, sommet *s);

int ajouter_arc(graph *g, arc *a);

graph *creer_graphe_de_matrice_char(t_mat_char_star_dyn *mat);

graph *creer_graphe_de_matrice_duel(t_mat_int_dyn *mat_duel, char **listeNomSommets);

void afficher_graph(graph *g);
#endif