/*
Module: file_porte
Description:

Auteurs: Noah Tremblay :
         Jules Gaudet : GAUJ71370101
Dernière modification :
*/
/*****************************************************************************/

#include "file_portes.h"
#define _CRT_SECURE_NO_WARNINGS 

/*****************************************************************************/

//Initialiser une file, la file sera vide 
void initfile(t_file* f)
{
    f->debut = 0;
    f->fin = MAXFILE - 1;
    f->total = 0;
}

//Vérifier si une file est pleine
int  pleine(const t_file* f)
{
    return (f->total == MAXFILE);
}

//Vérifier si une file est vide
int  vide(const t_file* f)
{
    return (f->total == 0);
}

//Ajouter un element de plus a la fin d'une file
void ajouterfin(t_file* f, t_file el)
{
    if (pleine(f))
        printf("ERREUR!!! Debordement de file.\n");
    else {
        f->fin = (f->fin + 1) % MAXFILE;
        f->items[f->fin] = el;
        f->total++;
    }
}

//Enlever un element du debut d'une file
void enleverdebut(t_file* f, t_file* el)
{
    if (vide(f))
        printf("ERREUR!!! File vide.\n");
    else {
        *el = f->items[f->debut];
        f->debut = (f->debut + 1) % MAXFILE;
        f->total--;
    }
}
