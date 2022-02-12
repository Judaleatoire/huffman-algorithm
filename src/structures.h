#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Définition du type Huffman */

typedef struct huffman{
    int occ; // occurences
    char c; // caractère
    char* bin; // valeur binaire
}Huffman;

/* Définition du type de l'arbre */

typedef struct arb{
    Huffman elmt;
    struct arb* fd; // fils gauche
    struct arb* fg; // fils droit 
    struct arb* suiv; // suivant de la liste chainée
}Arbre;

typedef Arbre* PArbre; // pointeur sur arbre

#define N 128 // taille du tableau
#define TRUE 1
#define FALSE 0

#endif