/**
 * \file filtre.h
 * \brief Ce fichier contient les déclarations de types et les prototypes des fonctions pour l'ajout de filtres à des images PNM.
 * 
 * \author: Russe Cyril s170220
 * \date: 19-03-2020
 * 
 */


//Include guard
#ifndef __FILTRE__
#define __FILTRE__

#include "pnm.h"

typedef enum
{
    mono,
    g,
    nb
} Filtre;

/**
 * \fn retournement(PNM *image)
 * \brief fait un rotation de 180 degrés de image.
 * 
 * \param image l'adresse d'un pointeur sur PNM dans laquelle faire une rotation.
 * 
 * \pre image != NULL
 * \post valeur_pixel de image retournée
 * 
 */
void retournement(PNM *image);

int monochrome(PNM *image, char *couleur);

int negatif(PNM *image);

int gris(PNM *image, char *technique);

int noir_blanc(PNM *image, char *seuil);

#endif