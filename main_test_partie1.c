/*
TESTER LES ENTREES ET LES SORTIES
Auteur: Eric Th�, 13-11-2023

Programme qui teste l'utilisation des librairies de circuits logique "t_entree" 
(avec "t_pin_sortie") et "t_sortie".  Plusieurs tests unitaires sont faits avec "assert()"
*/
/*****************************************************************************/
#include <assert.h>
#include "t_entree.h"
#include "t_sortie.h"
#include "t_porte.h"
#define _CRT_SECURE_NO_WARNINGS

/*****************************************************************************/
int test(void);		//Déclaration des fonctions avant le main
int test_porte(void);

/*****************************************************************************/
int main (void)
{
	printf("********************Premier test********************\n");
	test();		//Tester les entrées, sorties et pin
	printf("\n");
	printf("********************Deuxième test********************\n");
	test_porte();	//Tester les portes
	printf("\n");
}

int test(void)
{
	//d�claration de variables
	t_entree* entree0;     //les 2 entr�es
	t_entree* entree1;
	t_sortie* sortie0;     //les 2 sorties
	t_sortie* sortie1;
	t_pin_sortie* pin;     //pointeur vers un des pins de sortie (de E0 ou E1)
	t_pin_entree* pin_in;  //pointeur vers un des pins d'entr�e (de S0 ou S1)



	//Cr�er tous les �l�ments dynamiques
	entree0 = t_entree_init(0, "E0");
	entree1 = t_entree_init(1, "E1");
	sortie0 = t_sortie_init(0, "S0");
	sortie1 = t_sortie_init(1, "S1");

	//on teste si les entr�es/sorties sont reli�es
	if (t_entree_est_reliee(entree0) == 0)
		printf("L'entree %s n'est pas reliee!\n", t_entree_get_nom(entree0));

	if (t_entree_est_reliee(entree1) == 0)
		printf("L'entree %s n'est pas reliee!\n", t_entree_get_nom(entree1));

	if (t_sortie_est_reliee(sortie0) == 0)
		printf("La sortie %s n'est pas reliee!\n", t_sortie_get_nom(sortie0));

	if (t_sortie_est_reliee(sortie1) == 0)
		printf("La sortie %s n'est pas reliee!\n", t_sortie_get_nom(sortie1));

	//on r�cup�re une r�f�rence sur le pin de sortie de entree0
	pin = t_entree_get_pin(entree0);

	//on connecte entree0 � la sortie0
	t_sortie_relier(sortie0, t_entree_get_nom(entree0), pin);
	assert(t_entree_est_reliee(entree0) == 1);		//test unitaire rapide avec assert()
	assert(t_sortie_est_reliee(sortie0) == 1);		//test unitaire rapide avec assert()

	pin_in = t_sortie_get_pin(sortie0);
	printf("\nLa sortie %s est connectee a l'entree %s\n", t_sortie_get_nom(sortie0), 
		                                                   t_pin_entree_get_lien(pin_in));

	//on connecte entree0 � la sortie1
	t_sortie_relier(sortie1, t_entree_get_nom(entree0), pin);
	assert(t_sortie_est_reliee(sortie1) == 1);		//test unitaire rapide avec assert()

	pin_in = t_sortie_get_pin(sortie1);
	printf("\nLa sortie %s est connectee a l'entree %s\n", t_sortie_get_nom(sortie1),
		                                                   t_pin_entree_get_lien(pin_in));

	//mettre le signal � 1 dans le pin de entree0 et propager le signal
	t_pin_sortie_set_valeur(pin, 1);
	t_entree_propager_signal(entree0);

	//TEST 1: on confirme la r�ception du signal (1) dans les deux sorties
	printf("\nTEST 1: %s (%d) -> %s et %s\n", t_entree_get_nom(entree0), t_entree_get_valeur(entree0),
		                                      t_sortie_get_nom(sortie0), t_sortie_get_nom(sortie1));

	printf("Sortie %d = %d\n", t_sortie_get_id(sortie0), t_sortie_get_valeur(sortie0));
	printf("Sortie %d = %d\n", t_sortie_get_id(sortie1), t_sortie_get_valeur(sortie1));

	//on efface les valeurs des deux sorties
	t_sortie_reset(sortie0);
	assert(t_sortie_get_valeur(sortie0) == INACTIF);   //test unitaire rapide avec assert()

	t_sortie_reset(sortie0);
	assert(t_sortie_get_valeur(sortie0) == INACTIF);   //test unitaire rapide avec assert()

	//on r�cup�re une r�f�rence sur le pin de sortie de entree1
	pin = t_entree_get_pin(entree1);

	//on connecte entree1 � la sortie1
	t_sortie_relier(sortie1, t_entree_get_nom(entree1), pin);
	assert(t_entree_est_reliee(entree1) == 1);		//test unitaire rapide avec assert()
	assert(t_sortie_est_reliee(sortie1) == 1);		//test unitaire rapide avec assert()

	pin_in = t_sortie_get_pin(sortie1);
	printf("\nLa sortie %s est connectee a l'entree %s\n", t_sortie_get_nom(sortie1),
		                                                   t_pin_entree_get_lien(pin_in));

	//mettre le signal � 1 dans le pin de entree1 et propager le signal
	t_pin_sortie_set_valeur(pin, 1);
	t_entree_propager_signal(entree1);

	//mettre le signal � -1 dans le pin de sortie de entree0
	t_entree_reset(entree0);
	assert(t_entree_get_valeur(entree0) == INACTIF);    //test unitaire rapide avec assert()

	//mettre le signal � 0 dans le pin de entree0 et propager le signal
	pin = t_entree_get_pin(entree0);
	t_pin_sortie_set_valeur(pin, 0);
	t_entree_propager_signal(entree0);

	//TEST 2: on confirme la r�ception du signal (1) dans S0 et (0) dans S1
	printf("\nTEST 2: %s (%d) -> %s, %s (%d) -> %s\n", t_entree_get_nom(entree0), t_entree_get_valeur(entree0), 
		                                               t_sortie_get_nom(sortie0),
		                                               t_entree_get_nom(entree1), t_entree_get_valeur(entree1), 
		                                               t_sortie_get_nom(sortie1));

	printf("Sortie %d = %d\n", t_sortie_get_id(sortie0), t_sortie_get_valeur(sortie0));
	printf("Sortie %d = %d\n", t_sortie_get_id(sortie1), t_sortie_get_valeur(sortie1));
	system("pause");

	//lib�rer les 4 allocations
	t_entree_destroy(entree0);
	t_entree_destroy(entree1);
	t_sortie_destroy(sortie0);
	t_sortie_destroy(sortie1);
	return 0;
}

int test_porte(void) {

    t_porte* porte0 = t_porte_init(0, PORTE_ET, "Porte ET 0");
    t_porte* porte1 = t_porte_init(1, PORTE_NOT, "Porte NOT 1");
    t_porte* porte2 = t_porte_init(2, PORTE_OU, "Porte OU 2");
    t_porte* porte3 = t_porte_init(3, PORTE_XOR, "Porte XOR 3");

    // Relier les portes
    t_porte_relier(porte0, 0, "Sortie", t_porte_get_pin_sortie(porte1));
    t_porte_relier(porte1, 0, "Sortie", t_porte_get_pin_sortie(porte2));
    t_porte_relier(porte2, 0, "Sortie", t_porte_get_pin_sortie(porte3));

    // Propager un signal à travers les portes
    t_porte_propager_signal(porte0);

    // Afficher les informations des portes
    char resultat[100];
    t_porte_serialiser(porte0, resultat);
    printf("Porte 0 : %s\n", resultat);

    t_porte_serialiser(porte1, resultat);
    printf("Porte 1 : %s\n", resultat);

    t_porte_serialiser(porte2, resultat);
    printf("Porte 2 : %s\n", resultat);

    t_porte_serialiser(porte3, resultat);
    printf("Porte 3 : %s\n", resultat);

    // Libérer la mémoire
    t_porte_destroy(porte0);
    t_porte_destroy(porte1);
    t_porte_destroy(porte2);
    t_porte_destroy(porte3);

    return 0;
}