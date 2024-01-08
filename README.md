# Circuit Logique Combinatoire (CLC)

## Auteurs
- Jules Gaudet
- Noah Tremblay

---

## Description du Projet
L'objectif de ce TP est de développer un programme permettant de concevoir des circuits logiques combinatoires (CLCs) et de calculer leur table de vérité en tant que partie bonus.

Un CLC est constitué d'un ensemble de composants interreliés, comprenant des entrées de circuit, des sorties de circuit et des portes logiques. Chaque porte logique reçoit des signaux en entrée, les traite selon une table de vérité définie, et produit un signal en sortie. Le travail consiste à créer une librairie qui facilite la conception de circuits en ajoutant des composants (entrées, portes logiques, sorties) et en spécifiant les liaisons entre eux.

## Portes Logiques Disponibles
- Porte ET
- Porte OU
- Porte XOR (OU Exclusif)
- Porte NOT (Négation)

## Fonctionnalités de la Librairie
Une fois le circuit conçu, la librairie offre les fonctionnalités suivantes :
1. **Vérification de la Validité du Circuit :** Les critères de validité du circuit sont pris en compte, mais il reste à vérifier que toutes les composantes sont reliées entre elles.
2. **Propagation du Signal :** La librairie permet de propager un signal reçu sur les entrées du circuit afin de calculer le signal en sortie.

## Utilisation de la Librairie
Pour utiliser la librairie, suivez les étapes suivantes :
1. Importez la librairie dans votre projet.
2. Créez un circuit en ajoutant des composants et en spécifiant les liaisons.
3. Utilisez les fonctions de la librairie pour vérifier la validité du circuit et propager les signaux.
