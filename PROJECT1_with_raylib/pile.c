#include "pile.h"
#include <stdbool.h>

Pile pile_init(int size)
{
    Pile p;
    p.size = size;
    p.curr = -1;
    p.tab = malloc(size*sizeof(int));
    p.tabp = &p.tab;
    return p;
}

void pile_free(Pile p)
{
    free(p.tab);
}

void push(Pile *p, int x)
{
    if(p->curr == p->size-1)
    {
        p->size = p->size * 2;
        p->tab = reallocarray(p->tab, p->size, sizeof(int));
        if(p->tab == NULL){ perror("reallocarray\n"); exit(3); } 
    }
    p->curr++;
    p->tab[p->curr] = x;
}

bool pop(Pile *p, int *val)
{
    if(p->curr == -1) return false;
    *val = p->tab[p->curr];
    p->curr--;
    return true;
}

int pile_size(Pile p) { return p.curr+1; }

void pile_print(Pile p)
{
    for (int i = p.curr; i >=0 ; i--)
    {
       printf("|%d", p.tab[i]);
    }
    printf("|\n");
}