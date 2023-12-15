#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "condorcet.h"
#include "utils_sd/graph.h"
#include "utils_sd/util_log.h"
#include "utils_sd/arg_parse_util.h"
#define NOM_METHODE_CDC_MNMX "Condorcet minimax"
#define NOM_METHODE_CDC_SCH "Condorcet Schulze"
#define NOM_METHODE_CDC_P "Condorcet paires"
#define MAX_INT 998

char buf[200];

/**
 * \brief Fonction permettant de retrouver l'arc de poids minimal d'un graphe.
 * Fonction utile pour le fonctionnement de la méthode Schulze.
 *
 * \param[in] graph Le graphe pondéré des duels.
 * \returns L'arc de poids minimal du graphe.
 */
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

void redistributionPoidsUnique(arc **arcs, int nbArcs)
{
    for (unsigned i = 0; i < nbArcs; i++)
    {
        arcs[i]->poids *= 2;
    }
    for (unsigned i = 0; i < nbArcs - 1; i++)
    {
        for (unsigned j = i + 1; j < nbArcs; j++)
        {
            if (arcs[i]->poids == arcs[j]->poids)
            {
                arcs[i]->depart->nbSuccesseur > arcs[j]->depart->nbSuccesseur ? arcs[i]->poids++ : arcs[j]->poids++;
            }
        }
    }
}

void triArcsDecroissant(graph *g)
{
    arc *temp;
    for (int i = 0; i < g->nbArc - 1; i++)
    {
        for (int j = i + 1; j < g->nbArc; j++)
        {
            if (g->arcs[j]->poids > g->arcs[i]->poids)
            {
                temp = g->arcs[i];
                g->arcs[i] = g->arcs[j];
                g->arcs[j] = temp;
            }
        }
    }
}

void union_f(sommet *s, sommet *racine)
{
    s->CC = racine;
}

void retirerCircuits(graph *graphe)
{

    sommet *depart, *arrivee;
    int i = 0;

    while (graphe->nbArc > i)
    {
        depart = graphe->arcs[i]->depart;
        arrivee = graphe->arcs[i]->arrivee;
        if (depart->CC != arrivee->CC)
        {
            // printf("CC %s = %s , CC %s = %s\n", depart->nom, depart->CC->nom, arrivee->nom, arrivee->CC->nom);
            union_f(arrivee, depart->CC);
            i++;
        }
        else
        {
            printf("Arc retiré (cycle détecté) : %s -> %s (Poids : %d)\n",
                   graphe->arcs[i]->depart->nom, graphe->arcs[i]->arrivee->nom, graphe->arcs[i]->poids);
            enlever_arc(graphe, graphe->arcs[i]);
        }
    }
    
    // afficher_graph(graphe);
}

void afficherDuels(t_mat_int_dyn *mat_duels, char **entete)
{
    int nbCandidats = mat_duels->col;
    int compteur = 0, scoreCandidat1, scoreCandidat2;

    for (unsigned i = 0; i < nbCandidats; i++)
    {
        for (unsigned j = i + 1; j < nbCandidats; j++)
        {
            scoreCandidat1 = mat_duels->matrice[i][j];
            scoreCandidat2 = mat_duels->matrice[j][i];
            sprintf(buf, "[CDC] Duel %2d => %s (%2d victoires) vs %s (%2d victoires) => Vainqueur: %s(Score=%2d)\n",
                    ++compteur, entete[i], scoreCandidat1, entete[j], scoreCandidat2, scoreCandidat1 > scoreCandidat2 ? entete[i] : entete[j], scoreCandidat1 > scoreCandidat2 ? scoreCandidat1 - scoreCandidat2 : scoreCandidat2 - scoreCandidat1);
            append_to_log_file(buf);
        }
    }
    append_to_log_file("\n");
}



/**
 * \brief Retourne le vainqueur du suffrage selon la méthode de Condorcet. Si vainqueurCondorcet == NULL,
 * on doit faire appel aux méthodes de résolution du paradoxe de Condorcet.
 *
 * \param[in] matrice Le matrice de duels du fichier csv du scrutin, qu'on transformera en graphe.
 * \param[in] entete L'entete contenant les candidats du scrutin, utile pour la création du graphe.
 * \result Le vainqueur, s'il existe (NULL sinon), selon la méthode Condorcet.
 *
 */
char *vainqueurCondorcet(graph *graphe)
{

    int nbCandidats = graphe->nbSommet;

    char *vainqueur = NULL;

    /**Vérifications du déroulement des duels, création de logs*/

    for (unsigned i = 0; i < nbCandidats; i++)
    {
        sprintf(buf, "[CDC] Candidat %s => Nombre de duels remportés: %2d. Nombre de duels perdus: %2d. Nombre total de participants: %2d\n",
                graphe->sommets[i]->nom, graphe->sommets[i]->nbSuccesseur, graphe->sommets[i]->nbPredecesseur, nbCandidats);
        append_to_log_file(buf);
        if (graphe->sommets[i]->nbPredecesseur == 0)
        {
            vainqueur = graphe->sommets[i]->nom;
        }
    }
    if (vainqueur)
    {
        sprintf(buf, "\n[CDC] Le candidat %s est déclaré vainqueur de Condorcet.\n\n", vainqueur);
        append_to_log_file(buf);
    }
    else
    {
        sprintf(buf, "\n[CDC] Aucun candidat n'est déclaré vainqueur de Condorcet.\n\n");
        append_to_log_file(buf);
    }
    return vainqueur;
}

void condorcet_minimax(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{
    /**
     * On regarde, pour les arcs entrants de chaque sommet (représentant les défaites),
     * celui avec le poids le plus elevé, et donc celui avec la pire défaite.
     * Le sommet avec la pire défaite la plus basse remporte le scrutin
     */
    afficherDuels(matrice, entete);

    char *vainqueurMinimax, *vainqueurDeCondorcet;
    int nbCandidats = matrice->col;
    graph *graphe;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);

    if ((vainqueurDeCondorcet = vainqueurCondorcet(graphe)) != NULL)
    {
        vainqueurMinimax = vainqueurDeCondorcet;
    }
    else
    {
        sprintf(buf, "[CDC_MX] Résolution du paradoxe avec la méthode minimax.\n\n");
        append_to_log_file(buf);

        int nbSommets = graphe->nbSommet;
        int piresDefaites[nbSommets];
        for (unsigned i = 0; i < nbSommets; i++)
        {
            /*Initialisation du tableau des pires défaites (leur défaite avec le poids le plus élevé)*/

            piresDefaites[i] = 0;
            /**
             * Remarque : on suppose que chaque sommet à au moins une défaite, auquel cas il n'y a pas de vainqueur de condorcet.
             */
        }

        for (unsigned i = 0; i < nbSommets; i++)
        {
            for (unsigned j = 0; j < graphe->nbArc; j++)
            {
                if (graphe->arcs[j]->arrivee == graphe->sommets[i]) /*Le sommet représente-t-il l'arrivée d'un arc? (donc perd un duel)*/
                {
                    if (graphe->arcs[j]->poids > piresDefaites[i])
                    {
                        piresDefaites[i] = graphe->arcs[j]->poids;
                    }
                }
            }
        }

        /*Recherche linéaire du minimum de piresDefaites*/
        int indiceVainqueur, min = MAX_INT;

        for (unsigned i = 0; i < nbSommets; i++)
        {
            sprintf(buf, "[CDC_MX] Pire défaite du candidat %-s: %d\n", graphe->sommets[i]->nom, piresDefaites[i]);
            append_to_log_file(buf);
            if (piresDefaites[i] < min)
            {
                min = piresDefaites[i];
                indiceVainqueur = i;
            }
        }

        vainqueurMinimax = graphe->sommets[indiceVainqueur]->nom;

        sprintf(buf, "\n[CDC_MX] %s est le candidat ayant la pire défaite la plus basse, avec un poids de %d.\n", vainqueurMinimax, min);
        append_to_log_file(buf);
        sprintf(buf, "[CDC_MX] %s est déclaré vainqueur selon la méthode de Condorcet minimax.\n\n", vainqueurMinimax);
        append_to_log_file(buf);
    }
    afficher_res(NOM_METHODE_CDC_MNMX, nbCandidats, nbElecteurs, vainqueurMinimax, NULL);
    liberer_graph(graphe);
}

void condorcet_paires(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{
    afficherDuels(matrice, entete);

    char *vainqueurPaires, *vainqueurDeCondorcet;
    int nbCandidats = matrice->col;
    graph *graphe;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);

    if ((vainqueurDeCondorcet = vainqueurCondorcet(graphe)) != NULL)
    {
        vainqueurPaires = vainqueurDeCondorcet;
    }
    else
    {
        sprintf(buf, "[CDC_P] Résolution du paradoxe avec la méthode des paires par ordre decroissants.\n\n");
        append_to_log_file(buf);


        printf("premier affichage\n");

        triArcsDecroissant(graphe);
        afficher_graph(graphe);
        // redistributionPoidsUnique(graphe->arcs, graphe->nbArc);
        // triArcsDecroissant(graphe);

        printf("second affichage\n");
        afficher_graph(graphe);
        // afficher_matrice_int(matrice);

        retirerCircuits(graphe);

        // vainqueurCondorcet(graphe);

        for (unsigned i = 0; i < nbCandidats; i++)
        {
            if (graphe->sommets[i]->nbPredecesseur == 0)
            {
                vainqueurPaires = graphe->sommets[i]->nom;
            }
        }
    }
    liberer_graph(graphe);
    afficher_res(NOM_METHODE_CDC_P, nbCandidats, nbElecteurs, vainqueurPaires, NULL);
}

void condorcet_Schulze(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{

    /**
     * Retirer successivements les arcs de poids minimal jusqu'à retrouver un vainqueur de Condorcet
     * Si égalité, renvoyer tous les sommets restants après avoir retiré tous les arcs
     */
    afficherDuels(matrice, entete);

    char *vainqueurSchulze, *vainqueurDeCondorcet;
    int nbCandidats = matrice->col;
    graph *graphe;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);

    if (!vainqueurCondorcet(graphe))
    {
        sprintf(buf, "[CDC_S] Résolution du paradoxe avec la méthode Schulze.\n\n");
        append_to_log_file(buf);
    }
    
    while ((vainqueurDeCondorcet = vainqueurCondorcet(graphe)) == NULL)
    {
        enlever_arc(graphe, arcDePoidsMinimal(graphe));
    }
    vainqueurSchulze = vainqueurDeCondorcet;
    liberer_graph(graphe);
    afficher_res(NOM_METHODE_CDC_SCH, nbCandidats, nbElecteurs, vainqueurSchulze, NULL);
}