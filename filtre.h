/**
 * \file filtre.h
 * 
 * \brief Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour l'ajout de filtres à des images PNM.
 * 
 * \author: Russe Cyril s170220
 * \date: 19-03-2020
 * 
 */


//Include guard
#ifndef __FILTRE__
#define __FILTRE__

#include "pnm.h"

/**
 * \fn retournement
 * 
 * \brief fait un rotation de 180degrés de image.
 * 
 * \param image l'adresse d'un pointeur sur PNM dans laquelle faire une rotation.
 * 
 * \pre image != NULL
 * \post valeur_pixel de image retournée
 * 
 * \return
 *      0 Succès
 * 
 * 
 */
int retournement(PNM *image);

int monochrome(PNM *image, char type_monochrome);

int negatif(PNM *image);

int ppm_vers_pgm(PNM *image, int technique);

int pgm_vers_pbm(PNM *image, unsigned short seuil);

#endif