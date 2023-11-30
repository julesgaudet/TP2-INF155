/*
Module: Circuit_IO
Ce nouveau module a pour responsabilité de sauvegarder 
et de charger un circuit dans et depuis un fichier sur le
disque. Le circuit est sauvegardé en mode texte.

Auteur: Noah Tremblay : 
		Jules Gaudet  : GAUJ71370101

Derni�re modification: 
*/
#ifndef CIRCUIT_IO_H_
#define CIRCUIT_IO_H_

#include "t_circuit.h"
#include "t_entree.h"
#include "t_sortie.h"

//**************************************************************************************//

/*
Fonction: circuit_IO_sauvegarder

Description: Sauvegarde les composantes d'un circuit en format textuel. Les entrées, sorties, portes et liaisons sont sérialisées et écrites dans un fichier texte. Pendant l'écriture, des échos sont affichés dans la console pour valider l'état du circuit.

Paramètres:
- nom_fichier: Nom du fichier dans lequel sauvegarder le circuit.
- circuit: Pointeur vers la structure de circuit à sauvegarder.

Retour: Aucun
*/
void circuit_IO_sauvegarder(const char * nom_fichier, const  t_circuit * circuit);

/*
Fonction: circuit_IO_charger

Description: Charge un circuit à partir d'un fichier texte contenant la description textuelle du circuit. Les éléments du circuit (entrées, sorties, portes et liaisons) sont créés en utilisant les informations du fichier.

Paramètres:
- chemin_acces: Chemin d'accès du fichier à charger.
- circuit: Pointeur vers la structure de circuit qui sera remplie avec les informations du fichier.

Retour: Aucun
*/
void circuit_IO_charger(const char *chemin_acces, t_circuit *circuit);

/*
Fonction: t_circuit_tdv

Description: Calcule la table de vérité du circuit. La table de vérité est un tableau à deux dimensions où les colonnes représentent les entrées et les sorties, et les lignes représentent toutes les combinaisons de bits en entrée.

Paramètres:
- le_circuit: Pointeur vers la structure de circuit.

Retour: 
- Tableau à deux dimensions représentant la table de vérité du circuit.
  Nombre de colonnes = nombre d'entrées + nombre de sorties du circuit
  Nombre de lignes = 2^nombre d'entrées
*/
int **t_circuit_tdv(const t_circuit *le_circuit);

#endif