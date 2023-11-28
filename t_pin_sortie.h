/*
Module: T_PIN_SORTIE
Description: D�finit le type t_pin_sortie. Un t_pin_sortie est un point de connexion appartenant
			 � un �l�ment du circuit qui �met un signal (mais n'en re�oit pas).
			 Les �l�ments d'un circuit ayant une pin sortie sont les portes (les sorties des portes) 
			 ainsi que les entr�es du circuit.

			 Pour qu'un pin de sortie �mette un signal, ce signal doit �tre stock� dans le champs valeur. 
			 Un t_pin_sortie qui est inactif (pas aliment�e) aura la valeur -1.

			 Un pin de sortie permet de relier le composant auquel il appartient � d'autres composants.
			 Il doit �tre reli�e � des "pin d'entr�e" des composants auquel on souhaite se connecter.

			 Note: Contrairement � un pin d'entr�e, un pin de sortie peut �tre reli�e � plusieurs 
			 pins d'entr�es : Ceci permet d'�mettre le m�me signal � plusieurs composants.

Auteur: Anis Boubaker
Derni�re modification: Eric Th�, 2023-11-12
*/

#ifndef T_PIN_SORTIE_H_
#define T_PIN_SORTIE_H_

#include "t_pin_entree.h"

//Le nombre maximal de pins d'entr�es auquels une sortie peut �tre connect�e
#define SORTIE_MAX_LIAISONS 10

typedef struct t_pin_entree t_pin_entree;
typedef struct t_circuit t_circuit;


//D�finit le type t_pin_sortie
typedef struct t_pin_sortie {
	int valeur;		//Valeur du signal re�u par le pin d'entr�e. -1 si le pin est inactif.

	//Tableau de pointeurs vers les pins d'entr�es auquel ce pin sortie est connect�
	t_pin_entree *liaisons[SORTIE_MAX_LIAISONS];

	//Nombre de pins d'entr�es vers lesquels ce pin de sortie est connect�.
	//Ce champ repr�sente le nombre d'�l�ments effectifs du tableau "liaisons[]".
	int nb_liaisons;
} t_pin_sortie;


/*
Fonction: T_PIN_SORTIE_INIT (constructeur)
Description: Cr�e un nouveau pin de sortie qui contient aucune valeur et aucune liaison.

Param�tres: Aucun
Retour: Pointeur vers le pin de sortie qui a �t� cr��e
Param�tres modifi�: N/A.
*/
t_pin_sortie *t_pin_sortie_init(void);

/*
Fonction: T_PIN_SORTIE_DESTROY (Destructeur)
Description: Lib�re la m�moire occup�e par le pin de sortie.

Param�tres:
- pin: Pointeur vers le pin de sortie � d�truire.
Retour: Aucun.
Param�tres modifi�: pin
*/
void t_pin_sortie_destroy(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_GET_VALEUR (Accesseur)
Description: Accesseur du champs valeur.

Param�tres:
- pin: Pointeur vers le pin de sortie.
Retour: (entier) Valeur du pin : 0, 1 ou -1.
Param�tres modifi�: aucun
*/
int t_pin_sortie_get_valeur(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_SET_VALEUR (Mutateur)
Description: Mutateur du champs valeur.

Param�tres:
- pin: Pointeur vers le pin de sortie.
- valeur: nouvelle valeur du pin de sortie 
          (doit obligatoirement �tre -1, 0 ou 1, sinon aucun changement)
Retour: Aucun
Param�tres modifi�: pin
*/
void t_pin_sortie_set_valeur(t_pin_sortie *pin, int valeur);

/*
Fonction: T_PIN_SORTIE_AJOUTER_LIEN
Description: Relie le pin de sortie � un pin d'entr�e. Cette fonction permet de relier le composant, 
			 auquel apparatien le pin de sortie, � un autre composant, auquel appartient le pin d'entr�e.

			 La fonction doit v�rifier qu'on exc�de pas le nombre maximal de liens autoris�s 
			 (SORTIE_MAX_LIAISONS)

Param�tres:
- pin_sortie: le pin de sortie � relier
- pin_entree: Le pin d'entr�e � laquel le pin de sortie sera reli�.
Retour: Vrai si le lien a bien �t� ajout�, faux sinon.
*/
int t_pin_sortie_ajouter_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree);

/*
Fonction: T_PIN_SORTIE_SUPPRIMER_LIEN
Description: Supprime un lien existant entre le pin de sortie et un pin d'entree re�u en param�tre.
			 Si il n'existe aucun lien entre ces deux pins, la fonction n'aura aucun effet.
			 Si ce lien a �t� retrouv�, on le supprime en le rempla�ant par le lien suivant dans la
			 liste des liens. On d�cale toutes les liaisons suivantes vers la gauche �galement.

Param�tres:
- pin_sortie: le pin de sortie dont on veut supprimer le lien
- pin_entree: Le pin d'entr�e vers laquelle le pin de sortie est li�.
Retour: Aucun
*/
void t_pin_sortie_supprimer_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree);


/*
Fonction: T_PIN_SORTIE_EST_RELIEE
Description: Permet de v�rifier si un pin de sortie est reli� � au moins un pin d'entr�e.

Param�tres:
- pin_sortie: le pin de sortie dont on veut v�rifier la liaison
Retour: Bool�en: Vrai si le pin de sortie est reli�e, Faux sinon.
*/
int t_pin_sortie_est_reliee(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_PROPAGER_SIGNAL
Description: Fonction qui propage le signal du pin de sortie vers toutes les pins d'entr�es 
			 avec lesquels il est reli�.

			 Le pin ne doit pas �tre inactif (valeur == -1) et le nombre de liaisons doit �tre
			 non-z�ro pour que le signal puisse se propager.

Param�tres:
- pin_sortie: le pin de sortie dont on veut propager le signal
Retour: (Bool�en) Vrai si le signal s'est bien propag�, faux sinon. Le signal ne peut se propager
	    si le pin est inactif ou si il n'est reli� � aucun pin d'entr�e.
*/
int t_pin_sortie_propager_signal(t_pin_sortie *pin);

/*
Fonction: T_PIN_SORTIE_RESET
Description: R�-initialise la valeur du pin de sortie � INACTIF

Parametre:
- pin_entree: Le pin d'entr�e dont on veut r�initialiser la valeur
Retour: Aucun.
*/
void t_pin_sortie_reset(t_pin_sortie *pin);

#endif