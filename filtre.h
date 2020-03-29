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

/**
 * \enum typedef enum Filtre
 * \brief Définition de l'enum Filtre
 * 
 */
typedef enum
{
    mono,//monochrome
    g,//gris
    nb//noir et blanc
} Filtre;

/**
 * \fn retournement(PNM *image)
 * \brief fait un rotation de 180 degrés de image.
 * 
 * \param image un pointeur sur PNM
 * 
 * \pre image != NULL
 * \post valeur_pixel de image retournée
 * 
 */
void retournement(PNM *image);

/**
 * \fn monochrome(PNM *image, char *couleur)
 * \brief Applique un filtre monochrome sur une image PNM au format ppm
 * 
 * \param image un pointeur sur PNM
 * \param couleur une chaine de caractère contenant le type de 
 * filtre monochrome à appliquer ('r','v' ou 'b')
 * 
 * \pre image!=NULL, image->format=3
 * \post toutes les composantes de chaque pixels nulles, 
 * sauf celle de "couleur"
 * 
 * \return 
 *       0 Succès \n
 *      -1 format!=3
 *      -2 couleur n'est pas un param valable
 * 
 */
int monochrome(PNM *image, char *couleur);

/**
 * \fn negatif(PNM *image)
 * \brief Applique un filtre négatif sur une image PNM au format ppm
 * 
 * \param image un pointeur sur PNM auquel appliquer le filtre
 * 
 * \pre image!=NULL, image->format=3
 * \post toutes les composantes de pixels ont été transformées 
 * en leur composante négative
 * 
 */
int negatif(PNM *image);

/**
 * \fn gris(PNM *image, char *technique)
 * \brief Applique un filtre gris sur une image PNM au format ppm
 * 
 * \param image pointeur sur PNM auquel appliquer le filtre
 * \param technique une chaine de caractère contenant la valeur 
 * de la technique à utiliser ("1" ou "2")
 * 
 * \pre: image!=NULL, technique=="1" ou technique=="2"
 * \post: image->format=2, valeurs du tableau de pixel modifiées
 * 
 * \return
 *       0 Succès de l'application du filtre \n
 *      -1 Format d'image différent de ppm \n
 *      -2 Paramètre du filtre différent de 1 et de 2
 * 
 */
int gris(PNM *image, char *technique);

/**
 * \fn noir_blanc(PNM *image, char *seuil)
 * \brief Applique un filtre noir et blanc sur une image PNM au format ppm ou pgm
 * 
 * \param image pointeur sur PNM auquel appliquer le filtre
 * \param seuil chaine de caractère contenant une valeur représentant
 * le seuil à laquelle une valeur grise est noir ou blanche
 * 
 * \pre: image!=NULL, seuil!=NULL, 0 <= seuil <= image->valeur_max
 * \post: image->format=1, valeurs du tableau de pixel modifiées
 * 
 * \return 
 *       0 Succès de l'application du filtre \n
 *      -1 seuil n'est pas une valeur de seuil valable \n
 *      -2 Format d'entrée différent de 2(pgm) ou 3(ppm)
 * 
 */
int noir_blanc(PNM *image, char *seuil);

#endif