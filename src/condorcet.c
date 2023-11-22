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
        if (s->nbSuccesseur == (graph->nbSommet - 1))
            vainqueur = s;
    }

    /*TODO : Print logs*/

    return vainqueur;
}

sommet *vainqueurCondorcetMinimax(graph *graph){


    int maxmin = 0;
    sommet *s, *t, *res;
    arc* a = graph->arcs;
    for (unsigned i = 0; i < graph->nbSommet; i++)
    {
        s = graph->sommets[i];
        a->depart = s;
        for (unsigned j = 0; j < (graph->nbSommet -1); j++)
        {  
            t = graph->sommets[j]; 
            a->arrivee = j;
            if(a->poids < maxmin)
            {
                maxmin = a->poids;
                res = s;
            }
            
        }
        
    }
    /*TODO : Print logs*/
    return res;

}

sommet *vainqueurCondorcetSchulze(graph *graph){

}

sommet *vainqueurCondorcetPaires(graph *graph){


}