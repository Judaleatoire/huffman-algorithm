/*! \file compression.c
*  \author Chantôme Amandine
*  \author Tourrenc--Lecerf Alexis
*  \author Guillerm Francois
*  \version 1
*  \brief Ce fichier rassemble les fonctions nécessaires à la compression du fichier, on écrit tout d'abord l'entête puis le texte compressé dans un nouveau fichier.
*/

#include "compression.h"

/* Procédure d'écriture des valeurs binaires dans le fichier */

void ecritureBinaire (Huffman TabAscii[], FILE* fichierComp, char* fichierChaine){
    FILE* fichier = fopen (fichierChaine, "r"); // ouverture du fichier de lecture
    if(fichier == NULL){
        printf("Fichier non ouvert.");
        exit(-1);
    }

    char c = '\0'; // caractère à lire
    unsigned char tmp = 0; // le caractère à écrire
    int fill = 0;
    int i = 0;
    int index = 0; // position dans le tableau
    char* bin; // valeur binaire du tableau en position index
    int taille = 0; // taille de la chaine bin

    while (fread (&c, sizeof(char), 1, fichier) > 0){ // tant qu'on peut lire un caractère dans le fichier
        index = recherche(c, TabAscii); // recherche de la position du caractère dans le tableau
        bin = TabAscii[index].bin; // on stocke la valeur binaire
        taille = strlen(bin); // on récupère la taille de la valeur binaire

        for(i = 0; i<taille; i++) {
            tmp *=2; // on fait rentrer les valeurs dans notre caractère par la droite 
            if(bin[i] == '1') { // si la valeur binaire en position i est égale à 1
                tmp += 1; // le binaire prend +1 
            } // sinon il prend par défaut 0
            fill++; // incrémentation du fill
            if(fill == 8) { // s'il on a lu 8 bits
                fputc(tmp, fichierComp); // on écrit dans le nouveau fichier le caractère tmp
                fill = 0; // remise à 0 de fill
                tmp = 0; // remise à 0 de tmp
            }
        }
    }

    if(fill != 0) { // si fill n'est pas égal à 0
        taille = strlen(bin);
        for(i = 0; i<8-fill; i++){
            tmp *= 2; // on fait rentrer les valeurs dans notre caractère par la dorite
        }        
        fputc(tmp, fichierComp); // on écrit dans le nouveau fichier le caractère tmp 
    }

    fclose(fichier); // fermeture du fichier
}

/* Fonction d'écriture en entête */

void ecritureEntete(Huffman TabAscii[], FILE* fichierComp) {

    int i = 0;
    int nb = nbCarCode(TabAscii); // on récupère le nombre de caractère unique du texte d'origine
    
    fwrite(&nb, sizeof(int), 1, fichierComp); // ecriture du nombre de caractère unique en entête 
    while(TabAscii[i].occ == 0) { // tant que les occurrences sont nulle
        i++; // on avance dans le tableau
    }
    for(int j = i; j<N; j++) { // on a trouvé la position où les occurrences sont non-nulles donc on parcourt le tableau 
        fwrite(&TabAscii[j].c, sizeof(char), 1, fichierComp); // on écrit les caractères
        fwrite(&TabAscii[j].occ, sizeof(int), 1, fichierComp); // on écrit les occurrences des caractères correspondants
    }
}

/* Fonction nombre de caractère codé */

int nbCarCode(Huffman TabAscii[]) {
    int i = 0;
    while(TabAscii[i].occ == 0) { // tant que les occurrences sont nulles
        i++; // on avance dans le tableau
    }
    return N-i; // on retourne le nombre total - la position où les occurrences sont non-nulles
}

/* Procédure de compression */

void compression(Huffman TabAscii[], PArbre liste, PArbre A, FILE* fichierComp, char* fichierChaine) {
    ecritureEntete(TabAscii, fichierComp); // écriture en entête avec le tableau trié en ordre croissant

    liste = CreerListe(liste, TabAscii); // création de la liste qui sert à créer l'arbre
    A = CreationArbre(A, liste); // création de l'abre
    A = remplissageBinaire(A); // remplissage des valeurs binaires dans l'arbre

    tabCompression(TabAscii, A); // recréation du tableau avec les valeurs binaires
    TriTableauCroiss(TabAscii); // tri du nouveau tableau en ordre croissant

    TriTableauDecroiss(TabAscii); // tri du nouveau tableau en ordre décroissant
    ecritureBinaire(TabAscii, fichierComp, fichierChaine); // écriture binaire avec le tableau trié en ordre décroissant
}