/*! \file decompression.c
*  \author Chantôme Amandine
*  \author Tourrenc--Lecerf Alexis
*  \author Guillerm Francois
*  \version 1
*  \brief Ce fichier rassemble les fonctions nécessaires à la decompression du fichier, on lit tout d'abord l'entête du fichier compressé pour recrée l'arbre et ainsi retrouver les valeurs binaires des caractères compressés. Puis on lit le texte compressé et on recrée le texte d'origine grâce à l'arbre.
*/

#include "decompression.h"

/* Fonction permettant de lire l'entête du fichier compressé */

void lectureEntete(Huffman TabAscii[], FILE* fichierComp){

    int nbCaractereCode = 0;
    fread (&nbCaractereCode, sizeof(int), 1, fichierComp); // On lit la première valeur qui est un entier, correspondant au nombre de caractères codés
    Huffman e;

    for(int i = 0; i<nbCaractereCode; i++){ // On lit ensuite autant de caractères que le nombre récupéré précédemment
        fread (&e.c, sizeof(char), 1, fichierComp); // On récupère le caractère
        fread (&e.occ, sizeof(int), 1, fichierComp); // Puis son nombre d'occurrences
        // liste = AjoutListe(liste, creerArbre(e)); // On ajoute le caractère et son nombre d'occurrences à la liste
        TabAscii[i] = e;
    }
}

/* Fonction permettant de lire les caractères compressés et de les décompresser */

void decompBin (PArbre A, FILE* fichierComp, char* fichierDecompChaine){
    // On ouvre le fichier dans lequel on va faire la décompression
    FILE* fichier = fopen(fichierDecompChaine, "w");
    if(fichier == NULL){
        printf("Fichier non ouvert.\n");
        exit(-1);
    }

    // On initialise des variables qui vont servir à décompresser les caractères
    char c = '\0';
    char car = '\0';
    char tmp[8];
    int i = 0;
    PArbre actuel = A;

    while (fread (&c, sizeof(char), 1, fichierComp) > 0){ // On lit des caractères tant qu'il y en a 
        for(i = 7; i>=0; i--) { // On lit les 8 bits qui composent l'octet du caractère lu
            if(c & 1) { // Si le bit est égal à 1, on ajoute 1 à une chaîne de caractères temporaire
                tmp[i] = '1';
            }
            else { // Sinon, on ajoute 0
                tmp[i] = '0';
            }
            c = c >> 1; // On avance dans l'octet
        }
        for(int j = 0; j<=7; j++) { // On parcourt la chaîne de caractères temporaire
            if(tmp[j] == '1') { // Si le caractère est égal à 1, on se déplace à droite dans l'arbre
                actuel = actuel->fd;
            }
            else if(tmp[j] == '0') { // S'il est égal à 0, on se déplace à gauche dans l'arbre
                actuel = actuel->fg;
            }
            if((!actuel->fg) && (!actuel->fd)) { // Si on se retrouve dans une feuille, on stocke le caractère de la feuille
                car = actuel->elmt.c;
            }
            if(car != '\0') { // Si on est passé dans une feuille, alors la variable car a stocké un nouveau caractère et on entre dans cette condition
                fputc(car, fichier); // On écrit le caractère dans le fichier décompressé
                car = '\0'; // On remet le caractère à 0
                actuel = A; // On remonte en haut de l'arbre
            }
        }
    }

    fclose(fichier); // On ferme le fichier
}

/* Fonction permettant décompresser un fichier compressé */

void decompression (Huffman TabAscii[], PArbre liste, PArbre A, FILE* fichierComp, char* fichierDecompChaine) {
    lectureEntete(TabAscii, fichierComp); // On récupère les caractères et leur occurrences dans une liste
    TriTableauCroiss(TabAscii);
    liste = CreerListe(liste, TabAscii);
    A = CreationArbre(A, liste); // On crée l'arbre
    A = remplissageBinaire(A); // On assigne les valeurs binaires aux caractères de l'arbre
    decompBin(A, fichierComp, fichierDecompChaine); // On écrit dans le fichier décompressé
}