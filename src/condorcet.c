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
    /**
     * On regarde les arcs sortants de chaque sommet
     * Celui avec le poids le plus elevé, et donc celui avec la pire défaite
     * le sommet avec la pire défaite la plus basse remporte le scrutin
    */

    int maxmin = 0;
    sommet *sommet_depart, *sommet_arrivee, *res;
    arc **a;
    *a = graph->arcs;
    for (unsigned i = 0; i < graph->nbSommet; i++)
    {
        sommet_depart = graph->sommets[i];
        (*a)->depart = sommet_depart;
        for (unsigned j = 0; j < (graph->nbSommet - 1); j++)
        {
            sommet_arrivee = graph->sommets[j];
            (*a)->arrivee = sommet_arrivee;
            if ((*a)->poids < maxmin)
            {
                maxmin = (*a)->poids;
                res = sommet_depart;
            }
        }
    }
    /*TODO : Print logs*/
    return res;
}

sommet *vainqueurCondorcetSchulze(graph *graph)
{
    /**
     * Retirer successivements les arcs de poids minimal jusqu'à retrouver un vainqueur de Condorcet
    
    */

    sommet *vainqueur;
    arc **a;
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
