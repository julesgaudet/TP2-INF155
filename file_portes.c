/*
Module: file_porte
Description: Ce fichier définit les fonctions associées à la manipulation 
d'une file de portes (t_file). Cette file est conçue  pour stocker 
des pointeurs vers des structures de type t_porte. Ces fonctions sont 
déclarées dans le fichier d'en-tête correspondant file_portes.h. 

Auteurs: Noah Tremblay :
         Jules Gaudet  : GAUJ71370101
Dernière modification :
*/
/*****************************************************************************/

#include "file_portes.h"
#include <stdio.h> //Je l'ai mis ici parce que j'avais une erreur disant qu'il n'était pas inclu

/*****************************************************************************/

//Initialiser une file, la file sera vide 
void initfile(t_file* f)
{
    f->debut = 0;
    f->fin = MAXFILE - 1;
    f->total = 0;
}

/*****************************************************************************/

//Vérifier si une file est pleine
int  pleine(const t_file* f)
{
    return (f->total == MAXFILE);
}

/*****************************************************************************/

//Vérifier si une file est vide
int  vide(const t_file* f)
{
    return (f->total == 0);
}

/*****************************************************************************/

//Ajouter un element de plus a la fin d'une file
void ajouterfin(t_file* f, t_element el) {
    if (pleine(f))
        printf("ERREUR!!! Debordement de file.\n");
    else {
        f->fin = (f->fin + 1) % MAXFILE;
        f->items[f->fin] = el;
        f->total++;
    }
}

/*****************************************************************************/

//Enlever un element du debut d'une file
void enleverdebut(t_file* f, t_element* el) {
    if (vide(f))
        printf("ERREUR!!! File vide.\n");
    else {
        *el = f->items[f->debut];
        f->debut = (f->debut + 1) % MAXFILE;
        f->total--;
    }
}
/*****************************************************************************/
/*****************************************************************************/
