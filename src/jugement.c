/**
 * @file jugement.c
 * @author ROSET Nathan
 * @brief implémentation de la méthode de jugement majoritaire
 * Il était possible d'utiliser une unique structure mais pas besoin
 * @version 0.1
 * @date 2023-11-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "jugement.h"
#include "utils_sd/arg_parse_util.h"
#include "utils_sd/util_log.h"
#include "utils_sd/matrice.h"
#include "CSV/lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NB_MENTIONS 6

char *str_mentions[NB_MENTIONS] ={"TB","B","AB","P","M","A fuir"};
char buff[200];

/**
 * @brief transforme les valeurs attribuées à chaque candidat en une mention entre 0 (TB) et 5 (A fuir)
 * 
 * @param m tableau d'équivalences des mentions
 * @param mat CSV converti en matrice
 * @param liste_candidats Le nom des candidats par ordre d'apparence dans le CSV
 */
void eval_mention(t_mat_int_dyn *m,t_mat_char_star_dyn *mat, char **noms_candidats)
{
    int val;
    char *cur_value;
    int nb_l = recuperer_nb_lignes(mat);
    int nb_c = recuperer_nb_colonnes(mat);
    char buf[100];
    for (int i = 1; i < nb_l;i++) 
    {
        for (int j = 4; j < nb_c; j++) 
        {   
            cur_value = valeur_matrice_char_indice(mat, i, j);
            val = strtol(cur_value, NULL, 10);
            int equiv_mention = val / 2; //division entière ???
            if (val < 0) //traite les vals négatives
            {
                m->matrice[j - 4][5] += 1 ;
                sprintf(buf,"[JGM] Electeur %d: le candidat %s a reçu la mention %s\n", i, noms_candidats[j-4],str_mentions[5]);
            } 
            else 
            {
                m->matrice[j - 4][equiv_mention] += 1 ; 
                sprintf(buf,"[JGM] Electeur %d: le candidat %s a reçu la mention %s\n", i, noms_candidats[j-4],str_mentions[equiv_mention]);
            }
            append_to_log_file(buf);
            //ajouter le log pour chaque vote lu
        }
    }
}

/**
 * @brief affiche le tableau de mentions reçu par chaque candidat à l'utilisateur
 * avant de lancer la vote en lui-même
 * @param mentions matrice qui récupère les votes de chaque électeur
 * @param liste_candidats noms des candidats
 * @param nb_candidats
 */
void afficher_tab_mentions(t_mat_int_dyn *mentions, char ** noms_candidats, int nb_candidats)
{
    //pour s'assurer du bon alignement il faudrait convertir en ASCII ? les "é" et "à" ne passent pas...
    char *nom_methode = " **** Jugement majoritaire ****";
    printf("%s\n",nom_methode);
    printf("%-40s","");
    for (int i = 0; i < NB_MENTIONS; i++) {
        printf("%7s",str_mentions[i]);
    }
    printf("\n");
    for (int i = 0; i < nb_candidats; i++) 
    {   
        printf("%-40s",noms_candidats[i]);
        for (int j = 0; j < NB_MENTIONS;j++ ) 
        {
            printf("%7d",mentions->matrice[i][j]);
        }
        printf("\n");
    }
}
/**
 * @brief retourne la médiane du nombre d'électeur. Cet électeur décidera de la mention obtenue par le candidat
 * @param number Le nombre d'électeur
 * @return mediane
 */
int mediane(int number)
{
    return ((number % 2 == 0) ? (number / 2) : (number / 2 + 1));
}

/**
 * @brief algorithme qui attribue à chaque étape, à chaque candidat non éliminé une mention, et
 * modifie la variable contenant la plus meilleure mention
 * @param m matrice qui récupère les votes de chaque électeur
 * @param nb_candidats le nombre de candidat (invariant)
 * @param nb_electeurs nb d'electeurs à cette étape
 * @param noms_c nom des candidats
 * @param best_result la plus haute mention observée pour cette étape
 * @param rank tableau de candidat avec l'entier correspondant à leur mention
 */
void classer_cand(t_mat_int_dyn *m, int nb_candidats, int nb_electeurs,char ** noms_c, int *best_result, int *rank)
{
    int electeur_median = mediane(nb_electeurs);
    int compteur = 0, j = NB_MENTIONS - 1;
    for (int i = 0; i < nb_candidats; i++)
    {
        //s'assurer que les candidats éliminés le reste
        if (rank[i] <= 5)
        {
            while (compteur < electeur_median)
            {
                compteur += m->matrice[i][j];
                if (compteur < electeur_median) j--; //"inférieur" ou "inférieur ou égal" ??
            }
            rank[i] = j;
            if (j < *best_result) *best_result = j; // on récupère dans best_result la mention la plus haute
            sprintf(buff,"[JGM] Le candidat %s reçoit la mention majoritaire %s\n",noms_c[i],str_mentions[j]);
            append_to_log_file(buff);
        j = NB_MENTIONS - 1;
        compteur = 0;
        }
    }
    // cas ou les mentions empirent pour tous les candidats ex aequo non éliminés:
    int j2 = 5;
    for (int i = 0; i < nb_candidats; i++)
    {
        if (rank[i] < j2)
        {
            j2 = rank[i];
        }
    }
    *best_result = j2;
    append_to_log_file("\n");
}
/**
 * @brief on retire un électeur dans la colonne meilleure_mention pour chaque candidat
 * @param mentions matrice d'entier ou chaque
 * @param meilleure_mention colonne dans laquelle on retire un électeur
 * @param nb_electeurs nb d'electeurs à cette étape
 */
void retirer_mediane(t_mat_int_dyn *mentions, int meilleure_mention,int *nb_electeurs)
{
    int nb_l = mentions->ligne;
    // int electeur_median = mediane(*nb_electeurs); //why is this here
    for (int i = 0; i < nb_l; i++) 
    {
        mentions->matrice[i][meilleure_mention]--;
    }
    *nb_electeurs = *nb_electeurs - 1;
}

/**
 * @brief on s'assure que certains candidats éliminés ne faussent pas les résultats lorque
 * l'on modifie le nombre d'électeur
 * @param classement_candidat tableau de candidat avec l'entier correspondant à leur mention
 * @param nb_candidats le nombre de candidat (invariant)
 * @param best_result la plus haute mention observée pour cette étape
 * @param nom_candidats 
 */
void eliminer_candidats(int *classement_candidat, int nb_candidats, int *best_result, char ** nom_candidats)
{
    for (int i = 0; i < nb_candidats; i++) 
    {
        if (classement_candidat[i] > *best_result)
        {
            sprintf(buff, "[JGM] Le candidat %s a été éliminé\n",nom_candidats[i]);
            append_to_log_file(buff);
            classement_candidat[i] = 99;
        }
    }
    append_to_log_file("\n");
}

/**
 * @brief vérifie si plusieurs vainqueurs existent, si oui, on continue l'algo
 * 
 * @param best_result la plus haute mention observée pour ce tour
 * @param classement_candidat tableau de candidat avec l'entier correspondant à leur mention
 * @param nb_candidats le nombre de candidat (invariant)
 * @return nb_vainqueurs si il est supérieur à 1, on continue l'algo 
 */
int plusieurs_vainqueurs(int *best_result,int* classement_candidat, int nb_candidats)
{   
    int exaeq = 0;
    for (int i = 0 ; i < nb_candidats;i++) 
    {
        if (classement_candidat[i] == *best_result)
        {
            exaeq++;
        }
        if (exaeq > 1) return exaeq;
    }
    return exaeq;
}

/**
 * @brief 
 * 
 * @param classement_candidat tableau de candidat avec l'entier correspondant à leur mention
 * @param nb_candidats le nombre de candidat (invariant)
 * @param best_result 
 * @return int 
 */
int declarer_vainqueur(int *classement_candidat, int nb_candidats, int *best_result)
{
    for (int i = 0; i < nb_candidats; i++) {
        if (classement_candidat[i] == *best_result) return i;
    }
    return -1;
}

/**
 * @brief algorithme de jugement majoritaire
 * 
 * @param mat la matrice de vote
 */
void methode_jugement (t_mat_char_star_dyn *mat)
{   
    int nb_candidats = recuperer_nb_colonnes(mat) - 4;
    int nb_electeurs = recuperer_nb_lignes(mat) - 1; //nb_electeur = 2N
    char **nom_candidats = recuperer_candidats(mat);
    
    t_mat_int_dyn *mentions = creer_matrice_int(nb_candidats, NB_MENTIONS);

    eval_mention(mentions, mat, nom_candidats);

    afficher_tab_mentions(mentions, nom_candidats, nb_candidats);

    int meilleure_mention = 5;
    // attribue à chaque candidat une mention et renvoie 
    // dans meilleure_mention la mention la plus haute observée
    int classement_candidat[nb_candidats];
    //memset ne marche pas ??
    for (int i = 0; i < nb_candidats; i++) {
        classement_candidat[i] = 5;
    };

    classer_cand(mentions, nb_candidats, nb_electeurs, nom_candidats, &meilleure_mention,classement_candidat);
    
    eliminer_candidats(classement_candidat,nb_candidats,&meilleure_mention, nom_candidats);

    while (plusieurs_vainqueurs(&meilleure_mention, classement_candidat, nb_candidats) > 1)
    {
        //retirer l'electeur median de la matrice mention, et refaire le vote
        retirer_mediane(mentions,meilleure_mention,&nb_electeurs);
        //re-classer les candidats
        classer_cand(mentions, nb_candidats, nb_electeurs, nom_candidats, &meilleure_mention,classement_candidat);

        eliminer_candidats(classement_candidat,nb_candidats,&meilleure_mention, nom_candidats);
    }
    //déclarer le vainqueur en sortie de boucle
    int vainqueur = declarer_vainqueur(classement_candidat, nb_candidats, &meilleure_mention);
    sprintf(buff, "[JGM] Le candidat %s a été déclaré vainqueur par méthode de jugement majoritaire", nom_candidats[vainqueur]);
    append_to_log_file(buff);
    printf("%s%s%s\n",GREEN, buff, END_COLOR);
    supprimer_matrice_int(mentions);
}
