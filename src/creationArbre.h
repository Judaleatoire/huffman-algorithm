#ifndef CREATIONARBRE_H
#define CREATIONARBRE_H

/* On inclut les fichiers headers nécessaires au fonctionnement du programme */

#include "structures.h"
#include "lecture_fichier.h"

/* Prototypage des fonctions */

void AffListe(PArbre liste); // Affichage de la liste
int estFeuille (PArbre a); // Vérification pour savoir si un arbre est une feuille ou non
int estVide (PArbre a); // Vérification pour savoir si un arbre est vide ou non
int existeFilsGauche(PArbre arbre); // Vérification pour savoir si le fils gauche d'un arbre existe
int existeFilsDroit(PArbre arbre); // Vérification pour savoir si le fils droit d'un arbre existe
int SommeLettre(Huffman TabAscii[]); // Calcule la somme des occurrences des lettres présentes dans TabAscii
int longueurListe(PArbre liste); // Calcule la longueur d'une liste
PArbre creerArbre (Huffman e); // Création du noeud d'un arbre
PArbre AjoutListe(PArbre liste, PArbre e); // Ajout d'un élément à une liste
PArbre CreerListe(PArbre liste, Huffman TabAscii[]); // Créer une liste à partir de TabAscii
PArbre CreationArbre(PArbre arbre, PArbre liste); // Créer un arbre à partir d'une liste
char* ajoutChaine(char* c, char x); // Ajouter un caractère à une chaine de caractères dynamique
PArbre binaire(PArbre a, char* bintmp, char x); // Utilise la fonction remplissageBinaire et vérifie si l'arbre est déjà une feuille au début
PArbre remplissageBinaire(PArbre a); // Affecte les nouvelles valeurs binaires aux caractères contenus dans l'arbre
void tabCompression(Huffman TabAscii[], PArbre a); // Utilise la fonction parcoursTabCompression après avoir réinitialisé TabAscii
void parcoursTabCompression(Huffman TabAscii[], PArbre a, int* i); // Permet d'assigner la nouvelle valeur binaire des caractères de TabAscii
void Traiter (PArbre a); // Affiche le contenu du noeud d'un arbre
void ParcoursPrefix (PArbre a); // Parcours Prefix d'un arbre

#endif