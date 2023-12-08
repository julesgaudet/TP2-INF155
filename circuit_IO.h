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

Description: Calcule la table de vérité du circuit. La table de vérité 
est un tableau à deux dimensions où les colonnes représentent les entrées 
et les sorties, et les lignes représentent toutes les combinaisons de bits en entrée.

Paramètres:
- le_circuit: Pointeur vers la structure de circuit.

Retour: 
- Tableau à deux dimensions représentant la table de vérité du circuit.
  Nombre de colonnes = nombre d'entrées + nombre de sorties du circuit
  Nombre de lignes = 2^nombre d'entrées
*/
int **t_circuit_tdv(const t_circuit *le_circuit);

/*
Fonction: ecrire_nb_entrees_sorties_portes

Description: Écrit le nombre d'entrées, de sorties et de portes dans le fichier.

Paramètres:
- fichier: Pointeur vers le fichier où écrire les informations.
- circuit: Pointeur vers la structure de circuit.

Retour: Aucun
*/
void ecrire_nb_entrees_sorties_portes(FILE *fichier, const t_circuit *circuit);

/*
Fonction: ecrire_entrees

Description: Écrit les informations des entrées dans le fichier.

Paramètres:
- fichier: Pointeur vers le fichier où écrire les informations.
- circuit: Pointeur vers la structure de circuit.
- resultat: Tableau de caractères utilisé pour stocker les informations sérialisées temporairement.

Retour: Aucun
*/
void ecrire_entrees(FILE *fichier, const t_circuit *circuit, char *resultat);

/*
Fonction: ecrire_sorties

Description: Écrit les informations des sorties dans le fichier.

Paramètres:
- fichier: Pointeur vers le fichier où écrire les informations.
- circuit: Pointeur vers la structure de circuit.
- resultat: Tableau de caractères utilisé pour stocker les informations sérialisées temporairement.

Retour: Aucun
*/
void ecrire_sorties(FILE *fichier, const t_circuit *circuit, char *resultat);

/*
Fonction: ecrire_portes

Description: Écrit les informations des portes dans le fichier.

Paramètres:
- fichier: Pointeur vers le fichier où écrire les informations.
- circuit: Pointeur vers la structure de circuit.
- resultat: Tableau de caractères utilisé pour stocker les informations sérialisées temporairement.

Retour: Aucun
*/
void ecrire_portes(FILE *fichier, const t_circuit *circuit, char *resultat);

/*
Fonction: ecrire_liens

Description: Écrit les informations des liaisons dans le fichier.

Paramètres:
- fichier: Pointeur vers le fichier où écrire les informations.
- circuit: Pointeur vers la structure de circuit.
- resultat: Tableau de caractères utilisé pour stocker les informations sérialisées temporairement.

Retour: Aucun
*/
/*
Fonction: ecrire_liens

Description: Écrit les liens entre les portes et leurs entrées dans un fichier texte.

Paramètres:
- fichier: Pointeur vers le fichier dans lequel écrire les liens.
- circuit: Pointeur vers la structure de circuit contenant les informations.
- resultat: Chaîne de caractères servant à stocker temporairement le résultat.

Retour: Aucun
*/
void ecrire_liens(FILE *fichier, const t_circuit *circuit, char *resultat);

/*
Fonction: charger_entrees

Description: Charge les entrées d'un circuit à partir d'un fichier texte.

Paramètres:
- fichier: Pointeur vers le fichier texte contenant les informations.
- circuit: Pointeur vers la structure de circuit qui sera remplie avec les informations du fichier.
- nb_entrees: Nombre d'entrées à charger.

Retour: Aucun
*/
void charger_entrees(FILE *fichier, t_circuit *circuit, int nb_entrees);

/*
Fonction: charger_sorties

Description: Charge les sorties d'un circuit à partir d'un fichier texte.

Paramètres:
- fichier: Pointeur vers le fichier texte contenant les informations.
- circuit: Pointeur vers la structure de circuit qui sera remplie avec les informations du fichier.
- nb_sorties: Nombre de sorties à charger.

Retour: Aucun
*/
void charger_sorties(FILE *fichier, t_circuit *circuit, int nb_sorties);

/*
Fonction: charger_portes

Description: Charge les portes d'un circuit à partir d'un fichier texte.

Paramètres:
- fichier: Pointeur vers le fichier texte contenant les informations.
- circuit: Pointeur vers la strutcture de circuit qui sera remplie avec les informations du fichier.
- nb_portes: Nombre de portes à charger.

Retour: Aucun
*/
void charger_portes(FILE *fichier, t_circuit *circuit, int nb_portes);

/*
Fonction: charger_liaisons

Description: Charge les liaisons d'un circuit à partir d'un fichier texte.

Paramètres:
- fichier: Pointeur vers le fichier texte contenant les informations.
- circuit: Pointeur vers la structure de circuit qui sera remplie avec les informations du fichier.

Retour: Aucun
*/
void charger_liaisons(FILE *fichier, t_circuit *circuit);

#endif

