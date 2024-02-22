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

void pile_free(Pile p);

void push(Pile *p, int x);

bool pop(Pile *p, int *val);

int pile_size(Pile p);

void pile_print(Pile p);

#endif