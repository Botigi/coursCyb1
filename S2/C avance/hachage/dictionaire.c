#include "dictionnaire.h"
#include <stdlib.h>
#include <string.h>


struct dictionnaire* creer(int capacite){

    struct dictionnaire* dico = malloc(sizeof(struct dictionnaire)); 
    if (dico == NULL) {
        return NULL;
    }
    dico->tableau = NULL;
    dico->taille = 0;
    return dico;
}



dico_t* creer_dico(){

    dico_t* dico = malloc(sizeof(dico_t));
    if (dico == NULL) {
        return NULL;
    }
    for (int i = 0; i < TAILLE_DICO; i++) {
        dico->tableau[i] = NULL;
    }
    dico->taille = 0;
    return dico;
}

void supprimer_dico(dico_t* dico) {
    if (dico == NULL) {
        return;
    }
    vider_dico(dico);
    free(dico);
}

void liberer_chaine(dico_t* dico) {

}
void vider_dico(dico_t* dico) {
    if (dico == NULL) {
        return;
    }
    for (int i = 0; i < TAILLE_DICO; i++) {
        node* courant = dico->tableau[i];
        while (courant != NULL) {
            node* temp = courant;
            courant = courant->suivant;
            free(temp->cle);
            free(temp->valeur);
            free(temp);
        }
        dico->tableau[i] = NULL;
    }
    dico->taille = 0;
}

int taille(const dico_t* dico) {
    if (dico == NULL) {
        return -1;
    }
    return dico->taille;
}

char* valeur(const char* cle, const dico_t* dico) {
    if (dico == NULL) {
        return NULL;
    }
    unsigned int index = hash(cle);
    node* courant = dico->tableau[index];
    while (courant != NULL) {
        if (strcmp(courant->cle, cle) == 0) {
            return strdup(courant->valeur);
        }
        courant = courant->suivant;
    }
    return NULL;
}






static unsigned int hash(const char* cle) {
    if(cle == NULL) {
        return 0;
    }
    unsigned int somme = 0;
    for (int i = 0; cle[i] != '\0'; i++) {
        somme += cle[i];
    }
    return somme % TAILLE_DICO;
}