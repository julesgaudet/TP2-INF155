/*
Module: T_PIN_ENTREE
Description: Définit le type t_pin_entree. Un t_pin_entree est un point de connexion appartenant 
		     � un �l�ment du circuit qui re�oit un signal (mais n'en �met pas). 
			 Les �l�ments d'un circuit ayant un pin d'entr�e de signal sont les portes (les entr�es
			 des portes) ainsi que les sorties du circuit.

			 Si un pin d'entr�e re�oit un signal, ce signal est stock� dans le champs valeur. Un 
			 t_pin_entree qui est inactif (pas aliment�) a la valeur -1. 

			 Un pin d'entree permet de relier le composant auquel il appartient � un autre composant. 
			 Il doit �tre reli� � un "pin de sortie" du composant auquel on souhaite se connecter.

Auteur: Anis Boubaker
Derni�re modification: Eric Th�, 2023-11-12
*/

#ifndef T_PIN_ENTREE_H_
#define T_PIN_ENTREE_H_

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t_pin_sortie.h"

#define NOM_ENTREE_TAILLE_MAX 3  	//Taille maximale du nom de l'entr�e
#define INACTIF    -1				//Indique qu'un composant (entree/sortie) est inactif
#define FAUX 0
#define VRAI 1

typedef struct t_pin_sortie t_pin_sortie;

//D�finit le type t_pin_entree
typedef struct t_pin_entree {
	int valeur;		//Valeur du signal re�u par le pin d'entree. -1 si le pin est inactif.
	char *nom_liaison;      //le nom de la liaison vers le pin de sortie
	t_pin_sortie *liaison;	//Pointeur vers le pin de sortie
							//� laquelle ce pin est connect�
} t_pin_entree;


/*
Fonction: T_PIN_ENTREE_INIT (constructeur)
Description: Cr�e un nouveau pin entr�e qui contient aucune valeur et pas de liaison.

Param�tres: Aucun
Retour: Pointeur vers le pin d'entr�e qui a �t� cr��e
Param�tres modifi�: N/A.
*/
t_pin_entree *t_pin_entree_init();

/*
Fonction: T_PIN_ENTREE_DESTROY (Destructeur)
Description: Lib�re la m�moire occup�e par le pin d'entree.

Param�tres:
- pin: Pointeur vers le pin d'entr�e � d�truire.
Retour: Aucun.
Param�tres modifi�: pin
*/
void t_pin_entree_destroy(t_pin_entree *pin);

/*
Fonction: T_PIN_ENTREE_GET_VALEUR (Accesseur)
Description: Accesseur du champs valeur.

Param�tres:
- pin: Pointeur vers le pin d'entr�e.
Retour: (entier) Valeur du pin : 0, 1 ou -1.
Param�tres modifi�: aucun
*/
int t_pin_entree_get_valeur(const t_pin_entree *pin);

/*
Fonction: T_PIN_ENTREE_GET_LIEN (Accesseur)
Description: Accesseur du champs liaison.

Param�tres:
- pin: Pointeur vers le pin d'entr�e.
Retour: (char *) le nom de la liaison de sortie.
Param�tres modifi�: aucun
*/
char * t_pin_entree_get_lien(const t_pin_entree* pin);

/*
Fonction: T_PIN_ENTREE_SET_VALEUR (Mutateur)
Description: Mutateur du champs valeur.

Param�tres:
- pin: Pointeur vers le pin d'entr�e.
- valeur: nouvelle valeur du pin d'entr�e (doit obligatoirement �tre -1, 0 ou 1)
Retour: Aucun
Param�tres modifi�: pin
*/
void t_pin_entree_set_valeur(t_pin_entree *pin, int valeur);

/*
Fonction: T_PIN_ENTREE_RELIER
Description: Relie le pin d'entr�e � un pin de sortie. Cette fonction permet de relier le composant, auquel 
			 apparatien le pin d'entr�e, � un autre composant, auquel appartient le pin de sortie.

			 Cette fonction s'assure que la relation est bi-directionnelle: le pin de sortie aura le pin d'entr�e
			 comme un des pins auxquels il est reli� (fait en utilisant la fontion t_pin_sortie_ajouter_lien)

Param�tres:
- pin_entree: le pin d'entr�e � relier
- pin_sortie: Le pin de sortie � lequel le pin d'entr�e sera reli�.
Retour: Aucun
*/
void t_pin_entree_relier(t_pin_entree *pin_entree, char * nom_sortie, const t_pin_sortie *pin_sortie);


/*
Fonction: T_PIN_ENTREE_EST_RELIEE
Description: Permet de v�rifier si un pin d'entr�e est reli�e � un pin de sortie.

Param�tres:
- pin_entree: le pin d'entr�e dont on veut v�rifier la liaison
Retour: Bool�en: Vrai si le pin d'entr�e est reli�e, Faux sinon.
*/
int t_pin_entree_est_reliee(t_pin_entree *pin);

/*
Fonction: T_PIN_ENTREE_RESET
Description: R�-initialise la valeur du pin d'entree � INACTIF

Parametre: 
- pin_entree: le pin d'entr�e dont on veut r�initialiser la valeur
Retour: Aucun.
*/
void t_pin_entree_reset(t_pin_entree *pin);


#endif