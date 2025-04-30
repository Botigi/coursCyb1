#ifndef LISTE_H
#define LISTE_H

#include <stdlib.h>

// Structure d'un maillon pour l'implémentation chaînée
#ifdef IMPL_CHAINEE
typedef struct maillon {
    char* element;
    struct maillon* suivant;
} maillon;
#endif

// Structure principale de la liste
typedef struct {
    int taille;
    int capacite;
    #ifndef IMPL_CHAINEE
    char** tableau;  // Implémentation tableau
    #else
    maillon* tete;   // Implémentation chaînée
    maillon* queue;
    #endif
} liste;

// Prototypes des fonctions
liste* creer(int capacite);
void supprimer(liste* liste);
void vider(liste* liste);  // Ajout du prototype de vider
int taille(const liste* liste);
int estVide(const liste* liste);
char* lire(const liste* liste, int position);
int ajouter(liste* liste, int position, const char* element);
char* retirer(liste* liste, int position);
int position(const liste* liste, const char* element);
int contient(const liste* liste, const char* element);
char* enChaine(const liste* liste);

#endif // LISTE_H
