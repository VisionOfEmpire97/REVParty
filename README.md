#  Projet Avancé Niveau 3 - REVParty

## Equipe 001
- VALLAT Antoine
- ZERKANI Yanis
- ROSET Nathan
- JOSEPH Remy

* [Instructions pour utiliser git](#instructions-rapide-pour-utiliser-git-v1)
* [Questions à poser au tuteur](#trucs-pas-clairs)

### Instructions rapide pour utiliser git v1

- cloner/mettre à jour votre dossier de travail avec `git clone [lien-vers-github]` la première fois, puis `git pull`
- créer une nouvelle branche avec `git branch [nom_de_la_branche]`
Exemple : si vous voulez travaillez sur la méthode Condorcet Minimax, faites `git branch cdc_minimax`
- se positionner sur la nouvelle branche avec `git checkout [nom_de_la_branche]`
- **travaillez sur votre branche**
- **assurez vous d'être sur la bonnse branche avec `git status`**
- quand vous avez fini, vous pouvez faire `git add .`, `git commit -m [message expliquant les changements]`, et `git push` **sur votre branche** 
- repasser sur la branche principale avec `git checkout master`
- appliquer les changements de votre branche avec la branche principale : `git merge [nom_de_la_branche]`<br>
_Utilisez des noms de branches sans espaces genre `util_sd` ou `Uni_DeuxTours` pour éviter les pbs_  
_On pourra voir si on a besoin d'utiliser des pull requests au fur et à mesure._  
- Supprimez la branche de travail quand vous avez fini avec `git branch -d [nom_de_la_branche]`
- par pitié ne supprimez pas la branche master merci bcp


### Trucs pas clairs 
- à partir des [fichiers csv dispo](https://moodle.univ-tlse3.fr/mod/folder/view.php?id=407976) sur moodle, quelle est la syntaxe exacte qui nous permet de retrouver la ligne correspondant à notre vote vu que l'algorithme sha est sensible à la casse  
_à noter que j'ai testé uniquement avec `sha256sum` et pas l'algo donné sur moodle_  
- Comment compter les votes à partir d'un fichier ou tous les candidats sont classés ? **à débattre en réunion**  