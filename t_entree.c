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

	nouv_entree = (t_entree*)malloc(sizeof(t_entree));

	//Associer le ID (en assumant qu'il est unique)
	nouv_entree->id = id;

	//Associer à INACTIF
	nouv_entree->pin = INACTIF;

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
	t_pin_sortie_destroy((entree->pin));

	//Détruire le tableau de caractere contenant le nom de l'entrée
	free(entree->nom);

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
	if (t_pin_sortie_est_reliee(entree->pin) == VRAI)
		return VRAI;
	return FAUX;
}

/*****************************************************************************/
void t_entree_reset(t_entree* entree)
{
	//Re-initialise la pin de sortie de l'entrée
	t_pin_sortie_reset(entree->pin);
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
	//Vérifier si l'entree est valide ou non
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
	if (resultat != NULL && entree != NULL) {
		//Utilisation de sprintf pour formater une chaine de caractères 
		//Regarde dans le cours 11, il explique sprintf
		//J'ai mis %s pour nom parce que c'est une chaine de caractères
		sprintf(resultat, "ID : %d, valeur : %d, nom : %s, connecté : %d\n", t_entree_get_id(entree), t_entree_get_valeur(entree), t_entree_get_nom(entree), t_entree_est_reliee(entree));
		return;
	}
}







