#ifndef PILE_H_
#define PILE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Pile{
    int curr;
    int *tab;
    int **tabp;
    int size;
};
typedef struct Pile Pile;

Pile pile_init(int size);
// @requires : /
// @assigns : alloue une nouvelle pile
// @ensures : une pile utilisable

void pile_free(Pile p);
// @requires : une pile p proprement initiée
// @assigns : /
// @ensures : la libération de la mémoire de la pile

void push(Pile *p, int x);
// @requires : une pile p proprement initée
// @assigns : un nouvel élément x dans la pile
// @ensures : la pile p aura toujours assez de place

bool pop(Pile *p, int *val);
// @requires : une pile p proprement initiée
// @assigns : /
// @ensures : renvoie true si le dépilement dans val s'est bien fait, false si la pile est vide

int pile_size(Pile p);
// @requires : une pile p proprement initiée
// @assigns : /
// @ensures : renvoie le nombre d'éléments dans la pile

void pile_print(Pile p);

#endif