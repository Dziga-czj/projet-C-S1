#include "utils.h"


double luminance(px pix) { return pix.r * 0.202 + pix.g * 0.707 + pix.b * 0.071; }

short **tab_init(int w, int h)
{
    short **tab = calloc(w, sizeof(short*));
    for (int i = 0; i < w; i++)
    {
        tab[i] = calloc(h, sizeof(short));
    }
    return tab;
}

void tab_free(short **tab, int w)
{
    for (int i = 0; i < w; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

char rotate(char c)
{
    if(c == 'n') return 'e';
    if(c == 'e') return 's';
    if(c == 's') return 'o';
    return 'n';
}

bool same_colors(px p1, px p2) { return ((p1.r == p2.r) && (p1.g == p2.g) && (p1.b == p2.b)) ; }

void px_print(px pix) { printf("(%3d,%3d,%3d)", pix.r, pix.g, pix.b); }

unsigned char hex2_to_char(char *hex)
{
    char r = 0;
    for (int i = 0; i <= 1; i++)
    {
        
        if(48 <= hex[i] && hex[i] <= 57)
        {
            r += (hex[i]-48)*(1 + 15*(i == 0));
        }else if(97 <= hex[i] && hex[i] <= 102)
        {
            r += (hex[i]-87)*(1 + 15*(i == 0)); 
        }
    }
    return r;
}

px hex_to_px(char *hex)
{
    px pix;
    pix.r = hex2_to_char(&hex[0]);
    pix.g = hex2_to_char(&hex[2]);
    pix.b = hex2_to_char(&hex[4]);
    return pix;
}

bool est_bloquant(px pix) { return luminance(pix) < 128; }

int tore(int x, int w)
{
    if(x == -1) return w-1;
    else if(x == w) return 0;
    return x;
}

vector2 continue_coords(vector2 coords, char dir, int w, int h)
{
    vector2 res = coords;
    switch(dir)
    {
        case 'n':
            res.y = tore(res.y-1, h);
        break;
        case 'e':
            res.x = tore(res.x+1, w);
        break;
        case 's':
            res.y = tore(res.y+1, h);
        break;
        case 'o':
            res.x = tore(res.x-1, w);
        break;
        default:
        perror("next_coords\n");
        exit(4);
        break;
    }
    return res;
}

char *get_state_str(char dir, char bord)
{
    char *st = malloc(3*sizeof(char));
    sprintf(st, "%c%c", dir, bord);
    return st;
}

vector2 int_to_coord(int val)
{
    vector2 v;
    v.y = val/10000;
    v.x = val - 10000*v.y;
    return v;
}


