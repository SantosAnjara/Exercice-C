#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int *donnees;
    int taille; // nombre d'élément réellement stockés
    int capacite; // nombre de cases alloués
}Tableau;


Tableau *creer(int capacite_initiale){
    // réserve une place pour 1 tableau , un struct n'existe pas en mémoire
    Tableau *t = malloc(sizeof(*t));
    if (t == NULL){
        return NULL; // signal d'échec
    }

    t->donnees = malloc(capacite_initiale * sizeof(*t->donnees));
    if (t->donnees == NULL){
        free(t); // on supprime la structure avant de partir
        return NULL;
    }

    t->taille = 0; // Aucun element stocke pour l'instant
    t->capacite = capacite_initiale;

    return t;
}


void afficher(const Tableau *t){ // const signifie que la fonction ne modifie par le tableau, elle ne fait que le lire
    if (t == NULL){
        return;
    }
    for (int i = 0; i < t->taille; i++)
    {
        printf("%d\n", t->donnees[i]);
    }
}


int ajouter(Tableau *t, int valeur)
{
    int i = t->taille - 1; // [la taille - 1 c'est l'indice]
    if (t->taille == t->capacite){
        int *nouveau = realloc(t->donnees, (t->capacite + 1) * sizeof(*nouveau));
        if (nouveau == NULL){
            return 1;
        }
        t->donnees = nouveau;
        t->capacite += 1;
         // la valeur augmente
        t->donnees[i] = valeur;
    }
        t->donnees[t->taille] = valeur; //  taille représentait une case vide
        t->taille += 1;
}


int main(void)
{
    Tableau *t = creer(3);

    t->donnees[0] = 10;
    t->donnees[1] = 20;
    t->taille = 2;
    afficher(t);
    printf("=======\n");
    ajouter(t, 2);
    afficher(t);

    return 0;
}
