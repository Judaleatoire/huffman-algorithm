#ifndef COMPRESSION_H
#define COMPRESSION_H

/* On inclut les fichiers headers nécessaires au fonctionnement du programme */

#include "structures.h"
#include "lecture_fichier.h"
#include "creationArbre.h"

/* Prototypage des fonctions */

void ecritureBinaire (Huffman TabAscii[], FILE* fichierComp, char* fichierChaine); // Ecriture du texte compressé
void ecritureEntete(Huffman TabAscii[], FILE* fichierComp); // Ecriture de l'entête du fichier compressé
int nbCarCode(Huffman TabAscii[]); // Calcul du nombre de caractères uniques dans le texte
void compression(Huffman TabAscii[], PArbre liste, PArbre A, FILE* fichierComp, char* fichierChaine); // Rassemble toutes les fonctions permettant de compresser le fichier

#endif