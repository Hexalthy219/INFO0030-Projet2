/**
 * \file main.c
 * \brief Ce fichier contient la fonction main() du programme d'application de filtre sur images PNM.
 * \author: Russe Cyril s170220
 * \date: 28-03-2020
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
   char *optstring = "i:f:p:o:h";
   PNM *image;
   int option[4]={0};
   char *filename=NULL, *filtre=NULL, *parametre=NULL, *filename_output=NULL;
   int val, erreur_filtre=0;

   

   while((val=getopt(argc, argv, optstring))!=EOF){
      switch (val){
         case 'i':
            filename=optarg;
            option[0]=1;
            break;
         case 'f':
            filtre=optarg;
            option[1]=1;
            break;
         case 'p':
            option[3]=1;
            parametre=optarg;
            break;
         case 'o':
            option[2]=1;
            filename_output=optarg;
            break;
         case 'h':
            printf("-i <image_input> -f <filtre> [-p <parametre>] -o <image_output>\n");
            return 0;

         default:
            break;
      }
   }

   for(int i=0; i<3; i++){
      if(option[i]==0){
         printf("Option(s) manquante(s). Option h -> help.\n");
      }
   }

   if(load_pnm(&image, filename)!=0)
      return -1;
   
   if(strcmp(filtre, "retournement")==0)
      retournement(image);
   else if(strcmp(filtre, "monochrome")==0){
      if(option[3]==0){
         printf("Paramètre nécessaire pour l'application du filtre monochrome.\n");
         erreur_filtre=1;
      }
      else if(monochrome(image, parametre)!=0)
         erreur_filtre=1;
   }
   else if(strcmp(filtre, "negatif")==0){
      if(negatif(image)!=0)
         erreur_filtre=1;
   }
   else if(strcmp(filtre, "gris")==0){
      if(option[3]==0){
         printf("Paramètre nécessaire pour l'application du filtre gris.\n");
         erreur_filtre=1;
      }
      else if(gris(image, parametre)!=0)
         erreur_filtre=1;
   }
   else if(strcmp(filtre, "NB")==0){
      if(option[3]==0){
         printf("Paramètre nécessaire pour l'application du filtre noir et blanc.\n");
         erreur_filtre=1;
      }
      else if(noir_blanc(image, parametre)!=0)
         erreur_filtre=1;
   }
   else{
      printf("Le filtre entré en argument ne correspond à aucun filtre.\n");
      libere_PNM(&image);
      return -1;
   }
   if(erreur_filtre==1){
      libere_PNM(&image);
      return -1;
   }
   
   if(verifie_extension_fichier(filename_output, image)==0){
      if(write_pnm(image, filename_output)==0)
         printf("Le filtre a correctement été appliqué sur %s et enregistrer dans %s.\n", filename, filename_output);
      else{
         libere_PNM(&image);
         return -1;
      }
   }
   

   libere_PNM(&image);

   return 0;
}

