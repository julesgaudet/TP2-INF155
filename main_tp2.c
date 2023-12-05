/*
TESTER LES ENTREES ET LES SORTIES
Auteur: Eric Th�, 13-11-2023

Programme qui teste l'utilisation des librairies de circuits logique "t_entree"
(avec "t_pin_sortie") et "t_sortie".  Plusieurs tests unitaires sont faits avec "assert()"
*/
#include <assert.h>
#include "circuit_IO.h"

int main(void)
{//déclaration des variables
	int signal[MAX_ENTREES], 	 //les valeurs (0/1) pour les entrées du circuit
		i,choix;

	t_circuit* circuit;   //le circuit complet
	circuit = t_circuit_init();   //Création du circuit
	construire_circuit(circuit);
	printf("Veuillez choisir un mode de creation de circuit:\n1 - creation manuelle\n2 - a partir d'un fichier");
	scanf("%d", choix);




	switch (choix)
		case 1:
			//Vérification de la validité du circuit
			if (t_circuit_est_valide(circuit)) {
				printf("Circuit valide!\n");
			}
			else {
				printf("Circuit invalide!\n");
			}

			//On définit un signal de 3 bits (eg. 111)
			for (i = 0; i < t_circuit_get_nb_entrees(circuit); i++) {
				printf("Quel est la valeur du signal de l'entree %d (0 ou 1) ? ", i);
				scanf("%d", &signal[i]);		//assignation du signal d'entrée pour l'entrée #i
			}
			t_circuit_reset(circuit);
			t_circuit_appliquer_signal(circuit, signal, t_circuit_get_nb_entrees(circuit));

			if (t_circuit_propager_signal(circuit)) {
				printf("Signal propage avec succes.\n");

				for (i = 0; i < t_circuit_get_nb_sorties(circuit); i++)
					printf("Sortie %d: %d\n", i, t_sortie_get_valeur(t_circuit_get_sortie(circuit, i)));
			}
			else  printf("Erreur lors de la propagation du signal.\n");

			t_circuit_destroy(circuit);
			system("pause");
			return EXIT_SUCCESS;
}
