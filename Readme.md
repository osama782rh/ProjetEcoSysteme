Simulation d'Écosystème
Ce projet implémente une simulation d'écosystème en C++, où des moutons, des loups et de l'herbe interagissent dans un univers simulé. Les entités se déplacent et interagissent en fonction de règles spécifiques, et la simulation peut être configurée pour différents niveaux de difficulté et modes de déplacement.

Fonctionnalités
Deux modes de déplacement :
Mode normal : Déplacements aléatoires.
Mode intelligent : Déplacements vers la ressource la plus proche, avec reproduction des animaux.
Niveaux de difficulté :
Facile : Beaucoup d'herbe.
Moyen : Quantité moyenne d'herbe.
Difficile : Peu d'herbe.
Simulation avec un nombre configurable de tours.
Historique des loups et moutons enregistré et sauvegardé dans un fichier parcours.txt.
Affichage de l'état de l'univers à chaque tour.
Pré-requis
Un compilateur C++ (g++)
Make
Compilation et exécution
Compilation
Pour compiler le projet, utilisez la commande suivante :

sh
Copy code
make
Cela utilisera le Makefile fourni pour compiler les fichiers sources et générer l'exécutable simulation.

Exécution
Pour exécuter la simulation, utilisez la commande suivante :

sh
Copy code
./simulation
Instructions
Choisissez le mode de jeu :

1 : Mode normal
2 : Mode intelligent
Entrez le nombre de moutons et de loups :

Le nombre maximum de moutons est 25.
Le nombre maximum de loups est 15.
Choisissez le niveau de difficulté :

1 : Facile (beaucoup d'herbe)
2 : Moyen (quantité moyenne d'herbe)
3 : Difficile (peu d'herbe)
La simulation s'exécute pour un nombre de tours configuré dans le code (200 par défaut).

À la fin de la simulation, choisissez si vous souhaitez sauvegarder l'historique du jeu dans un fichier parcours.txt.

Vous pouvez également choisir de recommencer la simulation.

Structure du Projet
main.cpp : Le fichier principal contenant la boucle de la simulation.
Univers.h, Univers.cpp : Définit l'univers de la simulation.
Mouton.h, Mouton.cpp : Définit les moutons.
Loup.h, Loup.cpp : Définit les loups.
SelsMineraux.h, SelsMineraux.cpp : Définit les sels minéraux.
Herbe.h, Herbe.cpp : Définit l'herbe.
Entite.h, Entite.cpp : Définit l'entité de base.
Animal.h, Animal.cpp : Définit les caractéristiques communes aux animaux.
Makefile : Script de compilation.
Sauvegarde de l'Historique
L'historique des loups et moutons au fil des tours est sauvegardé dans un fichier parcours.txt. Chaque ligne du fichier contient le nombre de loups et de moutons à chaque tour.

Auteurs
Ce projet a été développé par RAHIM Osama.