#include "debugger.h"
#include "raylib.h"
#include "inter.h"

void draw_screen(grid g, inter in)
{
    int decalx = 60;
    int decaly = 120;
    Vector2 size = (Vector2) {1800/g.w, 800/g.h};
    for (int j = 0; j < g.h; j++)
    {
        for (int i = 0; i < g.w; i++)
        {  
            px pix = g.pix[i][j];
            bool codant = est_codant(pix, in);
            bool bloquant = est_bloquant(pix);
            Vector2 pos = (Vector2) {decalx + size.x*i, decaly+size.y*j};

            Color col = (Color) {pix.r, pix.g, pix.b, 255};
            Color opp = (Color) { abs(255-pix.r), abs(255-pix.g), abs(255-pix.b), 255};
            DrawRectangleV(pos, size, col);
            if(bloquant && !codant)
            {
                
                DrawLine(pos.x, pos.y, pos.x+size.x, pos.y+size.y, RED);
                DrawLine(pos.x+size.x, pos.y, pos.x, pos.y+size.y, RED);

            }
            if(!bloquant && !codant)
            {
                int decal = size.y/5;
                for (int i = 0; i < 5; i++)
                {
                    DrawLine(pos.x, pos.y+i*decal, pos.x+size.x, pos.y+i*decal, opp);
                }   
                
                
            }

            if((i == in.pos.x) && (j == in.pos.y))
            {
                DrawRectangleLines(decalx + size.x*i, decaly + size.y*j, size.x, size.y, opp);
                Vector2 pos2;

                switch(in.dir)
                {
                    case 'e':
                        pos2 = (Vector2) {decalx+i*size.x+size.x, decaly+j*size.y+size.y/2};
                    break;
                    case 's':
                        pos2 = (Vector2) {decalx+i*size.x+size.x/2, decaly+j*size.y+size.y};
                    break;
                    case 'o':
                        pos2 = (Vector2) {decalx+i*size.x, decaly+j*size.y+size.y/2};
                    break;
                    case 'n':
                        pos2 = (Vector2) {decalx+i*size.x+size.x/2, decaly+j*size.y};
                    break;
                    default:
                    break;
                }
                DrawLineEx((Vector2) {decalx+i*size.x+size.x/2, decaly+j*size.y+size.y/2}, pos2, 1.5, opp);
                
            }
        }  
    }
    
    
}





