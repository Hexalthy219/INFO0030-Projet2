/**
 * pnm.h
 * 
 * Ce fichier contient les déclarations de types et les prototypes
 * des fonctions pour la manipulation d'images PNM.
 * 
 * @author: Russe Cyril s170220
 * @date: 01-03-2020
 * @projet: INFO0030 Projet 1
 */

/*
 * Include guard (pour éviter les problèmes d'inclusions multiplies
 * Bonne pratique: toujours encadrer un header avec un include guard
 */
#ifndef __PNM__
#define __PNM__

/**
 * Déclaration du type opaque PNM
 *
 */
typedef struct PNM_t PNM;

/**
 * Déclaration de l'énumération reprenenat les différents type de fichier PNM
 * 
 */
typedef enum {PBM, PGM, PPM}Type_PNM;

/**
 * Déclaration de la struct Format_Image
 * 
 */
typedef struct Dimension_pixel_t Dimension_pixel;

/**
 * load_pnm
 *
 * Charge une image PNM depuis un fichier.
 *
 * @param image l'adresse d'un pointeur sur PNM à laquelle écrire l'adresse
 *              de l'image chargée.
 * @param filename le chemin vers le fichier contenant l'image.
 *
 * @pre: image != NULL, filename != NULL
 * @post: image pointe vers l'image chargée depuis le fichier.
 *
 * @return:
 *     0 Succès
 *    -1 Erreur à l'allocation de mémoire
 *    -2 Nom du fichier malformé
 *    -3 Contenu du fichier malformé
 *
 */
int load_pnm(PNM **image, char* filename);

/**
 * constructeur_PNM
 * 
 * @param dimensions
 * @param format
 * @param valeur_max
 * @param fichier 
 * 
 * @return:
 *      NULL en cas d'erreur lors de l'allocation dynamique
 *      image un pointeur sur PNM, si toutes les informations de l'image et le tableau d'entier représentant l'image
 *              ont correctement été chargés dans image
 * 
 */ 
PNM *constructeur_PNM(Dimension_pixel dimensions, Type_PNM format, unsigned int valeur_max, FILE *fichier);

/**
 * libere_PNM
 * 
 * free tous les pointeurs de l'image donnée en argument et free image si image!=NULL
 * 
 * @param image un pointeur sur PNM à libérer
 * 
 * @pre: image != NULL
 * @post: image == NULL
 * 
 */ 
void libere_PNM(PNM **image);

/**
 * lit_valeur_max
 * 
 * enregistre dans la variable que pointe valeur_max, la valeur max de l'image si est du format PGM ou PPM
 * 
 * @param valeur_max un pointeur sur unsigned int valeur_max
 * 
 * @param fichier un pointeur vers FILE, le fichier dans lequel lire la valeur_max
 * 
 * @return:
 *       0 valeur_max correctement enregistrée
 *      -1 échec de la lecture de la valeur_max
 */
int lit_valeur_max(unsigned int *valeur_max, FILE  *fichier);

/**
 * lit_dimensions_image
 * 
 * enregistre dans la variable dimension, les dimensions de l'image contenues dans fichier
 * 
 * @param Dimension_pixel un pointeur sur Dimension_pixel auquel écrire les dimensions
 *                        de l'image PNM
 * @param fichier un pointeur sur FILE permettant d'en lire le contenu
 * 
 * @return:
 *       0 dimensions enregistrées avec succès dans la variable dimension
 *      -1 échec de la lecture des dimensions de l'image
 * 
 */
int lit_dimensions_image(Dimension_pixel *dimension, FILE *fichier);

/**
 * verifie_nombre_magique
 * 
 * lis le fichier PNM et en detecte le type
 * 
 * @param fichier un pointeur sur un fichier de type FILE
 * 
 * @pre: \
 * @post: \
 * 
 * @return:
 *       PBM si numéro magique == "P1"
 *       PGM si numéro magique == "P2"
 *       PPM si numéro magique == "P3"
 *      -1  Numéro magique malformé / inexistant
 * 
 */
int verifie_nombre_magique(Type_PNM *type, FILE*  fichier);

/**
 * verifie_correspondance_extension_format
 * 
 * vérifie si l'extension du fichier dans le nom de celui-ci correspond au type de type_image déduit du nombre magique
 * 
 * @param type_image enum contenant le type de l'image de type Type_PNM
 * @param filename une chaine de caractère contenant le nom du fichier
 * 
 * @return  
 *       0 succès de la vérification
 *      -1 échec de la vérification
 * 
 */ 
int verifie_correspondance_extension_format(Type_PNM type_image, char *filename, Type_PNM *extension_fichier);

/**
 * Type_PNM_vers_chaine
 * 
 * revoit une chaine de caractère correspondant aux différents éléments de l'énumération "Type_PNM"
 * 
 * @param type_image une variable de type Type_PNM
 * 
 * @return:
 *      la chaine de caractère correspondante si possible
 *      "inconnu" sinon
 */
char *Type_PNM_vers_chaine(Type_PNM type_image);

/**
 * chaine_vers_Type_PNM
 * 
 * revoit un Type_PNM correspondant à la 
 * 
 * @param chaine un pointeur vers la chaine de caractère à laquelle vérifier de quel type de l'enum elle correspond
 * 
 * @param type_image pointeur vers Type_PNM dans lequel transmettre la valeur correspodnante à la chaine de caractère
 * 
 * @pre:/
 * @post:/
 * 
 * @return:
 *       0 la chaine de caractère correspond bien à un des type de Type_PNM
 *      -1 la chaine de caractère ne correspond à aucun des types et n'a donc pas été donnée à type_image
 *  
 */
int chaine_vers_Type_PNM(char *chaine, Type_PNM *type_image);

/**
 * write_pnm
 *
 * Sauvegarde une image PNM dans un fichier.
 *
 * @param image un pointeur sur PNM.
 * @param filename le chemin vers le fichier de destination.
 *
 * @pre: image != NULL, filename != NULL
 * @post: le fichier filename contient l'image PNM image.
 *
 * @return:
 *     0    Succès
 *    -1    Nom du fichier malformé
 *    -2    Erreur lors de la manipulation du fichier
 *
 */
int write_pnm(PNM *image, char* filename);

/**
 * ecrit_image_dans_fichier
 * 
 * écrit les valeurs de image dans fichier
 * 
 * @param image un pointeur sur PNM qui contient les informations de l'iamge à retranscrire dans fichier
 * 
 * @param fichier un pointeur sur FILE, un fichier ouvert en mode "write" afin d'y retranscrire une image PNM
 * 
 * @pre:/
 * @post:/
 * 
 * @return:
 *   0  succès de l'écriture du fichier
 * 
 */
int ecrit_image_dans_fichier(PNM *image, FILE *fichier);

/**
 * ecrit_en_tete_fichier_PNM
 * 
 * écrit en en tete du fichier l'en tête: nombre magique, dimensions et valeurs max si c'est un fichier pgm ou ppm
 * 
 * @param image pointeur sur PNM structure contenant les informations nécessaires à la création de l'en tête 
 * @param fichier pointeur sur FILE un fichier ouvert en mode "write" afin d'y écrire l'en tête
 * 
 * @pre:/
 * @post:/
 * 
 * @return:
 *       0  succès de l'écriture de l'en tête dans fichier
 *      -1  échèc de l'écriture de l'en tête dans fichier car format format incorrect
 * 
 */
int ecrit_en_tete_fichier_PNM(PNM *image, FILE *fichier);

/**
 * verifie_validite_filename
 * 
 * vérifie si le nom du fichier d'écriture ne contient pas de caractère interdit
 * 
 * @param filename pointeur sur une chaine de caractère contenant le nom du fichier à vérifier
 * 
 * @pre:/
 * @post:/
 * 
 * @return:
 *       0  le nom de fichier ne contient pas de caractère interdit
 *      -1  le nom de fichier contient des caractères interdits
 */
int verifie_validite_filename(char *filename);

/**
 * ajoute_extension_filename
 * 
 * modifie filename afin d'y ajouter le nom d'extension correspondant au format de image
 * 
 * @param filename pointeur sur une chaine de caractère contenant le nom de fichier à modifier
 * @param image pointeur sur PNM, structure contenant toutes les informations de l'image à retranscrire
 * 
 * @pre:/
 * @post:filename modifié afin qu'il se termine par "pbm", "pgm" ou "ppm" en fonctin du format image
 * 
 */
void ajoute_extension_filename(char *filename, PNM *image);

#endif // __PNM__

