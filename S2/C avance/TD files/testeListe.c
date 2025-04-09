#include <stdio.h>
#include <string.h>
#include <stddef.h>

#include "liste.h"

liste* creer(int capacite)
{
    if (capacite < 0) {
        int capacite_effective = 100;  // valeur par défaut
    }
    int capacite_effective = capacite;
    // attention au cas ou capacite = -1 alors on alloue 100 et on realoura plus tard si la limite est atteinte
    liste* liste = malloc(sizeof(liste));
    if ( liste == NULL ) {
        return NULL;
    }
    #ifndef IMPL_CHAINEE
    
    liste->capacite = capacite;
    liste->tableau = malloc(sizeof(char*) * capacite_effective);

    #else
    liste->tete = NULL;
    liste->queue = NULL;
    #endif
    liste->taille = 0;
    if ( liste == NULL ) {
        return NULL;
    }
    return liste;
}

void supprimer(liste* liste)
{
    #ifndef IMPL_CHAINEE
    for (int i = 0; i < liste->taille; i++) {
        free(liste->tableau[i]);
    }
    free(liste->tableau);
    #endif
    free(liste);
}

int taille(const liste* liste)  // independante de chainee ou tableau
{
    if ( liste == NULL ) {
        return -1;
    }
    return liste->taille;
}

int estVide(const liste* liste) // independante de chainee ou tableau
{
    if ( liste == NULL ) {
        return 0;
    }
    return liste->taille == 0;
}

char* lire(const liste* liste, int position) 
{
    if ( liste == NULL ) {
        return NULL;
    }
    if (position < 0 || position >= liste->taille) {
        return NULL;
    }
    #ifndef IMPL_CHAINEE
    
    return liste->tableau[position];
    
    #endif
    maillon* maillon = liste->tete;
    while (position > 0) {
        maillon = maillon->suivant;
        position --;
    }
    return maillon->element;
}

int ajouter(liste* liste, int position, const char* element)
{
    if (liste == NULL || element == NULL) {
        return 0;
    }
    // gerer le cas ou la capacite est negative i.e. infinie
    #ifndef IMPL_CHAINEE
    if (liste->capacite < 0 && liste->taille % 100 == 0) {
        liste->tableau = realloc(liste->tableau, sizeof(char*) * 100);
    }
    #endif
    if (liste->taille == liste->capacite) {
        return 0;
    }
    if (position < 0) {
        position = liste->taille;  // ajout en fin de liste par défaut
    }
    if (position > liste->taille) {
        position = liste->taille;
    }
    #ifndef IMPL_CHAINEE
    for (int i = liste->taille; i > position; i--) {
        liste->tableau[i] = liste->tableau[i - 1];
    }
    liste->tableau[position] = strdup(element);
    #endif
    
    while (position > 1 ) {
        liste->tete = liste->tete->suivant;
        position --;
    }
    
    maillon* nouveau = malloc(sizeof(maillon));
    if (nouveau == NULL) {
        return 0;
    }
    liste->tete->suivant = nouveau;
    nouveau->element = strdup(element);
    nouveau->suivant = liste->tete->suivant;
    liste->taille += 1;
    return 1;
}

char* retirer(liste* liste, int position)
{
    if (liste->taille == 0) {
        return NULL;
    }
    if (position < 0 || position >= liste->taille) {
        return NULL;
    }
    #ifndef IMPL_CHAINEE
    char* element = liste->tableau[position];
    for (int i = position; i < liste->taille - 1; i++) {
        liste->tableau[i] = liste->tableau[i + 1];
    }
    #endif
    while (position > 1) { 
        liste->tete = liste->tete->suivant;
        position --;
    }
    liset->tete->suivant = liste->tete->suivant->suivant;

    liste->taille -= 1;
    return element;
}

// retourne une chaine representant la liste donnée
char* enChaine(const liste* liste) {
    
    int t = taille(liste);
    if (t == 0) {
        return strdup("[]");
    }

    char chaine[4096];
    int l = sprintf(chaine, "[");
    for (int i = 0; i < t - 1; i++) {
        char* element = lire(liste, i);
        if (l + strlen(element) + 8 >= sizeof(chaine)) {
            sprintf(chaine + l, "...]");
            return strdup(chaine);
        }
        l += sprintf(chaine + l, "\"%s\", ", element);
    }

    sprintf(chaine + l, "\"%s\"]", lire(liste, t - 1));
    return strdup(chaine);
}

//
// Usage : testListe [arguments]* [-]
//
// Ajoute les arguments de lancement à une liste, en queue (défaut) ou en tête (si - final), 
// affiche la liste, puis retire ses éléments un à un.
//
// Exerce les fonctions essentielles du service de gestion de listes : 
// - creer(), supprimer()
// - taille(), lire()
// - ajouter(), retirer()
//
int main(int argc, const char* argv[]) {

    // ajouter en queue ou en tête ?
    int ou = -1;
    if (strcmp(argv[argc - 1], "-") == 0) {
        ou = 0;
        argc -= 1;
    }

    // ajoute les arguments dans une liste
    liste* liste = creer(1024);
    printf("creer(...) = %p\n", liste);
    for (int i = 1; i < argc; i++) {
        printf("ajouter(...) = %d\n", ajouter(liste, ou, argv[i]));
    }

    // affiche la liste et sa taille
    printf("arguments : (%d) %s\n", taille(liste), enChaine(liste));

    // vide la liste élément par élément par la tête
    while (taille(liste) != 0) {
        printf("retirer(...) = %s\n", retirer(liste, 0));
    }

    // fin d'utilisation
    printf("supprimer(...)\n");
    supprimer(liste);
    printf("terminé\n");
}
