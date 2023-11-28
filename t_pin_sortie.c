/*
Auteur: Anis Boubaker, Jules Gaudet et Noah Tremblay 
Date de modification: 25 novembre 2023 
Module: T_PIN_SORTIE
Description: D�finit le type t_pin_sortie. Un t_pin_sortie est un point de connexion appartenant
			 � un �l�ment du circuit qui envoie un signal (mais n'en recoit pas).
			 Les �l�ments d'un circuit ayant un pin de sortie de signal sont les portes (les entr�es
			 des portes) ainsi que les entrée du circuit.

			 Un pin de sortie permet de relier le composant auquel il appartient � un autre composant.
			 Il doit �tre reli� � un "pin d'entrée" du composant auquel on souhaite se connecter.
*/
/*****************************************************************************/

#include "t_pin_sortie.h"

/*****************************************************************************/
t_pin_sortie *t_pin_sortie_init(void) 
{
    int i;

    t_pin_sortie *nouv_pin;

    nouv_pin = (t_pin_sortie*)malloc(1*sizeof(t_pin_sortie));
    
    //pin est vide et n'a aucune liais
    nouv_pin->valeur = INACTIF;
    nouv_pin->nb_liaisons = 0;


    return nouv_pin;
}

/*****************************************************************************/
void t_pin_sortie_destroy(t_pin_sortie *pin) 
{
    free(pin);
}

/*****************************************************************************/
int t_pin_sortie_get_valeur(t_pin_sortie *pin) 
{
    return pin->valeur;
}

/*****************************************************************************/
void t_pin_sortie_set_valeur(t_pin_sortie *pin, int valeur) 
{
	if (valeur < INACTIF || valeur > 1) {
		return;
	}
	pin->valeur = valeur;
}

/*****************************************************************************/
int t_pin_sortie_ajouter_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree) 
{
    //verification ajouter un lien
    if (pin_sortie->nb_liaisons >= SORTIE_MAX_LIAISONS)
        return FAUX;

    //ajouter l'adresse de la pin entrée dans le tab de la pin sortie
    pin_sortie->liaisons[pin_sortie->nb_liaisons] = pin_entree;

    //ajouter 1 au nb de liaison pin sortie
    pin_sortie->nb_liaisons += 1;

    return pin_sortie->nb_liaisons;
}

/*****************************************************************************/
void t_pin_sortie_supprimer_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree) 
{
    int i, j;

    //recherche de la pin d'entrée dans le tableau liaison de la pins de sortie
    for (i = 0; i < pin_sortie->nb_liaisons; i++)
    {
        if (pin_sortie->liaisons[i] == pin_entree)
        {
            pin_sortie->nb_liaisons -= 1;

            //décalge de toutes les cases apres la "bonne" vers la gauche pour écraser la "bonne"
            for (j = i; j < pin_sortie->nb_liaisons; j++)
            {
                pin_sortie->liaisons[j] = pin_sortie->liaisons[j + 1];
            }
            return;
        }
    }
    //la pin d'entrée n'est pas reliée a la pin de sortie
    return;
}

/*****************************************************************************/
int t_pin_sortie_est_reliee(t_pin_sortie *pin) 
{
    //retourne faux si le nb de liaisons est 0 sinon vrai
    if (pin->nb_liaisons > 0)
        return VRAI;
    else
        return FAUX;
}

/*****************************************************************************/
int t_pin_sortie_propager_signal(t_pin_sortie *pin) 
{
    int i;

    //si la pin sortie n'est pas inactive et qu'elle possede des liaisons
    if (pin->valeur = !INACTIF || pin->nb_liaisons > 0)
    {
        //associe la valeur de la pin de sortie a ses pin d'entrées
        for (i = 0; i < pin->nb_liaisons; i++)
        {
            (pin->liaisons[i])->valeur = pin->valeur;
        }
        return VRAI;
    }
    //si ca n'a pas marché
    return FAUX;
}

/*****************************************************************************/
void t_pin_sortie_reset(t_pin_sortie *pin) 
{
    t_pin_sortie_set_valeur(pin, INACTIF);
}
/*****************************************************************************/
/*****************************************************************************/