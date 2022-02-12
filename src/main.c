/*! \file main.c
*  \author Chantôme Amandine
*  \author Tourrenc--Lecerf Alexis
*  \author Guillerm Francois
*  \version 1
*  \brief Programme principal du projet, il contient simplement les fonctions d'initialisations, 
*  puis l'appel de la fonction menu.  
*/

/*! \mainpage Présentation
*  \section introduction Introduction
*
*  Le programme commence par initialiser le tableau de structures pour les structures Huffman.\n
*  On appelle ensuite le menu qui exécutera soit la compression, soit la decompression, soit une aide en fonction des paramètres entrés.
*
*  \section fichiers Fichiers
*
*  Le code est divisé en fichiers afin de mieux se repérer et d'avoir une meilleure vue d'ensemble du projet.
*
*  \section fonctions_procedures Fonctions et procédures
*
*  Le programme est décomposé en plusieurs fonctions et procédures afin d'avoir le moins de code brut possible.
*/

#include "header.h"

int main (int argc, char** argv){

    // On crée les variables nécessaires au programme entier
    Huffman TabAscii[N];
    PArbre A = NULL;
    PArbre liste = NULL;

    // On appelle la fonction menu qui gère les paramètres et appelle les fonctions nécessaires en fonction des paramètres
    menu(argc, argv, TabAscii, liste, A);

    return 0;
}