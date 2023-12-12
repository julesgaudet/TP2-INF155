/*
MAIN FINAL
Auteurs: Noah Tremblay : TREN85330401
		 Jules Gaudet  : GAUJ71370101

		 Date de modification : 09/12/2023

Description : Main final du projet TP2_Circuits qui donne 3 options a l'utilisateur :
	-Donner un signal a un circuit préétabli par l'enseignant
	-Donner un signal a un ciruit préétabli par les auteurs (nous)
	-Importer un circuit a partir d'un fichier .txt

*/
/*****************************************************************************/

#include "circuit_IO.h"
#define MANUEL1 1
#define MANUEL2 2
#define CHARGER 3

/*****************************************************************************/

//fonction void construire circuit qui construit un circuit avec 4 portes et 3 entrées
static void construire_circuit(t_circuit* circuit)
{  //variables locales pour les composantes du circuit
	t_porte* porte_ou;	//les 4 portes
	t_porte* porte_et;
	t_porte* porte_not;
	t_porte* porte_xor;
	t_entree* entree0;	//les 3 entrées
	t_entree* entree1;
	t_entree* entree2;
	t_sortie* sortie0;	//les 2 sorties
	t_sortie* sortie1;

	//Ajout des entrées
	entree0 = t_circuit_ajouter_entree(circuit, 0, "E0");
	entree1 = t_circuit_ajouter_entree(circuit, 1, "E1");
	entree2 = t_circuit_ajouter_entree(circuit, 2, "E2");

	//Ajout des sorties
	sortie0 = t_circuit_ajouter_sortie(circuit, 0, "S0");
	sortie1 = t_circuit_ajouter_sortie(circuit, 1, "S1");
	//Ajout des portes
	porte_ou = t_circuit_ajouter_porte(circuit, PORTE_OU, 0, "P0");
	porte_et = t_circuit_ajouter_porte(circuit, PORTE_ET, 1, "P1");
	porte_xor = t_circuit_ajouter_porte(circuit, PORTE_XOR, 2, "P2");
	porte_not = t_circuit_ajouter_porte(circuit, PORTE_NOT, 3, "P3");
	//Ajout des liens
	t_porte_relier(porte_ou, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));
	t_porte_relier(porte_ou, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 0, t_entree_get_nom(entree1), t_entree_get_pin(entree1));
	t_porte_relier(porte_et, 1, t_entree_get_nom(entree2), t_entree_get_pin(entree2));
	t_porte_relier(porte_not, 0, t_porte_get_nom(porte_ou), t_porte_get_pin_sortie(porte_ou));
	t_porte_relier(porte_xor, 0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_porte_relier(porte_xor, 1, t_porte_get_nom(porte_et), t_porte_get_pin_sortie(porte_et));
	t_sortie_relier(sortie0, t_porte_get_nom(porte_not), t_porte_get_pin_sortie(porte_not));
	t_sortie_relier(sortie1, t_porte_get_nom(porte_xor), t_porte_get_pin_sortie(porte_xor));
}

int main(void)
{//déclaration des variables
	int signal[MAX_ENTREES], 	 //les valeurs (0/1) pour les entrées du circuit
		i,choix;
	t_circuit* circuit;   //le circuit complet
	circuit = t_circuit_init();//Création du circuit


	printf("Veuillez choisir un mode de creation de circuit:");
	printf("\n1 - creation manuelle #1\n2 - creation manuelle #2\n3 - a partir d'un fichier\n");
	//scanf("%d", &choix);
	choix = CHARGER;
	switch (choix)
	{
	case MANUEL1:
		{
			
		construire_circuit(circuit);
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
		

	case MANUEL2:
		{
		t_circuit_destroy(circuit);
		system("pause");
		return EXIT_SUCCESS;
		}

	case CHARGER:
        {
		char chemin[1000]; 

        printf("\nVeuillez inserer le chemin d'acces du fichier que vous voulez tester\n");
        //scanf("%s", chemin);
		strcpy(chemin, "/Users/julesgaudet/Desktop/TP2/circuitA.txt");
        circuit_IO_charger(chemin, circuit);

		//Détermination du nombre de lignes pour la table de vérité
		int nb_entrees = t_circuit_get_nb_entrees(circuit);
		int nb_lignes;
		for (int i = 0; i < nb_entrees; i++) {
        	nb_lignes *= 2;
    	}

		//Construction de la table de vérité
		int **table_verite = t_circuit_tdv(circuit);

		//Libérer l'espace utilisé pour la table de vérité
		liberer_table_verite(table_verite, nb_lignes);

        t_circuit_destroy(circuit);

        system("pause");
        return EXIT_SUCCESS;
		}
	}
}