/*
Module: T_SORTIE
Description: D�finit le type t_sortie (sortie de circuit) et fournit les
			 fonctions pour le manipuler.
Auteur: Anis Boubaker
Derni�re modification: Eric Th�, 2023-11-12
*/


#ifndef SORTIE_H_
#define SORTIE_H_

#include "t_pin_entree.h"

typedef struct t_pin_entree t_pin_entree;

#define NOM_SORTIE_TAILLE_MAX 3 	//Taille maximale du nom de la sortie

typedef struct t_sortie{
	int id;				//Identifiant num�rique de la sortie de circuit.
						//Doit �tre unique parmi les sorties du circuit
	char *nom;			//Nom de la sortie (ex. "S1")
	t_pin_entree *pin;  //Pin de la sortie
} t_sortie;


/*
Fonction: T_SORTIE_INIT
Description: Cr�e une nouvelle sortie de circuit. Le constrcuteur re�oit un
			 identifiant num�rique et un nom qui (on assume) sont uniques dans le circuit.
			 Ex. 1 et "S1"
		
Param�tres:
- id: Entier repr�sentant l'identifiant num�rique de la sortie (unique dans un circuit)
- nom: Chaine de caract�res repr�sentant le nom de l'entr�e (unique dans un circuit)
Retour: Pointeur vers la sortie de circuit cr��e
Param�tres modifi�: Aucun.
*/
t_sortie *t_sortie_init(int id, char *nom);

/*
Fonction: T_SORTIE_DESTROY
Description: Lib�re la m�moire occup�e par la sortie et tous ses composants (i.e. le pin).
NDE: Ne pas oublier de premi�rement d�truire le pin_entr�e de la sortie.

Param�tres:
- sortie: Pointeur vers la sortie � d�truire.
Retour: Aucun.
*/
void t_sortie_destroy(t_sortie *sortie);

/*
Fonction: T_SORTIE_GET_PIN
Description: Accesseur - Retourne un pointeur vers le pin_entree de la sortie de circuit.

Param�tres:
- sortie: Pointeur vers la sortie de circuit dont on veut acc�der au pin_entree.
Retour: Pointeur vers le pin_entree de la sortie de circuit.
*/
t_pin_entree *t_sortie_get_pin(t_sortie *sortie);


/*
Fonction: T_SORTIE_RELIER
Description: Relie une sortie de circuit à un autre composant du circuit (une entr�e ou une porte)
			 On note ici qu'on relie le pin_entree de la sortie vers un pin_sortie
			 d'un autre composant. Les seuls autres composants disposant d'un pin_sortie sont
			 les entrées et les portes du circuit. 
			 Si la sortie a déjà été reliée, le nouveau lien va écraser l'ancien. 
NDE: Pour faire la liaison, la fonction t_pin_entree_relier() vous sera très utile!

Param�tres:
- dest: Pointeur vers la sortie de circuit à relier.
- nom_composant: Le nom du composant de circuit à lequel ont relie la sortie.
- source: Le pin_sortie vers lequel nous allons relier la sortie de circuit. 
Retour: Booléen : Vrai si la liaison a bien été effectuée. Faux sinon. 
*/
int t_sortie_relier(t_sortie *dest, char* nom_composant, const t_pin_sortie *source);

/*
Fonction: T_SORTIE_EST_RELIEE
Description: V�rifie si une sortie de circuit est reli�e. Pour qu'elle soit reli�e,
			 son pin_entree doit �tre reli�.
NDE: Il existe une fonction dans t_pin_entree qui vous permet
	 de v�rifier si un pin est reli�. Utilisez-la!

Param�tres:
- sortie: Pointeur vers la sortie que l'on souhaite v�rifier.
Retour: Bool�en Vrai si la porte est enti�rement reli�e, Faux sinon.
*/
int t_sortie_est_reliee(t_sortie *sortie);

/*
Fonction: T_SORTIE_RESET
Description: R�initialise une sortie. Pour r�initialiser une sortie, il suffit
de r�-initialiser son pin_entree.
NDE: Il y'a une fonction pr�te pour �a dans le module t_pin_entree.

Param�tres:
- sortie: Pointeur vers la sortie de circuit � r�initialiser.
Retour: Aucun
*/
void t_sortie_reset(t_sortie *sortie);

/*
Fonction: T_SORTIE_GET_VALEUR
Description: Retourne la valeur du signal de la sortie. Ceci correspond � la valeur
			 du signal de son pin_entree.
NDE: Il y'a une fonction pr�te pour �a dans le module t_pin_entree.

Param�tres:
- sortie: Pointeur vers la sortie de circuit dont on veut connaitre la valeur.
Retour: Entier: valeur du signal � la sortie
*/
int t_sortie_get_valeur(const t_sortie *sortie);

/*
Fonction: T_SORTIE_GET_ID
Description: Retourne le id (num�ro) de la sortie.

Param�tres:
- sortie: Pointeur vers la sortie de circuit dont on veut connaitre son id
Retour: Entier: valeur de l'id de la sortie (son num�ro).
*/
int t_sortie_get_id(const t_sortie* sortie);

/*
Fonction: T_SORTIE_GET_NOM
Description: Retourne le nom de la sortie.

Param�tres:
- sortie: Pointeur vers la sortie de circuit dont on veut connaitre son nom
Retour: String: valeur du nom de la sortie.
*/
char* t_sortie_get_nom(const t_sortie* sortie);

/*
Fonction: T_SORTIE_SERIALISER_LIENS
Description: Transforme en texte les informations d'une sortie.

Param�tres:
- sortie: Pointeur vers la sortie de circuit � s�rialiser.
- resultat: Chaine de caract�res dans laquelle on copie le texte g�n�r�.
*/
void t_sortie_serialiser(const t_sortie* sortie, char* resultat);   


#endif