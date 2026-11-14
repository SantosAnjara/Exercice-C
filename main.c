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
    if (t == NULL){
        return 1;
    }
    if (t->taille == t->capacite){
        int nouvelle_capacite = t->capacite == 0 ? 1 : t->capacite * 2 ; //On double pour éviter de faire plusieurs realloc à chaque ajout
        int *nouveau = realloc(t->donnees,  nouvelle_capacite * sizeof(*nouveau));
        if (nouveau == NULL){
            return 1;
        }
        t->donnees = nouveau;
        t->capacite = nouvelle_capacite;
         // la valeur augmente
    }
        //  taille représente une case vide
        t->donnees[t->taille] = valeur;
        t->taille += 1;
    return 0;
}

void liberer(Tableau *t){
    if (t == NULL){
        return;
    }
    free(t->donnees);
    free(t);

}


int supprimer_dernier(Tableau *t){
    if (t == NULL){
        return 1;
    }
    if (t->taille == 0){
        return 1;
    }
    t->donnees[t->taille - 1] = 0;// taille - 1 représente le dernier élément
    t->taille -= 1; // cela implique une réduction de la taille

    return 0;
}


int main(void)
{
    Tableau *t = creer(3);

//    t->donnees[0] = 10;
//    t->donnees[1] = 20;
//    t->taille = 2;
    ajouter(t, 2);
    ajouter(t, 4);

    supprimer_dernier(t);
    ajouter(t, 3);

    supprimer_dernier(t);

    afficher(t);

    liberer(t);
    t = NULL;

    return 0;
}
