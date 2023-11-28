/*
Module: T_CIRCUIT
Description: D�finit le type t_circuit. 

Auteur: Noah Tremblay, Jules Gaudet
Derni�re modification: 
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
}

/*****************************************************************************/
void t_circuit_destroy(t_circuit *circuit) 
{
    for (int i = 0; i < circuit->nb_sorties; i++) {
        t_sortie_destroy(circuit->sorties[i]);
    }
    for (int i = 0; i < circuit->nb_entrees; i++) {
        t_entree_destroy(circuit->entrees[i]);
    }
    for (int i = 0; i < circuit->nb_portes; i++) {
        t_porte_destroy(circuit->portes[i]);
    }
    free(circuit);
}

/*****************************************************************************/
t_porte* t_circuit_ajouter_porte(t_circuit *circuit, e_types_portes le_type, int id, char *nom) 
{

}

/*****************************************************************************/
t_entree* t_circuit_ajouter_entree(t_circuit * circuit, int id, char *nom)
{

}

/*****************************************************************************/
t_sortie* t_circuit_ajouter_sortie(t_circuit * circuit, int id, char *nom)
{

}

/*****************************************************************************/
int t_circuit_est_valide(t_circuit *circuit)
{

}

/*****************************************************************************/
int t_circuit_appliquer_signal(t_circuit * circuit, int signal[], int nb_bits)
{

}

/*****************************************************************************/
void t_circuit_reset(t_circuit *circuit)
{

}

/*****************************************************************************/
int t_circuit_propager_signal(t_circuit *circuit)
{

}

/*****************************************************************************/
int t_circuit_get_nb_portes(const t_circuit* circuit)
{
    return circuit->nb_portes;
}

/*****************************************************************************/
t_porte* t_circuit_get_porte(const t_circuit* circuit, int pos) 
{

}

/*****************************************************************************/
int t_circuit_get_nb_sorties(const t_circuit* circuit)
{
    return circuit->nb_sorties;
}

/*****************************************************************************/
t_sortie* t_circuit_get_sortie(const t_circuit* circuit, int pos)
{

}

/*****************************************************************************/
int t_circuit_get_nb_entrees(const t_circuit* circuit)
{
    return circuit->nb_entrees;
}


/*****************************************************************************/
t_entree* t_circuit_get_entree(const t_circuit* circuit, int pos) 
{

}