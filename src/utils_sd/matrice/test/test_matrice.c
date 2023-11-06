#include "../matrice.h"
#include "../../../CSV/lecture_csv.h"
/// \brief program de teste sur une matrice

int main(int argc, char *argv[])
{
    /// creation de la matrice
    t_mat_char_star_dyn *ma_matrice = creer_matrice_char(), *m;
    t_mat_int_dyn *mat_duel;
    /// insertion des valeurs dans la matrice
    printf("TEST MATRICE:\n");

    printf("TEST CONSTRUCTION ET AJOUT DANS UNE MATRICE\n");
    ajouter_ligne(ma_matrice);
    inserer_matrice_char("1", ma_matrice);
    inserer_matrice_char("2", ma_matrice);
    ajouter_ligne(ma_matrice);
    inserer_matrice_char("3", ma_matrice);
    inserer_matrice_char("4", ma_matrice);
    printf("TEST OK!\n");

    printf("TEST AFFICHAGE\n");
    /// affichage de la matrice
    afficher_matrice_char(ma_matrice);
    printf("TEST OK!\n");

    /// suppression de la matrice
    printf("TEST SUPPRESSION MATRICE DE CHAINE\n");
    supprimer_matrice_char(ma_matrice);
    printf("TEST OK!\n");

    printf("TEST CREATION MATRICE DUEL\n");
    m = lecture_fichier(argv[1]);
    printf("s\n");
    mat_duel = construire_mat_duel(ma_matrice);
    printf("s\n");
    printf("TEST OK!\n");

    printf("TEST AFFICHAGE\n");
    afficher_matrice_int(mat_duel);
    printf("TEST OK!\n");
    return 0;
}