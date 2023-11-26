/*
Module: T_ENTREE
Description: D�finit le type t_entree. 

Auteur: Noah Tremblay, Jules Gaudet
Derni�re modification: 
*/
/*****************************************************************************/

#include "t_porte.h"

/*****************************************************************************/
t_porte *t_porte_init(int id, e_types_portes type, char *nom)
{
    //Création et allocation de la mémoire pour la nouvelle porte
    t_porte *nouv_porte = (t_porte*)malloc(sizeof(t_porte));

    //Associer le ID (en assumant qu'il est unique)
    nouv_porte->id = id;

    //Créer la chaine dynamique pour le nom de l'entrée
    nouv_porte->nom = (char*)calloc(NOM_ENTREE_TAILLE_MAX, sizeof(char));

    //Initialiser le nombre d'entrées à 0
    nouv_porte->nb_entrees = 0;
}

/*****************************************************************************/
void t_porte_destroy(t_porte *porte)
{

}

/*****************************************************************************/
void t_porte_calculer_sorties(t_porte *porte)
{

}

/*****************************************************************************/
int t_porte_relier(t_porte *dest, int num_entree, char* nom_sortie, const t_pin_sortie *source)
{

}

/*****************************************************************************/
int t_porte_est_reliee(t_porte *porte)
{

}

/*****************************************************************************/
void t_porte_reset(t_porte *porte)
{

}

/*****************************************************************************/
int t_porte_propager_signal(t_porte *porte) 
{
    
}

/*****************************************************************************/
int t_porte_get_id(const t_porte* porte)
{

}

/*****************************************************************************/
char * t_porte_get_nom(const t_porte* porte)
{

}

/*****************************************************************************/
int t_porte_get_nb_entrees(const t_porte* porte)
{

}

/*****************************************************************************/
e_types_portes t_porte_get_type(const t_porte* porte)
{

}

/*****************************************************************************/
t_pin_entree* t_porte_get_pin_entree(const t_porte* porte, int num)
{

}
/*****************************************************************************/
t_pin_sortie* t_porte_get_pin_sortie(const t_porte* porte)
{

}

/*****************************************************************************/
void t_porte_serialiser(const t_porte* porte, char* resultat) 
{

}

/*****************************************************************************/