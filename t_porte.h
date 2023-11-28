/*
Module: T_PORTE
Description: D�finit le type porte et fournit les fonctions pour manipuler une porte.
Note: Ce module a �t� con�u de sorte � ce qu'il soit facielement extensible pour traiter
      des portes peronnalis�es (i.e. des circuits qu'on r�utilise comme des portes dans 
	  d'autres circuits. Pour limiter le travail des �tudiants, cette fonctionnalit� a �t�
	  abandonn�e mais il n'en demeure pas moins un point d'�volution potentiel du projet. 
      Les �tudiants courageux sont encourag�s � consid�rer, voir impl�menter cette �volution.
Auteur: Anis Boubaker
Derni�re modification: Eric Th�, 2023-11-06
*/

#ifndef T_PORTE_H_
#define T_PORTE_H_

#include <string.h>
#include <stdio.h>
#include "t_pin_entree.h"
#include "t_pin_sortie.h"
#include "t_circuit.h"


typedef struct t_pin_entree t_pin_entree;
typedef struct t_pin_sortie t_pin_sortie;

#define MAX_ENTREES_PORTE  2    //Nombre maximales d'entr�es pour une porte (AND, OR, XOR)
#define NOM_PORTE_TAILLE_MAX 3  //Taille maximale du nom d'une porte
								//en nombre de caract�res

/*
�num�ration: E_TYPES_PORTES
Description: �num�re les types de portes permis 
*/
typedef enum e_types_portes { PORTE_ET, PORTE_OU, PORTE_NOT, PORTE_XOR } e_types_portes;


/*
D�finit le type t_porte qui permet de stocker l'information relative � une porte.
*/
typedef struct t_porte {
	int id;      //Identifiant num�rique de la porte (doit �tre unique dans un circuit)

	char *nom;            //Nom de la porte construit � partir de l'identifiant (ex. "P1")

	e_types_portes type;  //Type �num�r� de la porte (parmi les types �num�r�s)

	//Tableau statique de pointeurs vers des pins d�entr�es. L'ensemble des pins d�entr�es
	//repr�sente les entr�es de la porte.
	t_pin_entree *entrees[MAX_ENTREES_PORTE];

	t_pin_sortie *sortie;   //Pointeur vers le pin de sortie de la porte

	//Nombre d'entr�es de la porte. Repr�sente le nombre d'�l�ments effectifs
	//dans le tableau du champ "entrees[]"
	int nb_entrees;
} t_porte;



/*
Fonction: T_PORTE_INIT
Description: Cr�e une nouvelle porte du type sp�cifi� en param�tre. Selon le type, la 
			 fonction initialise les pin_entrees n�cessaires pour ce type de porte.

			 L'identifiant num�rique ainsi que le nom re�u en param�tre doivent �tre unique 
			 dans le circuit. Ex. 1 et "P1"

Param�tres: 
- id: Entier repr�sentant l'identifiant num�rique de la porte (unique dans un circuit)
- type: Le type de porte � cr�er, selon la liste des types pr�d�finis dans e_types_portes
- nom: Chaine de caract�res repr�sentant le nom de la porte (unique dans un circuit)
Retour: Pointeur vers la porte cr��e
Param�tres modifi�: Aucun.
*/
t_porte *t_porte_init(int id, e_types_portes type, char *nom);

/*
Fonction: T_PORTE_DESTROY
Description: Lib�re la m�moire occup�e par la porte et tous ses composants.
NDE: Ne pas oublier de d�truire toutes les pin_entree et le pin_sortie appartenant � la porte.
Param�tres:
- porte: Pointeur vers la porte � d�truire.
Retour: Aucun.
*/
void t_porte_destroy(t_porte *porte);

/*
Fonction: T_PORTE_CALCULER_SORTIES
Description: Calcule la valeur du pin de sortie de la porte, selon la valeur des pin_entree 
			 et le type de porte. Par exemple, si la porte est une porte ET, et que les deux
			 pin_entree de la porte ont une valeur de 1, la pin_sortie de la porte doit avoir
			 la valeur 1. 
NDE: 
- N'oubliez pas qu'il existe des op�rateurs binaires en C. Utilisez-les!
- N'oubliez pas que, pour modifier la valeur d'un pin_sortie vous devez utiliser le
  mutateur correspondant (par exemple t_pin_sortie_set_valeur) et ne pas modifier la valeur
  du champ directement ici (car nous sommes � l'ext�rieur du module t_pin_sortie).
Param�tres:
- porte: Pointeur vers la porte dont on souhaite calculer la sortie  
		 (il n'existe qu'une seule sortie par porte).
Retour: Aucun.
*/
void t_porte_calculer_sorties(t_porte *porte);


/*
Fonction: T_PORTE_RELIER
Description: Relie une des entr�es de la porte � un autre composant du circuit (une entr�e ou une autre porte)
			 On note ici qu'on relie une des pin_entree de la porte vers une pin_sortie
			 d'un autre composant. Les seuls autres composants disposant de pin_sortie sont
			 les entr�es du circuit et les autres portes. 

			 Si l'entr�e de la porte en question a d�j� �t� reli�e, l'ancien lien est remplac� par le nouveau.
NDE: Pour faire la liaison, la fonction t_pin_entree_relier vous sera tr�s utile!

Param�tres:
- porte: Pointeur vers la porte � relier.
- num_entree: l'indice de la pin_entree � relier dans le tableau des entr�es. 
			  Si cet indice n'existe pas, la fonction retourne faux.  
- nom_sortie: Le nom du composant qui contient le pin de sortie � connecter.
- source: Le pin_sortie vers laquelle nous allons relier l'entr�e de la porte. 
Retour: Bool�en : Vrai si la liaison a bien �t� effectu�e. Faux sinon. 
*/
int t_porte_relier(t_porte *dest, int num_entree, char* nom_sortie, t_pin_sortie *source);

/*
Fonction: T_PORTE_EST_RELIEE
Description: V�rifie si une porte est enti�rement reli�e. Pour qu'elle soit enti�rement
			 reli�e, ses pin d'entr�es et son pin de sortie doivent tous �tre reli�es.
NDE: Il existe des fonctions dans t_pin_entree et t_pin_sortie qui vous permettent
     de v�rifier si une pin est reli�e. Utilisez-les!

Param�tres:
- porte: Pointeur vers la porte que l'on souhaite v�rifier.
Retour: Bool�en Vrai si la porte est enti�rement reli�e, faux sinon.
*/
int t_porte_est_reliee(t_porte *porte);

/*
Fonction: T_PORTE_RESET
Description: R�initialise une porte. Pour r�initialiser une porte, il suffit
			 de r�-initialise	r chacuns de ses pins (� INACTIF). 
NDE: Encore ici, il y'a des fonctions pr�tes dans les modules t_pin_entree
	 et t_pin_sortie pour r�-initialiser tous les pins.

Param�tres:
- porte: Pointeur vers la porte � r�initialiser.
Retour: Aucun
*/
void t_porte_reset(t_porte *porte);

/*
Fonction: T_PORTE_PROPAGER_SIGNAL
Description: Propage le signal � partir de la porte pass�e en param�tre.
			 Pour que le signal puisse se propager, il faut que la porte
			 ait une valeur valide sur chacune de ses entr�es (i.e. != -1).
			 Si c'est le cas, il suffit de calculer la sortie, puis de propager
			 le signal � partir du pin_sortie de la porte.
NDE: Une fois que vous avez calcul� la valeur du pin de sortie,  
	 utilisez la fonction t_pin_sortie_propager_signal.

Param�tres:
- porte: Pointeur vers la porte dont on veut propager le signal.
Retour: Bool�en: vrai si le signal a pu se propager (i.e. toutes les entr�es ont
		r��u un signal, Faux sinon.
*/
int t_porte_propager_signal(t_porte *porte);

/************************** Les ACCESSEURS ************************************/

/*
Fonction: T_PORTE_GET_ID
Description: Retourne le id (num�ro) de la porte.

Param�tres:
- porte: Pointeur vers la porte de circuit dont on veut connaitre son id
Retour: Entier: valeur de l'id de la porte (son num�ro).
*/
int t_porte_get_id(const t_porte* porte);

/*
Fonction: T_PORTE_GET_NOM
Description: Retourne le nom de la porte.

Param�tres:
- porte: Pointeur vers la porte de circuit dont on veut connaitre son nom
Retour: String: valeur du nom de la porte.
*/
char * t_porte_get_nom(const t_porte* porte);

/*
Fonction: T_PORTE_GET_NB_ENTREES
Description: Retourne le nombre d'entr�es de la porte (soit 1 ou 2).

Param�tres:
- porte: Pointeur vers la porte de circuit dont on veut connaitre son nb. d'entr�es
Retour: Entier: valeur du nombre d'entr�es de la porte.
*/
int t_porte_get_nb_entrees(const t_porte* porte);

/*
Fonction: T_PORTE_GET_TYPE
Description: Retourne le type logique de la porte.

Param�tres:
- porte: Pointeur vers la porte de circuit dont on veut connaitre son type
Retour: (e_types_portes) valeur du type logique de la porte.
*/
e_types_portes t_porte_get_type(const t_porte* porte);

/*
Fonction: T_PORTE_GET_PIN_ENTREE
Description: Accesseur - Retourne un pointeur vers un des t_pin_entree de la porte.

Param�tres:
- porte: Pointeur vers la porte de circuit dont on veut acc�der � un de ses pins de sortie.
- num: Position de l'entr�e d�sir�e (soit 0 ou 1).
Retour: Pointeur vers le t_pin_sortie d�sir� de la porte.
*/
t_pin_entree* t_porte_get_pin_entree(const t_porte* porte, int num);

/*
Fonction: T_PORTE_GET_PIN_SORTIE
Description: Accesseur - Retourne un pointeur vers le t_pin_sortie de la porte.

Param�tres:
- porte: Pointeur vers la porte de circuit dont on veut acc�der au pin de sortie.
Retour: Pointeur vers le t_pin_sortie de la porte.
*/
t_pin_sortie* t_porte_get_pin_sortie(const t_porte* porte);

/*
Fonction: T_PORTE_SERIALISER
Description: Transforme en texte les informations d'une porte.

Param�tres:
- porte: Pointeur vers la porte de circuit � s�rialiser.
- resultat: Chaine de caract�res dans laquelle on copie le texte g�n�r�.
*/
void t_porte_serialiser(const t_porte* porte, char* resultat);

#endif