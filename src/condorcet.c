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
#define MAX_INT 999

/**
 * \brief Fonction permettant de retrouver l'arc de poids minimal d'un graphe.
 * Fonction utile pour le fonctionnement des méthodes Paires et Schulze.
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

/**
 * \brief Retourne le vainqueur du suffrage selon la méthode de Condorcet. Si vainqueurCondorcet == NULL,
 * on doit faire appel aux méthodes de résolution du paradoxe de Condorcet.
 *
 * \param[in] matrice Le matrice de duels du fichier csv du scrutin, qu'on transformera en graphe.
 * \param[in] entete L'entete contenant les candidats du scrutin, utile pour la création du graphe.
 * \result Le vainqueur, s'il existe (NULL sinon), selon la méthode Condorcet.
 *
 */
char *vainqueurCondorcet(t_mat_int_dyn *matrice, char **entete)
{
    graph *graphe;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);

    int nbCandidats = graphe->nbSommet;
    int compteur = 0, scoreCandidat1, scoreCandidat2;
    char buff[200];
    char *vainqueur = NULL;

    /**Vérifications du déroulement des duels, création de logs*/
    for (unsigned i = 0; i < nbCandidats; i++)
    {
        for (unsigned j = i + 1; j < nbCandidats; j++)
        {
            scoreCandidat1 = matrice->matrice[i][j];
            scoreCandidat2 = matrice->matrice[j][i];
            sprintf(buff, "[CDC] Duel %2d => %-35s \t(%2d victoires) \tvs %-30s \t(%2d victoires) => Vainqueur: %s.\n",
                    ++compteur, entete[i], scoreCandidat1, entete[j], scoreCandidat2, scoreCandidat1 > scoreCandidat2 ? entete[i] : entete[j]);
            append_to_log_file(buff);
        }
    }
    append_to_log_file("\n");
    for (unsigned i = 0; i < nbCandidats; i++)
    {
        sprintf(buff, "[CDC] Candidat %-35s \t=> Nombre de duels remportés: %2d. Nombre de duels perdus: %2d. Nombre total de participants: %2d\n",
                graphe->sommets[i]->nom, graphe->sommets[i]->nbSuccesseur, graphe->sommets[i]->nbPredecesseur, nbCandidats);
        append_to_log_file(buff);
        if (graphe->sommets[i]->nbPredecesseur == 0)
        {
            vainqueur = graphe->sommets[i]->nom;
        }
    }
    if (vainqueur)
    {
        sprintf(buff, "\n[CDC] Le candidat %s est déclaré vainqueur de Condorcet.\n\n", vainqueur);
        append_to_log_file(buff);
    }else
    {
        sprintf(buff, "\n[CDC] Aucun candidat n'est déclaré vainqueur de Condorcet.\n\n");
        append_to_log_file(buff);
    }
    

    liberer_graph(graphe);
    return vainqueur;
}

void condorcet_minimax(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{
    /**
     * On regarde, pour les arcs entrants de chaque sommet (représentant les défaites),
     * celui avec le poids le plus elevé, et donc celui avec la pire défaite.
     * Le sommet avec la pire défaite la plus basse remporte le scrutin
     */

    char *vainqueurMinimax, *vainqueurDeCondorcet;
    char buff[200];
    int nbCandidats = matrice->col;

    if ((vainqueurDeCondorcet = vainqueurCondorcet(matrice, entete)) != NULL)
    {
        vainqueurMinimax = vainqueurDeCondorcet;
    }
    else
    {
        sprintf(buff, "[CDC_MX] Résolution du paradoxe avec la méthode minimax.\n\n");
        append_to_log_file(buff);

        graph *graphe;
        graphe = creer_graphe_de_matrice_duel(matrice, entete);
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
            sprintf(buff, "[CDC_MX] Pire défaite du candidat %-s: %d\n", graphe->sommets[i]->nom, piresDefaites[i]);
            append_to_log_file(buff);
            if (piresDefaites[i] < min)
            {
                min = piresDefaites[i];
                indiceVainqueur = i;
            }
        }
        vainqueurMinimax = graphe->sommets[indiceVainqueur]->nom;

        /*TODO : Print logs*/
        sprintf(buff, "\n[CDC_MX] %s est le candidat ayant la pire défaite la plus basse, avec un poids de %d.\n", vainqueurMinimax, min);
        append_to_log_file(buff);
        sprintf(buff, "[CDC_MX] %s est déclaré vainqueur selon la méthode de Condorcet minimax.\n\n", vainqueurMinimax);
        append_to_log_file(buff);
        liberer_graph(graphe);
    }
    afficher_res(NOM_METHODE_CDC_MNMX, nbCandidats, nbElecteurs, vainqueurMinimax, NULL);
}

void condorcet_paires(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{
    /**
     * (*) Verifier si un cycle est formé (voire algorithmes de dijkstra et bellman-ford)
     * (*) Supprimer l'arc de poids minimal de ce cycle
     * (*) Répeter jusqu'a obtenir un vainqueur de condorcet (P- == 0)
     */
    graph *graphe;
    // graphe = creer_graphe_de_matrice_char(matrice);
    sommet *vainqueur = NULL;
    return;
}

void condorcet_Schulze(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
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
    return;
}
