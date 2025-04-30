
#include <stdlib.h>
#include <string.h>
#include "liste.h"

// Implémentation avec tableau
#ifndef IMPL_CHAINEE

liste* creer(int capacite) {
    liste* l = malloc(sizeof(liste));
    if (!l) return NULL;
    
    l->taille = 0;
    l->capacite = capacite; // On garde -1 si infini
    // On alloue 100 places initialement même si capacité infinie
    int taille_initiale = (capacite < 0) ? 100 : capacite;
    l->tableau = malloc(taille_initiale * sizeof(char*));
    
    if (!l->tableau) {
        free(l);
        return NULL;
    }
    return l;
}

void supprimer(liste* liste) {
    if (!liste) return;
    
    for (int i = 0; i < liste->taille; i++) {
        free(liste->tableau[i]);
    }
    free(liste->tableau);
    free(liste);
}

void vider(liste* liste) {
    if (!liste) return;
    
    for (int i = 0; i < liste->taille; i++) {
        free(liste->tableau[i]);
    }
    liste->taille = 0;
}

int taille(const liste* liste) {
    return liste ? liste->taille : -1;
}

int estVide(const liste* liste) {
    return liste ? (liste->taille == 0) : 1;
}

char* lire(const liste* liste, int position) {
    if (!liste || position < 0 || position >= liste->taille) 
        return NULL;
    
    char* element = liste->tableau[position];
    if (!element) return NULL;
    
    char* copie = strdup(element);
    return copie;
}

int ajouter(liste* liste, int position, const char* element) {
    if (!liste || !element || position < 0 || position > liste->taille) 
        return 0;
    
    // Si on atteint la capacité physique du tableau
    if (liste->taille >= (liste->capacite < 0 ? 100 : liste->capacite)) {
        // Si la liste est infinie (capacité = -1), on réalloue
        if (liste->capacite < 0) {
            char** nouveau_tableau = realloc(liste->tableau, 
                                          (liste->taille + 100) * sizeof(char*));
            if (!nouveau_tableau) return 0;
            liste->tableau = nouveau_tableau;
        } else {
            // Si capacité finie atteinte, on refuse l'ajout
            return 0;
        }
    }
    
    // Décalage des éléments
    for (int i = liste->taille; i > position; i--) {
        liste->tableau[i] = liste->tableau[i-1];
    }
    
    liste->tableau[position] = strdup(element);
    liste->taille++;
    return 1;
}

char* retirer(liste* liste, int position) {
    if (!liste || position < 0 || position >= liste->taille) 
        return NULL;
    
    char* element = liste->tableau[position];
    
    // Décalage des éléments
    for (int i = position; i < liste->taille - 1; i++) {
        liste->tableau[i] = liste->tableau[i+1];
    }
    
    liste->taille--;
    return element;
}

// Implémentation avec liste chaînée
#else

liste* creer(int capacite) {
    liste* l = malloc(sizeof(liste));
    if (!l) return NULL;
    
    l->taille = 0;
    l->capacite = capacite;
    l->tete = NULL;
    l->queue = NULL;
    return l;
}

void supprimer(liste* liste) {
    if (!liste) return;
    
    maillon* courant = liste->tete;
    while (courant) {
        maillon* suivant = courant->suivant;
        free(courant->element);
        free(courant);
        courant = suivant;
    }
    free(liste);
}

void vider(liste* liste) {
    if (!liste) return;
    
    maillon* courant = liste->tete;
    while (courant) {
        maillon* suivant = courant->suivant;
        free(courant->element);
        free(courant);
        courant = suivant;
    }
    liste->tete = NULL;
    liste->queue = NULL;
    liste->taille = 0;
}

int taille(const liste* liste) {
    return liste ? liste->taille : -1;
}

int estVide(const liste* liste) {
    return liste ? (liste->taille == 0) : 1;
}

char* lire(const liste* liste, int position) {
    if (!liste || position < 0 || position >= liste->taille) 
        return NULL;
    
    maillon* courant = liste->tete;
    for (int i = 0; i < position; i++) {
        courant = courant->suivant;
    }
    
    return strdup(courant->element);
}

int ajouter(liste* liste, int position, const char* element) {
    if (!liste || !element || position < 0 || position > liste->taille) 
        return 0;
    
    if (liste->capacite >= 0 && liste->taille >= liste->capacite) 
        return 0;
    
    maillon* nouveau = malloc(sizeof(maillon));
    if (!nouveau) return 0;
    
    nouveau->element = strdup(element);
    
    if (position == 0) {
        nouveau->suivant = liste->tete;
        liste->tete = nouveau;
        if (!liste->queue) liste->queue = nouveau;
    } else if (position == liste->taille) {
        nouveau->suivant = NULL;
        liste->queue->suivant = nouveau;
        liste->queue = nouveau;
    } else {
        maillon* precedent = liste->tete;
        for (int i = 0; i < position - 1; i++) {
            precedent = precedent->suivant;
        }
        nouveau->suivant = precedent->suivant;
        precedent->suivant = nouveau;
    }
    
    liste->taille++;
    return 1;
}

char* retirer(liste* liste, int position) {
    if (!liste || position < 0 || position >= liste->taille) 
        return NULL;
    
    maillon* aRetirer;
    char* element;
    
    if (position == 0) {
        aRetirer = liste->tete;
        liste->tete = aRetirer->suivant;
        if (liste->taille == 1) liste->queue = NULL;
    } else {
        maillon* precedent = liste->tete;
        for (int i = 0; i < position - 1; i++) {
            precedent = precedent->suivant;
        }
        aRetirer = precedent->suivant;
        precedent->suivant = aRetirer->suivant;
        if (position == liste->taille - 1) liste->queue = precedent;
    }
    
    element = aRetirer->element;
    free(aRetirer);
    liste->taille--;
    
    return element;
}

#endif

int position(const liste* liste, const char* element) {
    if (!liste || !element) return -1;
    
    #ifndef IMPL_CHAINEE
    for (int i = 0; i < liste->taille; i++) {
        if (strcmp(liste->tableau[i], element) == 0) 
            return i;
    }
    #else
    int pos = 0;
    maillon* courant = liste->tete;
    while (courant) {
        if (strcmp(courant->element, element) == 0) 
            return pos;
        courant = courant->suivant;
        pos++;
    }
    #endif
    
    return -1;
}

int contient(const liste* liste, const char* element) {
    return position(liste, element) != -1;
}

