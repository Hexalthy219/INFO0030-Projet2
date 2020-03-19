/**
 * main.c
 * 
 * Ce fichier contient la fonction main() du programme de manipulation
 * de fichiers pnm.
 *
 * @author: Russe Cyril s170220
 * @date: 01-03-2020
 * @projet: INFO0030 Projet 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#include "pnm.h"


int main(int argc, char *argv[]) {

   /* options :
   *  -f <format> <fichier> -> permet de lancer le chargement de fichier et de le recopier dans le dossier de l'executable pnm sous le nom "test"
   *     suivi de l'extension correspondante dans le répertoire de l'executable
   */
   char *optstring = "f:";
   PNM *image;
   Type_PNM format_PNM, extension_fichier;
   char *filename, *format;
   int retour_chargement, retour_ecriture, retour_verif_extension, val;

   while((val=getopt(argc, argv, optstring))!=EOF){
      if(val=='f'){
            format = optarg;
            filename = argv[argc-1];
      }
      else
         return 0;
   }

   if(filename==NULL || argc<4){
      printf("Option 'f' requiert un argument 'fichier'.\n");
      return -1;
   }

   if(chaine_vers_Type_PNM(format, &format_PNM)==-1){
      printf("Le format %s passé en argument n'est pas un format PNM.\n", Type_PNM_vers_chaine(format_PNM));
      return -1;
   }

   if((retour_verif_extension = verifie_correspondance_extension_format(format_PNM, filename, &extension_fichier))==-1){
      printf("Mauvais format passé en argument. Le fichier %s est du type %s et non %s.\n", filename, Type_PNM_vers_chaine(extension_fichier), Type_PNM_vers_chaine(format_PNM));
      return -1;
   }

   retour_chargement = load_pnm(&image, filename);
   if(retour_chargement == 0)
      printf("Chargement de l'image %s en mémoire avec succès.\n", filename);

   if(retour_chargement == 0){
      char nom_fichier_ecriture[] = "test.pxm";
      ajoute_extension_filename(nom_fichier_ecriture, image);
      retour_ecriture = write_pnm(image, nom_fichier_ecriture);
      if(retour_ecriture==0)
         printf("Image copiée dans le fichier %s.\n", nom_fichier_ecriture);
      libere_PNM(&image);
   }

   return 0;
}

