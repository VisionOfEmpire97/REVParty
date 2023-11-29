/**
 * @file jugement.c
 * @author ROSET Nathan
 * @brief implémentation de la méthode de jugement majoritaire
 * @version 0.1
 * @date 2023-11-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "jugement.h"
#include "utils_sd/util_log.h"
#include "utils_sd/matrice.h"
#include "CSV/lecture_csv.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NB_MENTIONS 6

char *str_mentions[NB_MENTIONS] ={"TB","B","AB","P","M","A fuir"};

/**
 * @brief 
 * 
 * @param m tableau d'équivalences des mentions
 * @param mat CSV converti en matrice
 * @param liste_candidats Le nom des candidats par ordre d'apparence dans le CSV
 */
void eval_mention(t_mat_int_dyn *m,t_mat_char_star_dyn *mat, char **liste_candidats)
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
            // remplacer le switch case par val // 2 ?
            int equiv_mention = val / 2; //division entière ???
            if (val < 0) //traite les vals négatives
            {
                m->matrice[j - 4][5] += 1 ;
                sprintf(buf,"[JGM] Electeur %d: le candidat %s a reçu la mention %s\n", i, liste_candidats[j-4],str_mentions[5]);
            } 
            else 
            {
                m->matrice[j - 4][equiv_mention] += 1 ; 
                sprintf(buf,"[JGM] Electeur %d: le candidat %s a reçu la mention %s\n", i, liste_candidats[j-4],str_mentions[equiv_mention]);
            }
            append_to_log_file(buf);
            //ajouter le log pour chaque vote lu
        }
    }
}

/**
 * @brief affiche le tableau de mention à l'utilisateur avant de lancer la vote en lui-même
 * 
 * @param mentions 
 * @param candidats 
 * @param nb_candidats 
 */
void afficher_tab_mentions(t_mat_int_dyn *mentions, char ** candidats, int nb_candidats)
{
    //pour s'assurer du bon alignement il faudrait convertir en ASCII ? les "é" et à ne passent pas...
    char *nom_methode = " **** Jugement majoritaire";
    printf("%s\n",nom_methode);
    printf("%-25s","");
    for (int i = 0; i < NB_MENTIONS; i++) {
        printf("%7s",str_mentions[i]);
    }
    printf("\n");
    for (int i = 0; i < nb_candidats; i++) 
    {   
        printf("%-25s",candidats[i]);
        for (int j = 0; j < NB_MENTIONS;j++ ) 
        {
            printf("%7d",mentions->matrice[i][j]);
        }
        printf("\n");
    }
}

void methode_jugement (t_mat_char_star_dyn *mat)
{   
    int nb_candidats = recuperer_nb_colonnes(mat) - 4;
    char **candidats = recuperer_candidats(mat);
    
    t_mat_int_dyn *mentions = creer_matrice_int(nb_candidats, NB_MENTIONS);

    eval_mention(mentions, mat, candidats);

    afficher_tab_mentions(mentions, candidats, nb_candidats);
    // afficher_matrice_int(mentions);

    // IL FAUT MAINTENANT TRAITER le tableau
    supprimer_matrice_int(mentions);
}