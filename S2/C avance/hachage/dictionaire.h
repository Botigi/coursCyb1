#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H

#include <stdlib.h>

/*
 * Structure d'un élément de la liste de collision
 */
struct element {
    char* cle;    /* ne peut etre null*/
    char* valeur; /* ne peut etre null*/
    struct element* suivant;
};

/*
 * Structure de la table de hachage
 */
struct dictionnaire {
    struct element** table;  /* Tableau de listes de collision */
    int taille;              /* Nombre de couples (clé,valeur) stockés */
 };

/*
 * Crée un nouveau dictionnaire.
 * 
 * Paramètre capacite : nombre de cases du tableau
 * 
 * Retourne le dictionnaire créé ou NULL si erreur
 */
struct dictionnaire* creer(int capacite);

/*
 * Supprime le dictionnaire spécifié.
 * 
 * Paramètre dict : dictionnaire à supprimer
 */
void supprimer(struct dictionnaire* dict);

/*
 * Retourne le nombre de couples (clé,valeur) du dictionnaire.
 * 
 * Paramètre dict : dictionnaire à consulter
 */
int taille(const struct dictionnaire* dict);

/*
 * Retourne la valeur associée à la clé spécifiée.
 * 
 * Paramètres :
 * - dict : dictionnaire à consulter
 * - cle : clé dont on veut la valeur
 * 
 * Retourne la valeur associée ou NULL si la clé n'existe pas
 */
char* valeur(const struct dictionnaire* dict, const char* cle);

/*
 * Ajoute ou met à jour un couple (clé,valeur).
 * 
 * Paramètres :
 * - dict : dictionnaire à modifier
 * - cle : clé à ajouter/modifier
 * - valeur : valeur à associer à la clé
 * 
 * Retourne 1 si succès, 0 si erreur
 */
int ajouter(struct dictionnaire* dict, const char* cle, const char* valeur);

/*
 * Retire le couple (clé,valeur) associé à la clé spécifiée.
 * 
 * Paramètres :
 * - dict : dictionnaire à modifier
 * - cle : clé à retirer
 * 
 * Retourne la valeur associée ou NULL si la clé n'existait pas
 */
char* retirer(struct dictionnaire* dict, const char* cle);

#endif /* DICTIONNAIRE_H */