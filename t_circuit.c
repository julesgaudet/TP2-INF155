/*
Module: T_CIRCUIT
Description: Le fichier t_circuit.h définit le type t_circuit qui représente 
un circuit logique. Ce module fournit des fonctions pour créer, manipuler et 
gérer les circuits. Un circuit est composé d'entrées, de sorties et de portes 
logiques. Les entrées et les sorties sont connectées aux portes, formant ainsi 
une structure logique.

Auteurs: Noah Tremblay : TREN85330401
         Jules Gaudet  : GAUJ71370101
Derni�re modification  : 
*/
/*****************************************************************************/

#include "t_circuit.h"

/*****************************************************************************/

t_circuit* t_circuit_init(void) 
{
    t_circuit *nouv_circuit;

    nouv_circuit = (t_circuit*)malloc(sizeof(t_circuit));
    
    nouv_circuit->nb_entrees = 0;
    nouv_circuit->nb_sorties = 0; 
    nouv_circuit->nb_portes = 0;

    return nouv_circuit;
}

/*****************************************************************************/

void t_circuit_destroy(t_circuit *circuit) 
{
    int i;

    for (i = 0; i < circuit->nb_sorties; i++) {
        t_sortie_destroy(circuit->sorties[i]);
    }
    for (i = 0; i < circuit->nb_entrees; i++) {
        t_entree_destroy(circuit->entrees[i]);
    }
    for (i = 0; i < circuit->nb_portes; i++) {
        t_porte_destroy(circuit->portes[i]);
    }
    free(circuit);
}

/*****************************************************************************/

t_porte* t_circuit_ajouter_porte(t_circuit *circuit, e_types_portes le_type, int id, char *nom) 
{
    t_porte* nouv_porte;

    //S'il ne reste pas de place pour les portes
    if (circuit->nb_portes >= CIRCUIT_MAX_PORTES)
        return NULL;

    //Créer une porte 
    nouv_porte = t_porte_init(id, le_type, nom);

    //Ajouter la porte au circuit
    circuit->portes[circuit->nb_portes] = nouv_porte;

    //Ajouter 1 porte au circuit
    circuit->nb_portes += 1;

    return nouv_porte;
}

/*****************************************************************************/

t_entree* t_circuit_ajouter_entree(t_circuit * circuit, int id, char *nom)
{
    t_entree* nouv_entree;

    //si il ne rete pas de place pour ajouter une entree
    if (circuit->nb_entrees >= MAX_ENTREES)
        return NULL;

    //créer une nouvelle entrée
    nouv_entree = t_entree_init(id, nom);

    //ajouter l'entree au circuit
    circuit->entrees[circuit->nb_entrees] = nouv_entree;

    //ajouter 1 au nb d'entres 
    circuit->nb_entrees += 1;

    return nouv_entree;
}

/*****************************************************************************/

t_sortie* t_circuit_ajouter_sortie(t_circuit * circuit, int id, char *nom)
{
    t_sortie* nouv_sortie;

    //S'il ne reste pas de place pour ajouter une sortie
    if (t_circuit_get_nb_sorties(circuit) >= MAX_SORTIES)
        return NULL;

    //Créer une nouvelle entrée
    nouv_sortie = t_sortie_init(id, nom);

    //Ajouter l'entree au circuit
    circuit->sorties[t_circuit_get_nb_sorties(circuit)] = nouv_sortie;

    //Ajouter 1 au nb d'entres 
    circuit->nb_sorties += 1;

    return nouv_sortie;
}

/*****************************************************************************/

int t_circuit_est_valide(t_circuit *circuit)
{
    int i, non_reliee;

    non_reliee = VRAI;

    //Vérification que toutes les ENTREES reliees
    for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++) {
        if (t_entree_est_reliee(t_circuit_get_entree(circuit, i)) == FAUX)
        {
            printf("\nentree %d non reliee", t_entree_get_id(t_circuit_get_entree(circuit, i)));
            non_reliee = FAUX;
        }
    }
    
    //Vérification que toutes les SORTIES reliees
    for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++) {
        if (t_sortie_est_reliee(t_circuit_get_sortie(circuit, i)) == FAUX)
        {
            printf("\nsortie %d non reliee", t_sortie_get_id(t_circuit_get_sortie(circuit, i)));
            non_reliee = FAUX;
        }
    }

    //Vérification que toutes les PORTES reliees
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++) {
        if (t_porte_est_reliee(t_circuit_get_porte(circuit,i)) == FAUX)
        {
            printf("\nporte %d non reliee", t_porte_get_id(t_circuit_get_porte(circuit, i)));
            non_reliee = FAUX;
        }
    }
    return non_reliee;
}

/*****************************************************************************/

int t_circuit_appliquer_signal(t_circuit * circuit, int signal[], int nb_bits)
{
    int i;

    //verificaton qu'il y aye autant de signal que d'entrees
    if (nb_bits != t_circuit_get_nb_entrees(circuit))
        return FAUX;

    //application des bits a leur entrées respectives
    for (i = 0; i < nb_bits; i++)
    {
        t_pin_sortie_set_valeur(t_entree_get_pin (t_circuit_get_entree(circuit, i)), signal[i]);
    }

    return VRAI;
}

/*****************************************************************************/

void t_circuit_reset(t_circuit *circuit)
{
    int i;

    //reset les SORTIES
    for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++) {
        t_sortie_reset(t_circuit_get_sortie(circuit, i));
    }

    //restet les ENTREES
    for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++) {
        t_entree_reset(t_circuit_get_entree(circuit, i));
    }

    //reset les PORTES
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++) {
        t_porte_reset(t_circuit_get_porte(circuit, i));
    }
}


/*****************************************************************************/

int t_circuit_propager_signal(t_circuit *circuit)
{
    t_file* file;
    t_porte* porte_courante = NULL;
    int nb_iterations,i;

    nb_iterations = 0;

    file = (t_file*)malloc(sizeof(t_file));

    //si le circuit est invalide
    if (t_circuit_est_valide(circuit) == FAUX)
        return FAUX;

    //si le circuit n'as pas été alimenté
    for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++)
    {
        if (t_entree_get_valeur(t_circuit_get_entree(circuit, i)) == INACTIF)
            return FAUX;
    }

    //demander a chaque entrée du circuit de propager le signal
    for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++)
    {
        t_entree_propager_signal(t_circuit_get_entree(circuit, i));
    }

    //remplir la file
    initfile(file);
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++)
    {
        porte_courante = t_circuit_get_porte(circuit, i);
        ajouterfin(file, porte_courante);
    }

    //while file n’est pas vide ET nb_iterations < nb_portes *(nb_portes + 1)/2 
    while ((!vide(file)) &&
        (nb_iterations < t_circuit_get_nb_portes(circuit) * (t_circuit_get_nb_portes(circuit) + 1) / 2))
    {
        //Défiler une porte de la file et la stocker dans porte_courante
        enleverdebut(file, &porte_courante);

        //Demander à porte_courante de propager son signal
        if (!t_porte_propager_signal(porte_courante))
            ajouterfin(file, porte_courante);

        nb_iterations++;
    }

    //si le circuit a une boucle FAUX sinon VRAI
    if (vide(file))
    {
        free(file);
        return VRAI;
    }
    else
    {
        free(file);
        return FAUX;
    }
}

/*****************************************************************************/

int t_circuit_get_nb_portes(const t_circuit* circuit)
{
    return circuit->nb_portes;
}

/*****************************************************************************/

t_porte* t_circuit_get_porte(const t_circuit* circuit, int pos) 
{
    if(pos<t_circuit_get_nb_portes(circuit))
        return circuit->portes[pos];
    return NULL;
}

/*****************************************************************************/

int t_circuit_get_nb_sorties(const t_circuit* circuit)
{
    return circuit->nb_sorties;
}

/*****************************************************************************/

t_sortie* t_circuit_get_sortie(const t_circuit* circuit, int pos)
{
    if (pos < t_circuit_get_nb_sorties(circuit))
        return circuit->sorties[pos];
    return NULL;
}

/*****************************************************************************/

int t_circuit_get_nb_entrees(const t_circuit* circuit)
{
    return circuit->nb_entrees;
}

/*****************************************************************************/

t_entree* t_circuit_get_entree(const t_circuit* circuit, int pos) 
{
    if (pos < t_circuit_get_nb_entrees(circuit)) 
        return circuit->entrees[pos];
    return NULL;
}

/*****************************************************************************/
/*****************************************************************************/