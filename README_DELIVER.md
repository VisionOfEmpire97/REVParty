#  Projet Avancé Niveau 3 - REVParty
---
## Membres de l'Equipe 001
- VALLAT Antoine
- ZERKANI Yanis
- ROSET Nathan
- JOSEPH Remy
---
## Prérequis 
 - Doxygen
 - Dot
 - GCC, make
 - Valgrind pour le test mémoire

# RENDU FINAL
- Appelez __make all_tests__ pour tester toutes les méthodes de scrutin dans des appels séparés afin d'obtenir un fichier de log différent pour chaque méthode
- Appelez __make all__ afin de générer également la documentation et tester le programme indépendant verify_my_vote 
- Appelez __make test_all_methods__ pour tester le programme avec la balise `-m all`

## CC2
- Pour vérifier que le programme `verify_my_vote` marche, lancez __make test_vmv__. Cette commande vous indiquera également avec quels arguments exécuter Valgrind
- Pour tester la lecture du CSV, faites __make test_lecture_csv__, le programme sera appelé avec:
`./bin/lecture_csv fichiers_votes/VoteCondorcet.csv `
- Pour tester la création d'une matrice et l'ajout d'éléments, faites __make test_matrice__
- Le code pour la fonction SHA nous a été fournis mais vous pouvez le tester avec __make test_sha__
- Vous pouvez également compiler `verify_my_vote` uniquement avec __make vmv__
- Pour générer la documentation, lancez __make doxygen__
- Pour se débarrasser des exécutables et fichiers objets; lancez __make clean__, et __make mrproper__ afin de supprimer la documentation également 

## CC3
- Appelez __make test_scrutin__ pour compiler et tester directement la méthode uninominale ainsi que le programme principal.
- Compilez le programme principal avec __make scrutin__ et fournissez les arguments sous la forme suivante : `./scrutin  [-i|d nom_du_csv] [-o nom_du_log] [-m méthodes]`
- Il est également possible de tester la méthode uninominale uniquement avec __make uninominal__ ou __make test_uni__
- **Important** :
    - Au deuxième tour, on considère que si le vote de préférence est le même pour les deux candidants, alors c'est un vote blanc que ne sera pas compté.


