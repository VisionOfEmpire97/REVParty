#include <stdlib.h>
#include "matrice.h"
#include "graph.h"

sommet *creer_sommet(char *nom)
{
    sommet *s = malloc(sizeof(sommet));
    s->nom = nom;
    s->nbPredecesseur = 0;
    s->nbSuccesseur = 0;
    s->tabSuccesseur = NULL;
    s->tabPredecesseur = NULL;
    s->CC = s;
    return s;
}
void liberer_graph(graph *g)
{
    for (int i = 0; i < (g->nbSommet); i++)
    {
        free((g->sommets)[i]->tabPredecesseur);
        free((g->sommets)[i]->tabSuccesseur);
        free((g->sommets)[i]);
    }
    for (int i = 0; i < (g->nbArc); i++)
    {
        free((g->arcs)[i]);
    }
    free(g->arcs);
    free(g->sommets);
    free(g);
}

arc *creer_arc(sommet *arrivee, sommet *depart, int poids)
{

    arc *a = malloc(sizeof(arc));
    a->arrivee = arrivee;
    a->depart = depart;
    a->poids = poids;
    return a;
}

graph *creer_graph()
{

    graph *g = malloc(sizeof(graph));
    g->sommets = NULL;
    g->nbSommet = 0;
    g->arcs = NULL;
    g->nbArc = 0;
    return g;
}

int ajouter_sommet(graph *g, sommet *s)
{

    int nbs = (++(g->nbSommet));
    g->sommets = realloc(g->sommets, nbs * sizeof(sommet *));
    g->sommets[nbs - 1] = s;
    return nbs;
}

void ajouter_Successeur(sommet *depart, sommet *arrivee)
{
    int indicepPred = (arrivee->nbPredecesseur)++;
    int indicepSucc = (depart->nbSuccesseur)++;
    depart->tabSuccesseur = (sommet **)realloc((depart)->tabSuccesseur, (indicepSucc + 1) * sizeof(sommet *));
    arrivee->tabPredecesseur = (sommet **)realloc((arrivee)->tabPredecesseur, (indicepPred + 1) * sizeof(sommet *));

    depart->tabSuccesseur[indicepSucc] = arrivee;
    arrivee->tabPredecesseur[indicepPred] = depart;
}

int ajouter_arc(graph *g, arc *a)
{
    int nba = (++(g->nbArc));

    g->arcs = realloc(g->arcs, nba * sizeof(arc *));
    g->arcs[nba - 1] = a;
    ajouter_Successeur(a->depart, a->arrivee);
    return nba;
}

void initialiser_sommet(graph *g, char *listeNomSommets[], int nbCandidats)
{

    sommet *s;
    for (int i = 0; i < nbCandidats; i++)
    {

        s = creer_sommet(listeNomSommets[i]);
        ajouter_sommet(g, s);
    }
}

void initialiser_arc(graph *g, t_mat_int_dyn *mat_duel)
{

    int colonne = mat_duel->col;

    int poids, poids2;
    sommet *arrivee, *depart;
    arc *pa;
    for (int i = 0; i < colonne - 1; i++)
    {

        for (int j = i + 1; j < colonne; j++)
        {

            poids = mat_duel->matrice[i][j];
            poids2 = mat_duel->matrice[j][i];
            arrivee = g->sommets[j];
            depart = g->sommets[i];
            if (poids < poids2)
            {
                poids = poids2 - poids;
                arrivee = g->sommets[i];
                depart = g->sommets[j];
            }
            else if (poids == poids2)
            {
                poids = 1;
                if (!rand()%2)
                {
                    arrivee = g->sommets[i];
                    depart = g->sommets[j];
                }else
                {
                    arrivee = g->sommets[j];
                    depart = g->sommets[i];
                }
            }
            else
            {
                poids = poids - poids2;
            }
            pa = creer_arc(arrivee, depart, poids);
            ajouter_arc(g, pa);
        }
    }
}
graph *creer_graphe_de_matrice_duel(t_mat_int_dyn *mat_duel, char **listeNomSommets)
{

    int nbCandidats = mat_duel->col;
    graph *g = creer_graph();
    initialiser_sommet(g, listeNomSommets, nbCandidats);
    initialiser_arc(g, mat_duel);
    return g;
}

graph *creer_graphe_de_matrice_char(t_mat_char_star_dyn *mat)
{
    graph *g;
    char **entete = recuperer_candidats(mat,1);
    t_mat_int_dyn *mat_duel = construire_mat_duel(mat);
    g = creer_graphe_de_matrice_duel(mat_duel, entete);
    supprimer_matrice_int(mat_duel);
    return g;
}

void afficher_graph(graph *g)
{

    printf("MON GRAPH\n");
    printf("-Sommets\n");
    for (int i = 0; i < (g->nbSommet); i++)
    {
        printf("%s \n", (g->sommets[i])->nom);
    }
    printf("\n");
    printf("-Arcs\n");
    for (int j = 0; j < (g->nbArc); j++)
    {
        printf("(%-20s \t---%d---> (%s)\n", (((g->arcs[j])->depart)->nom), ((g->arcs[j])->poids), (((g->arcs[j])->arrivee)->nom));
    }
}
void enlever_sommet(int taille, sommet **tableau, sommet *sEnlever)
{
    int i = 0;
    while (i < taille && tableau[i] != sEnlever)
    {
        i++;
    };

    for (int j = i; j < taille - 1; j++)
    {
        tableau[j] = tableau[j + 1];
    }
    tableau[taille - 1] = NULL;
}

int enlever_arc(graph *g, arc *a)
{
    int nbArc = (g->nbArc) - 1;
    arc **nouvelListe = NULL;
    int temp = 0;
    enlever_sommet(((a->arrivee)->nbPredecesseur)--, (a->arrivee)->tabPredecesseur, a->depart);
    enlever_sommet(((a->depart)->nbSuccesseur)--, (a->depart)->tabSuccesseur, a->arrivee);
    if (nbArc > 0)
    {
        nouvelListe = (arc **)malloc(nbArc * sizeof(arc *));
        for (int i = 0; i < (g->nbArc); i++)
        {
            if ((g->arcs[i]) != a)
            {
                nouvelListe[temp] = (g->arcs[i]);
                temp += 1;
            }
            else
            {
                free((g->arcs[i]));
            }
        }
    }
    free(g->arcs);
    g->arcs = nouvelListe;
    (g->nbArc)--;

    return nbArc;
}
