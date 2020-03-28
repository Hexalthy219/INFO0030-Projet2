/**
 * \file filtre.c
 * \brief Ce fichier contient les définitions de types et les fonctions de filtre d'images PNM.
 * 
 * \author: Russe Cyril s170220
 * \date: 19-03-2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "filtre.h"
#include "pnm.h"



void retournement(PNM *image){
    assert(image!=NULL);
    unsigned short ***matrice_pixels = acces_valeurs_pixel_PNM(image);
    int nbr_ligne = acces_nbr_ligne_PNM(image), nbr_colonne = acces_nbr_colonne_PNM(image);
    int format = acces_format_PNM(image);
    unsigned short tampon[3];
    for(int i=0; i<nbr_ligne/2; i++){
        for(int j=0; j<nbr_colonne; j++){
            if(format==3){
                for(int x=1; x<3; x++){
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

}

int monochrome(PNM *image, char *couleur){
    assert(couleur!=NULL);
    char type_monochrome = couleur[0];
    assert(image!=NULL || (type_monochrome!='r' && type_monochrome!='v' && type_monochrome!='b'));
    assert(acces_format_PNM(image)==3);
    unsigned short ***matrice_pixels = acces_valeurs_pixel_PNM(image);
    int nbr_ligne = acces_nbr_ligne_PNM(image), nbr_colonne = acces_nbr_colonne_PNM(image);



    for(int i=0; i<nbr_ligne; i++){
        for(int j=0; j<nbr_colonne; j++){
            for(int x=0; x<2; x++){
                if(type_monochrome=='r' && x!=0)
                        matrice_pixels[i][j][x]=0;
                if(type_monochrome=='v' && x!=1)
                        matrice_pixels[i][j][x]=0;
                if(type_monochrome=='b' && x!=2)
                        matrice_pixels[i][j][x]=0;
            }
        }
    }

    return 0;
}

int negatif(PNM *image){
    assert(image!=NULL && acces_format_PNM(image)==3);
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

int gris(PNM *image, char *technique){
    int format;
    assert(image!=NULL && ((format=acces_format_PNM(image))==3) && (technique==1||technique==2));
    unsigned short ***matrice_pixels = acces_valeurs_pixel_PNM(image);
    int nbr_ligne = acces_nbr_ligne_PNM(image), nbr_colonne = acces_nbr_colonne_PNM(image), valeur_max = acces_valeur_max_PNM(image);
    float moyenne;
    unsigned short gris[1];

    PNM *image_PGM;
    if((image_PGM = constructeur_PNM(nbr_ligne, nbr_colonne, 2, valeur_max))==NULL){
        printf("Echec lors de l'application du filtre gris.\n");
        return -1;
    }

    for(int i=0; i<nbr_ligne; i++){
        for(int j=0; j<nbr_colonne; j++){
            if(technique==1){
                moyenne = 0;
                for(int x=0; x<3; x++)
                    moyenne += matrice_pixels[i][j][x];
                moyenne /= 3;
            }
            else
                moyenne = 0.299 * matrice_pixels[i][j][0] + 0.587 * matrice_pixels[i][j][1] + 0.114 * matrice_pixels[i][j][2];
            
            gris[0] = moyenne;
            if((moyenne - gris[0])>0.5)
                gris[0]++;
            
            changer_valeur_pixel_PNM(image_PGM, i, j, gris);
        }
    }
    image = image_PGM;
    libere_PNM(&image_PGM);
    
    return 0;
}

int noir_blanc(PNM *image,char *seuil){
    assert(image!=NULL && seuil!=NULL);
    int format;
    (format=acces_format_PNM(image))==2||format==3)
    if(verifie_param_filtre(nb, seuil, image)==-1)
    {
        printf("Le seuil entré n'est pas une valeur de seuil valable.\n");
        return -1;
    }
    if(format==3){
        if(gris(image, 1)==-1)
            return -1;
    }
    unsigned short ***matrice_pixels = acces_valeurs_pixel_PNM(image);
    int nbr_ligne = acces_nbr_ligne_PNM(image), nbr_colonne = acces_nbr_colonne_PNM(image);
    unsigned short noir_blanc[1];
    changer_format(image, 1);

    for(int i=0; i<nbr_ligne; i++){
        for(int j=0; j<nbr_colonne; j++){
            if(matrice_pixels[i][j][0]>seuil)
                noir_blanc[0]=1;
            else
                noir_blanc[0]=0;
            changer_valeur_pixel_PNM(image, i, j, noir_blanc);
        }
    }

    return 0;
}

static int verifie_param_filtre(Filtre filtre, char *param, PNM *image){
    assert(param!=NULL&&(filtre==monochrome||filtre==gris||filtre==nb));
    if(filtre==monochrome){
        if (param[0]!='r'&&param[0]!='v'&&param[0]!='b')
            return -1;
        else
            return 0;
    }
    else if(filtre==gris){
        if(atoi(param)!=1&&atoi(param)==2)
            return -1;
        else
            return 0;
    }
    else if(filtre==nb){
        if(atoi(param)<0||acces_valeur_max_PNM(image)<atoi(param))
            return -1;
        else
            return 0;
    }

}