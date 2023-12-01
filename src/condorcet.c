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

sommet *vainqueurCondorcet(t_mat_char_star_dyn *matrice)
{

    graph *graphe;
    graphe = creer_graphe_de_matrice_char(matrice);
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

sommet *vainqueurCondorcetMinimax(t_mat_char_star_dyn *matrice)
{
    /**
     * On regarde les arcs entrants de chaque sommet (représentant les défaites)
     * Celui avec le poids le plus elevé, et donc celui avec la pire défaite
     * le sommet avec la pire défaite la plus basse remporte le scrutin
     */

    graph *graphe;
    graphe = creer_graphe_de_matrice_char(matrice);
    int nbSommets = graphe->nbSommet;
    int pireDefaite[nbSommets];
    int max, min;
    sommet *vainqueur;

    for (unsigned i = 0; i < nbSommets; i++)
    {
        pireDefaite[i] = 0;
    }
    for (unsigned i = 0; i < graphe->nbSommet; i++)
    {
        for (unsigned j = 0; i < graphe->nbArc; i++)
        {
            max = 0;
            if (graphe->arcs[j]->arrivee == graphe->sommets[i])
            {
                if (graphe->arcs[j]->poids > pireDefaite[i])
                {
                    pireDefaite[i] = graphe->arcs[j]->poids;
                }
            }
        }
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

sommet *vainqueurCondorcetSchulze(t_mat_char_star_dyn *matrice)
{
    /**
     * Retirer successivements les arcs de poids minimal jusqu'à retrouver un vainqueur de Condorcet
     * Si égalité, renvoyer tous les sommets restants après avoir retiré tous les arcs
    */

    graph *graphe;
    graphe = creer_graphe_de_matrice_char(matrice);
    sommet *vainqueur = NULL;
    arc **a;
    for (unsigned i = 0; i < graphe->nbSommet; i++)
    {
        if (graphe->sommets[i]->nbPredecesseur != 0)
        {
            enlever_arc(graphe, arcDePoidsMinimal(graphe));
        }
        else
        {
            vainqueur = graphe->sommets[i];
            break;
        }
    }
    /*TODO : Print logs*/
    return vainqueur;
}

sommet *vainqueurCondorcetPaires(t_mat_char_star_dyn *matrice)
{
    /**
     * (*) Verifier si un cycle est formé (voire algorithmes de dijkstra et bellman-ford)
     * (*) Supprimer l'arc de poids minimal de ce cycle
     * (*) Répeter jusqu'a obtenir un vainqueur de condorcet (P- == 0)
     */
    graph *graphe;
    graphe = creer_graphe_de_matrice_char(matrice);
    sommet *vainqueur = NULL;
    return vainqueur;
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
            *arcPoidsMin = graph->arcs[i];
        }
    }

    return *arcPoidsMin;
}
