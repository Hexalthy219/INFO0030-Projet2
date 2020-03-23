/**
 * filtre.c
 * 
 * Ce fichier contient les définitions de types et 
 * les fonctions de filtre d'images PNM.
 * 
 * @author: Russe Cyril s170220
 * @date: 19-03-2020
 * @projet: INFO0030 Projet 2
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "filtre.h"
#include "pnm.h"

int retournement(PNM *image){
    assert(image!=NULL);
    unsigned short ***matrice_pixels = acces_valeurs_pixel_PNM(image);
    int nbr_ligne = acces_nbr_ligne_PNM(image), nbr_colonne = acces_nbr_colonne_PNM(image);
    int format = acces_format_PNM(image);
    unsigned short tampon[3];
    for(int i=0; i<nbr_ligne/2; i++){
        for(int j=0; j<nbr_colonne; j++){
            if(format==2){
                for(int x=0; x<3; x++){
                    tampon[x] = matrice_pixels[i][j][x];
                    matrice_pixels[i][j][x] = matrice_pixels[nbr_ligne-i-1][nbr_colonne-j-1][x];
                    matrice_pixels[nbr_ligne-i-1][nbr_colonne-j-1][x] = tampon[x];
                }
            }
            else{
                tampon[0] = matrice_pixels[i][j][0];
                matrice_pixels[i][j][0] = matrice_pixels[nbr_ligne-i-1][nbr_colonne-j-1][0];
                matrice_pixels[nbr_ligne-i-1][nbr_colonne-j-1][0] = tampon[0];
            }
        }
    }

    return 0;
}

int monochrome(PNM *image, char type_monochrome){
    assert(image!=NULL || (type_monochrome!='r' && type_monochrome!='v' && type_monochrome!='b'));
    assert(acces_format_PNM(image)==2);
    unsigned short ***matrice_pixels = acces_valeurs_pixel_PNM(image);
    int nbr_ligne = acces_nbr_ligne_PNM(image), nbr_colonne = acces_nbr_colonne_PNM(image);
    for(int i=0; i<nbr_ligne; i++){
        for(int j=0; j<nbr_colonne; j++){
            for(int x=0; x<2; x++){
                if(type_monochrome=='r'){
                    if(x!=0)
                        matrice_pixels[i][j][x]=0;
                }
                if(type_monochrome=='v'){
                    if(x!=1)
                        matrice_pixels[i][j][x]=0;
                }
                if(type_monochrome=='b'){
                    if(x!=2)
                        matrice_pixels[i][j][x]=0;
                }
            }
        }
    }

    return 0;
}

int negatif(PNM *image){
    assert(image!=NULL);
    assert(acces_format_PNM(image)==2);
    unsigned short ***matrice_pixels = acces_valeurs_pixel_PNM(image);
    int nbr_ligne = acces_nbr_ligne_PNM(image), nbr_colonne = acces_nbr_colonne_PNM(image);

    for(int i=0; i<nbr_ligne; i++){
        for(int j=0; j<nbr_colonne; j++){
            for(int x=0; x<3; x++)
                matrice_pixels[i][j][x]=255-matrice_pixels[i][j][x];
        }
    }

    return 0;
}