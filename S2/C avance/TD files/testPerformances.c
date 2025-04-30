
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "liste.h"  // Ajout de l'include pour liste.h
#include "pile.h"
#include "file.h"

#define ANSI_COLOR_1 "\x1b[38;2;0;255;0m"    // Vert vif
#define ANSI_COLOR_2 "\x1b[38;2;150;255;0m"  // Vert-jaune
#define ANSI_COLOR_3 "\x1b[38;2;255;150;0m"  // Orange
#define ANSI_COLOR_4 "\x1b[38;2;255;0;0m"    // Rouge
#define ANSI_RESET   "\x1b[0m"
#define ANSI_BOLD    "\x1b[1m"

typedef struct {
    double temps;
    const char* implementation;
    const char* structure;
} ResultatTest;

void afficher_temps_colore(double temps, ResultatTest* resultats, int nb_resultats) {
    // Trouver la position (1er = plus rapide, dernier = plus lent)
    int position = 1;
    for (int i = 0; i < nb_resultats; i++) {
        if (resultats[i].temps < temps) position++;
    }
    
    // Choisir la couleur en fonction de la position
    const char* couleur;
    switch(position) {
        case 1: couleur = ANSI_COLOR_1; break;
        case 2: couleur = ANSI_COLOR_2; break;
        case 3: couleur = ANSI_COLOR_3; break;
        default: couleur = ANSI_COLOR_4; break;
    }
    
    printf("│ %s%8.2f µs%s ", couleur, temps, ANSI_RESET);
}

void afficher_tableau_resultats(const char* titre, double temps_op1, double temps_op2, 
                              const char* op1_name, const char* op2_name) {
    printf("\n%s :\n", titre);
    printf("┌────────────┬──────────────┐\n");
    printf("│ Opération  │    Temps     │\n");
    printf("├────────────┼──────────────┤\n");
    printf("│ %-10s │ %10.2f µs │\n", op1_name, temps_op1);
    printf("│ %-10s │ %10.2f µs │\n", op2_name, temps_op2);
    printf("└────────────┴──────────────┘\n");
}

void afficher_resultats_detailles(const char* structure, const char* implementation,
                                double temps_insertion, double temps_suppression,
                                int nb_operations) {
    double temps_total = temps_insertion + temps_suppression;
    double temps_par_op = temps_total / (2.0 * nb_operations);
    
    printf("\n%s (%s):\n", structure, implementation);
    printf("┌────────────┬──────────────┐\n");
    printf("│ Métrique   │    Valeur    │\n");
    printf("├────────────┼──────────────┤\n");
    printf("│ Insertion  │ %10.2f µs │\n", temps_insertion);
    printf("│ Suppression│ %10.2f µs │\n", temps_suppression);
    printf("│ Total      │ %10.2f µs │\n", temps_total);
    printf("│ Par op     │ %10.2f µs │\n", temps_par_op);
    printf("└────────────┴──────────────┘\n");
}

// Usage: ./testPerformances <type> <nb_operations>
// type: "pile" ou "file"
// nb_operations: nombre d'opérations à effectuer

void test_pile(int nb_operations) {
    printf("\n=== Test PILE ===\n");
    #ifdef IMPL_CHAINEE
    printf("Implementation: Liste chainée\n");
    #else
    printf("Implementation: Tableau\n");
    #endif

    pile* p = creerP(nb_operations);
    if (p == NULL) {
        printf("Erreur: Impossible de créer la pile\n");
        return;
    }

    clock_t debut, fin;
    double temps;

    // Test empiler
    debut = clock();
    for (int i = 0; i < nb_operations; i++) {
        if (!empiler(p, "test")) {
            printf("Erreur lors de l'empilage à l'itération %d\n", i);
            break;
        }
    }
    fin = clock();
    temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    printf("Empiler %d éléments: %f secondes (%.2f µs/op)\n", 
           nb_operations, temps, (temps * 1000000.0) / nb_operations);

    // Test depiler
    debut = clock();
    for (int i = 0; i < nb_operations; i++) {
        char* val = depiler(p);
        if (val != NULL) {
            free(val);
        } else {
            printf("Erreur lors du dépilage à l'itération %d\n", i);
            break;
        }
    }
    fin = clock();
    temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    printf("Dépiler %d éléments: %f secondes (%.2f µs/op)\n", 
           nb_operations, temps, (temps * 1000000.0) / nb_operations);

    supprimerP(p);
}

void test_file(int nb_operations) {
    printf("\n=== Test FILE ===\n");
    #ifdef IMPL_CHAINEE
    printf("Implementation: Liste chainée\n");
    #else
    printf("Implementation: Tableau\n");
    #endif

    file* f = creerF(nb_operations);
    if (f == NULL) {
        printf("Erreur: Impossible de créer la file\n");
        return;
    }

    clock_t debut, fin;
    double temps;

    // Test enfiler
    debut = clock();
    for (int i = 0; i < nb_operations; i++) {
        if (!enfiler(f, "test")) {
            printf("Erreur lors de l'enfilage à l'itération %d\n", i);
            break;
        }
    }
    fin = clock();
    temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    printf("Enfiler %d éléments: %f secondes (%.2f µs/op)\n", 
           nb_operations, temps, (temps * 1000000.0) / nb_operations);

    // Test defiler
    debut = clock();
    for (int i = 0; i < nb_operations; i++) {
        char* val = defiler(f);
        if (val != NULL) {
            free(val);
        } else {
            printf("Erreur lors du défilage à l'itération %d\n", i);
            break;
        }
    }
    fin = clock();
    temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    printf("Défiler %d éléments: %f secondes (%.2f µs/op)\n", 
           nb_operations, temps, (temps * 1000000.0) / nb_operations);

    supprimerF(f);
}

void test_comparatif(int nb_operations) {
    clock_t debut, fin;
    double temps_empiler, temps_depiler, temps_enfiler, temps_defiler;
    
    printf("\n=== Test COMPARATIF ===\n");
    printf("Nombre d'opérations: %d\n", nb_operations);
    
    #ifdef IMPL_CHAINEE
    const char* implementation = "Liste chaînée";
    #else
    const char* implementation = "Tableau";
    #endif

    // Test PILE
    pile* p = creerP(nb_operations);
    if (p) {
        // Test empiler
        debut = clock();
        for (int i = 0; i < nb_operations; i++) {
            empiler(p, "test");
        }
        fin = clock();
        temps_empiler = ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000.0;

        // Test depiler
        debut = clock();
        for (int i = 0; i < nb_operations; i++) {
            char* val = depiler(p);
            if (val) free(val);
        }
        fin = clock();
        temps_depiler = ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000.0;
        
        supprimerP(p);
    }

    // Test FILE
    file* f = creerF(nb_operations);
    if (f) {
        // Test enfiler
        debut = clock();
        for (int i = 0; i < nb_operations; i++) {
            enfiler(f, "test");
        }
        fin = clock();
        temps_enfiler = ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000.0;

        // Test defiler
        debut = clock();
        for (int i = 0; i < nb_operations; i++) {
            char* val = defiler(f);
            if (val) free(val);
        }
        fin = clock();
        temps_defiler = ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000000.0;
        
        supprimerF(f);
    }

    // Affichage des résultats
    afficher_resultats_detailles("PILE", implementation, 
                                temps_empiler, temps_depiler, 
                                nb_operations);
    
    afficher_resultats_detailles("FILE", implementation, 
                                temps_enfiler, temps_defiler, 
                                nb_operations);

    // Résumé global
    printf("\nRésumé global (%s):\n", implementation);
    double temps_total_pile = temps_empiler + temps_depiler;
    double temps_total_file = temps_enfiler + temps_defiler;
    printf("- Pile : %.2f µs total, %.2f µs/opération\n", 
           temps_total_pile, temps_total_pile/(2.0*nb_operations));
    printf("- File : %.2f µs total, %.2f µs/opération\n", 
           temps_total_file, temps_total_file/(2.0*nb_operations));
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <type> <nb_operations>\n", argv[0]);
        printf("type: 'pile', 'file', 'tous' ou 'compare'\n");
        return 1;
    }

    int nb_operations = atoi(argv[2]);
    if (nb_operations <= 0) {
        printf("Le nombre d'opérations doit être positif\n");
        return 1;
    }

    printf("Nombre d'opérations: %d\n", nb_operations);

    if (strcmp(argv[1], "pile") == 0) {
        test_pile(nb_operations);
    }
    else if (strcmp(argv[1], "file") == 0) {
        test_file(nb_operations);
    }
    else if (strcmp(argv[1], "tous") == 0) {
        test_pile(nb_operations);
        test_file(nb_operations);
    }
    else if (strcmp(argv[1], "compare") == 0) {
        test_comparatif(nb_operations);
    }
    else {
        printf("Type invalide. Utilisez 'pile', 'file', 'tous' ou 'compare'\n");
        return 1;
    }

    return 0;
}
