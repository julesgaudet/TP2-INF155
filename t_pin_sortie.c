/*
Auteur: Anis Boubaker, Jules Gaudet et Noah Tremblay 
Date de modification: 25 novembre 2023 
Module: T_PIN_SORTIE
Description: D�finit le type t_pin_sortie. Un t_pin_sortie est un point de connexion appartenant
			 � un �l�ment du circuit qui envoie un signal (mais n'en recoit pas).
			 Les �l�ments d'un circuit ayant un pin de sortie de signal sont les portes (les entr�es
			 des portes) ainsi que les entrée du circuit.

			 Si un pin d'entr�e re�oit un signal, ce signal est stock� dans le champs valeur. Un
			 t_pin_entree qui est inactif (pas aliment�) a la valeur -1.

			 Un pin d'entree permet de relier le composant auquel il appartient � un autre composant.
			 Il doit �tre reli� � un "pin de sortie" du composant auquel on souhaite se connecter.

Auteur: Anis Boubaker
Derni�re modification: Eric Th�, 2023-11-12
*/