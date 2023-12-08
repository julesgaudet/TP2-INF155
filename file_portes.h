/*
Module: FILE_PORTE
Description: Ce fichier définit les fonctions associées à la manipulation 
d'une file de portes (t_file). Cette file est conçue  pour stocker 
des pointeurs vers des structures de type t_porte. 

Auteur: Noah Tremblay : TREN85330401
		Jules Gaudet  : GAUJ71370101
		Eric Thé
Derni�re modification : 09/12/2023
*/
#ifndef FILE_PORTES_H_
#define FILE_PORTES_H_

//**************************************************************************************//

//definitions pour la librairie de fonctions FILESLIB.CPP
#define  MAXFILE  100

//changer cette declaration pour obtenir une file pour un autre type
typedef struct t_porte t_porte;
typedef t_porte*  t_element;

typedef struct {
	t_element  items[MAXFILE];
	int      debut, fin;
	int      total;		//le nombre total d'éléments dans la file
} t_file;

/*
Fonction: INITFILE

Description: Initialise une file en la vidant (aucun élément).

Paramètres: -f(pointeur vers la file à initialiser)

Retour: Aucun			 
*/
void initfile(t_file*);

/*
Fonction: PLEINE

Description: Vérifie si la file est pleine

Paramètres: -f(pointeur vers la file à vérifier)

Retour : Renvoie 1 si la file est pleine, 0 sinon.			 
*/
int  pleine(const t_file*);

/*
Fonction: VIDE

Description:  Vérifie si la file est vide.

Paramètres: -f(pointeur vers la file à vérifier)

Retour: Aucun			 
*/
int  vide(const t_file*);

/*
Fonction: AJOUTERFIN

Description:  Ajoute un élément à la fin de la file.

Paramètres: -f(pointeur vers la file à laquelle ajouter l'élément) 
			-el(Élément à ajouter à la file)

Retour: Aucun			 
*/
void ajouterfin(t_file*, t_element);

/*
Fonction: ENLEVERDEBUT

Description:  Enlève un élément du début de la file.

Paramètres: -f(pointeur vers la file à laquelle enlever l'élément) 
			-el(pointeur vers la variable où stocker l'élément enlevé)
			
Retour: Aucun			 
*/
void enleverdebut(t_file*, t_element*);

#endif
