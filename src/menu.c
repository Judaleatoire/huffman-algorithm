/*! \file menu.c
*  \author Chantôme Amandine
*  \author Tourrenc--Lecerf Alexis
*  \author Guillerm Francois
*  \version 1
*  \brief Le programme prend en compte les paramètres entrés par l'utilisateur et exécute l'instruction correspondante.
*/

#include "menu.h"

/* Procédure affichant une aide pour l'utilisateur */

void aide() {
    printf("L'exécutable fonctionne de la manière suivante : bin/main -PARAMETRE FICHIER\n\n");
    printf("Paramètres disponibles :\n");
    printf("\t-c : compression\n");
    printf("\t-d : decompression\n");
    printf("\t-h : aide\n\n");
    printf("FICHIER : chemin du fichier à compresser ou decompresser, doit avoir une extension .txt (faire un glisser/déposer du fichier dans le terminal)\n\n");
}

/* Procédure gérant les paramètres entrés avec l'exécutable */

void menu(int argc, char** argv, Huffman TabAscii[], PArbre liste, PArbre A) {

    // On initialise le tableau
    initialisation_tab (TabAscii);

    int nbParam = argc-1; // On récupère le nombre de paramètres

    // Si un mauvais nombre de paramètres a été entré, on sort du programme
    if(nbParam>2 || nbParam == 0) {
        system("clear");
        printf("Vous n'avez pas entré le bon nombre de paramètres (bin/main -h pour plus d'informations)\n");
        exit(-1);
    }

    if((strrchr(argv[2], '.') == NULL) || strcmp(strrchr(argv[2], '.'), ".txt")) {
        system("clear");
        printf("Vous n'avez pas entré le bon type de fichier (bin/main -h pour plus d'informations)\n");
        exit(-1);
    }

    // On récupère la chaine entrée en paramètre
    char* fichierChaine = malloc(strlen(argv[2]));
    strcpy(fichierChaine, argv[2]);
    size_t taille = strlen(fichierChaine);

    if((nbParam == 1) && (strcmp(argv[1], "-h") == 0)) { // S'il y a seulement un paramètre et qu'il est égal à -h, on affiche une aide pour l'utilisateur
        system("clear");
        aide();
        exit(-1);
    }
    else if(nbParam == 2) {
        if(strcmp(argv[1], "-c") == 0){ // S'il y a exactement 2 paramètres et que le premier est égal à -c, alors on compresse le fichier

            // On manipule les chaines pour pouvoir crée le chemin ainsi que le nom du fichier compressé
            char* fichierCompChaine = malloc(taille + 9);
            strncpy(fichierCompChaine, fichierChaine, taille - 4);
            strcat(fichierCompChaine, "_Comp.txt");

            printf("%s\n", fichierCompChaine);

            FILE* fichierComp = fopen(fichierCompChaine, "wb"); // ouverture du fichier de compression
            init_fichier(fichierComp); // on vérifie que le fichier s'est bien ouvert

            system("clear");
            // On effectue la compression
            CreerHistogramme (TabAscii, fichierChaine);
            TriTableauCroiss(TabAscii);
            compression(TabAscii, liste, A, fichierComp, fichierChaine);

            printf("Compression terminée\n"); // On affiche un message quand la compression est finie

            fclose(fichierComp);
        }
        else if(strcmp(argv[1], "-d") == 0){ // S'il y a exactement 2 paramètres et que le premier est égal à -d, alors on decompresse le fichier

            // On manipule les chaines pour pouvoir crée le chemin ainsi que le nom du fichier décompressé
            char* fichierDecompChaine = malloc(taille + 11);
            strncpy(fichierDecompChaine, fichierChaine, taille - 4);
            strcat(fichierDecompChaine, "_Decomp.txt");

            FILE* fichierComp = fopen(fichierChaine, "rb"); // On ouvre le fichier compressé
            init_fichier(fichierComp); // On vérifie que le fichier s'est bien ouvert

            system("clear");
            // On effectue la decompression
            decompression(TabAscii, liste, A, fichierComp, fichierDecompChaine);

            printf("Decompression terminée\n"); // On affiche un message quand la decompression est finie
            
            fclose(fichierComp);
        }
        else { // Sinon on affiche un message d'erreur
            system("clear");
            printf("Vous n'avez pas entré le bon nombre de paramètres, ou les paramètres sont invalides  (bin/main -h pour plus d'informations)\n");
            exit(-1);
        }
    }
    else { // Sinon on affiche un message d'erreur
        system("clear");
        printf("Vous n'avez pas entré le bon nombre de paramètres, ou les paramètres sont invalides  (bin/main -h pour plus d'informations)\n");
        exit(-1);
    }
}