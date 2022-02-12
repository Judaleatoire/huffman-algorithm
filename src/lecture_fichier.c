/*! \file lecture_fichier.c
*  \author Chantôme Amandine
*  \author Tourrenc--Lecerf Alexis
*  \author Guillerm Francois
*  \version 1
*  \brief Ce fichier rassemble les fonctions nécessaires à la lecture du fichier à compressé, et à la création du tableau contenant les caractères et leur occurrences.
*/

#include "lecture_fichier.h"

/* Procédure de test de l'existance du fichier */

void init_fichier (FILE* fichier){
    if (fichier == NULL){ // fichier non existant
        puts ("Fichier non ouvert");
        exit (1);
    }
}

/* Procédure d'initialisation d'un tableau d'huffman */

void initialisation_tab (Huffman TabAscii[]){
    int i; 
    for (i = 0; i<N; i++){
        TabAscii[i].c = '\0'; // initialisation du caractère en caractère vide
        TabAscii[i].occ = 0; // initialisation des occurences à 0
        TabAscii[i].bin = '\0'; // initialisation de la chaine de caractère de binaire en caractère vide
    }
}

/* Procédure d'affichage d'un tableau */

void affTab (Huffman TabAscii[]){
    int i; 
    for (i = 0; i<N; i++){
        printf ("Caractere : %c Occurences : %d Binaire : %s\n", TabAscii[i].c, TabAscii[i].occ, TabAscii[i].bin); // affichage du caractère, de ses occurences, et de son binaire
    }
}

/* Fonction de recherche (qui renvoie une position) */

int recherche (char c, Huffman TabAscii[]){
    int i; 
    for (i = 0; i<N; i++){
        if (TabAscii [i].c == c){ // si le caractère du tableau en position i = au caractère entré en paramètre
            return i; // si le caractère est dans le tableau, on renvoie la position 
        }
    }
    return -1; // si le caractère n'est pas dans le tableau, on renvoie -1
}

/* Fonction Test Fichier  */

void testFichier(FILE* fichier) {
    if(fichier == NULL){ // fichier non existant
        printf("Fichier non ouvert.\n");
        exit(-1);
    }

    char tp;
    
    if(fread(&tp, sizeof(char), 1, fichier) == 0) { // il n'y a aucun caractère dans le fichier 
        printf("Fichier vide.\n");
        exit(1);
    }
}

/* Procédure de création de l'histogramme */

void CreerHistogramme (Huffman TabAscii[], char* fichierChaine){
    FILE* tmp;
    tmp = fopen (fichierChaine, "r"); // ouverture du fichier pour vérifier qu'il n'est pas vide
    testFichier(tmp); 
    fclose(tmp);

    tmp = fopen (fichierChaine, "r"); // ouverture du fichier

    // Déclaration et initialisation de variables
    char tp = '\0'; 
    int i = 0;
    int j = 0;
    
    while (fread (&tp, sizeof(char), 1, tmp) > 0){ // On lit des caractères dans le fichier tant qu'il y en a
        i = recherche (tp, TabAscii); // lancement de la recherche de la position du caractère dans le tableau
        if (i != -1){ // si le caractère est dans le tableau
            TabAscii[i].occ++; // incrémentation de son occurence
        }else{ 
            while (TabAscii[j].c != '\0'){ // recherche de la position du tableau où il faut ajouter le caractère
                j++;
            }
            TabAscii[j].c = tp; // ajout du caractère
            TabAscii[j].occ = 1; // initialisation de l'occurence à 1
            TabAscii[j].bin = '\0'; 
        }
    } 
    fclose(tmp); // fermeture du fichier
}

/* Tri du Tableau dans l'ordre croissant d'occurences - Tri par insertion */

void TriTableauCroiss(Huffman TabAscii[]) {
    int noEtape;
    int decalage;
    Huffman tmp;
    for(noEtape = 1; noEtape<N; noEtape++) {
        tmp = TabAscii[noEtape]; // stockage temporaire
        decalage = noEtape-1; // initialistaion de décalage
        while(decalage>-1 && TabAscii[decalage].occ>tmp.occ) { // recherche de la position
            TabAscii[decalage+1] = TabAscii[decalage]; // décalage des éléments vers la droite
            decalage--;
        }
        TabAscii[decalage+1] = tmp; // intercalage dans le tableau de tmp
    }
}

/* Tri du Tableau dans l'ordre décroissant d'occurences - Tri par insertion */

void TriTableauDecroiss(Huffman TabAscii[]) {
    int noEtape;
    int decalage;
    Huffman tmp;
    for(noEtape = 1; noEtape<N; noEtape++) {
        tmp = TabAscii[noEtape]; // stockage temporaire
        decalage = noEtape-1; // initialistaion de décalage
        while(decalage>-1 && TabAscii[decalage].occ<tmp.occ) { // recherche de la position
            TabAscii[decalage+1] = TabAscii[decalage]; // décalage des éléments vers la droite
            decalage--;
        }
        TabAscii[decalage+1] = tmp; // intercalage dans le tableau de tmp
    }
}