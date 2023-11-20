/**
 * \author Équipe 001 (JOSEPH REMY)
 * \date 10 Novembre 2023
 * \brief Fichier de definition de la structure de donnée
 * \file graph.h
 */
#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdlib.h>
#include <stdio.h>
#include "matrice.h"
/** \defgroup ADTGraph Graph
 *  Documentation de l'implémentation de la structure de données Graph
 * @{*/
/**
 * \defgroup Type Type de données
 * Types de données utilisés afin de manipuler des graph
 *@{
 */
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
/**
 * @}
 */
/**
 * \defgroup Cons Constructeur du tad graph
 * Types de données utilisés afin de manipuler des graph
 *@{
 */

/// \brief Creer un sommet
/// \param nom Le nom du sommet
/// \return Le sommet
sommet *creer_sommet(char *nom);

/// @brief Creer un arc
/// @param arrivee Le sommet de destination de l'arc
/// @param depart Le sommet de depart de lars
/// @param poids Le poids de l'arc
/// @return Un arc
arc *creer_arc(sommet *arrivee, sommet *depart, int poids);

/// @brief Creer un graphe
/// @return Une structure vide de graph sans sommet
graph *creer_graph();

/// @brief Ajouter un sommet a un graph
/// @param g le graph
/// @param s le sommet
/// @return le nombre de sommets dans le graph
int ajouter_sommet(graph *g, sommet *s);

/// @brief Ajouter un arc a un graph
/// @param g Le graph
/// @param a L'arc
/// @return Le nombre d'arc du graph
int ajouter_arc(graph *g, arc *a);

/// @brief Creer un graph avec un matrice de chaine de charactere en entree
/// @param mat La matrice de chaine de charactere
/// @return Un graph
graph *creer_graphe_de_matrice_char(t_mat_char_star_dyn *mat);

/// @brief Construit un grap a partie d'une matrice de duel et une liste des noms des sommets
/// @param mat_duel
/// @param listeNomSommets
/// @return Un graph
graph *creer_graphe_de_matrice_duel(t_mat_int_dyn *mat_duel, char **listeNomSommets);

/// @brief affiche le graphe passe en parametre
/// @param g Un graph
void afficher_graph(graph *g);

/// @brief libere la memoire alloue a la strcture graph et les sous structures
/// @param g Un graph
void liberer_graph(graph *g);
#endif