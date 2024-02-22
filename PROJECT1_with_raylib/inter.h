#ifndef INTER_H_
#define INTER_H_

#include "pile.h"
#include <stdbool.h>
#include <string.h>
#include "utils.h"


struct inter {
    vector2 pos;
    vector2 old;
    char dir;
    char bord;
    Pile p;
    px codants[NB_CODANTS];
    int timer;
    bool changed_bord;
    bool passe_par_non_bloquant;

    bool visualize;
    bool debug;
};
typedef struct inter inter;

struct grid{
    int w, h;
    px ** pix;
};
typedef struct grid grid;

inter inter_init();

void inter_free(inter in);

bool tick(grid g, inter *in);

bool est_codant(px pix, inter in);

int get_taille_bloc(grid g, vector2 pos);

vector2 get_pos_codant(inter in, px col);

#endif