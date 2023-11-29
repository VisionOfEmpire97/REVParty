#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "condorcet.h"
#include "utils_sd/graph.h"

/**
 * Créer le graph localement?
 *
 * 
*/

sommet *vainqueurCondorcet(graph *graphe)
{

    sommet *vainqueur = NULL;
    for (unsigned i = 0; i < graphe->nbSommet; i++)
    {
        sommet *s = graphe->sommets[i];
        if (s->nbPredecesseur == 0)
            vainqueur = s;
    }

    /*TODO : Print logs*/

    return vainqueur;
}

sommet *vainqueurCondorcetMinimax(graph *graphe)
{
    /**
     * On regarde les arcs entrants de chaque sommet (représentant les défaites)
     * Celui avec le poids le plus elevé, et donc celui avec la pire défaite
     * le sommet avec la pire défaite la plus basse remporte le scrutin
     */

    int nbSommets = graphe->nbSommet;
    int pireDefaite[nbSommets]; /*Tableau initialisé à une tres grande valeur?*/
    int max, min, indiceSommetCourant;
    sommet *vainqueur;

    for (unsigned i = 0; i < graphe->nbSommet; i++)
    {
        for (unsigned j = 0; i < graphe->nbArc; i++)
        {
            max = 0;
            if (graphe->arcs[j]->arrivee == graphe->sommets[i])
            {
                if (graphe->arcs[j]->poids > max)
                {
                    max = graphe->arcs[j]->poids;
                }
            }
        }
        pireDefaite[i] = max;
    }
    /*Faire le minimum de pireDefaite*/
    min = pireDefaite[0];
    vainqueur = graphe->sommets[0];
    for (unsigned i = 1; i < nbSommets; i++)
    {
        if (pireDefaite[i]<min)
        {
            min = pireDefaite[i];
            vainqueur = graphe->sommets[i];
        }
        
    }
    /*TODO : Print logs*/
    return vainqueur;
}

sommet *vainqueurCondorcetSchulze(graph *graphe)
{
    /**
     * Retirer successivements les arcs de poids minimal jusqu'à retrouver un vainqueur de Condorcet
     * Si égalité, renvoyer tous les sommets restants après avoir retiré tous les arcs
    */

    graph *g;
    memcpy(g, graphe, sizeof(graph));

    sommet *vainqueur;
    arc **a;
    for (unsigned i = 0; i < g->nbSommet; i++)
    {
        if (g->sommets[i]->nbPredecesseur != 0)
        {
            enlever_arc(g, arcDePoidsMinimal(g));
        }
        else
        {
            vainqueur = g->sommets[i];
            break;
        }
    }
    /*TODO : Print logs*/
    return vainqueur;
}

sommet *vainqueurCondorcetPaires(graph *graph)
{
    /**
     * (*) Verifier si un cycle est formé (voire algorithmes de dijkstra et bellman-ford)
     * (*) Supprimer l'arc de poids minimal de ce cycle
     * (*) Répeter jusqu'a obtenir un vainqueur de condorcet (P- == 0)
     */
}

arc *arcDePoidsMinimal(graph *graph)
{

    if (graph->nbArc == 0)
    {
        return NULL;
    }
    arc **arcPoidsMin;
    *arcPoidsMin = graph->arcs[0];
    for (int i = 1; i < graph->nbArc; i++)
    {
        if (graph->arcs[i]->poids < (*arcPoidsMin)->poids)
        {
            arcPoidsMin = graph->arcs[i];
        }
    }

    return arcPoidsMin;
}
