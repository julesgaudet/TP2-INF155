/*
Module: T_ENTREE
Description: D�finit le type t_entree (Entr�e de circuit) et fournit les 
			 fonctions pour le manipuler.
Auteur: Anis Boubaker
Derni�re modification: Eric Th�, 2023-11-12
*/

#ifndef ENTREE_H_
#define ENTREE_H_

#include "t_pin_sortie.h"


typedef struct t_pin_sortie t_pin_sortie;

typedef struct t_entree{
	int id;				//Identifiant num�rique de l'entr�e.
						//Doit �tre unique parmi les entr�es du circuit
	char *nom;			//Nom de l'entr�e (ex. "E1")
	t_pin_sortie *pin;  //Pin de sortie
} t_entree;


/*
Fonction: T_ENTREE_INIT
Description: Cr�e une nouvelle entr�e de circuit. Le constrcuteur re�oit un 
			 identifiant num�rique et un nom qui (on assume) sont uniques dans le circuit.
			 Ex. 1 et "E1"

Param�tres:
- id: Entier repr�sentant l'identifiant num�rique de l'entr�e (unique dans un circuit)
- nom: Chaine de caract�res repr�sentant le nom de l'entr�e (unique dans un circuit)
Retour: Pointeur vers l'entr�e de circuit cr��e
Param�tres modifi�: Aucun.
*/
t_entree *t_entree_init(int id, char *nom);

/*
Fonction: T_ENTREE_DESTROY
Description: Lib�re la m�moire occup�e par l'entr�e et tous ses composants (i.e. le pin).
NDE: Ne pas oublier de premi�rement d�truire le pin_sortie de l'entr�e.

Param�tres:
- entree: Pointeur vers l'entr�e � d�truire.
Retour: Aucun.
*/
void t_entree_destroy(t_entree *entree);

/*
Fonction: T_ENTREE_GET_PIN
Description: Accesseur - Retourne un pointeur vers le t_pin_sortie de l'entr�e

Param�tres:
- entree: Pointeur vers l'entr�e de circuit dont on veut acc�der au pin de sortie.
Retour: Pointeur vers le t_pin_sortie de l'entr�e.
*/
t_pin_sortie *t_entree_get_pin(t_entree *entree);

/*
Fonction: T_ENTREE_EST_RELIEE
Description: V�rifie si une entr�e de circuit est reli�e. Pour qu'elle soit reli�e,
			 son pin de sortie doit �tre reli�.
NDE: Il existe une fonction dans t_pin_sortie qui vous permet
	 de v�rifier si un pin est reli�. Utilisez-la!

Param�tres:
- entree: Pointeur vers l'entr�e que l'on souhaite v�rifier.
Retour: Bool�en Vrai si la porte est enti�rement reli�e, faux sinon.
*/
int t_entree_est_reliee(t_entree *entree);

/*
Fonction: T_ENTREE_RESET
Description: R�initialise une entr�e. Pour r�initialiser une entr�e, il suffit
			 de r�-initialiser son pin_sortie.
NDE: Il y'a une fonction pr�te pour �a dans le module t_pin_sortie.

Param�tres:
- entree: Pointeur vers l'entr�e de circuit � r�initialiser.
Retour: Aucun
*/
void t_entree_reset(t_entree *entree);

/*
Fonction: T_ENTREE_PROPAGER_SIGNAL
Description: Propage le signal � partir de l'entr�e de circuit pass�e en param�tre.
			 Pour que le signal puisse se propager, il faut que le pin_sortie de
			 l'entr�e ait une valeur valide (i.e. != -1).
NDE: Utilisez la fonction t_pin_sortie_propager_signal().

Param�tres:
- entree: Pointeur vers l'entr�e de circuit dont on veut propager le signal.
Retour: Bool�en: vrai si le signal a pu se propager (i.e. le pin_sortie a une
		valeur), Faux sinon.
*/
int t_entree_propager_signal(t_entree *entree);

/*
Fonction: T_ENTREE_GET_VALEUR
Description: Retourne la valeur du signal de l'entr�e. Ceci correspond � la valeur
			 du signal de son pin_sortie.

Param�tres:
- entree: Pointeur vers l'entr�e de circuit dont on veut connaitre la valeur.
Retour: Entier: valeur du signal � l'entr�e du circuit. 
*/
int t_entree_get_valeur(const t_entree *entree);

/*
Fonction: T_ENTREE_GET_ID
Description: Retourne le id (num�ro) de l'entr�e.

Param�tres:
- entree: Pointeur vers l'entr�e de circuit dont on veut connaitre son id
Retour: Entier: valeur de l'id de l'entr�e (son num�ro).
*/
int t_entree_get_id(const t_entree* entree);

/*
Fonction: T_ENTREE_GET_NOM
Description: Retourne le nom de l'entr�e.

Param�tres:
- entree: Pointeur vers l'entr�e de circuit dont on veut connaitre son nom
Retour: String: valeur du nom de l'entr�e.
*/
char* t_entree_get_nom(const t_entree* entree);

/*
Fonction: T_ENTREE_SERIALISER_LIENS
Description: Transforme en texte les informations d'une entr�e.

Param�tres:
- entree: Pointeur vers l'entr�e de circuit � s�rialiser.
- resultat: Chaine de caract�res dans laquelle on copie le texte g�n�r�.
*/
void t_entree_serialiser(const t_entree* entree, char* resultat);     

#endif