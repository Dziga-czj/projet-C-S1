#include "get_ppm.h"

void pass_and_get(FILE *fp, char *buff)
{
    bool comment = 1;
    do {
        fgets(buff, 200, fp);
        if(buff[0] != '#') comment = 0;
    }while (comment);
}

void grid_free(grid g)
{
    for (int i = 0; i < g.w; i++)
    {
        free(g.pix[i]);
    }
    free(g.pix);
}


grid get_content(char *filename)
{
    FILE *fp = fopen(filename, "r");
    char buff[200];
    pass_and_get(fp, buff);
    pass_and_get(fp, buff);
    int width;
    int height;
    sscanf(buff, "%d %d\n", &width ,&height);
    
    pass_and_get(fp, buff);

    px **pixels = malloc(width * sizeof(px*));
    for (int i = 0; i < width; i++)
    {
        pixels[i] = malloc(height * sizeof(px));
    }
    
    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            pixels[i][j].r = fgetc(fp);
            pixels[i][j].g = fgetc(fp);
            pixels[i][j].b = fgetc(fp);
        }
    }

    fclose(fp);

    grid g;

    g.w = width;
    g.h = height;
    g.pix = pixels;
    return g;
}


