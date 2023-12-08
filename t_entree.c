﻿/*
Module: T_ENTREE
Description: Le fichier  définit le type t_entree, 
représentant une entrée dans un circuit logique. Ce module offre 
des fonctions pour créer, manipuler et interagir avec des objets 
t_entree. Chaque entrée est associée à un identifiant unique, un 
nom, une valeur logique (activée ou désactivée), ainsi qu'une pin 
de sortie. Les entrées sont des composants essentiels d'un circuit 
logique, et leur état peut être propagé à travers le circuit.

Auteur: Noah Tremblay : TREN85330401
		Jules Gaudet  : GAUJ71370101
Derni�re modification : 09/12/2023
*/
/*****************************************************************************/

#include "t_entree.h"

/*****************************************************************************/

t_entree* t_entree_init(int id, char* nom)
{
	t_entree *nouv_entree;

	nouv_entree = (t_entree*)malloc(sizeof(t_entree));

	//Associer le ID (en assumant qu'il est unique)
	nouv_entree->id = id;

	//Créer la chaine dynamique pour le nom de l'entrée
	nouv_entree->nom = (char*)calloc(NOM_ENTREE_TAILLE_MAX, sizeof(char));

	//Associer le nom
	strcpy((nouv_entree->nom), nom);

	//creer une pin et la relier a l'entree
	nouv_entree->pin = t_pin_sortie_init();

	return nouv_entree;
}

/*****************************************************************************/

void t_entree_destroy(t_entree* entree)
{
	//Détruire la pin de sortie de l'entreée
	t_pin_sortie_destroy((t_entree_get_pin(entree)));

	//Détruire le tableau de caractere contenant le nom de l'entrée
	free(t_entree_get_nom(entree));

	//Détruire la pin
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
	if (t_pin_sortie_est_reliee(t_entree_get_pin(entree)) == VRAI)
		return VRAI;
	return FAUX;
}

/*****************************************************************************/

void t_entree_reset(t_entree* entree)
{
	//Re-initialise la pin de sortie de l'entrée
	t_pin_sortie_reset(t_entree_get_pin(entree));
}

/*****************************************************************************/

int t_entree_propager_signal(t_entree* entree)
{
	if (t_entree_get_pin(entree) != INACTIF)
	{
		t_pin_sortie_propager_signal(t_entree_get_pin(entree));
		return VRAI;
	}
	return FAUX;
}

/*****************************************************************************/

int t_entree_get_valeur(const t_entree* entree)
{
	//Vérifier si l'entree est valide ou non
	if (t_entree_get_pin(entree) != INACTIF)
		return (t_entree_get_pin(entree)->valeur);
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
	if (entree != NULL) {

		sprintf(resultat, "%d %s", t_entree_get_id(entree), 
								   t_entree_get_nom(entree));
	}
}
/*****************************************************************************/
/*****************************************************************************/







