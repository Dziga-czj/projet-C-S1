#include "inter.h"

// @requires : /
// @assigns : a local inter type
// @ensures : a properly initiated inter type
inter inter_init()
{
    inter in;
    in.pos = (vector2) {.x = 0, .y = 0};
    in.old = in.pos;
    in.dir = 'e';
    in.bord = 'b';
    in.p = pile_init(5);
    in.changed_bord = false;
    in.timer = 0;
    in.debug = false;
    in.passe_par_non_bloquant = false;

    char codants[NB_CODANTS][6] = {
        "ff8080","ffff80","80ff80","80ffff","8080ff","ff80ff",
        "ff0000","ffff00","00ff00","00ffff","0000ff","ff00ff",
        "800000","808000","008000","008080","000080","800080"
    };

    for (int i = 0; i < NB_CODANTS; i++)
    {
        in.codants[i] = hex_to_px(codants[i]);
    }
    return in;
}

// @requires : a properly initiated inter type, a px type
// @assigns : /
// @ensures : returns true only if the pixel pix is in the 'codants' array of type inter
bool est_codant(px pix, inter in)
{
    for (int i = 0; i < 18; i++)
    {
        if(same_colors(pix, in.codants[i])) return true;
    }
    return false;
}

// @requires : a properly initiated grid type, with 0 <= x < g.w and 0 <= y < g.h
// @assigns : a vector2 array
// @ensures : a vector2 array with the four coords around the position (x,y) considering the tore g
vector2 *next_coords(grid g, int x, int y)
{
    vector2 *coords = malloc(4*sizeof(vector2));
    coords[0].x = x+1;
    coords[0].y = y;
    coords[1].x = x;
    coords[1].y = y+1;
    coords[2].x = x-1;
    coords[2].y = y;
    coords[3].x = x;
    coords[3].y = y-1;

    for (int i = 0; i < 4; i++)
    {
        coords[i].x = tore(coords[i].x, g.w);
        coords[i].y = tore(coords[i].y, g.h);
    }
    
    return coords;
}

// @requires : a properly initiated matrix tab, the same size of g.tab, a grid type, a Pile type and valid coordinates in grid type
// @assigns : changes value of matrix tab, and pushes values into the heap pointed by p
// @ensures : recursively goes through the pixels of a same bloc, and pushed all border pixels once in the heap pointed by p
void parcourt_frontiere(short **tab, grid g, Pile *p, vector2 pos)
{
    if(tab[pos.x][pos.y] == 5) return; // assure la finition de la fonction
    vector2 *coords = next_coords(g, pos.x, pos.y);
    tab[pos.x][pos.y]++;
    for (int i = 0; i < 4; i++)
    {
        if(!same_colors(GET_PIX(pos), GET_PIX(coords[i]))) 
        {
            tab[pos.x][pos.y]++;

            // si pixel de frontière (assure l'unicité dans la pile p)
            if(tab[pos.x][pos.y] == 2) push(p, pos.x + pos.y*10000);

        } else if(tab[coords[i].x][coords[i].y] == 0)
        {
            parcourt_frontiere(tab, g, p, coords[i]);
        }
    }

    free(coords);
}

// @requires : a properly initiated grid type and inter type
// @assigns : /
// @ensures : returns the next coords of interpreter, considering it's current state
vector2 next_bloc(grid g, inter in)
{
    Pile p = pile_init(32);
    Pile p_front = pile_init(32);

    short **tab = tab_init(g.w, g.h);

    parcourt_frontiere(tab, g, &p_front, in.pos);

    int temp;
    while(pop(&p_front, &temp))
    {
        vector2 coords = int_to_coord(temp);
        int x = coords.x;
        int y = coords.y;
        switch(in.dir)
        {
            case 'e':
                if(tab[tore(x+1, g.w)][y] == 0) push(&p, x+10000*y);
            break;
            case 's':
                if(tab[x][tore(y+1, g.h)] == 0) push(&p, x+10000*y);
            break;
            case 'o':
                if(tab[tore(x-1, g.w)][y] == 0) push(&p, x+10000*y);
            break;
            case 'n':
                if(tab[x][tore(y-1, g.h)] == 0) push(&p, x+10000*y);
            break;
            default:
            break;
        }
        
    }

    tab_free(tab, g.w);
    pile_free(p_front);

    vector2 curr = int_to_coord(p.tab[0]);
    for (int i = 1; i < p.curr+1; i++)
    {
        vector2 coord = int_to_coord(p.tab[i]);
        switch(in.dir)
        {
            case 'e':
                if(coord.x > curr.x) curr = coord;
            break;
            case 's':
                if(coord.y > curr.y) curr = coord;
            break;
            case 'o':
                if(coord.x < curr.x) curr = coord;
            break;
            case 'n':
                if(coord.y < curr.y) curr = coord;
            break;
            default:
            break;
        }
    }
    
    vector2 res = curr;

    while(pop(&p, &temp))
    {
        vector2 coord = int_to_coord(temp);
        switch(in.dir)
        {
            case 'e':
                if(coord.x != curr.x) continue;
                if(in.bord == 'b')
                {
                    if(coord.y < res.y) res = coord;
                }else 
                {
                    if(coord.y > res.y) res = coord;
                }
            break;
            case 's':
                if(coord.y != curr.y) continue;
                if(in.bord == 'b')
                {
                    if(coord.x > res.x) res = coord;
                }else 
                {
                    if(coord.x < res.x) res = coord;
                }
            break;
            case 'o':
                if(coord.x != curr.x) continue;
                if(in.bord == 'b')
                {
                    if(coord.y > res.y) res = coord;
                }else 
                {
                    if(coord.y < res.y) res = coord;
                }
            break;
            case 'n':
                if(coord.y != curr.y) continue;
                if(in.bord == 'b')
                {
                    if(coord.x < res.x) res = coord;
                }else 
                {
                    if(coord.x > res.x) res = coord;
                }
            break;
            default:
            break;
        }
    }
    
    //on avance de 1 en fonction de la direction
    res = continue_coords(res, in.dir, g.w, g.h);

    pile_free(p);
    return res;
}

// @requires : a properly initiated type inter
// @assigns : frees the heap of type inter
// @ensures : a properly freed type inter
void inter_free(inter in) { pile_free(in.p); }

// @requires : a properly initiated type inter
// @assigns : /
// @ensures : if the pixel given is a coding pixel in inter 'in', returns the color value and luminosity value of the coding color
vector2 get_pos_codant(inter in, px col)
{
    for (int i = 0; i < NB_CODANTS; i++)
    {
        if(same_colors(col, in.codants[i]))
        {
            vector2 res;
            res.y = i/6;
            res.x = i - res.y*6;
            return res;
        }
    }
    return (vector2) {0,0};
}

// @requires : a properly initiated type grid and short matrix tab
// @assigns : /
// @ensures : recursively goes through the bloc at coord pos, and returns it's size
int taille_parcourt(grid g, short **tab, vector2 pos)
{
    vector2 *coords = next_coords(g, pos.x, pos.y);
    tab[pos.x][pos.y]++;
    int res = 1;
    for (int i = 0; i < 4; i++)
    {
        // si de la même couleur et non exploré (assure la fin du programme)
        if(same_colors(GET_PIX(pos), GET_PIX(coords[i])) && (tab[coords[i].x][coords[i].y] == 0))
        {
            res = res + taille_parcourt(g, tab, coords[i]);
        }
    }
    free(coords);
    return res;
}

// @requires : a properly initiated type grid and valid coordinates in grid g
// @assigns : /
// @ensures : returns the size of the bloc at coords pos in grid g
int get_taille_bloc(grid g, vector2 pos)
{
    short **tab = tab_init(g.w, g.h);
    
    int taille = taille_parcourt(g, tab, pos);

    tab_free(tab, g.w);
    return taille;
}

// @requires : a properly initiated grid type and inter type pointer with the interpreter beeing on a coding pixel
// @assigns : changes the coordinates of interpreter in and can change the values of heap p in interpreter in
// @ensures : executes the corresponding action between the old position of the interpreter in and the new one
void action(grid g, inter *in)
{
    px new = GET_PIX(in->pos);
    vector2 col_old = get_pos_codant(*in, GET_PIX(in->old));
    vector2 col_new = get_pos_codant(*in, new);

    int curr = col_old.x;
    int diff_col = 0;
    while(col_new.x != curr){
        diff_col++;
        curr = (curr+1)%6;
    }

    curr = col_old.y;
    int diff_teinte = 0;
    while(col_new.y != curr)
    {
        diff_teinte++;
        curr = (curr+1)%3;
    }

    bool debug = in->debug;

    switch(diff_col)
    {
        case 0:
            if(diff_teinte == 0){
                //impossible
            }else if(diff_teinte == 1){ 
                // empile
                if(debug) printf("empile\n");
                push(&in->p, get_taille_bloc(g, in->old));
            }else { 
                //depile
                if(debug) printf("depile\n");
                int val;
                pop(&in->p, &val);
            }
        break;
        case 1:
            if(diff_teinte == 0){
                // plus
                if(debug) printf("plus\n");
                if(pile_size(in->p) < 2) break;
                else {
                    int val1, val2;
                    pop(&in->p, &val1);
                    pop(&in->p, &val2);
                    push(&in->p, val1 + val2);
                }
            }else if(diff_teinte == 1){
                // moins
                if(debug) printf("moins\n");
                if(pile_size(in->p) < 2) break;
                else {
                    int val1, val2;
                    pop(&in->p, &val1);
                    pop(&in->p, &val2);
                    push(&in->p, val2 - val1);
                }
            }else {
                // fois
                if(debug) printf("fois\n");
                if(pile_size(in->p) < 2) break;
                else {
                    int val1, val2;
                    pop(&in->p, &val1);
                    pop(&in->p, &val2);
                    push(&in->p, val1 * val2);
                }
            }
        break;
        case 2: 
            if(diff_teinte == 0){
                // divise
                if(debug) printf("divise\n");
                if(pile_size(in->p) < 2) break;
                else {
                    int val1, val2;
                    pop(&in->p, &val1);
                    pop(&in->p, &val2);
                    push(&in->p, val2 / val1);
                }
            }else if(diff_teinte == 1){
                // reste
                if(debug) printf("reste\n");
                if(pile_size(in->p) < 2) break;
                else {
                    int val1, val2;
                    pop(&in->p, &val1);
                    pop(&in->p, &val2);
                    int div = val2 / val1;
                    push(&in->p, (val2 - div*val1));
                }
            }else {
                // non
                if(debug) printf("non\n");
                int val;
                if(!pop(&in->p, &val)) {}
                else {
                    if(val == 0) push(&in->p, 1);
                    else push(&in->p, 0);
                }
            }
        break;
        case 3:
            if(diff_teinte == 0){
                // plus grand
                if(debug) printf("plus grand\n");
                if(pile_size(in->p) < 2) break;
                else {
                    int val1, val2;
                    pop(&in->p, &val1);
                    pop(&in->p, &val2);
                    if(val2 > val1) push(&in->p, 1);
                    else push(&in->p, 0);
                }
            }else if(diff_teinte == 1){
                // direction
                if(debug) printf("direction\n");
                int val1;
                if(!pop(&in->p, &val1)) {}
                else {
                    for (int i = 0; i < val1; i++)
                    {
                        in->dir = rotate(in->dir);
                    }
                }
            }else {
                // bord
                if(debug) printf("bord\n");
                int val1;
                if(!pop(&in->p, &val1)) {}
                else {
                    for (int i = 0; i < val1; i++)
                    {
                        in->bord = CHANGE_BORD(in->bord);
                    }
                }
            }
        break;
        case 4:
            if(diff_teinte == 0){
                //duplique
                if(debug) printf("duplique\n");
                int val;
                if(!pop(&in->p, &val)) {}
                else {
                    push(&in->p, val);
                    push(&in->p, val);
                }
            }else if(diff_teinte == 1){
                //tourne
                if(debug) printf("tourne\n");
                int n, prof;
                if(!pop(&in->p, &n)) {}
                else if(!pop(&in->p, &prof))
                {
                    push(&in->p, n);
                }else {
                    if(pile_size(in->p) < prof){
                        push(&in->p, n);
                        push(&in->p, prof);
                        break;
                    }
                    Pile p2 = pile_init(prof+2);
                    for (int m = 0; m < n; m++)
                    {
                        int som; pop(&in->p, &som);

                        for (int i = 0; i < prof-1; i++)
                        {
                            int temp; pop(&in->p, &temp);
                            push(&p2, temp);
                        }
                        push(&in->p, som);
                        for (int i = 0; i < prof-1; i++)
                        {
                            int temp; pop(&p2, &temp);
                            push(&in->p, temp);
                        }
                    }
                    pile_free(p2);
                }
            }else {
                // in (nombre)
                if(debug) printf("in (nombre)\n");
                if(debug) printf("entrez un nombre: ");
                int val;
                scanf("%d", &val);
                push(&in->p, val);
            }
        break;
        case 5:
            if(diff_teinte == 0){
                // in (char)
                if(debug) printf("in (char)\n");
                if(debug) printf("entrez un charactere: ");
                int val = getc(stdin);
                push(&in->p, val);
            }else if(diff_teinte == 1){
                // out (nombre)
                int val;
                if(!pop(&in->p, &val)) {}
                else {
                    printf("%d", val);
                    fflush(stdout);
                }
            }else {
                // out (char)
                int val;
                if(!pop(&in->p, &val)) {}
                else {
                    putchar((unsigned char) val);
                    fflush(stdout);
                }
            }
        break;
        default:
        perror("erreur switch actions\n");
        exit(6);
        break;
    }
    if(debug) printf("-------------------\n");
    in->old = in->pos;
}

// @requires : a properly initiated inter type and valid coordinates for the interpreter
// @assigns : resets new values to interpreter in, and resets it's position to the coords 'current'
// @ensures : a properly reset interpreter
void reset_apres_action(inter *in, vector2 current)
{
    in->timer = 0;
    in->changed_bord = false;
    in->pos = current;
    in->old = current;
    in->passe_par_non_bloquant = false;
}

// @requires : a properly initiated grid type and inter type pointer
// @assigns : makes a new step for the interpreter in, and changes it's values if it hasn't done an action
// @ensures : returns true if the program can continue, false if it should stop
bool tick(grid g, inter *in)
{
    vector2 current = next_bloc(g, *in);

    if(in->debug) // for debug mode
    {
        printf("current : %d, %d\n", current.x, current.y);
        printf("est_codant : %d\n", est_codant(GET_PIX(current), *in));
        printf("est_bloquant : %d\n", est_bloquant(GET_PIX(current)));
        printf("timer : %d\n", in->timer);
        px_print(GET_PIX(in->pos));
        putchar('\n');
        pile_print(in->p);
    }
    
    if(est_codant(GET_PIX(current), *in))
    {
        in->pos = current;
        if(!in->passe_par_non_bloquant)
            action(g, in);
        
        reset_apres_action(in, current);

        
        return true;
    }

    if(est_bloquant(GET_PIX(current)))
    {
        if(in->timer == 8)
        {
            if(in->debug) printf("\narret...\n");
            return false;
        }
        in->timer++;
        if(in->changed_bord) // bloqué et changé de bord
        {
            in->changed_bord = false;
            in->dir = rotate(in->dir);
        }else // bloqué et non changé de bord
        {
            in->bord = CHANGE_BORD(in->bord);
            in->changed_bord = true;
        }
        
        return true;
    }
    vector2 first = current;
    
    // if est passant : 
    // continue dans la mem direction

    do { // ne finit que si on rencontre des non passants
        current = continue_coords(current, in->dir, g.w, g.h);
    }
    while(!est_bloquant(GET_PIX(current)) && !est_codant(GET_PIX(current), *in));


    if(est_codant(GET_PIX(current), *in))
    {
        reset_apres_action(in, current);
    }else 
    {
        
        in->pos = first;
        in->passe_par_non_bloquant = true;
        if(in->timer == 0) {
            in->changed_bord = false;
        }
        else if(in->changed_bord) // bloqué et changé de bord
        {
            in->timer = 0;
            in->changed_bord = false;
            in->dir = rotate(in->dir);
        }else // bloqué et non changé de bord
        {
            in->timer = 0;
            in->bord = CHANGE_BORD(in->bord);
            in->changed_bord = true;
        }
        
    }

    return true;
}

