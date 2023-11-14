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

#include "t_pin_sortie.h"

t_pin_sortie *t_pin_sortie_init(void) {

    t_pin_sortie *nouv_pin;
	nouv_pin = (t_pin_sortie*)malloc(sizeof(t_pin_sortie));

    nouv_pin->valeur = INACTIF;
	nouv_pin->liaison = NULL;

    nouv_pin->nom_liaison = (char*)calloc(NOM_ENTREE_TAILLE_MAX, sizeof(char));
	return nouv_pin;
}

void T_PIN_SORTIE_DESTROY(t_pin_sortie *pin) {
    if (pin != NULL) {
        free(pin->nom_liaison);
        free(pin);
    }
}

int t_pin_sortie_get_valeur(t_pin_sortie *pin) {
    return pin->valeur;
}

int t_pin_sortie_ajouter_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree) {
    
}

void t_pin_sortie_supprimer_lien(t_pin_sortie *pin_sortie, const t_pin_entree *pin_entree) {

}

int t_pin_sortie_est_reliee(t_pin_sortie *pin) {

}

int t_pin_sortie_propager_signal(t_pin_sortie *pin) {

}

void t_pin_sortie_reset(t_pin_sortie *pin) {

}