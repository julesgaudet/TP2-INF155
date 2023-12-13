/*
Module: Circuit_IO
Ce nouveau module a pour responsabilité de sauvegarder 
et de charger un circuit dans et depuis un fichier sur le
disque. Le circuit est sauvegardé en mode texte.

Auteur: Noah Tremblay : TREN85330401
        Jules Gaudet  : GAUJ71370101

Dernière modification : 09/12/2023
*/
#ifndef CIRCUIT_IO_H_
#define CIRCUIT_IO_H_

#include "t_circuit.h"

//**************************************************************************************//

/*
Fonction: circuit_IO_sauvegarder

Description: Sauvegarde les composantes d'un circuit en format textuel. 
Les entrées, sorties, portes et liaisons sont sérialisées et écrites dans 
un fichier texte.

Paramètres:
- nom_fichier: Nom du fichier dans lequel sauvegarder le circuit.
- circuit: Pointeur vers la structure de circuit à sauvegarder.

Retour: Aucun
*/
void circuit_IO_sauvegarder(const char * nom_fichier, const  t_circuit * circuit);

/*
Fonction: circuit_IO_charger

Description: Charge un circuit à partir d'un fichier texte contenant 
la description textuelle du circuit. Les éléments du circuit (entrées, 
sorties, portes et liaisons) sont créés en utilisant les informations du fichier.

Paramètres:
- chemin_acces: Chemin d'accès du fichier à charger.
- circuit: Pointeur vers la structure de circuit qui sera remplie avec les informations du fichier.

Retour: Aucun
*/
void circuit_IO_charger(const char *chemin_acces, t_circuit *circuit);

/*
Fonction: t_circuit_tdv

Description: cette fonctions fait appel a d'autres fonctions pour generer, calculer, afficher et 
liberer la table de véritée

Paramètres:
- le_circuit: Pointeur vers la structure de circuit.

Retour: 

*/
void t_circuit_tdv(const t_circuit *le_circuit);

#endif