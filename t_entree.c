/*
Module: T_ENTREE
Description: D�finit le type t_entree. 

Auteur: Noah Tremblay, Jules Gaudet
Derni�re modification: 
*/
/*****************************************************************************/

#include "t_entree.h"

/*****************************************************************************/
t_entree* t_entree_init(int id, char* nom)
{
	t_entree *nouv_entree;

	//associer le no (en assumant qu'il est unique)
	nouv_entree->id = id;

	//associer a INACTIF 
	nouv_entree->pin = INACTIF;

	//Cr�er la chaine dynamique pour le nom de l'entree
	nouv_entree->nom = (char*)calloc(NOM_ENTREE_TAILLE_MAX, sizeof(char));
	//associer le nom
	strcpy((nouv_entree->nom), nom);

	return nouv_entree;
}

/*****************************************************************************/
void t_entree_destroy(t_entree* entree)
{
	//destroy la pin de sortie de l'entreée
	t_pin_sortie_destroy((entree->pin));

	//destroy le tableau dde caractere contenant le nom de l'entrée
	free(entree->nom);

	//destoy la pin
	free(entree);
}

/*****************************************************************************/
t_pin_sortie* t_entree_get_pin(t_entree* entree)
{
	return entree->pin;
}

/*****************************************************************************/
int t_entree_est_reliee(t_entree* entree)
{
	if (t_pin_sortie_est_reliee(entree->pin) == VRAI)
		return VRAI;
	return FAUX;
}

/*****************************************************************************/
void t_entree_reset(t_entree* entree)
{
	//re-initialise la pin de sortie de l'entree
	entree->pin = t_pin_sortie_init();
}

/*****************************************************************************/
int t_entree_propager_signal(t_entree* entree)
{
	if (entree->pin != INACTIF)
	{
		t_pin_sortie_propager_signal(entree->pin);
		return VRAI;
	}
	return FAUX;
}

/*****************************************************************************/
int t_entree_get_valeur(const t_entree* entree)
{
	if (entree->pin != INACTIF)
		return ((entree->pin)->valeur);
	return INACTIF;
}

/*****************************************************************************/
int t_entree_get_id(const t_entree* entree)
{
	return entree->id;
}

/*****************************************************************************/
char* t_entree_get_nom(const t_entree* entree)
{
	return entree->nom;
}

/*****************************************************************************/
void t_entree_serialiser(const t_entree* entree, char* resultat)
{
	//A FAIRE!!!!!
}







