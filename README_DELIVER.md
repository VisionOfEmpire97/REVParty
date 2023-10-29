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

## CC2
- Pour vérifier que le programme `verify_my_vote` marche, lancez __make test_vmv__. Cette commande vous indiquera également avec quels arguments exécuter Valgrind
- Pour tester la lecture du CSV, faites __make test_lecture_csv__, le programme sera appelé avec:
`./bin/lecture_csv fichiers_votes/VoteCondorcet.csv `
- Pour tester la création d'une matrice et l'ajout d'éléments, faites __make test_matrice__
- Le code pour la fonction SHA nous a été fournis mais vous pouvez le tester avec __make test_sha__
- Vous pouvez également compiler `verify_my_vote` uniquement avec __make vmv__
- Pour générer la documentation, lancez __make doxygen__
- Pour se débarrasser des exécutables et fichiers objets; lancez __make clean__, et __make mrproper__ afin de supprimer la documentation également 