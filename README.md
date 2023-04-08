# Hex Game of Life
 Une version hexagonal du jeu de la vie de Conway.

En première version, uniquement un type de cellule avec deux état : mort ou vivant , qui seront défini à l'avance dans un l'initialisation. 

Elles meurrent si elles ont plus de 3 de voisin ou naissent si elles ont exactement deux voisin.

# TODO
- Choisir les Règles de naissance 🌱et de mort. ☠️
- Clear Button : kill all cell

# InProgress
- Déterminer les voisins de chaque cellule

# Done
- Dessin des Hexagones
- Coordonnées Hexagonal
- Structure du programme
- Play/Pause + NextStep Button
- Ajout de cellules avec la souris au runtime.

# Maybe
- ▶️Animation des changement d'état
- Plusieurs type de cellules
- Movement des cellules
- Plusieurs espèce : 
  - Pelouse qui se répand
  - Herbivore(Mouton) qui mange un de pelouse sinon meur, se déplace si deux , et se reproduit si a proximité d'un autre herbivore et que suffisment de nourriture présnete
  - Carnivore(Loup) meur si pas manger mouton pendant trop de tour, se déplace.
  - Loup : Noir, Mouton : BLanc, herbe : Verte
- Statistiques afficher sur l'écran : nombre d'entité de chaque type, nombre d'étape
- (En/Dis)able Rules with menu
- Menu avec des système de départ
- Export des Système de départ 
- Random Start System

# Observations 
- Augmenter la totélrance à la surpopulation ne détruit pas les flikers
- Les vagues ne survive pas
- l'état suivant par défaut est la mort donc il n'existe aucune structure stable que des flikers
  - utiliser avec génération aléatoire pour détcter des flikers
  - désactiver pour obtenir des structure stable