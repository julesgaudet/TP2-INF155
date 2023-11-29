/*
Module: T_PIN_ENTREE
Description: D�finit le type t_pin_entree. Un t_pin_entree est un point de connexion appartenant
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
/*****************************************************************************/

#include "t_pin_entree.h"

/*****************************************************************************/

t_pin_entree *t_pin_entree_init()
{
	t_pin_entree *nouv_pin;

	nouv_pin = (t_pin_entree*)malloc(sizeof(t_pin_entree));

	//Ce pin contient aucune valeur et pas de liaison.
	nouv_pin->valeur = INACTIF;
	nouv_pin->liaison = NULL;

	//Cr�er la chaine dynamique pour le nom de la connexion (toute � z�ro)
	nouv_pin->nom_liaison = (char*)calloc(NOM_ENTREE_TAILLE_MAX, sizeof(char));

	return nouv_pin;
}

/*****************************************************************************/

int t_pin_entree_get_valeur(const t_pin_entree * pin)
{
	return pin->valeur;
}

/*****************************************************************************/

char* t_pin_entree_get_lien(const t_pin_entree* pin)
{
	return pin->nom_liaison;
}

/*****************************************************************************/

void t_pin_entree_set_valeur(t_pin_entree * pin, int valeur)
{
	if (valeur < INACTIF || valeur > 1) {
		//Valeur erron�e
		return;
	}
	pin->valeur = valeur;
}

/*****************************************************************************/

void t_pin_entree_relier(t_pin_entree * pin_entree, char * nom_sortie, const t_pin_sortie * pin_sortie)
{
	//On v�rifie d'abord si on avait un lien existant
	if (pin_entree->liaison != NULL) {
		//On supprime la liaison du pin de sortie � lequel on est pr�sentement li�s
		t_pin_sortie_supprimer_lien(pin_entree->liaison, pin_entree);
	}
	pin_entree->liaison = pin_sortie;

	strcpy(pin_entree->nom_liaison, nom_sortie);      //on copie le nom de la connexion

	t_pin_sortie_ajouter_lien(pin_sortie, pin_entree);
}

/*****************************************************************************/

int t_pin_entree_est_reliee(t_pin_entree * pin)
{
	return pin->liaison != NULL;
}

/*****************************************************************************/

void t_pin_entree_reset(t_pin_entree * pin)
{
	pin->valeur = INACTIF;
}

/*****************************************************************************/

void t_pin_entree_destroy(t_pin_entree * pin)
{
	free(pin->nom_liaison);
	free(pin);
}

/*****************************************************************************/
/*****************************************************************************/