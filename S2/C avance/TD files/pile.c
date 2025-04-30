
#include <stdlib.h>
#include <string.h>
#include "pile.h"

pile* creerP(int capacite) {
    return creer(capacite);
}

void supprimerP(pile* pile) {
    supprimer(pile);
}

int tailleP(const pile* pile) {
    return taille(pile);
}

int estVideP(const pile* pile) {
    return estVide(pile);
}

char* sommet(const pile* pile) {
    if (!pile || estVideP(pile)) return NULL;
    #ifdef IMPL_CHAINEE
        return lire(pile, 0);  // Lire en tête pour la version chaînée
    #else
        return lire(pile, tailleP(pile) - 1);  // Lire en queue pour la version tableau
    #endif
}

int empiler(pile* pile, const char* element) {
    if (!pile || !element) return 0;
    #ifdef IMPL_CHAINEE
        return ajouter(pile, 0, element);  // Ajouter en tête pour la version chaînée
    #else
        return ajouter(pile, tailleP(pile), element);  // Ajouter en queue pour la version tableau
    #endif
}

char* depiler(pile* pile) {
    if (!pile || estVideP(pile)) return NULL;
    #ifdef IMPL_CHAINEE
        return retirer(pile, 0);  // Retirer en tête pour la version chaînée
    #else
        return retirer(pile, tailleP(pile) - 1);  // Retirer en queue pour la version tableau
    #endif
}

void viderP(pile* pile) {
    vider(pile);
}

