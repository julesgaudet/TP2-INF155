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
    //Détruire l'allocation dynamique pour le nom
    free(porte->nom);

    //Détruire l'allocation dynamique pour la porte
    free(porte);

    //Détruire l'allocation dynamique pour la porte de sortie
    t_pin_sortie_destroy(porte->sortie);

    //Détruire l'allocation dynamique pour la porte d'entrée
    t_pin_entree_destroy(porte->entrees);
}

/*****************************************************************************/
void t_porte_calculer_sorties(t_porte *porte)
{
    //Valeur de la porte selon les entrées
    int nouvelle_valeur;

    //Retourne si la porte n'existe pas
    if(porte == NULL)
        return;
    
    switch(porte->type) {

        //Porte ET
        case PORTE_ET : 
            nouvelle_valeur = &
            break;

        //Porte NOT
        case PORTE_NOT : 
            nouvelle_valeur = !
            break;

        //Porte OU
        case PORTE_OU : 
            nouvelle_valeur = |
            break;

        //Porte XOR
        case PORTE_XOR : 
            nouvelle_valeur = ^
            break;
    }

    //Renvoyer les modifications selon la condition de la porte
    t_pin_sortie_set_valeur(porte->sortie, nouvelle_valeur);
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
 return (porte->id);
}

/*****************************************************************************/
char * t_porte_get_nom(const t_porte* porte)
{
 return (porte->nom);
}

/*****************************************************************************/
int t_porte_get_nb_entrees(const t_porte* porte)
{
 return (porte->nb_entrees);
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
    //Afficher les informations de la porte
    if (porte != NULL && resultat != NULL) {
        sprintf(resultat, "ID : %d, nombre d'entrées : %d, nom : %s, type : %d, pin entree : %p, pin sortie : %p",
            t_porte_get_id(porte), t_porte_get_nb_entrees(porte), t_porte_get_nom(porte),
            t_porte_get_type(porte), t_porte_get_pin_entree(porte), t_porte_get_pin_sortie(porte));
        return;
    }

    //Si la porte est NULL ou le résultat est NULL, un message s'affichera dans la console
    printf("La porte est NULL ou le résultat est NULL");
}
/*****************************************************************************/