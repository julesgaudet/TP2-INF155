/*
Module: T_ENTREE
Description: Le fichier définit le type t_porte, qui représente 
une porte logique dans un circuit. Ce module propose des fonctions
pour créer, manipuler, et interagir avec des objets t_porte. Chaque 
porte possède un identifiant unique, un nom, un type (ET, OU, NOT, XOR), 
une ou plusieurs entrées, ainsi qu'une sortie. Ces portes sont des éléments 
fondamentaux dans la modélisation des circuits logiques, et 
leur état est déterminé par les valeurs de leurs entrées.

Auteurs: Noah Tremblay : TREN85330401
         Jules Gaudet  : GAUJ71370101
Derni�re modification  : 
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

    //donner son type
    nouv_porte->type = type;

    //créer la sortie
    nouv_porte->sortie = t_pin_sortie_init();

    //Initialiser le bon nombre d'entrées

    //Si c'est une porte NOT
    if (nouv_porte->type == PORTE_NOT)
    {
        nouv_porte->nb_entrees = 1;
        nouv_porte->entrees[0] = t_pin_entree_init();
    }
    //Si c'est une porte XNOT, AND et OR
    else
    {
        nouv_porte->nb_entrees = 2;
        nouv_porte->entrees[0] = t_pin_entree_init();
        nouv_porte->entrees[1] = t_pin_entree_init();
    }
    return nouv_porte;
}

/*****************************************************************************/

void t_porte_destroy(t_porte *porte)
{
    int i;
    //Détruire l'allocation dynamique pour les porte d'entrée
    for (i=0; i< porte->nb_entrees; i++)
        t_pin_entree_destroy(porte->entrees[i]);

    //détruire la pin de sortie
    t_pin_sortie_destroy(porte->sortie);

    //Détruire l'allocation dynamique pour le nom
    free(porte->nom);

    //Détruire l'allocation dynamique pour la porte
    free(porte);
}

/*****************************************************************************/

void t_porte_calculer_sorties(t_porte *porte)
{
    //Valeur de la porte selon les entrées
    int nouvelle_valeur;
    nouvelle_valeur = INACTIF;

    //Retourne si la porte n'existe pas
    if(porte == NULL)
        return;
    
    switch(t_porte_get_type(porte)) {

        //Porte ET
        case PORTE_ET : 
            nouvelle_valeur = porte->entrees[0]->valeur & porte->entrees[0]->valeur;
            break;

        //Porte NOT
        case PORTE_NOT : 
            nouvelle_valeur = !porte->entrees[0]->valeur;
            break;

        //Porte OU
        case PORTE_OU : 
            nouvelle_valeur = porte->entrees[0]->valeur | porte->entrees[0]->valeur;
            break;

        //Porte XOR
        case PORTE_XOR : 
            nouvelle_valeur = porte->entrees[0]->valeur ^ porte->entrees[0]->valeur;
            break;
    }

    //Renvoyer les modifications selon la condition de la porte
    t_pin_sortie_set_valeur(porte->sortie, nouvelle_valeur);
}

/*****************************************************************************/

int t_porte_relier(t_porte *dest, int num_entree, char* nom_sortie, t_pin_sortie *source)
{
    //Si l'indice de l'entree n'existe pas
    if (num_entree > (dest->nb_entrees))
        return FAUX;

    //Relie la pin de sortie a la pin d'entree de la porte
    t_pin_entree_relier(dest->entrees[num_entree], nom_sortie, source);
    return VRAI;
}

/*****************************************************************************/

int t_porte_est_reliee(t_porte *porte)
{
    int i;

    //Vérifier que tout les pins d'entrées sont reliées
    for (i = 0; i < porte->nb_entrees; i++)
    {
        if (t_pin_entree_est_reliee(porte->entrees[i]) == FAUX)
        {
            return FAUX;
        }
    }

    //Vérifier que le pin de sortie est reliée
    if (t_pin_sortie_est_reliee(porte->sortie) == FAUX)
    {
        return FAUX;
    }

    //Retourne vrai si les conditions sont respectés
    return VRAI;
}

/*****************************************************************************/

void t_porte_reset(t_porte *porte)
{
    int i;
    //initialise la valeur des entrées
    for (i = 0; i < porte->nb_entrees; i++)
    {
        t_pin_entree_reset(porte->entrees[i]);
    }
    //initialise la sortie
    t_pin_sortie_reset(porte->sortie);
}

/*****************************************************************************/

int t_porte_propager_signal(t_porte *porte) 
{
    int i;
    //verif tout les pins entree sont actifs
    for (i = 0; i < porte->nb_entrees; i++)
    {
        if (t_pin_entree_get_valeur(porte->entrees[i]) == INACTIF)
            return FAUX;
    }
    
    //calculer et assigner la valeur su pin sorte de la porte
    t_porte_calculer_sorties(porte);

    //propager le signal a partir de la pin de sortie
    t_pin_sortie_propager_signal(porte->sortie);
    
    return VRAI;
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
    return porte->type;
}

/*****************************************************************************/

t_pin_entree* t_porte_get_pin_entree(const t_porte* porte, int num)
{
    if (num == 0)
        return porte->entrees[0];

    else
        return porte->entrees[1];
}
/*****************************************************************************/

t_pin_sortie* t_porte_get_pin_sortie(const t_porte* porte)
{
    return porte->sortie;
}

/*****************************************************************************/

void t_porte_serialiser(const t_porte* porte, char* resultat) {
    
    if (porte != NULL) {
        sprintf(resultat, "%d %d %s", t_porte_get_id(porte), 
                                      t_porte_get_type(porte),
                                      t_porte_get_nom(porte));
    }
}
/*****************************************************************************/
/*****************************************************************************/