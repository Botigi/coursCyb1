#include <stdio.h>
#include <stdlib.h>
#include "dictionnaire.h"

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define CYAN    "\x1b[36m"
#define PURPLE  "\x1b[35m"
#define RESET   "\x1b[0m"

void afficher_dico(const dico_t* dico) {
    if (dico == NULL) {
        printf(RED "Dictionnaire NULL\n" RESET);
        return;
    }
    printf(YELLOW "Contenu du dictionnaire (taille = %d) : " RESET, dico->taille);

    if (dico->taille == 0) {
        printf(GREEN "{}\n\n" RESET);
        return;
    }

    printf(PURPLE "{");
    bool premier = true;

    for (int i = 0; i < TAILLE_DICO; i++) {
        node* courant = dico->tableau[i];
        while (courant != NULL) {
            if (!premier) {
                printf("; ");
            }
            printf(CYAN "%s" RESET ": " PURPLE "%s" RESET, courant->cle, courant->valeur);
            premier = false;
            courant = courant->suivant;
        }
    }
    printf(PURPLE "}\n\n" RESET);
}

int main() {
    printf(CYAN "=== TEST DICTIONNAIRE ===\n\n" RESET);

    // 1. Création du dictionnaire
    dico_t* dico = creer_dico();
    if (dico == NULL) {
        printf(RED "Erreur création dictionnaire\n" RESET);
        return 1;
    }
    printf(YELLOW "1. Dictionnaire créé. Taille = %d\n" RESET, taille(dico));
    afficher_dico(dico);

    // 2. Ajout de quelques clés/valeurs
    printf(YELLOW "2. Ajout de clés/valeurs\n" RESET);
    ajouter("pomme", "fruit rouge", dico);
    ajouter("banane", "fruit jaune", dico);
    ajouter("carotte", "légume orange", dico);
    printf(YELLOW "Après ajout, taille = %d\n" RESET, taille(dico));
    afficher_dico(dico);

    // 3. Recherche et affichage des valeurs
    printf(YELLOW "3. Recherche et affichage\n" RESET);
    char* val;

    val = valeur("pomme", dico);
    if (val) {
        printf(GREEN "Valeur pour " CYAN "'pomme'" GREEN " : %s\n" RESET, val);
        free(val);
    }

    val = valeur("banane", dico);
    if (val) {
        printf(GREEN "Valeur pour " CYAN "'banane'" GREEN " : %s\n" RESET, val);
        free(val);
    }

    val = valeur("carotte", dico);
    if (val) {
        printf(GREEN "Valeur pour " CYAN "'carotte'" GREEN " : %s\n\n" RESET, val);
        free(val);
    }

    // 4. Retirer une clé
    printf(YELLOW "4. Suppression de la clé 'banane'\n" RESET);
    char* val_supprimee = retirer("banane", dico);
    if (val_supprimee) {
        printf(GREEN "Valeur retirée pour " CYAN "'banane'" GREEN " : %s\n" RESET, val_supprimee);
        free(val_supprimee);
    }
    printf(YELLOW "Après suppression, taille = %d\n" RESET, taille(dico));
    afficher_dico(dico);

    // 5. Recherche clé supprimée (doit être NULL)
    val = valeur("banane", dico);
    if (val == NULL) {
        printf(RED "'banane' n'existe plus dans le dictionnaire\n\n" RESET);
    } else {
        free(val);
    }

    // 6. Vider le dictionnaire
    printf(YELLOW "6. Vidage du dictionnaire\n" RESET);
    vider_dico(dico);
    printf(YELLOW "Après vidage, taille = %d\n" RESET, taille(dico));
    afficher_dico(dico);

    // 7. Supprimer le dictionnaire
    printf(YELLOW "7. Suppression du dictionnaire\n" RESET);
    supprimer_dico(dico);

    printf(CYAN "=== FIN DU TEST ===\n" RESET);
    return 0;
}
