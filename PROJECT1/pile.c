#include "pile.h"
#include <stdbool.h>


// @requires : a positive int size
// @assigns : a new int array of size "size"
// @ensures : a usable Pile type
Pile pile_init(int size)
{
    Pile p;
    p.size = size;
    p.curr = -1;
    p.tab = malloc(size*sizeof(int));
    p.tabp = &p.tab;
    return p;
}

// @requires : a properly initiated Pile type
// @assigns : frees the tab parameter of type Pile
// @ensures : a properly freed Pile type
void pile_free(Pile p)
{
    free(p.tab);
}

// @requires : a properly initiated pile pointer
// @assigns : a new sized array if the size isn't enough
// @ensures : the int x to be at the top of the heap pointed by p
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

// @requires : a properly initiated pile pointer and a int pointer
// @assigns : changes the size of the current heap
// @ensures : returns true if there is a value to be popped, and put in the val int, returns false otherwise
bool pop(Pile *p, int *val)
{
    if(p->curr == -1) return false;
    *val = p->tab[p->curr];
    p->curr--;
    return true;
}

// @requires : a properly initiated Pile type
// @assigns : /
// @ensures : the number of elements in the given heap
int pile_size(Pile p) { return p.curr+1; }

// @requires : a properly initiated Pile type
// @assigns : /
// @ensures : prints the content of the given heap (prints |\n if the heap is empty)
void pile_print(Pile p)
{
    for (int i = p.curr; i >=0 ; i--)
    {
       printf("|%d", p.tab[i]);
    }
    printf("|\n");
}