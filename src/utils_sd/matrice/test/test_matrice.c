#include "../matrice.h"
/// \brief program de teste sur une matrice

int main(void)
{
    /// creation de la matrice
    t_mat_char_star_dyn *ma_matrice = creer_matrice();

    /// insertion des valeurs dans la matrice
    ajouter_ligne(ma_matrice);
    inserer_matrice_char("1", ma_matrice);

    inserer_matrice_char("2", ma_matrice);

    inserer_matrice_char("3", ma_matrice);

    /// affichage de la matrice
    afficher_matrice_char(ma_matrice);
    /// suppression de la matrice
    supprimer_matrice_char(ma_matrice);
    return 0;
}