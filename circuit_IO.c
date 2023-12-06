/*
Module: circuit_IO
Ce nouveau module a pour responsabilité de sauvegarder 
et de charger un circuit dans et depuis un fichier sur le
disque. Le circuit est sauvegardé en mode texte.

Auteurs: Noah Tremblay : TREN85330401
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
    fprintf(fichier, "%d %d %d\n", t_circuit_get_nb_entrees(circuit)
                                 , t_circuit_get_nb_sorties(circuit) 
                                 , t_circuit_get_nb_portes(circuit));

    printf("%d %d %d\n", t_circuit_get_nb_entrees(circuit)
                       , t_circuit_get_nb_sorties(circuit)
                       , t_circuit_get_nb_portes(circuit));

    //Écriture des entrées
    for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++) {
        t_entree_serialiser(circuit->entrees[i], resultat);
        fprintf(fichier, "%d %s\n", i, resultat);
        printf("%d %s\n", i, resultat);
    }

    //Écriture des sorties
    for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++) {
        t_sortie_serialiser(circuit->sorties[i], resultat);
        fprintf(fichier, "%d %s\n", i, resultat);
        printf("%d %s\n", i, resultat);
    }

    //Écriture des portes
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++) {
        t_porte_serialiser(circuit->portes[i], resultat);
        fprintf(fichier, "%d %s\n", i, resultat);
        printf("%d %s\n", i, resultat);
    }

    //Écriture des liens
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++) {
        fprintf(fichier, "%s", t_porte_get_nom(circuit->portes[i]));
        printf("%s", t_porte_get_nom(circuit->portes[i]));

        //Imprimer l'entrée de la porte
        for (int j = 0; j < t_porte_get_nb_entrees(circuit->portes[i]); j++) {
            
            //S'il n'y a pas d'entrées, ajouter XX
            if (t_porte_get_pin_entree(circuit->portes[i], j) == NULL) {
                fprintf(fichier, " XX");
                printf(" XX");
            }

            //S'il y a une entrée pour la porte
            else {
                fprintf(fichier, " %s", t_porte_get_pin_entree(circuit->portes[i], j));
                printf(" %s", t_porte_get_pin_entree(circuit->portes[i], j));
            }
            //Ajouter un saut de ligne pour la prochaine porte
            fprintf(fichier, "\n");
            printf("\n");
        }
    }

    //Ajouter les dernières pins de sorties avec les pins d'entrées
    for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++) {
        fprintf(fichier, "%s", t_sortie_get_nom(circuit->sorties[i]));
        printf("%s", t_sortie_get_nom(circuit->sorties[i]));

        //Ajouter la porte associée à la sortie
        fprintf(fichier, " %s\n", t_pin_entree_get_lien(t_sortie_get_pin(circuit->sorties)));
        printf(" %s\n", t_pin_entree_get_lien(t_sortie_get_pin(circuit->sorties)));
    }
    fclose(fichier);
}


/*****************************************************************************/

void circuit_IO_charger(const char *chemin_acces, t_circuit *circuit) {
    FILE *fichier = fopen(chemin_acces, "r");
    if (fichier == NULL) {
        printf("Erreur, le fichier est NULL\n");
        return;
    }

    int nb_entrees, nb_sorties, nb_portes, i, id, type;
    char nom[100];

    fscanf(fichier, "%d %d %d\n", &nb_entrees, &nb_sorties, &nb_portes);

    //Lecture et ajout des entrées
    for (i = 0; i < nb_entrees; ++i) {
        fscanf(fichier, "%d %s\n", &id, nom);
        t_circuit_ajouter_entree(circuit, id, nom);
    }

    //Lecture et ajout des sorties
    for (i = 0; i < nb_sorties; ++i) {
        fscanf(fichier, "%d %s\n", &id, nom);
        t_circuit_ajouter_sortie(circuit, id, nom);
    }

    //Lecture et ajout des portes
    for (i = 0; i < nb_portes; ++i) {
        fscanf(fichier, "%d %d %s\n", &type, &id, nom);
        t_circuit_ajouter_porte(circuit, type, id, nom);
    }

    //Vérifier que ce n'est pas la fin du fichier
    while(!feof(fichier)) {
        char premierCharactere[3];
        int deuxiemeCharactere;

        //Lecture de la première lettre
        fscanf(fichier, "%s ", premierCharactere);

        //Si c'est une porte ('P')
        if (premierCharactere[0] == 'P') {
            deuxiemeCharactere = premierCharactere[1] - '0';
            
        }

        //Si c'est une sortie ('S')
        else if (premierCharactere[0] == 'S') {
            deuxiemeCharactere = premierCharactere[1] - '0';
        }


        //utiliser t_pin_entree_get_lien pour les liaisons
        
    }
    fclose(fichier);
}


/*****************************************************************************/

int **t_circuit_tdv(const t_circuit *le_circuit)
{

    return 0;
}