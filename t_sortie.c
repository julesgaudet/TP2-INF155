/*
Module: T_ENTREE
Description: D�finit le type t_entree. 

Auteur: Noah Tremblay, Jules Gaudet
Derni�re modification: 
*/
/*****************************************************************************/

#include "t_sortie.h"

/*****************************************************************************/
t_sortie *t_sortie_init(int id, char *nom) 
{
    t_sortie *nouv_sortie;

    //Associer le NO (en assumant qu'il est unique)
    nouv_sortie->id = id;

    //Associer la pin à INACTIF
    nouv_sortie->pin = INACTIF;

    //Créer la chaine dynamique pour le nom de sortie
    nouv_sortie->nom = (char*)calloc(NOM_ENTREE_TAILLE_MAX, sizeof(char));

    //Associer le nom
    strcpy((nouv_sortie->nom), nom);

    return nouv_sortie;
}

/*****************************************************************************/
void t_sortie_destroy(t_sortie *sortie) 
{
    //Détruire le pin d'entrée de la sortie
    t_pin_entree_destroy((sortie->pin));

    //Détruire le tableau de caractères contenant le nom de la sortie
    free(sortie->nom);
}

/*****************************************************************************/
t_pin_entree *t_sortie_get_pin(t_sortie *sortie) 
{
   return sortie->pin; 
}

/*****************************************************************************/
int t_sortie_relier(t_sortie *dest, char* nom_composant, const t_pin_sortie *source) 
{

}

/*****************************************************************************/
int t_sortie_est_reliee(t_sortie *sortie) 
{
    if (t_pin_entree_est_reliee(sortie->pin) == VRAI)
        return VRAI;
    return FAUX;
}

/*****************************************************************************/
void t_sortie_reset(t_sortie *sortie) 
{
    //Re-initialise la pin d'entrée de la sortie
    sortie->pin = t_pin_entree_init();
}

/*****************************************************************************/
int t_sortie_get_valeur(const t_sortie *sortie)
{
    //Vérifier si la sortie est valide ou non
    if (sortie == NULL)
        return INACTIF;

    //Obtenir le pin d'entrée de la sortie
    t_pin_entree *pin_entree = t_sortie_get_pin_entree(sortie); 

    //Si le pin d'entrée est NULL
    if (pin_entree == NULL) {
        return INACTIF;
    }

    //Obtenir la valeur si elle est valide
    return t_pin_entree_get_valeur(pin_entree);
}

/*****************************************************************************/
int t_sortie_get_id(const t_sortie* sortie) 
{
    return sortie->id;
}

/*****************************************************************************/
char* t_sortie_get_nom(const t_sortie* sortie) 
{
    return sortie->nom;
}

/*****************************************************************************/
void t_sortie_serialiser(const t_sortie* sortie, char* resultat)
{
	if (resultat != NULL && sortie != NULL) {
		//Utilisation de sprintf pour formater une chaine de caractères 
		sprintf(resultat, "ID : %d, valeur : %d, nom : %s, connecté : %d\n", t_sortie_get_id(sortie), t_sortie_get_valeur(sortie), t_sortie_get_nom(sortie), t_sortie_est_reliee(sortie));
		return;
	}
}
