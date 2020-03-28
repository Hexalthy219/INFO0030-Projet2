/**
 * \file main.c
 * 
 * \brief Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * \author: Russe Cyril s170220
 * \date: 01-03-2020
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>

#include "pnm.h"
#include "filtre.h"


int main(int argc, char *argv[]) {

   /* options :
   *  
   */
   char *optstring = "i:f:p:o:";
   PNM *image;
   int filtre_input=0;
   char *filename=NULL, *filtre=NULL, *parametre=NULL, *filename_output=NULL;
   int val;

   

   while((val=getopt(argc, argv, optstring))!=EOF){
      switch (val){
         case 'i':
            filename=optarg;
            break;
         case 'f':
            filtre=optarg;
            filtre_input=1;
            break;
         case 'p':
            if(filtre_input!=1){
               printf("L'argument p est un argument optionnel de l'argument f. Veuillez entrer un filtre pour utiliser l'argument p.\n");
               return -1;
            }
            else{
               parametre=optarg;
            }
            break;
         case 'o':
            filename_output=optarg;
            break;

         default:
            break;
      }
   }

   if(load_pnm(&image, filename)!=0)
      return -1;
   
   if(strcmp(filtre, "retournement")==0)
      retournement(image);
   else if(strcmp(filtre, "monochrome")==0){
      monochrome(image, parametre);
   }
   else if(strcmp(filtre, "negatif")==0){
      negatif(image);
   }
   else if(strcmp(filtre, "gris")==0){
      gris(image, parametre);
   }
   else if(strcmp(filtre, "NB")==0){
      noir_blanc(image, parametre);
   }
   else{
      printf("Le filtre entré en argument ne correspond à aucun filtre.\n");
      libere_PNM(&image);
      return -1;
   }

   write_pnm(image, filename_output);
   

   return 0;
}

