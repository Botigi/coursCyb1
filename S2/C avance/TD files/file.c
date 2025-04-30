
#include <stdlib.h>
#include <string.h>
#include "file.h"

file* creerF(int capacite) {
    return creer(capacite);
}

void supprimerF(file* file) {
    supprimer(file);
}

int tailleF(const file* file) {
    return taille(file);
}

int estVideF(const file* file) {
    return estVide(file);
}

char* tete(const file* file) {
    if (!file || estVideF(file)) return NULL;
    return lire(file, 0);
}

int enfiler(file* file, const char* element) {
    if (!file || !element) return 0;
    return ajouter(file, tailleF(file), element);
}

char* defiler(file* file) {
    if (!file || estVideF(file)) return NULL;
    return retirer(file, 0);
}

void viderF(file* file) {
    vider(file);
}

