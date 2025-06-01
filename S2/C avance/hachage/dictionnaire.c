#include "dictionnaire.h"

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
    unsigned int index = hash(cle) % TAILLE_DICO;
    node* courant = dico->tableau[index];
    while (courant != NULL) {
        if (strcmp(courant->cle, cle) == 0) {
            return strdup(courant->valeur);
        }
        courant = courant->suivant;
    }
    return NULL;
}

bool ajouter(const char* cle, const char* valeur, dico_t* dico) {
    if (dico == NULL || valeur == NULL) {
        return false;
    }
    unsigned int index = hash(cle) % TAILLE_DICO;
    node* courrant = dico->tableau[index];
    while(courrant != NULL) {
        if (strcmp(courrant->cle, cle) == 0) {
            courrant->valeur = valeur;
            return true;
        }
        courrant = courrant->suivant;
    }
    node* nouveau = malloc(sizeof(node));
    if (nouveau == NULL) {
        return false;
    }
    nouveau->cle = strdup(cle);
    nouveau->valeur = strdup(valeur);
    nouveau->suivant = dico->tableau[index];
    dico->tableau[index] = nouveau;
    dico->taille++;
    return true;
}

char* retirer(const char* cle, dico_t* dico) {
    if (dico == NULL) {
        return NULL;
    }
    unsigned int index = hash(cle) % TAILLE_DICO;
    node* courant = dico->tableau[index];
    node* precedent = NULL;
    while (courant != NULL) {
        if (strcmp(courant->cle, cle) == 0) {
            char* valeurSupprimee = strdup(courant->valeur);
            if (precedent == NULL) {
                dico->tableau[index] = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }
            free(courant->cle);
            free(courant->valeur);
            free(courant);
            dico->taille--;
            return valeurSupprimee;
        }
        precedent = courant;
        courant = courant->suivant;
    }
    return NULL;
}

void vider_dico(dico_t* dico) {
    if (dico == NULL) {
        return;
    }
    if(dico->taille == 0) {
        return;
    }
    for (int i = 0; i < TAILLE_DICO; i++) {
        node* courant = dico->tableau[i];
        while (courant != NULL) {
            node* temp = courant;
            courant = courant->suivant;
            free(temp);
        }
        dico->tableau[i] = NULL;
    }
    dico->taille = 0;
}

static unsigned int hash(const char* cle) {
    if(cle == NULL) {
        return 0;
    }
    unsigned int somme = 0;
    for (int i = 0; cle[i] != '\0'; i++) {
        somme += cle[i];
    }
    return somme;
}