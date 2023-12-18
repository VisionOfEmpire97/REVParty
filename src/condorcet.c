/**
 * \author Équipe 001 (ZERKANI Yanis)
 * \date 17 Decembre 2023
 * \brief Proposition d'implémentation des trois solveurs du paradoxe de condorcet.
 * \file condorcet.c
 */

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

/**********************************************************************************************
 *                                                                                            *
 *                                 LOGS                                                       *
 *                                                                                            *
 **********************************************************************************************/

char buf[200]; /*Buffer pour la concatenation des logs*/

/**
 * @brief Affiche dans les logs les resultats des différents duels
 *
 * @param mat_duels La matrice de deuls.
 * @param entete L'entete des candidats.
 */
void duelsToLog(t_mat_int_dyn *mat_duels, char **entete)
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
                    ++compteur, entete[i], scoreCandidat1, entete[j], scoreCandidat2, scoreCandidat1 > scoreCandidat2 ? entete[i] : entete[j],
                    scoreCandidat1 > scoreCandidat2 ? scoreCandidat1 - scoreCandidat2 : scoreCandidat2 - scoreCandidat1);
            append_to_log_file(buf);
        }
    }
    append_to_log_file("\n");
}

/**
 * @brief Affiche dans les logs la liste des arcs d'un graph donné.
 * @param g Le graph.
 */
void arcsToLog(graph *g)
{

    sprintf(buf, "\n[CDC] Graph des confrontations :\n\n");
    append_to_log_file(buf);
    for (int j = 0; j < (g->nbArc); j++)
    {
        sprintf(buf, "%-20s \t---%d---> (%s)\n", (((g->arcs[j])->depart)->nom), ((g->arcs[j])->poids), (((g->arcs[j])->arrivee)->nom));
        append_to_log_file(buf);
    }
    append_to_log_file("\n");
}

/**********************************************************************************************
 *                                                                                            *
 *                                 UTILS                                                      *
 *                                                                                            *
 **********************************************************************************************/

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

/**
 * @brief Trie dans l'ordre décroissant les arcs d'un graphe donné, tout en accordant une pondération unique si des égalités existent.
 * @details La nouvelle pondération respecte les rapports de force précédents. Si deux arcs ont un poids égal, on incrémente en premier
 * celui dont l'origine à le plus grand nombre de victoires.
 *
 * @param g Le graph.
 */
void triArcsDecroissant(graph *g)
{
    sprintf(buf, "[CDC_P] Arcs avant tri : \n\n");
    append_to_log_file(buf);
    arcsToLog(g);

    arc *arc_temp;
    for (int i = 0; i < g->nbArc; i++)
    {
        for (int j = i + 1; j < g->nbArc; j++)
        {
            if (g->arcs[j]->poids > g->arcs[i]->poids)
            {
                arc_temp = g->arcs[i];
                g->arcs[i] = g->arcs[j];
                g->arcs[j] = arc_temp;
            }
            else if (g->arcs[j]->poids == g->arcs[i]->poids)
            {
                if (g->arcs[j]->depart->nbSuccesseur > g->arcs[i]->depart->nbSuccesseur)
                {
                    arc_temp = g->arcs[i];
                    g->arcs[i] = g->arcs[j];
                    g->arcs[j] = arc_temp;
                }
            }
        }
        for (int k = i; k > 0; k--)
        {
            if (k > 0 && g->arcs[k]->poids == g->arcs[k - 1]->poids)
            {
                g->arcs[k - 1]->poids++;
            }
        }
    }

    sprintf(buf, "[CDC_P] Arcs après tri : \n\n");
    append_to_log_file(buf);
    arcsToLog(g);
}

/**
 * @brief Remet à 0 la liste des successeurs et predecesseurs d'un graph pour le reparcourir à nouveau arc par arc.
 *
 * @param graphe Le graph.
 */
void resetDictionnaire(graph *graphe)
{
    sommet *s;

    for (unsigned i = 0; i < graphe->nbSommet; i++)
    {
        s = graphe->sommets[i];
        for (int i = 0; i < s->nbSuccesseur; i++)
        {
            s->tabSuccesseur[i] = NULL;
        }
        s->nbSuccesseur = 0;
        for (int i = 0; i < s->nbPredecesseur; i++)
        {
            s->tabPredecesseur[i] = NULL;
        }
        s->nbPredecesseur = 0;
    }
}

/**
 * @brief Fonction booléenne récursive qui vérifie si un chemin existe entre deux sommets.
 * @details On procède en regardant les successeurs du premier sommets, puis les successeurs des successeurs jusqu'à retrouver
 * le second sommet. On parcours ainsi tous les chemins possibles en partant de sommet1 pour voir s'il mène à sommet 2.
 *
 * @param sommet1 Sommet de départ.
 * @param sommet2 Sommet d'arrivée.
 * @return true si un chemin existe entre deux sommets,
 * @return false sinon.
 */
bool existeChemin(sommet *sommet1, sommet *sommet2)
{
    /*Si le sommet de départ ne possède aucun successeur, on entre pas dans la boucle*/
    for (unsigned i = 0; i < sommet1->nbSuccesseur; i++)
    {
        /*sommet2 est-il un successeur direct de sommet1?*/
        if (sommet2->nom ==  sommet1->tabSuccesseur[i]->nom)
        {
            sprintf(buf, "[CDC_P] Chemin entre %s et %s existe\n", sommet1->nom, sommet2->nom);
            append_to_log_file(buf);
            sprintf(buf, "[CDC_P] Successeurs de %s :", sommet1->nom);
            append_to_log_file(buf);
            for (unsigned j = 0; j < sommet1->nbSuccesseur; j++)
            {
                sprintf(buf, " %s ", sommet1->tabSuccesseur[j]->nom);
                append_to_log_file(buf);
            }
            append_to_log_file("\n");
            return true;
        }
        else
        {
            sprintf(buf, "[CDC_P] Pas de chemin direct entre %s et %s. On regarde le successeur %s de %s.\n", sommet1->nom, sommet2->nom, sommet1->tabSuccesseur[i]->nom, sommet1->nom);
            append_to_log_file(buf);
            if (existeChemin(sommet1->tabSuccesseur[i], sommet2))
            {
                return true;
            }
        }
    }
    sprintf(buf, "[CDC_P] Pas de chemin entre %s et %s\n", sommet1->nom, sommet2->nom);
    append_to_log_file(buf);
    return false; // Aucun chemin trouvé
}

/**
 * @brief Renvoie le graph donné sans ses circuits.
 *
 * @param graphe Le graph.
 */
void retirerCircuits(graph *graphe)
{
    sommet *depart, *arrivee;
    resetDictionnaire(graphe);
    int i = 0;
    while (i < graphe->nbArc)
    {
        depart = graphe->arcs[i]->depart;
        arrivee = graphe->arcs[i]->arrivee;
        sprintf(buf, "[CDC_P] Analyse de l'arc (%s - %s).\n", depart->nom, arrivee->nom);
        append_to_log_file(buf);
        if (!existeChemin(arrivee, depart))
        {

            sprintf(buf, "[CDC_P] L'arc (%s - %s) ne crée pas de cycle, on le conserve.\n\n", depart->nom, arrivee->nom);
            append_to_log_file(buf);
            depart->tabSuccesseur[depart->nbSuccesseur++] = arrivee;
            arrivee->tabPredecesseur[arrivee->nbPredecesseur++] = depart;
            i++;
        }
        else
        {
            sprintf(buf, "[CDC_P] Arc retiré (cycle détecté) : %s -> %s (Poids : %d)\n\n",
                    graphe->arcs[i]->depart->nom, graphe->arcs[i]->arrivee->nom, graphe->arcs[i]->poids);
            append_to_log_file(buf);
            enlever_arc(graphe, graphe->arcs[i]);
        }
    }
    directed_graph_to_dot(graphe, "log/graphe_condorcet_paire_sans_cycle.dot");
}

/**********************************************************************************************
 *                                                                                            *
 *                                 CONDORCET                                                  *
 *                                                                                            *
 **********************************************************************************************/

/**
 * \brief Retourne le vainqueur du suffrage selon la méthode de Condorcet. Si vainqueurCondorcet == NULL,
 * on fait appel aux méthodes de résolution du paradoxe de Condorcet implémentées.
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
            // Le candidat qui n'a perdu aucun duel
            vainqueur = graphe->sommets[i]->nom;
        }
    }
    arcsToLog(graphe);
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

/**********************************************************************************************
 *                                                                                            *
 *                                 CONDORCET_MINIMAX                                          *
 *                                                                                            *
 **********************************************************************************************/

void condorcet_minimax(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{
    /**
     * On regarde, pour les arcs entrants de chaque sommet (représentant les défaites),
     * celui avec le poids le plus elevé, et donc celui avec la pire défaite.
     * Le sommet avec la pire défaite la plus basse remporte le scrutin
     */
    duelsToLog(matrice, entete);

    char *vainqueurMinimax, *vainqueurDeCondorcet;
    int nbCandidats = matrice->col;
    graph *graphe;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);
    directed_graph_to_dot(graphe, "log/graphe_condorcet_origine.dot");

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

        sprintf(buf, "\n[CDC_MX] %s est le candidat ayant la pire défaite la plus basse, avec un poids de %d.\n", graphe->sommets[indiceVainqueur]->nom, min);
        append_to_log_file(buf);

        for (unsigned i = 0; i < nbSommets; i++)
        {
            if (piresDefaites[i] == min && i != indiceVainqueur)
            {
                sprintf(buf, "[CDC_MX] Le candidat %s à un score equivalent. Deul entre %s et %s.\n", graphe->sommets[i]->nom, graphe->sommets[i]->nom, graphe->sommets[indiceVainqueur]->nom);
                append_to_log_file(buf);
                if (trouver_direction_arc(graphe->sommets[i], graphe->sommets[indiceVainqueur]) == 1)
                {
                    indiceVainqueur = i;
                }                            
                sprintf(buf, "[CDC_MX] Le candidat %s ressort vainqueur du duel dans le graph initial.\n", graphe->sommets[indiceVainqueur]->nom);  
                append_to_log_file(buf);
            }
        }

        vainqueurMinimax = graphe->sommets[indiceVainqueur]->nom;

        sprintf(buf, "[CDC_MX] %s est déclaré vainqueur selon la méthode de Condorcet minimax.\n\n", vainqueurMinimax);
        append_to_log_file(buf);
    }
    liberer_graph(graphe);
    afficher_res(NOM_METHODE_CDC_MNMX, nbCandidats, nbElecteurs, vainqueurMinimax, NULL);
}

/**********************************************************************************************
 *                                                                                            *
 *                                 CONDORCET_PAIRES                                           *
 *                                                                                            *
 **********************************************************************************************/

void condorcet_paires(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{
    duelsToLog(matrice, entete);

    char *vainqueurPaires, *vainqueurDeCondorcet;
    int nbCandidats = matrice->col;
    graph *graphe;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);
    directed_graph_to_dot(graphe, "log/graphe_condorcet_origine.dot");

    if ((vainqueurDeCondorcet = vainqueurCondorcet(graphe)) != NULL)
    {
        vainqueurPaires = vainqueurDeCondorcet;
    }
    else
    {
        sprintf(buf, "[CDC_P] Résolution du paradoxe avec la méthode des paires par ordre decroissant.\n\n");
        append_to_log_file(buf);
        sprintf(buf, "[CDC_P] Tri des arcs dans l'ordre décroissant des poids (sans ex-aequo).\n\n");
        append_to_log_file(buf);

        triArcsDecroissant(graphe);

        retirerCircuits(graphe);

        vainqueurPaires = vainqueurCondorcet(graphe);
    }
    liberer_graph(graphe);
    afficher_res(NOM_METHODE_CDC_P, nbCandidats, nbElecteurs, vainqueurPaires, NULL);
}

/**********************************************************************************************
 *                                                                                            *
 *                                 CONDORCET_SCHULZE                                          *
 *                                                                                            *
 **********************************************************************************************/

void condorcet_Schulze(t_mat_int_dyn *matrice, char **entete, int nbElecteurs)
{

    /**
     * Retirer successivements les arcs de poids minimal jusqu'à retrouver un vainqueur de Condorcet
     * Si égalité, renvoyer tous les sommets restants après avoir retiré tous les arcs
     */
    duelsToLog(matrice, entete);

    char *vainqueurSchulze, *vainqueurDeCondorcet;
    int nbCandidats = matrice->col;
    graph *graphe;
    arc *arcMinimal;
    graphe = creer_graphe_de_matrice_duel(matrice, entete);
    directed_graph_to_dot(graphe, "log/graphe_condorcet_origine.dot");

    if (!vainqueurCondorcet(graphe))
    {
        sprintf(buf, "[CDC_S] Résolution du paradoxe avec la méthode Schulze.\n\n");
        append_to_log_file(buf);
    }

    while ((vainqueurDeCondorcet = vainqueurCondorcet(graphe)) == NULL)
    {
        arcsToLog(graphe);
        arcMinimal = arcDePoidsMinimal(graphe);
        sprintf(buf, "[CDC_S] Arc retiré: %s -> %s (Poids : %d)\n\n",
                arcMinimal->depart->nom, arcMinimal->arrivee->nom, arcMinimal->poids);
        append_to_log_file(buf);
        enlever_arc(graphe, arcMinimal);
    }
    directed_graph_to_dot(graphe, "log/graphe_condorcet_shulze.dot");
    vainqueurSchulze = vainqueurDeCondorcet;
    liberer_graph(graphe);
    afficher_res(NOM_METHODE_CDC_SCH, nbCandidats, nbElecteurs, vainqueurSchulze, NULL);
}