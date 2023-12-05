/*
Module: T_SORTIE
Description: Le fichier définit le type t_sortie, qui représente une sortie
 dans un circuit logique. Ce module propose des fonctions pour créer, manipuler, 
 et interagir avec des objets t_sortie. Chaque sortie est associée à une unique 
 pin d'entrée, permettant ainsi de recevoir des signaux d'autres composants. 
 Les sorties sont des éléments essentiels pour obtenir les résultats d'un circuit logique. 

Auteurs: Noah Tremblay :
         Jules Gaudet : GAUJ71370101
Derni�re modification: 
*/
/*****************************************************************************/

#include "t_sortie.h"

/*****************************************************************************/

t_sortie *t_sortie_init(int id, char *nom) 
{
    t_sortie *nouv_sortie;

    nouv_sortie = (t_sortie*)malloc(sizeof(t_sortie));

    //Associer le NO (en assumant qu'il est unique)
    nouv_sortie->id = id;

    //Créer la chaine dynamique pour le nom de sortie
    nouv_sortie->nom = (char*)calloc(NOM_ENTREE_TAILLE_MAX, sizeof(char));

    //Associer le nom
    strcpy((nouv_sortie->nom), nom);

    //Creer une pin et la relier a l'entrée
    nouv_sortie->pin = t_pin_entree_init();

    //Associer la pin à INACTIF
    t_sortie_get_pin(nouv_sortie)->valeur = INACTIF;

    return nouv_sortie;
}

/*****************************************************************************/

void t_sortie_destroy(t_sortie *sortie) 
{
    //Détruire le pin d'entrée de la sortie
    t_pin_entree_destroy((sortie->pin));

    //Détruire le tableau de caractères contenant le nom de la sortie
    free(sortie->nom);

    //Détruire la sortie
    free(sortie);
}

/*****************************************************************************/

t_pin_entree *t_sortie_get_pin(t_sortie *sortie) 
{
   return sortie->pin; 
}

/*****************************************************************************/

int t_sortie_relier(t_sortie *dest, char* nom_composant, t_pin_sortie *source) 
{
    //Relier le pin de sortie au pin d'entrée
    t_pin_entree_relier(t_sortie_get_pin(dest), nom_composant, source);

    //verification si le pin d'entree est dans le tableau du pin de sortie
    if (t_sortie_get_pin(dest) != source->liaisons[source->nb_liaisons-1])
        return FAUX;
    return VRAI;
}

/*****************************************************************************/

int t_sortie_est_reliee(t_sortie *sortie) 
{
    if (t_pin_entree_est_reliee(t_sortie_get_pin) == VRAI)
        return VRAI;
    return FAUX;
}

/*****************************************************************************/

void t_sortie_reset(t_sortie *sortie) 
{
    //Re-initialise la pin d'entrée de la sortie
    t_pin_entree_reset(sortie->pin);
}

/*****************************************************************************/

int t_sortie_get_valeur(const t_sortie *sortie)
{
    //Vérifier si la sortie est valide ou non
    if (sortie == NULL)
        return INACTIF;

    //Obtenir le pin d'entrée de la sortie
    t_pin_entree *pin_entree = t_sortie_get_pin(sortie); 

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
	if (sortie != NULL) {
		//Utilisation de sprintf pour formater une chaine de caractères 
		sprintf(resultat, "%d %st", t_sortie_get_id(sortie), 
                                    t_sortie_get_nom(sortie));
	}
}
/*****************************************************************************/
/*****************************************************************************/