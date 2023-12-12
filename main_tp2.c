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

/*****************************************************************************/

//fonction void construire circuit qui construit un circuit avec 10 portes et 10 entrées
//lien vers un shéma du circuit :
//https://imgur.com/a/499ujoW

static void construire_circuit2(t_circuit* circuit)
{  //variables locales pour les composantes du circuit
	t_porte* porte_not0;  // les 10 portes
	t_porte* porte_et1;
	t_porte* porte_ou2;
	t_porte* porte_xor3;
	t_porte* porte_et4;
	t_porte* porte_not5;
	t_porte* porte_ou6;
	t_porte* porte_xor7;
	t_porte* porte_et8;
	t_porte* porte_et9;

	t_entree* entree0;	//les 10 entrées
	t_entree* entree1;
	t_entree* entree2;
	t_entree* entree3;
	t_entree* entree4;
	t_entree* entree5;	
	t_entree* entree6;
	t_entree* entree7;
	t_entree* entree8;
	t_entree* entree9;

	t_sortie* sortie0;	//les 10 sorties
	t_sortie* sortie1;
	t_sortie* sortie2;	
	t_sortie* sortie3;
	t_sortie* sortie4;	
	t_sortie* sortie5;
	t_sortie* sortie6;
	t_sortie* sortie7;
	t_sortie* sortie8;
	t_sortie* sortie9;


	//Ajout des entrées
	entree0 = t_circuit_ajouter_entree(circuit, 0, "E0");
	entree1 = t_circuit_ajouter_entree(circuit, 1, "E1");
	entree2 = t_circuit_ajouter_entree(circuit, 2, "E2");
	entree3 = t_circuit_ajouter_entree(circuit, 3, "E3");
	entree4 = t_circuit_ajouter_entree(circuit, 4, "E4");
	entree5 = t_circuit_ajouter_entree(circuit, 5, "E5");
	entree6 = t_circuit_ajouter_entree(circuit, 6, "E6");
	entree7 = t_circuit_ajouter_entree(circuit, 7, "E7");
	entree8 = t_circuit_ajouter_entree(circuit, 8, "E8");
	entree9 = t_circuit_ajouter_entree(circuit, 9, "E9");


	//Ajout des sorties
	sortie0 = t_circuit_ajouter_sortie(circuit, 0, "S0");
	sortie1 = t_circuit_ajouter_sortie(circuit, 1, "S1");
	sortie2 = t_circuit_ajouter_sortie(circuit, 2, "S2");
	sortie3 = t_circuit_ajouter_sortie(circuit, 3, "S3");
	sortie4 = t_circuit_ajouter_sortie(circuit, 4, "S4");
	sortie5 = t_circuit_ajouter_sortie(circuit, 5, "S5");
	sortie6 = t_circuit_ajouter_sortie(circuit, 6, "S6");
	sortie7 = t_circuit_ajouter_sortie(circuit, 7, "S7");
	sortie8 = t_circuit_ajouter_sortie(circuit, 8, "S8");
	sortie9 = t_circuit_ajouter_sortie(circuit, 9, "S9");

	//Ajout des portes
	porte_not0 = t_circuit_ajouter_porte(circuit, PORTE_NOT, 0, "P0");
	porte_et1 = t_circuit_ajouter_porte(circuit, PORTE_ET, 1, "P1");
	porte_ou2 = t_circuit_ajouter_porte(circuit, PORTE_OU, 2, "P2");
	porte_xor3 = t_circuit_ajouter_porte(circuit, PORTE_XOR, 3, "P3");
	porte_et4 = t_circuit_ajouter_porte(circuit, PORTE_ET, 4, "P4");
	porte_not5 = t_circuit_ajouter_porte(circuit, PORTE_NOT, 5, "P5");
	porte_ou6 = t_circuit_ajouter_porte(circuit, PORTE_OU, 6, "P6");
	porte_xor7 = t_circuit_ajouter_porte(circuit, PORTE_XOR, 7, "P7");
	porte_et8 = t_circuit_ajouter_porte(circuit, PORTE_ET, 8, "P8");
	porte_et9 = t_circuit_ajouter_porte(circuit, PORTE_ET, 9, "P9");


	//Ajout des liens
	t_porte_relier(porte_not0, 0, t_entree_get_nom(entree0), t_entree_get_pin(entree0));

	t_porte_relier(porte_et1, 0, t_porte_get_nom(porte_not0), t_porte_get_pin_sortie(porte_not0));
	t_porte_relier(porte_et1, 1, t_entree_get_nom(entree1), t_entree_get_pin(entree1));

	t_porte_relier(porte_ou2, 0, t_porte_get_nom(porte_et1), t_porte_get_pin_sortie(porte_et1));
	t_porte_relier(porte_ou2, 1, t_entree_get_nom(entree2), t_entree_get_pin(entree2));

	t_porte_relier(porte_xor3, 0, t_porte_get_nom(porte_ou2), t_porte_get_pin_sortie(porte_ou2));
	t_porte_relier(porte_xor3, 1, t_entree_get_nom(entree2), t_entree_get_pin(entree2));

	t_porte_relier(porte_et4, 0, t_entree_get_nom(entree3), t_entree_get_pin(entree3));
	t_porte_relier(porte_et4, 1, t_entree_get_nom(entree4), t_entree_get_pin(entree4));

	t_porte_relier(porte_not5, 0, t_porte_get_nom(porte_et4), t_porte_get_pin_sortie(porte_et4));

	t_porte_relier(porte_ou6, 0, t_porte_get_nom(porte_not5), t_porte_get_pin_sortie(porte_not5));
	t_porte_relier(porte_ou6, 1, t_entree_get_nom(entree5), t_entree_get_pin(entree5));

	t_porte_relier(porte_xor7, 0, t_porte_get_nom(porte_ou6), t_porte_get_pin_sortie(porte_ou6));
	t_porte_relier(porte_xor7, 1, t_entree_get_nom(entree6), t_entree_get_pin(entree6));

	t_porte_relier(porte_et8, 0, t_entree_get_nom(entree7), t_entree_get_pin(entree7));
	t_porte_relier(porte_et8, 1, t_porte_get_nom(porte_et9), t_porte_get_pin_sortie(porte_et9));

	t_porte_relier(porte_et9, 0, t_entree_get_nom(entree8), t_entree_get_pin(entree8));
	t_porte_relier(porte_et9, 1, t_entree_get_nom(entree9), t_entree_get_pin(entree9));

	t_sortie_relier(sortie0, t_porte_get_nom(porte_not0), t_porte_get_pin_sortie(porte_not0));
	t_sortie_relier(sortie1, t_porte_get_nom(porte_et1), t_porte_get_pin_sortie(porte_et1));
	t_sortie_relier(sortie2, t_porte_get_nom(porte_ou2), t_porte_get_pin_sortie(porte_ou2));
	t_sortie_relier(sortie3, t_porte_get_nom(porte_xor3), t_porte_get_pin_sortie(porte_xor3));
	t_sortie_relier(sortie4, t_porte_get_nom(porte_et4), t_porte_get_pin_sortie(porte_et4));
	t_sortie_relier(sortie5, t_porte_get_nom(porte_not5), t_porte_get_pin_sortie(porte_not5));
	t_sortie_relier(sortie6, t_porte_get_nom(porte_ou6), t_porte_get_pin_sortie(porte_ou6));
	t_sortie_relier(sortie7, t_porte_get_nom(porte_xor7), t_porte_get_pin_sortie(porte_xor7));
	t_sortie_relier(sortie8, t_porte_get_nom(porte_et8), t_porte_get_pin_sortie(porte_et8));
	t_sortie_relier(sortie9, t_porte_get_nom(porte_et9), t_porte_get_pin_sortie(porte_et9));

}

/*****************************************************************************/

int main(void)
{//déclaration des variables
	int signal[MAX_ENTREES], 	 //les valeurs (0/1) pour les entrées du circuit
		i,choix;
	t_circuit* circuit;   //le circuit complet
	circuit = t_circuit_init();//Création du circuit


	printf("Veuillez choisir un mode de creation de circuit:");
	printf("\n1 - creation manuelle #1\n2 - creation manuelle #2\n3 - a partir d'un fichier\n");
	scanf("%d",&choix);

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

			//Construction de la table de vérité
			int **table_verite = t_circuit_tdv(circuit);
		
			t_circuit_destroy(circuit);
			system("pause");
			return EXIT_SUCCESS;
		
		}
		

	case MANUEL2:
		{
			construire_circuit2(circuit);
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

			//Construction de la table de vérité
			int** table_verite = t_circuit_tdv(circuit);

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
		int nb_lignes = 1;
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