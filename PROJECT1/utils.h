#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define NB_CODANTS 18

#define GET_PIX(vec) (g.pix[vec.x][vec.y])

#define CHANGE_BORD(bord) ((bord) == ('b') ? ('t') : ('b'))

struct vector2{
    int x,y;
};
typedef struct vector2 vector2;

struct px {
    unsigned char r,g,b;
};
typedef struct px px;

char rotate(char c);

short **tab_init(int w, int h);

void tab_free(short **tab, int w);

double luminance(px pix);

bool same_colors(px p1, px p2);

px hex_to_px(char *hex);

bool est_bloquant(px pix);

int tore(int x, int w);

vector2 continue_coords(vector2 coords, char dir, int w, int h);

char *get_state_str(char dir, char bord);

void px_print(px pix);

vector2 int_to_coord(int val);

#endif