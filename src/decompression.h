#ifndef DECOMPRESSION_H
#define DECOMPRESSION_H

/* On inclut les fichiers headers nécessaires au fonctionnement du programme */

#include "structures.h"
#include "lecture_fichier.h"
#include "creationArbre.h"

/* Prototypage des fonctions */

void lectureEntete(Huffman TabAscii[], FILE* fichierComp); // Lecture de l'entête du fichier, afin de récupérer la liste contenant les caractères et leur occurrences
void decompBin (PArbre A, FILE* fichierComp, char* fichierDecompChaine); // Lecture et analyse du texte compressé
void decompression (Huffman TabAscii[], PArbre liste, PArbre A, FILE* fichierComp, char* fichierDecompChaine); // Rassemble toutes les fonctions permettant de décompresser le fichier

#endif