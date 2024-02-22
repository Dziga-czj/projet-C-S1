#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>

#include "inter.h"
#include "get_ppm.h"


int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        printf("usage : ./exe [file.ppm] [d : debug]");
        return 1;
    }

    grid g = get_content(argv[1]);
    inter in = inter_init(false);


    // arguments managment
    if(argc == 2)
    {
        while(tick(g, &in)) {}
    }
    else if(argv[2][0] == '-' && argv[2][1] == 'd')
    {
        in.debug = true;
        
        bool cont = true;
        while(cont)
        if(getc(stdin) == 32) { // waits for space to be typed in the console
            putchar('\n');
            cont = tick(g, &in);
        }
    }
    else 
    {
        while(tick(g, &in)) {}
    }


    inter_free(in);
    grid_free(g);
    return 0;
}   