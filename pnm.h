/**
 * \file pnm.h
 * \brief Ce fichier contient les déclarations de types et les prototypes des fonctions pour la manipulation d'images PNM.
 * \author: Russe Cyril s170220
 * \date: 01-03-2020
 * 
 */

//Include guard
#ifndef __PNM__
#define __PNM__

/**
 * \struct typedef struct PNM_t PNM
 * \brief Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * \fn load_pnm(PNM **image, char* filename)
 * \brief Charge une image PNM depuis un fichier.
 * 
 * \param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse de l'image chargée.
 * \param filename le chemin vers le fichier contenant l'image.
 * 
 * \pre image != NULL, filename != NULL
 * \post image pointe vers l'image chargée depuis le fichier.
 * 
 * \return
 *     0 Succès \n
 *    -1 Erreur à l'allocation de mémoire \n
 *    -2 Nom du fichier malformé \n
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * \fn *constructeur_PNM(int nbr_ligne, int nbr_colonne, int format, unsigned int valeur_max)
 * \brief Alloue dynamiquement de la mémoire pour une structure PNM
 * 
 * \param nbr_ligne un entier contenant la valeur du nombre de ligne de l'image
 * \param nbr_colonne un entier contenant la valeur du nombre de ligne de l'image
 * \param format un entier contenant la valeur du format de l'image
 * \param valeur_max un entier contenant la valeur max des valeurs de pixel de l'image
 * 
 * \return
 *      NULL en cas d'erreur lors de l'allocation dynamique image un pointeur sur PNM, 
 *          si toutes les informations de l'image et le tableau d'entier représentant 
 *          l'image ont correctement été chargés dans image
 * 
 */
PNM *constructeur_PNM(int nbr_ligne, int nbr_colonne, int format, unsigned int valeur_max);

int charge_valeurs_fichier(PNM *image, FILE *fichier);

int acces_nbr_ligne_PNM(PNM *image);

int acces_nbr_colonne_PNM(PNM *image);

int acces_format_PNM(PNM *image);

unsigned int acces_valeur_max_PNM(PNM *image);

unsigned short ***acces_valeurs_pixel_PNM(PNM *image);

void changer_valeur_pixel_PNM(PNM *image, int numero_ligne, int numero_colonne, unsigned short valeur[]);

void changer_format(PNM *image, int format);

/**
 * \fn libere_PNM(PNM **image)
 * \brief Libere l'espace mémoire d'un pointeur sur PNM tous les pointeurs 
 *      de l'image donnée en argument et free image si image!=NULL
 * 
 * \param image un pointeur sur PNM à libérer
 * 
 * \pre image != NULL
 * \post image == NULL
 * 
 */ 
void libere_PNM(PNM **image);

/**
 * \fn lit_valeur_max(unsigned int *valeur_max, FILE  *fichier)
 * 
 * \brief Enregistre dans la variable que pointe valeur_max, la valeur max de l'image si est du format PGM ou PPM
 * 
 * \param valeur_max un pointeur sur unsigned int valeur_max
 * 
 * \param fichier un pointeur vers FILE, le fichier dans lequel lire la valeur_max
 * 
 * \return
 *       0 valeur_max correctement enregistrée \n
 *      -1 échec de la lecture de la valeur_max
 */
int lit_valeur_max(unsigned int *valeur_max, FILE  *fichier);

/**
 * \fn lit_dimensions_image(int *nbr_ligne, int *nbr_colonne, FILE *fichier)
 * 
 * \brief Enregistre dans la variable dimension, les dimensions de l'image contenues dans fichier
 * 
 * \param Dimension_pixel un pointeur sur Dimension_pixel auquel écrire les dimensions
 *                        de l'image PNM
 * \param fichier un pointeur sur FILE permettant d'en lire le contenu
 * 
 * \return
 *       0 dimensions enregistrées avec succès dans la variable dimension \n 
 *      -1 échec de la lecture des dimensions de l'image
 * 
 */
int lit_dimensions_image(int *nbr_ligne, int *nbr_colonne, FILE *fichier);

/**
 * \fn verifie_nombre_magique(int *type, FILE*  fichier)
 * 
 * \brief Lis le fichier PNM et en detecte le type
 * 
 * \param fichier un pointeur sur un fichier de type FILE
 * 
 * \pre: \
 * \post: \
 * 
 * @return:
 *       1 si numéro magique == "P1" \n 
 *       2 si numéro magique == "P2" \n 
 *       3 si numéro magique == "P3" \n 
 *      -1 Numéro magique malformé / inexistant
 * 
 */
int verifie_nombre_magique(int *type, FILE*  fichier);

/**
 * \fn verifie_correspondance_extension_format(int type_image, char *filename, int *extension_fichier)
 * 
 * \brief Vérifie si l'extension du fichier dans le nom de celui-ci correspond au type de type_image déduit du nombre magique
 * 
 * \param type_image enum contenant le type de l'image de type Type_PNM
 * \param filename une chaine de caractère contenant le nom du fichier
 * 
 * \return  
 *       0 succès de la vérification \n 
 *      -1 échec de la vérification
 * 
 */
int verifie_correspondance_extension_format(int type_image, char *filename, int *extension_fichier);

/**
 * \fn write_pnm(PNM *image, char* filename)
 *
 * \brief Sauvegarde une image PNM dans un fichier.
 *
 * \param image un pointeur sur PNM.
 * \param filename le chemin vers le fichier de destination.
 *
 * \pre: image != NULL, filename != NULL
 * \post: le fichier filename contient l'image PNM image.
 *
 * \return
 *     0    Succès \n
 *    -1    Nom du fichier malformé \n
 *    -2    Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);

/**
 * \fn ecrit_image_dans_fichier(PNM *image, FILE *fichier)
 * 
 * \brief écrit les valeurs de image dans fichier
 * 
 * \param image un pointeur sur PNM qui contient les informations de l'iamge à retranscrire dans fichier
 * 
 * \param fichier un pointeur sur FILE, un fichier ouvert en mode "write" afin d'y retranscrire une image PNM
 * 
 * \pre:/
 * \post:/
 * 
 * \return
 *   0  succès de l'écriture du fichier
 * 
 */
int ecrit_image_dans_fichier(PNM *image, FILE *fichier);

/**
 * \fn ecrit_en_tete_fichier_PNM(PNM *image, FILE *fichier)
 * 
 * \brief écrit en en tete du fichier l'en tête: nombre magique, dimensions et valeurs max si c'est un fichier pgm ou ppm
 * 
 * \param image pointeur sur PNM structure contenant les informations nécessaires à la création de l'en tête 
 * \param fichier pointeur sur FILE un fichier ouvert en mode "write" afin d'y écrire l'en tête
 * 
 * \pre:/
 * \post:/
 * 
 * \return
 *       0  succès de l'écriture de l'en tête dans fichier \n
 *      -1  échèc de l'écriture de l'en tête dans fichier car format format incorrect
 * 
 */
int ecrit_en_tete_fichier_PNM(PNM *image, FILE *fichier);

/**
 * \fn verifie_validite_filename(char *filename)
 * 
 * \brief Vérifie si le nom du fichier d'écriture ne contient pas de caractère interdit
 * 
 * \param filename pointeur sur une chaine de caractère contenant le nom du fichier à vérifier
 * 
 * \pre:/
 * \post:/
 * 
 * \return
 *       0  le nom de fichier ne contient pas de caractère interdit \n
 *      -1  le nom de fichier contient des caractères interdits
 */
int verifie_validite_filename(char *filename);

int verifie_extension_fichier(char *filename, PNM *image);

#endif // __PNM__

