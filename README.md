# Hex Game of Life
Une version hexagonale du jeu de la vie de Conway.

**Règles** : Les cellules meurent en cas de (sur/sous)population et peuvent se reproduire.

# Shortcuts
- 0 à 9 pour de/activer les règles
- c pour afficher les coordonnés
- g pour afficher la grille
- flèche de droite pour passer à l'état suivant
- espace pour enter en mode auto
- entrer pour tuer toutes les cellules 
- d pour sauvegarder un monde de démarrage 
- s pour sauvegarder un monde
- l pour charger un monde 

# TODO

# InProgress
- Équilibrage des règles
- 
# Done
- 🌱☠️Règles de naissance, de mort et de reproduction. 
- ✅Règles affichées sur l'écran et de/activable
- 🏘️Déterminer les voisins de chaque cellule
- ☠️Bouton "Tuer toutes les cellules"
- ▶️Play/Pause + Next Bouton
- 🖱️Ajout de cellules avec la souris au runtime.
- ▶️ Animation des états grâce aux interpolations (en mode auto)
- 📤Sauvegarde et Chargement 
- 🌍Monde de démarrage 
- Systèmes de départ
- 🎲Random Start System
- 🎨Dessin des Hexagones
- 🗺️Coordonnées Hexagonal
- 🏠Structure du programme

# MaybeOneDay

- Plusieurs types de cellules
- Movement des cellules
- Plusieurs espèces : 
  - Pelouse qui se répand
  - Herbivores (Mouton) qui mange un de pelouse sinon meure, se déplace si deux , et se reproduit si a proximité d'un autre herbivore et que suffisment de nourriture présnete
  - Carnivores (Loup) meur si pas manger mouton pendant trop de tour, se déplace.
  - Loup : Noir, Mouton : Blanc, herbe : Verte
- Statistiques afficher sur l'écran : nombre d'entités de chaque type, nombre d'étape

# Observations 
- Augmenter la tolérance à la surpopulation ne détruit pas les flikers
- Les vagues ne survivent pas
- l'état suivant par défaut est la mort donc il n'existe aucune structure stable que des flikers
  - utiliser avec génération aléatoire pour détecter des flikers
  - désactiver pour obtenir des structures stables