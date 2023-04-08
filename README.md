# Hex Game of Life
 Une version hexagonal du jeu de la vie de Conway.

En première version, uniquement un type de cellule avec deux état : mort ou vivant , qui seront défini à l'avance dans un l'initialisation. 

Elles meurrent si elles ont plus de 3 de voisin ou naissent si elles ont exactement deux voisin.

# TODO
- Choisir les Règles de naissance 🌱et de mort. ☠️


# InProgress
- Déterminer les voisins de chaque cellule

# Done
- Dessin des Hexagones
- Coordonnées Hexagonal
- Structure du programme

# Maybe
- ▶️Animation des changement d'état
- Ajout de cellules avec la souris au runtime.
- Plusieurs type de cellules
- Movement des cellules
- Plusieurs espèce : 
  - Pelouse qui se répand
  - Herbivore(Mouton) qui mange un de pelouse sinon meur, se déplace si deux , et se reproduit si a proximité d'un autre herbivore et que suffisment de nourriture présnete
  - Carnivore(Loup) meur si pas manger mouton pendant trop de tour, se déplace.
  - Loup : Noir, Mouton : BLanc, herbe : Verte
