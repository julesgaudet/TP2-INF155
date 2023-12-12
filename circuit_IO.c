/*
Module: circuit_IO
Ce nouveau module a pour responsabilité de sauvegarder 
et de charger un circuit dans et depuis un fichier sur le
disque. Le circuit est sauvegardé en mode texte.

Auteurs: Noah Tremblay : TREN85330401
         Jules Gaudet  : GAUJ71370101
Dernière modification  : 09/12/2023
*/
/*****************************************************************************/

#include "circuit_IO.h"

/*****************************************************************************/

//Déclarations des sous-fonctions
//Pour circuit_IO_sauvegarder 
void ecrire_nb_entrees_sorties_portes(FILE *fichier, const t_circuit *circuit);
void ecrire_entrees(FILE *fichier, const t_circuit *circuit, char *resultat);
void ecrire_sorties(FILE *fichier, const t_circuit *circuit, char *resultat);
void ecrire_portes(FILE *fichier, const t_circuit *circuit, char *resultat);
void ecrire_liens(FILE *fichier, const t_circuit *circuit, char *resultat);

//Pour circuit_IO_charger
void charger_entrees(FILE *fichier, t_circuit *circuit, int nb_entrees);
void charger_sorties(FILE *fichier, t_circuit *circuit, int nb_sorties);
void charger_portes(FILE *fichier, t_circuit *circuit, int nb_portes);
void charger_liaisons(FILE *fichier, t_circuit *circuit);

//Pour la table de vérité 
int** allouer_table_verite(int nb_lignes, int nb_colonnes);
void generer_table_verite(int **table_verite, int nb_lignes, int nb_entrees);
void calculer_sorties_circuit(t_circuit* le_circuit, int** table_verite, int nb_lignes, int nb_entrees, int nb_sorties);
void afficher_table_verite(int** table_verite, int nb_lignes, int nb_colonnes, t_circuit* circuit);

/*****************************************************************************/

void circuit_IO_sauvegarder(const char *nom_fichier, const t_circuit *circuit) {
    FILE *fichier = fopen(nom_fichier, "w");

    if (fichier == NULL) {
        printf("Erreur, le fichier est NULL\n");
        return;
    }

    //Déclaration de la variable resultat ici
    char resultat[1000];

    //Écriture du nombre d'entrées, de sorties et de portes
    ecrire_nb_entrees_sorties_portes(fichier, circuit);

    //Écriture des entrées
    ecrire_entrees(fichier, circuit, resultat);

    //Écriture des sorties
    ecrire_sorties(fichier, circuit, resultat);

    //Écriture des portes
    ecrire_portes(fichier, circuit, resultat);

    //Écriture des liens
    ecrire_liens(fichier, circuit, resultat);

    fclose(fichier);
}

/*****************************************************************************/

void circuit_IO_charger(const char *chemin_acces, t_circuit *circuit) {
    
    int nb_entrees, nb_sorties, nb_portes;
    
    FILE *fichier = fopen(chemin_acces, "r");

    if (fichier == NULL) {
        printf("Erreur, le fichier est NULL\n");
        return;
    }

    fscanf(fichier, "%d %d %d\n", &nb_entrees, &nb_sorties, &nb_portes);

    //Lecture des entrées
    charger_entrees(fichier, circuit, nb_entrees);

    //Lecture des sorties
    charger_sorties(fichier, circuit, nb_sorties);

    //Lecture du nombre de portes
    charger_portes(fichier, circuit, nb_portes);

    //Lecture du nombre de liaisons
    charger_liaisons(fichier, circuit);

    fclose(fichier);
}

/*****************************************************************************/

void t_circuit_tdv(const t_circuit *le_circuit) 
{
    int nb_lignes = 1;
    int nb_entrees = t_circuit_get_nb_entrees(le_circuit);
    int nb_sorties = t_circuit_get_nb_sorties(le_circuit);
    
    for (int i = 0; i < nb_entrees; i++) {
        nb_lignes *= 2;
    }

    int nb_colonnes = nb_entrees + nb_sorties;

    //Allocation de la mémoire 
    int **table_verite = allouer_table_verite(nb_lignes, nb_colonnes);

    //Générer la table avec chaque possibilité d'entrées 
    generer_table_verite(table_verite, nb_lignes, nb_entrees);

    //Calcul des sorties selon les entrées 
    calculer_sorties_circuit(le_circuit, table_verite, nb_lignes, nb_entrees, nb_sorties);

    afficher_table_verite(table_verite, nb_lignes, nb_colonnes, le_circuit);

    //Libérer l'espace utilisé pour la table de vérité
    liberer_table_verite(table_verite, nb_lignes);

}

/*****************************************************************************/

void ecrire_nb_entrees_sorties_portes(FILE *fichier, const t_circuit *circuit) {
    //Écriture du nombre d'entrées, de sorties et de portes
    fprintf(fichier, "%d %d %d\n", t_circuit_get_nb_entrees(circuit)
                                 , t_circuit_get_nb_sorties(circuit) 
                                 , t_circuit_get_nb_portes(circuit));

    printf("%d %d %d\n", t_circuit_get_nb_entrees(circuit)
                       , t_circuit_get_nb_sorties(circuit)
                       , t_circuit_get_nb_portes(circuit));
}

/*****************************************************************************/

void ecrire_entrees(FILE *fichier, const t_circuit *circuit, char *resultat) {
    int i;

    //Écriture des entrées
    for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++) {
        t_entree_serialiser(t_circuit_get_entree(circuit, i), resultat);
        fprintf(fichier, "%s\n", resultat);
        printf("%s\n", resultat);
    }
}

/*****************************************************************************/

void ecrire_sorties(FILE *fichier, const t_circuit *circuit, char *resultat) {
    int i;

    //Écriture des sorties
    for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++) {
        t_sortie_serialiser(t_circuit_get_sortie(circuit, i), resultat);
        fprintf(fichier, "%s\n", resultat);
        printf("%s\n", resultat);
    }
}

/*****************************************************************************/

void ecrire_portes(FILE *fichier, const t_circuit *circuit, char *resultat) {
    int i;

    //Écriture des portes
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++) {
        t_porte_serialiser(t_circuit_get_porte(circuit, i), resultat);
        fprintf(fichier, "%s\n", resultat);
        printf("%s\n", resultat);
    }
}

/*****************************************************************************/

void ecrire_liens(FILE *fichier, const t_circuit *circuit, char *resultat) {
    int i;

    //Écriture des liens
    for (i = 0; i < t_circuit_get_nb_portes(circuit); i++) {
        fprintf(fichier, "%s", t_porte_get_nom(t_circuit_get_porte(circuit, i)));
        printf("%s", t_porte_get_nom(t_circuit_get_porte(circuit, i)));

        //Imprimer l'entrée de la porte
        for (int j = 0; j < t_porte_get_nb_entrees(t_circuit_get_porte(circuit, i)); j++) {
            
            //S'il n'y a pas d'entrées, ajouter XX
            if (t_porte_get_pin_entree(t_circuit_get_porte(circuit, i), j) == NULL) {
                fprintf(fichier, " XX");
                printf(" XX");
            }

            //S'il y a une entrée pour la porte
            else {
                fprintf(fichier, " %s", t_pin_entree_get_lien(t_porte_get_pin_entree(t_circuit_get_porte(circuit, i), j)));
                printf(" %s", t_pin_entree_get_lien(t_porte_get_pin_entree(t_circuit_get_porte(circuit, i), j)));
            }
        }

        //Ajouter un saut de ligne pour la prochaine porte
        fprintf(fichier, "\n");
        printf("\n");
    }
    
    //Ajouter les dernières pins de sorties avec les pins d'entrées
    for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++) {
        fprintf(fichier, "%s", t_sortie_get_nom(t_circuit_get_sortie(circuit, i)));
        printf("%s", t_sortie_get_nom(t_circuit_get_sortie(circuit, i)));

        //Ajouter la porte associée à la sortie
        fprintf(fichier, " %s\n", t_pin_entree_get_lien(t_sortie_get_pin(circuit->sorties[i])));
        printf(" %s\n", t_pin_entree_get_lien(t_sortie_get_pin(circuit->sorties[i])));
    }
}

/*****************************************************************************/

void charger_entrees(FILE *fichier, t_circuit *circuit, int nb_entrees) {
    int i, id;
    char nom[3];

    for (i = 0; i < nb_entrees; ++i) {
        fscanf(fichier, "%d %s\n", &id, nom);
        t_circuit_ajouter_entree(circuit, id, nom);
    }
}

/*****************************************************************************/

void charger_sorties(FILE *fichier, t_circuit *circuit, int nb_sorties) {
    int i, id;
    char nom[3];

    for (i = 0; i < nb_sorties; ++i) {
        fscanf(fichier, "%d %s\n", &id, nom);
        t_circuit_ajouter_sortie(circuit, id, nom);
    }
}

/*****************************************************************************/

void charger_portes(FILE *fichier, t_circuit *circuit, int nb_portes) {
    int i, id, type;
    char nom[3];

    for (i = 0; i < nb_portes; ++i) {
        fscanf(fichier, "%d %d %s\n", &id, &type, nom);
        t_circuit_ajouter_porte(circuit, type, id, nom);
    }
}

/*****************************************************************************/

void charger_liaisons(FILE *fichier, t_circuit *circuit) {

    while (!feof(fichier)) {
        char premierCharactere[3];
        int deuxiemeCharactere;

        //Lecture de la première lettre
        fscanf(fichier, "%s ", premierCharactere);

        //Si c'est une porte ('P')
        if (premierCharactere[0] == 'P') {
            deuxiemeCharactere = premierCharactere[1] - '0'; 

            //Récupérer la porte correspondante dans le circuit
            t_porte *porte_destination = t_circuit_get_porte(circuit, deuxiemeCharactere);

            //Lire le nom des entrées de la porte et les connecter
            for (int i = 0; i < t_porte_get_nb_entrees(porte_destination); ++i) {
                char nom_entree[3];
                fscanf(fichier, "%s ", nom_entree);

                //Vérifier si le nom d'entrée n'est pas "XX" (connexion absente)
                if (nom_entree[0] == 'X' && nom_entree[1] == 'X') {
                    continue;  //Ignorer la connexion absente
                }

                //Si le nom d'entrée débute par 'E', connecter à une entrée
                if (nom_entree[0] == 'E') {
                    int num_entree = nom_entree[1] - '0';
                    t_pin_entree *entree_source = t_circuit_get_entree(circuit, num_entree);
                    t_porte_relier(porte_destination, i, nom_entree, t_entree_get_pin(entree_source)); 
                }

                //Si le nom d'entrée débute par 'P', connecter à une autre porte
                else if (nom_entree[0] == 'P') {
                    int num_porte_source = nom_entree[1] - '0';
                    t_porte *porte_source = t_circuit_get_porte(circuit, num_porte_source);
                    t_porte_relier(porte_destination, i, nom_entree, t_porte_get_pin_sortie(porte_source));
                }
            }
        }
        //Si c'est une sortie ('S')
        else if (premierCharactere[0] == 'S') {
            deuxiemeCharactere = premierCharactere[1] - '0';

            //Récupérer la sortie correspondante dans le circuit
            t_sortie *sortie_destination = t_circuit_get_sortie(circuit, deuxiemeCharactere);

            //Lire le nom de la porte et la connecter
            char nom_porte[3];
            fscanf(fichier, " %s\n", nom_porte);

            //Si le nom de la porte débute par 'P', connecter à une porte
            if (nom_porte[0] == 'P') {
                int num_porte_source = nom_porte[1] - '0';
                t_porte *porte_source = t_circuit_get_porte(circuit, num_porte_source);
                t_sortie_relier(sortie_destination, nom_porte, t_porte_get_pin_sortie(porte_source)); //JPAS SUR ICI
            }
        }
    }
}

/*****************************************************************************/

int** allouer_table_verite(int nb_lignes, int nb_colonnes) {
    int **table_verite = (int **)malloc(nb_lignes * sizeof(int *));
    for (int i = 0; i < nb_lignes; ++i) {
        table_verite[i] = (int *)malloc(nb_colonnes * sizeof(int));
    }
    return table_verite;
}

/*****************************************************************************/

void generer_table_verite(int **table_verite, int nb_lignes, int nb_entrees) {
    for (int i = 0; i < nb_lignes; ++i) {
        int temp_combination = i;
        for (int j = nb_entrees - 1; j >= 0; --j) {
            table_verite[i][j] = temp_combination % 2;
            temp_combination /= 2;
        }
    }
}

/*****************************************************************************/

void calculer_sorties_circuit(t_circuit* le_circuit, int** table_verite, int nb_lignes, int nb_entrees, int nb_sorties) 
{
    for (int i = 0; i < nb_lignes; ++i) 
    {
        t_circuit_reset(le_circuit);

        int* valeur = table_verite[i];

        t_circuit_appliquer_signal(le_circuit, valeur, t_circuit_get_nb_entrees(le_circuit));

        if (!t_circuit_propager_signal(le_circuit))
            printf("ERREUR dans la propagation du signal a la ligne: %d\n",i);

        //Lire les valeurs de sorties
        for (int j = 0; j < nb_sorties; ++j) 
        {
            table_verite[i][nb_entrees + j] = t_sortie_get_valeur(t_circuit_get_sortie(le_circuit, j));
        }
    }
}

/*****************************************************************************/

void afficher_table_verite(int** table_verite, int nb_lignes, int nb_colonnes, t_circuit* circuit)
{

    //entete de la table de verite
    printf("\n -TABLE DE VERITE-\n");

    printf(" ");
    for (int j = 0; j < t_circuit_get_nb_entrees(circuit); ++j)
    {
        printf("%s ", t_entree_get_nom(t_circuit_get_entree(circuit, j)));
    }
    printf("| ");
    for (int j = 0; j < t_circuit_get_nb_sorties(circuit); ++j)
    {
        printf("%s ", t_sortie_get_nom(t_circuit_get_sortie(circuit, j)));
    }
    printf("\n");

    //la table de véritée ligne par ligne
    for (int i = 0; i < nb_lignes; ++i) {
        for (int j = 0; j < nb_colonnes; ++j) {
            if (j == (t_circuit_get_nb_entrees(circuit)))
                printf(" |"); //pour faire une ligne entre les entrées et sorties
            printf("%3d", table_verite[i][j]);
        }
        printf("\n");
    }
}

/*****************************************************************************/

void liberer_table_verite(int **table_verite, int nb_lignes) {
    for (int i = 0; i < nb_lignes; ++i) {
        free(table_verite[i]);
    }
    free(table_verite);
}

/*****************************************************************************/