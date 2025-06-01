#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dictionnaire.h"

#define ANSI_COLOR_GREEN  "\x1b[32m"
#define ANSI_COLOR_RED    "\x1b[31m"
#define ANSI_RESET        "\x1b[0m"

void test_simple(void) {
    printf("\n=== Test simple des fonctionnalités ===\n");
    
    struct dictionnaire* dict = creer(10);
    printf("creer(10) = %p\n", (void*)dict);
    
    // Test d'ajout
    printf("\nTest d'ajout :\n");
    printf("ajouter('cle1', 'valeur1') = %d\n", ajouter(dict, "cle1", "valeur1"));
    printf("ajouter('cle2', 'valeur2') = %d\n", ajouter(dict, "cle2", "valeur2"));
    printf("taille() = %d\n", taille(dict));
    
    // Test de consultation
    printf("\nTest de consultation :\n");
    printf("valeur('cle1') = %s\n", valeur(dict, "cle1"));
    printf("valeur('cle2') = %s\n", valeur(dict, "cle2"));
    printf("valeur('inexistant') = %s\n", valeur(dict, "inexistant"));
    
    // Test de mise à jour
    printf("\nTest de mise à jour :\n");
    printf("ajouter('cle1', 'nouvelle_valeur') = %d\n", ajouter(dict, "cle1", "nouvelle_valeur"));
    printf("valeur('cle1') = %s\n", valeur(dict, "cle1"));
    
    // Test de suppression
    printf("\nTest de suppression :\n");
    printf("retirer('cle1') = %s\n", retirer(dict, "cle1"));
    printf("taille() = %d\n", taille(dict));
    printf("valeur('cle1') = %s\n", valeur(dict, "cle1"));
    
    supprimer(dict);
    printf("\nDictionnaire supprimé\n");
}

void test_performance(int nb_operations) {
    printf("\n=== Test de performance (%d opérations) ===\n", nb_operations);
    
    struct dictionnaire* dict = creer(nb_operations);
    clock_t debut, fin;
    double temps;
    char cle[20], valeur[20];
    
    // Test des ajouts
    debut = clock();
    for (int i = 0; i < nb_operations; i++) {
        sprintf(cle, "cle%d", i);
        sprintf(valeur, "valeur%d", i);
        if (!ajouter(dict, cle, valeur)) {
            printf(ANSI_COLOR_RED "Erreur lors de l'ajout à l'itération %d\n" ANSI_RESET, i);
            break;
        }
    }
    fin = clock();
    temps = ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000.0;
    printf("Temps pour %d ajouts : %.2f µs (%.2f µs/op)\n", 
           nb_operations, temps, temps/nb_operations);
    
    // Test des consultations
    debut = clock();
    for (int i = 0; i < nb_operations; i++) {
        sprintf(cle, "cle%d", i);
        if (!valeur(dict, cle)) {
            printf(ANSI_COLOR_RED "Erreur lors de la consultation à l'itération %d\n" ANSI_RESET, i);
            break;
        }
    }
    fin = clock();
    temps = ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000.0;
    printf("Temps pour %d consultations : %.2f µs (%.2f µs/op)\n", 
           nb_operations, temps, temps/nb_operations);
    
    // Test des suppressions
    debut = clock();
    for (int i = 0; i < nb_operations; i++) {
        sprintf(cle, "cle%d", i);
        if (!retirer(dict, cle)) {
            printf(ANSI_COLOR_RED "Erreur lors de la suppression à l'itération %d\n" ANSI_RESET, i);
            break;
        }
    }
    fin = clock();
    temps = ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000.0;
    printf("Temps pour %d suppressions : %.2f µs (%.2f µs/op)\n", 
           nb_operations, temps, temps/nb_operations);
    
    supprimer(dict);
}

void test_collisions(void) {
    printf("\n=== Test des collisions ===\n");
    
    struct dictionnaire* dict = creer(1); // Petite taille pour forcer les collisions
    
    // Ajout de plusieurs éléments qui devraient créer des collisions
    printf("Ajout de plusieurs éléments :\n");
    for (int i = 0; i < 5; i++) {
        char cle[20], valeur[20];
        sprintf(cle, "collision%d", i);
        sprintf(valeur, "valeur%d", i);
        printf("ajouter('%s', '%s') = %d\n", cle, valeur, ajouter(dict, cle, valeur));
    }
    
    printf("\nConsultation des éléments :\n");
    for (int i = 0; i < 5; i++) {
        char cle[20];
        sprintf(cle, "collision%d", i);
        printf("valeur('%s') = %s\n", cle, valeur(dict, cle));
    }
    
    supprimer(dict);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <type_test> [nb_operations]\n", argv[0]);
        printf("type_test: 'simple', 'performance' ou 'collisions'\n");
        return 1;
    }
    
    if (strcmp(argv[1], "simple") == 0) {
        test_simple();
    }
    else if (strcmp(argv[1], "performance") == 0) {
        if (argc < 3) {
            printf("Erreur: nombre d'opérations requis pour le test de performance\n");
            return 1;
        }
        test_performance(atoi(argv[2]));
    }
    else if (strcmp(argv[1], "collisions") == 0) {
        test_collisions();
    }
    else {
        printf("Type de test invalide. Utilisez 'simple', 'performance' ou 'collisions'\n");
        return 1;
    }
    
    return 0;
}