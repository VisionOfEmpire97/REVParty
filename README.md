#  Projet Avancé Niveau 3 - REVParty
---
## Equipe 001
- VALLAT Antoine
- ZERKANI Yanis
- ROSET Nathan
- JOSEPH Remy
---
* [Instructions pour utiliser git](#instructions-rapide-pour-utiliser-git-v1)
* [Questions à poser au tuteur](#trucs-pas-clairs)
* [Résoudre les conflits de merge](#résoudre-les-conflits-de-merge)
* [Gérer le caractère EOL](#gérer-le-caractère-eol)
---
### Instructions rapide pour utiliser git v1

- cloner/mettre à jour votre dossier de travail avec `git clone [lien-vers-github]` la première fois, puis `git pull`
- créer une nouvelle branche avec `git branch [nom_de_la_branche]`
Exemple : si vous voulez travaillez sur la méthode Condorcet Minimax, faites `git branch cdc_minimax`
- se positionner sur la nouvelle branche avec `git checkout [nom_de_la_branche]`
- **travaillez sur votre branche**
- **assurez vous d'être sur la bonne branche avec `git status`**
- quand vous avez fini, vous pouvez faire `git add .`, `git commit -m [message expliquant les changements]`, et `git push` **sur votre branche** 
- repasser sur la branche principale avec `git checkout master`
- appliquer les changements de votre branche avec la branche principale : `git merge [nom_de_la_branche]`<br>
_Utilisez des noms de branches sans espaces genre `util_sd` ou `Uni_DeuxTours` pour éviter les pbs_  
_On pourra voir si on a besoin d'utiliser des pull requests au fur et à mesure._  
- Supprimez la branche de travail quand vous avez fini avec `git branch -d [nom_de_la_branche]`
- par pitié ne supprimez pas la branche master merci bcp



### Résoudre les conflits de merge
- [lien vers la doc officielle en **Anglais**](https://docs.github.com/en/pull-requests/collaborating-with-pull-requests/addressing-merge-conflicts/resolving-a-merge-conflict-using-the-command-line)
- [lien vers la doc officielle en **Français**](https://docs.github.com/fr/pull-requests/collaborating-with-pull-requests/addressing-merge-conflicts/resolving-a-merge-conflict-using-the-command-line)
- si il y a un conflit lors du `git merge` entre votre branche de travail et la branche principale, il faut **ouvrir tous les fichiers** qui ont été modifiés sur `master` et choisir quels changements devront être gardés (ceux de la branche de travail ou ceux de `master`)
- L'endroit ou il y a des conflits est indiqué par les marqueurs `<<<<<<<`,`=======`,`>>>>>>>` qu'il faudra supprimer après avoir effectué la modification.
- Quand la modification de tous les fichiers à été faite, juste faites `git add .`, `git commit -m [msg]`, et `git push`.

### Gérer le caractère EOL
- Ajoutez à votre `./vscode/settings.json` cette ligne : 
> `"files.eol": "\n"`
- C'est pour faire en sorte qu'on ait moins de conflit de merge dans le futur.


### Trucs pas clairs 
- ~~à partir des [fichiers csv dispo](https://moodle.univ-tlse3.fr/mod/folder/view.php?id=407976) sur moodle, quelle est la syntaxe exacte qui nous permet de retrouver la ligne correspondant à notre vote vu que l'algorithme sha est sensible à la casse~~  
~~_à noter que j'ai testé uniquement avec `sha256sum` et pas l'algo donné sur moodle_~~
- par rapport à `verify_my_vote`, la syntaxe exacte pour retrouver le hash à partir de `nom+prénom+codepersonnel` c'est 
`NOM Prénom Codepersonnel`
- càd la chaine de caractère c'est une concaténation de `Nom_en_majuscule+espace+Prénom_avec_première_lettre_majuscule+espace+CodePersonnel` d'après M. Dugat, du coup dans verify_my_vote, on mettre le **Nom de famille en majuscule**, **le prénom en miniscule sauf la première lettre** suivi du **code personnel**, peut importe ce que l'utilisateur a tapé.

