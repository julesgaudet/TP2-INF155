/*
Module: circuit_IO
Ce nouveau module a pour responsabilité de sauvegarder 
et de charger un circuit dans et depuis un fichier sur le
disque. Le circuit est sauvegardé en mode texte.

Auteurs: Noah Tremblay : 
         Jules Gaudet  : GAUJ71370101
Derni�re modification  : 
*/
/*****************************************************************************/

#include "circuit_IO.h"

/*****************************************************************************/

void circuit_IO_sauvegarder(const char *nom_fichier, const t_circuit *circuit) {
    FILE *fichier = fopen(nom_fichier, "w");
    int i;
    char resultat[100];

    if (fichier == NULL) {
        printf("Erreur, le fichier est NULL\n");
        return;
    }

    // Écriture du nombres d'entrées, de sorties et de portes
    fprintf(fichier, "%d %d %d\n", t_circuit_get_nb_entrees(circuit),
                                   t_circuit_get_nb_sorties(circuit), 
                                   t_circuit_get_nb_portes(circuit));

    // Écriture des entrées
    for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++) {
        t_entree_serialiser(circuit->entrees[i], resultat);
        fprintf(fichier, "%s\n", resultat);
    }

    // Écriture des sorties
    for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++) {
        t_sortie_serialiser(circuit->sorties[i], resultat);
        fprintf(fichier, "%s\n", resultat);
    }

    // Écriture des portes
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++) {
        t_porte_serialiser(circuit->portes[i], resultat);
        fprintf(fichier, "%s\n", resultat);
    }

    //Il manque le reste 
    //Est-ce qu'il faut utiliser t_pin_entree_get_lien?

    fclose(fichier);
}

/*****************************************************************************/

void circuit_IO_charger(const char *chemin_acces, t_circuit *circuit)
{

}

/*****************************************************************************/

int **t_circuit_tdv(const t_circuit *le_circuit)
{

}