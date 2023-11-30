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
    char resultat[1000];

    if (fichier == NULL) {
        printf("Erreur, le fichier est NULL\n");
        return;
    }

    //Écriture du nombre d'entrées, de sorties et de portes
    fprintf(fichier, "%d %d %d\n", t_circuit_get_nb_entrees(circuit),
                                   t_circuit_get_nb_sorties(circuit), 
                                   t_circuit_get_nb_portes(circuit));

    //Écriture des entrées
    for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++) {
        t_entree_serialiser(circuit->entrees[i], resultat);
        fprintf(fichier, "%s\n", resultat);
    }

    //Écriture des sorties
    for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++) {
        t_sortie_serialiser(circuit->sorties[i], resultat);
        fprintf(fichier, "%s\n", resultat);
    }

    //Écriture des portes
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++) {
        t_porte_serialiser(circuit->portes[i], resultat);
        fprintf(fichier, "%s\n", resultat);
    }

    //Écriture des liens
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++) {
        fprintf(fichier, "%s ", t_porte_get_nom(circuit->portes[i]));

        //Imprimer l'entrée de la porte
        for (int j = 0; j < t_porte_get_nb_entrees(circuit->portes[i]); j++) {
            
            //S'il n'y a pas d'entrées, ajouter XX
            if (t_porte_get_pin_entree(circuit->portes[i], j) == NULL) {
                fprintf(fichier, "XX ");
            }

            //S'il y a une entrée pour la porte
            else {
                fprintf(fichier, "%s ", t_porte_get_pin_entree(circuit->portes[i], j));
            }
        }

        //Ajouter un saut de ligne pour la prochaine porte
        fprintf(fichier, "\n");
    }

    //Ajouter les dernières pins de sorties avec les pins d'entrées
    for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++) {
        fprintf(fichier, "%s ", t_sortie_get_nom(circuit->sorties[i]));

        //Ajouter la porte associée à la sortie
        fprintf(fichier, "%s\n", t_sortie_get_porte_nom(circuit->sorties[i]));
    }

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