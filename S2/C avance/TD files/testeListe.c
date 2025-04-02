#include <stdio.h>
#include <string.h>

#include "liste.h"

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