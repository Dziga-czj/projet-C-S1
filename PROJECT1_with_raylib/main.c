#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include "raylib.h"

#include "inter.h"
#include "debugger.h"
#include "get_ppm.h"


int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("usage : ./exe [file.ppm] [d : debug | v : visualise]\n");
        return 1;
    }

    Vector2 screen = {1920, 1080};

    grid g = get_content(argv[1]);
    inter in = inter_init(false);

    if(argc == 2)
    {
        while(tick(g, &in)) {}
    }
    else if(argv[2][0] == 'd')
    {
        in.debug = true;
        in.visualize = true;
        InitWindow(screen.x, screen.y, "visualizer");
        SetTargetFPS(60);
        bool cont = true;
        while(!WindowShouldClose() && cont) {
            BeginDrawing();
                ClearBackground(WHITE);
                draw_screen(g, in);
                if(IsKeyPressed(KEY_SPACE)) {
                    cont = tick(g, &in);
                }
            EndDrawing();
        }
        CloseWindow();
    }
    else if(argv[2][0] == 'v'){
        in.visualize = true;
        InitWindow(screen.x, screen.y, "visualizer");
        SetTargetFPS(60);
        bool cont = true;
        while(!WindowShouldClose() && cont) {
            BeginDrawing();
                ClearBackground(WHITE);
                cont = tick(g, &in);
                draw_screen(g, in);
            EndDrawing();
        }
        CloseWindow();
    }
    else if(argv[2][0] == 'b'){
        in.debug = true;
        bool cont = true;
        InitWindow(100, 100, "visualizer");
        SetTargetFPS(60);
        while(cont)
        {
            BeginDrawing();
                ClearBackground(WHITE);

            
            if(IsKeyPressed(KEY_SPACE)) {
                cont = tick(g, &in);
            } 
            EndDrawing();
        }
        CloseWindow();
    }
    else 
    {
        while(tick(g, &in)) {}
    }


    inter_free(in);
    grid_free(g);
    return 0;
}   