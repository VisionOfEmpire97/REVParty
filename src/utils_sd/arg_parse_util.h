#include <stdio.h>
#include <stdlib.h>

// Variables pour ajouter de zolis couleurs
char *RED = "\033[1;31m";
char *GREEN = "\033[1;32m";
char *END_COLOR = "\e[00m";

// méthodes de votes
char *valid_methods[7] = {"uni1", "uni2", "cm", "cp", "cs", "jm", "all"};

void begin_to_log(const char *filename);

void check_compatibility(int *tab, int len_tab);

void lancer_methode(char *methode);