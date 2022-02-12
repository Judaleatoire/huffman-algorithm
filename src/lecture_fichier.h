#ifndef LECTUREFICHIER_H
#define LECTUREFICHIER_H

/* On inclut les fichiers headers nécessaires au fonctionnement du programme */

#include "structures.h"

/* Prototypage des fonctions */

void init_fichier (FILE* fichier); // initialisation d'un fichier
void initialisation_tab (Huffman TabAscii[]); // initialisation du tableau
void affTab (Huffman TabAscii[]); // affichage du tableau
int recherche (char c, Huffman TabAscii[]); // recherche dans le tableau
void testFichier(FILE* fichier); // test du ficher
void CreerHistogramme (Huffman TabAscii[], char* fichierChaine); // Création histogramme
void TriTableauCroiss(Huffman TabAscii[]); // tri tableau en ordre croissant
void TriTableauDecroiss(Huffman TabAscii[]); // tri tableau en ordre décroissant

#endif