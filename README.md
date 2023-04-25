# Hex Game of Life
Une version hexagonal du jeu de la vie de Conway.

En première version, uniquement un type de cellule avec deux état : mort ou vivant , qui seront défini à l'avance dans un l'initialisation. 

Elles meurrent si elles ont plus de 3 de voisin ou naissent si elles ont exactement deux voisin.

# Shortcut
- 1 pour afficher les coordonnés
- 2 pour afficher la grille
- flèche de droite pour passer à l'état suivant
- espace pour enter en mode auto
- entrer pour tuer toute les cellules 
- w pour sauvegarder un monde de démarage 
- s pour sauvegarder un monde
- l pour charger un monde 

# TODO
- Choisir les Règles de naissance 🌱et de mort. ☠️
- Grapic Menu pour charger des configuration préfaite.

# InProgress
- (En/Dis)able Rules with menu

# Done
- Déterminer les voisins de chaque cellule
- Clear Button : kill all cell
- Dessin des Hexagones
- Coordonnées Hexagonal
- Structure du programme
- Play/Pause + NextStep Button
- Ajout de cellules avec la souris au runtime.
- Animation des états grâce aux interpolations (en mode auto)
- Savegarde et Chargement
- Monde de démarage 
- ▶️Animation des changement d'état
- Export des Système de départ
- Random Start System

# Maybe

- Plusieurs type de cellules
- Movement des cellules
- Plusieurs espèce : 
  - Pelouse qui se répand
  - Herbivore(Mouton) qui mange un de pelouse sinon meur, se déplace si deux , et se reproduit si a proximité d'un autre herbivore et que suffisment de nourriture présnete
  - Carnivore(Loup) meur si pas manger mouton pendant trop de tour, se déplace.
  - Loup : Noir, Mouton : BLanc, herbe : Verte
- Statistiques afficher sur l'écran : nombre d'entité de chaque type, nombre d'étape

# Observations 
- Augmenter la tolérance à la surpopulation ne détruit pas les flikers
- Les vagues ne survive pas
- l'état suivant par défaut est la mort donc il n'existe aucune structure stable que des flikers
  - utiliser avec génération aléatoire pour détcter des flikers
  - désactiver pour obtenir des structure stable