/*! \file creationArbre.c
*  \author Chantôme Amandine
*  \author Tourrenc--Lecerf Alexis
*  \author Guillerm Francois
*  \version 1
*  \brief Ce fichier rassemble les fonctions nécessaires à la création de l'arbre, et à l'assignation des nouvelles valeurs binaires des caractères.
*/

#include "creationArbre.h"

/* Procédure d'affichage de la liste */

void AffListe(PArbre liste) {
    if(liste == NULL) { // liste vide
        printf("La liste est vide\n");
    }
    else{
        while(liste){ 
            printf("caractère : %c occurrences : %d\n", liste->elmt.c, liste->elmt.occ); // affichage du caractère et de l'occurrence
            liste = liste->suiv; // on avance dans la liste
        }
    }
    puts(""); 
}

/* Fonction est feuille */

int estFeuille (PArbre a){
    if ((a->fg == NULL) && (a->fd == NULL)){ // s'il n'existe pas de fils droit et de fils gauche
        return TRUE; // return 1
    }
    return FALSE; // return 0
}

/* Fonction est vide  */

int estVide (PArbre a){
    if (a == NULL){ // si l'arbre est vide
        return TRUE; // return 1
    }
    return FALSE; // return 0
}

/* Fonction existe fils gauche */

int existeFilsGauche(PArbre arbre) {
    if(!arbre->fg || estVide(arbre)) return FALSE; // s'il n'existe pas de fils gauche ou que l'arbre est vide return 0
    else return TRUE; // sinon return 1
}

/* Fonction existe fils droit */

int existeFilsDroit(PArbre arbre) {
    if(!arbre->fd || estVide(arbre)) return FALSE; // s'il n'existe pas de fils droit ou que l'arbre est vide return 0
    else return TRUE; // sinon return 1
}

/* Fonction somme lettre (qui permet de faire la somme des occurrences pour créer l'arbre) */

int SommeLettre(Huffman TabAscii[]) {
    int somme = 0;
    for(int i = 0; i<N; i++) {
        somme += TabAscii[i].occ; // ajout des occurrences
    }
    return somme; // on retourne la somme
}

/* Fonction pour calculer la longueur de la liste */

int longueurListe(PArbre liste) {
    PArbre p = liste; 
    int l = 0;
    while(p) { // tant que la liste n'est pas vide
        l++; // incrémentation
        p = p->suiv; // on avance dans la liste 
    }
    return l; // on retourne la valeur de l incrémentée qui correspond à la longueur
}

/* Fonction créer arbre */

PArbre creerArbre (Huffman e){
    PArbre ptr = (Arbre*) malloc(sizeof(Arbre)); // allocation mémoire de ptr
    if(!ptr) { // Arbre vide 
        printf("ERREUR ALLOCATION ARBRE");
        exit(1);
    }
    ptr->fd = NULL; // pas de fils droit
    ptr->fg = NULL; // pas de fils gauche
    ptr->suiv = NULL; // pas de suivant
    ptr->elmt = e; // l'élément de l'arbre est e 
    return ptr;
}

/* Fonction ajout liste dans l'ordre croissant d'occurrences */

PArbre AjoutListe(PArbre liste, PArbre e) {
    PArbre ptr = e; 
    PArbre p = liste;
    if(!p) return ptr; // si la liste est vide on renvoie juste l'arbre
    if(p->elmt.occ > ptr->elmt.occ) { // si l'élément à ajouter a un nombre d'occurrences plus petit que celui du premier élément de la liste 
        ptr->suiv = p;
        return ptr;
    }
    while((p->suiv) && (p->suiv->elmt.occ < ptr->elmt.occ)) { // recherche de la position où il faut insérer l'élément
        p = p->suiv; // on avance dans la liste 
    }
    ptr->suiv = p->suiv; // on insère l'élément
    p->suiv = ptr;
    return liste; // on renvoie la nouvelle liste
}

/* Fonction créer liste */

PArbre CreerListe(PArbre liste, Huffman TabAscii[]) {
    if(SommeLettre(TabAscii) == 0) return NULL; // si la somme = 0 on renvoie NULL
    int i = 0;
    int j = 0;
    while(TabAscii[i].occ == 0) i++; // Recherche de la position dans le tableau à partir de laquelle on crée la liste 
    for(j=i; j<N; j++) {
        liste = AjoutListe(liste, creerArbre(TabAscii[j])); // ajout dans la liste
    }
    return liste; // On renvoie la liste
}

/* Fonction création arbre */

PArbre CreationArbre(PArbre arbre, PArbre liste) {
    Huffman e; // élément à insérer
    e.c = '\0'; // initialisation de l'élément
    e.occ = 0; 
    e.bin = '\0';
    PArbre tmp = NULL;
    PArbre premier = NULL;
    PArbre deuxieme = NULL;
    if(!liste) return NULL;
    while((liste) && (liste->suiv)) { // tant que la tête de liste et le suivant de la tête de liste existent
        tmp = creerArbre(e); // création de l'arbre en e
        premier = liste; // premier pointe sur le premier élément de la liste
        deuxieme = liste->suiv; // deuxième pointe sur le deuxième élément de la liste
        liste = (liste->suiv)->suiv; // on avance de 2 dans la liste
        premier->suiv = NULL; // on ne sélectionne que le premier noeud de la liste
        deuxieme->suiv = NULL;// on ne sélectionne que le deuxième noeud de la liste
        tmp->fg = premier; // le premier element de la liste devient le fils gauche du sous arbre
        tmp->fd = deuxieme; // le premier element de la liste devient le fils droit du sous arbre
        tmp->elmt.c = '\0'; // les noeuds internes n'ont pas de caractère
        tmp->elmt.occ = tmp->fg->elmt.occ + tmp->fd->elmt.occ; // les noeuds internes ont la somme des occurences
        tmp->elmt.bin = '\0'; // les noeuds internes n'ont pas de valeur binaire
        liste = AjoutListe(liste, tmp); // ajout du sous arbre dans la liste 
    }
    return liste;
}

/* Fonction ajout chaine */

char* ajoutChaine(char* c, char x){
    char* tmp = NULL;
    if(!c) { // si la chaine c ne pointe sur rien
        tmp = malloc(sizeof(char));
        if(!tmp) {
            printf("ERREUR ALLOCATION MEMOIRE");
            exit(1);
        }
        tmp[0] = x; // ajout d'un caractère dans la chaine en première position
        tmp[1] = '\0'; // ajout du caractère vide dans la chaine en deuxième position
    }
    else {
        size_t taille = strlen(c); // on calcule la taille de c
        tmp = malloc(taille + 2); 
        if(!tmp) {
            printf("ERREUR ALLOCATION MEMOIRE");
            exit(1);
        }
        strcpy(tmp, c); // on copie une chaine dans une autre
        tmp[taille] = x; // ajout d'un caractère dans la chaine en postion taille
        tmp[taille + 1] = '\0'; // ajout du caractère vide dans la chaine en position taille+1
    }
    return tmp;
}

/* Fonction affectation des valeurs binaires */

PArbre binaire(PArbre a, char* bintmp, char x) {
    if(x == '0' || x == '1') { 
        bintmp = ajoutChaine(bintmp, x); // ajout dans la chaine de caractère binaire
    }
    if(estFeuille(a)){ // si c'est une feuille
        size_t taille = strlen(bintmp); // taille de la chaine bintmp
        a->elmt.bin = malloc(taille); // allocation de la valeur binaire
        if(!a->elmt.bin) {
            printf("ERREUR ALLOCATION MEMOIRE");
            exit(1);
        }        
        strcpy(a->elmt.bin, bintmp); // copie de la chaine bintmp dans le noeud dans lequel on se trouve, qui est don une feuille
        return a;
    }
    if(existeFilsGauche(a)) a->fg = binaire(a->fg, bintmp, '0'); // existe fils gauche => on part à gauche, en ajoutant un 0 à la chaine
    if(existeFilsDroit(a)) a->fd = binaire(a->fd, bintmp, '1'); // existe fils droit => on part à droite, en ajoutant un 1 à la chaine
    return a;
}

/* Fonction remplissage binaire */

PArbre remplissageBinaire(PArbre a) {
    if(estFeuille(a)) { // si c'est une feuille
        a->elmt.bin = malloc(sizeof(char)); // allocation mémoire
        if(!a->elmt.bin) {
            printf("ERREUR ALLOCATION MEMOIRE");
            exit(1);
        }        
        a->elmt.bin[0] = '0'; // premier élément initialisé à 0
    }
    else {
        char* bintmp = NULL;
        a = binaire(a, bintmp, '2');
    }
    return a;
}

/* Fonction de création du tableau de compression */

void tabCompression(Huffman TabAscii[], PArbre a) {
    int i = 0;
    initialisation_tab(TabAscii); // réinitialisation du tableau
    parcoursTabCompression(TabAscii, a, &i);
}

/* Fonction du parcours de l'arbre pour recréer le tableau de caractère, avec les nouvelles valeurs binaires */

void parcoursTabCompression(Huffman TabAscii[], PArbre a, int* i) {
    if(a) {
        if(estFeuille(a)) { // si c'est une feuille, on ajoute le contenu de la feuille dans le tableau
            TabAscii[*i] = a->elmt; 
            *i = *i + 1;
        }
        // sinon, on continue de parcourir le tableau
        parcoursTabCompression(TabAscii, a->fg, i);
        parcoursTabCompression(TabAscii, a->fd, i);
    }
}

/* Procédure traiter */

void Traiter (PArbre a){
    //On affiche l'emplacement du pointeur, son caractère ainsi que son nombre d'occurrence associés
    printf ("caractere : %c occurences : %d ", a->elmt.c, a->elmt.occ); 
    //On affiche aussi la nouvelle valeur binaire du caractère seulement si elle existe
    if(!a->elmt.bin) printf("La chaine est vide\n");
    else printf("%s\n", a->elmt.bin);
}

/* Procédure de parcours de l'arbre */

void ParcoursPrefix (PArbre a){
    // On vérifie d'abord si le pointeur entré en paramètre est égal à NULL ou non
    if (!(estVide(a) == 1)){
        // S'il n'est pas égal à NULL, on traite son contenu
        Traiter (a);
        // Puis on fait un appel récursif sur son fils gauche et son fils droit
        ParcoursPrefix (a->fg);
        ParcoursPrefix (a->fd);
    }
}