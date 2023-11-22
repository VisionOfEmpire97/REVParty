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
 * @param nb_c nb de candidats (colonnes à parcourir)
 * @param nb_v nb de votants (lignes à parcourir)
 */
void eval_mention(t_mat_int_dyn *m,t_mat_char_star_dyn *mat)
{
    int val;
    char *cur_value;
    for (int i = 1; i < m->ligne;i++) 
    {
        for (int j = 4; j < m->col; j++) 
        {   
            cur_value = valeur_matrice_char_indice(mat, i, j);
            val = strtol(cur_value, NULL, 10);
            switch (val)
            {   //ajouter le log pour chaque vote lu
                case 1:
                    m->matrice[j][0] += 1 ;
                    break;
                case 2:
                case 3:
                    m->matrice[j][1] += 1 ;
                    break;
                case 4:
                case 5:
                    m->matrice[j][2] += 1 ;
                    break;
                case 6:
                case 7:
                    m->matrice[j][3] += 1 ;
                    break;
                case 8:
                case 9:
                    m->matrice[j][4] += 1 ;
                    break;
                default: // on peut avoir des valeurs négatives dans les fichiers de votes
                    m->matrice[j][5] += 1 ;
                    break;
            }
        }
    }
}

void methode_jugement (char *nom_csv)
{   
    printf("BONJOUR");
    t_mat_char_star_dyn *mat = lecture_fichier(nom_csv);
    char *nom_methode = "Jugement majoritaire";
    //t_mat_char_star_dyn *nom_candidats = lecture_entete(nom_csv);
    int nb_candidats = recuperer_nb_colonnes(mat);
    char **candidats = recuperer_candidats(mat);
    
    t_mat_int_dyn *mentions = creer_matrice_int(nb_candidats, NB_MENTIONS);

    eval_mention(mentions, mat);
    //afficher_matrice_int(mentions);
    printf("%s",nom_methode);
    printf("            ");
    for (int i = 0; i < NB_MENTIONS; i++) {
        printf("%7s",str_mentions[i]);
    }
    for (int i = 0; i < nb_candidats; i++) 
    {   
        printf("%-12s",candidats[i]);
        for (int j = 0; j < NB_MENTIONS;j++ ) 
        {
            printf("%7d",mentions->matrice[i][j]);
        }
    }
    supprimer_matrice_char(mat);
    //supprimer_matrice_char(nom_candidats);
    supprimer_matrice_int(mentions);
}