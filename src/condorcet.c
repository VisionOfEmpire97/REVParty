#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "condorcet.h"
#include "utils_sd/graph.h"
#include "utils_sd/util_log.h"
#include "utils_sd/arg_parse_util.h"
#define NOM_METHODE_CDC "Condorcet"
#define NOM_METHODE_CDC_MNMX "Condorcet minimax"
#define NOM_METHODE_CDC_SCH "Condorcet Schulze"
#define NOM_METHODE_CDC_P "Condorcet paires"


void printLogsVote(t_mat_int_dyn *matrice, char **entete){
    graph *graphe;
    char **candidats = entete;
    int nbCandidats = matrice->col;
    graphe = creer_graphe_de_matrice_duel(matrice, candidats);
    char buff[100];
    int compteur = 0;

    for (unsigned i = 0; i < nbCandidats; i++)
    {
        for (unsigned j = 1; j < nbCandidats; j++)
        {
            printf("[CDC] Duel %d => %s (%d victoires) vs %s (%d victoires). Vainqueur : %s.\n", ++compteur, candidats[i], matrice->matrice[i][j], candidats[j], matrice->matrice[j][i], candidats[i]);
        }
        
    }
    
    // printf("[CDC] Duel 1 => %s (%d victoires) vs %s (%d victoires). Vainqueur : %s.\n", candidats[0], matrice->matrice[0][1], candidats[1], matrice->matrice[1][0], candidats[0]);


    // for (unsigned i = 1; i < recuperer_nb_lignes(matrice) ; i++)
    // {
    //     sprintf(buff, "[CDC] Duel 1 => %s (%d victoires) vs %s (%d victoires). Vainqueur : %s.", );
    //     append_to_log_file(buff);
    //     for (unsigned j = 0; j<nbCandidats; j++)
    //     {
    //         sprintf(buff, "%d/%s ", atoi(valeur_matrice_char_indice(matrice, i, j+4)), candidats[j]);
    //         append_to_log_file(buff);
    //     }
    //     append_to_log_file("\n");
    // }
}

void vainqueurCondorcet(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{
    graph *graphe;
    int nbCandidats = graphe->nbSommet;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);
    char *vainqueur = NULL;
    for (unsigned i = 0; i < nbCandidats; i++)
    {
        sommet *s = graphe->sommets[i];
        if (s->nbPredecesseur == 0)
            vainqueur = s->nom;
    }

    /*TODO : Print logs*/
    liberer_graph(graphe);
    afficher_res(NOM_METHODE_CDC, nbCandidats, nbElecteurs, vainqueur != NULL ? vainqueur : "Pas de vainqueur", NULL);
}

void vainqueurCondorcetMinimax(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{
    /**
     * On regarde, pour les arcs entrants de chaque sommet (représentant les défaites),
     * celui avec le poids le plus elevé, et donc celui avec la pire défaite.
     * Le sommet avec la pire défaite la plus basse remporte le scrutin
     */

    graph *graphe;
    sommet *vainqueur;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);
    int nbSommets = graphe->nbSommet;
    int pireDefaite[nbSommets];
    int min;
    char *vainqueurMinimax;
    int nbCandidats = graphe->nbSommet;

    for (unsigned i = 0; i < nbSommets; i++)
    {
        /*Initialisation du tableau des pires défaites (leur défaite avec le poids le plus élevé)*/

        pireDefaite[i] = 0;
        /**
         * Remarque : si un sommet n'a aucune défaite, sa valeur reste à 0, il est donc déclaré vainqueur car sa pire défaite
         * sera la plus basse.
         */
    }

    for (unsigned i = 0; i < nbSommets; i++)
    {
        for (unsigned j = 0; j < graphe->nbArc; j++)
        {
            if (graphe->arcs[j]->arrivee == graphe->sommets[i]) /*Le sommet représente-t-il l'arrivée d'un arc? (donc perd un duel)*/
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
        if (pireDefaite[i] < min)
        {
            min = pireDefaite[i];
            vainqueur = graphe->sommets[i];
        }
    }

    /*TODO : Print logs*/
    vainqueurMinimax = vainqueur->nom;
    afficher_res(NOM_METHODE_CDC_MNMX, nbCandidats, nbElecteurs, vainqueurMinimax != NULL ? vainqueurMinimax : "Pas de vainqueur", NULL);
    liberer_graph(graphe);
}

char *vainqueurCondorcetSchulzeSimpl(t_mat_int_dyn *matrice, char **entete)
{
    /**
     * Retirer successivements les arcs de poids minimal jusqu'à retrouver un vainqueur de Condorcet
     * Si égalité, renvoyer tous les sommets restants après avoir retiré tous les arcs
     */

    graph *graphe;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);
    int n = graphe->nbSommet;
    sommet *vainqueur;
    char *vainqueurSchulze;
    for (unsigned i = 0; i < n; i++)
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
    vainqueurSchulze = vainqueur->nom;
    liberer_graph(graphe);

    return vainqueurSchulze;
}

// // sommet *vainqueurCondorcetSchulze(t_mat_char_star_dyn *matrice)
// // {
// //     graph *graphe;
// //     graphe = creer_graphe_de_matrice_char(matrice);

// //     for (unsigned i = 0; i < graphe->nbSommet; i++)
// //     {
// //         if (!appartientEnsembleDeSchwartz(graphe->sommets[i], ensembleDeSchwartz(graphe, graphe->nbSommet), graphe->nbSommet))
// //         {
// //             free(graphe->sommets[i]);
// //             for (unsigned j = 0; j < graphe->nbArc; j++)
// //             {
// //                 if (graphe->arcs[j]->depart == NULL || graphe->arcs[j]->arrivee == NULL)
// //                 {
// //                     enlever_arc(graphe, graphe->arcs[j]);
// //                 }

// //             }

// //         }
// //     }
// // }

// sommet *vainqueurCondorcetPaires(t_mat_int_dyn *matrice, char **entete)
// {
//     /**
//      * (*) Verifier si un cycle est formé (voire algorithmes de dijkstra et bellman-ford)
//      * (*) Supprimer l'arc de poids minimal de ce cycle
//      * (*) Répeter jusqu'a obtenir un vainqueur de condorcet (P- == 0)
//      */
//     graph *graphe;
//     // graphe = creer_graphe_de_matrice_char(matrice);
//     sommet *vainqueur = NULL;
//     return vainqueur;
// }

arc *arcDePoidsMinimal(graph *graphe)
{

    if (graphe->nbArc == 0)
    {
        return NULL;
    }
    arc *arcPoidsMin = graphe->arcs[0];
    for (int i = 1; i < graphe->nbArc; i++)
    {
        if (graphe->arcs[i]->poids < arcPoidsMin->poids)
        {
            arcPoidsMin = graphe->arcs[i];
        }
    }

    return arcPoidsMin;
}

// int appartientEnsembleDeSchwartz(sommet *candidat, sommet **groupeDeTete, int tailleGroupeDeTete)
// {

//     /*Le candidat n'a perdu aucune confrontation contre un membre du groupe de tête*/
//     for (unsigned i = 0; i < tailleGroupeDeTete; i++)
//     {
//         for (unsigned j = 0; j < candidat->nbPredecesseur; j++)
//         {
//             if (groupeDeTete[i] == candidat->tabPredecesseur[i])
//             {
//                 return 0;
//             }
//         }
//     }

//     /*Le candidat appartient à un groupe de tête minimal*/
//     for (unsigned i = 0; i < tailleGroupeDeTete; i++)
//     {
//         for (unsigned j = 0; j < candidat->nbSuccesseur; j++)
//         {
//             if (groupeDeTete[i] == candidat->tabSuccesseur[i])
//             {
//                 return 0;
//             }
//         }
//     }

//     /*Vérifier si tout candidat qui "bat indirectement" A est aussi "battu indirectement" par A*/
//     for (int i = 0; i < tailleGroupeDeTete; i++)
//     {
//         for (int j = 0; j < candidat->nbPredecesseur; j++)
//         {
//             sommet *concurrent = candidat->tabPredecesseur[j];

//             /*Vérifier si le concurrent "bat indirectement" A*/
//             if (!appartientEnsembleDeSchwartz(concurrent, groupeDeTete, tailleGroupeDeTete))
//             {
//                 /*Vérifier si A "battu indirectement" le concurrent*/
//                 for (int k = 0; k < candidat->nbSuccesseur; k++)
//                 {
//                     if (candidat->tabSuccesseur[k] == concurrent)
//                     {
//                         return 0;
//                     }
//                 }
//             }
//         }
//     }
//     return 1;
// }

// sommet **ensembleDeSchwartz(graph *graphe, int *tailleEnsemble)
// {

//     int nbSommetsMax = graphe->nbSommet;
//     sommet **ensembleSchwartz = (sommet **)malloc(nbSommetsMax * sizeof(sommet *));
//     int tailleEnsembleSchwartz = 0;

//     for (unsigned i = 0; i < nbSommetsMax; i++)
//     {
//         if (appartientEnsembleDeSchwartz(graphe->sommets[i], graphe->sommets, graphe->nbSommet))
//         {
//             ensembleSchwartz[tailleEnsembleSchwartz++] = graphe->sommets[i];
//         }
//     }
//     *tailleEnsemble = tailleEnsembleSchwartz;

//     return ensembleSchwartz;
// }
