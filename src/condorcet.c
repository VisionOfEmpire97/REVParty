#include <stdlib.h>
#include <stdio.h>
#include <condorcet.h>
#include "utils_sd/graph.h"

sommet *vainqueurCondorcet(graph *graph)
{

    sommet *vainqueur = NULL;
    for (unsigned i = 0; i < graph->nbSommet; i++)
    {
        sommet *s = graph->sommets[i];
        if (s->nbPredecesseur == 0)
            vainqueur = s;
    }

    /*TODO : Print logs*/

    return vainqueur;
}

sommet *vainqueurCondorcetMinimax(graph *graph)
{

    int maxmin = 0;
    sommet *s, *t, *res;
    arc *a = graph->arcs;
    for (unsigned i = 0; i < graph->nbSommet; i++)
    {
        s = graph->sommets[i];
        a->depart = s;
        for (unsigned j = 0; j < (graph->nbSommet - 1); j++)
        {
            t = graph->sommets[j];
            a->arrivee = j;
            if (a->poids < maxmin)
            {
                maxmin = a->poids;
                res = s;
            }
        }
    }
    /*TODO : Print logs*/
    return res;
}

sommet *vainqueurCondorcetSchulze(graph *graph)
{

    sommet *vainqueur;
    arc *a;
    for (unsigned i = 0; i < graph->nbSommet; i++)
    {
        if (graph->sommets[i]->nbPredecesseur != 0)
        {
            // graph = retirerArc(graph, arcDePoidsMinimal(graph));
        }
        else
        {
            vainqueur = graph->sommets[i];
            break;
        }
    }
    /*TODO : Print logs*/
    return vainqueur;
}

sommet *vainqueurCondorcetPaires(graph *graph)
{
    /**
     * (*) Verifier si un cycle est formé
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
    arc *arcPoidsMin = graph->arcs[0];
    for (int i = 1; i < graph->nbArc; i++)
    {
        if (graph->arcs[i]->poids < arcPoidsMin->poids)
        {
            arcPoidsMin = graph->arcs[i];
        }
    }

    return arcPoidsMin;
}
