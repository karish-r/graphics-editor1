#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 50

char canvas[ROWS][COLS];

/* Initialize canvas with '_' */
void initializeCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

/* Display canvas */
void displayCanvas()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

/* Draw Rectangle */
void drawRectangle(int x, int y, int width, int height)
{
    for(int i = y; i < y + height; i++)
    {
        for(int j = x; j < x + width; j++)
        {
            if(i >= 0 && i < ROWS && j >= 0 && j < COLS)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

/* Bresenham Line Algorithm */
void drawLine(int x1, int y1, int x2, int y2)
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1)
    {
        if(x1 >= 0 && x1 < COLS &&
           y1 >= 0 && y1 < ROWS)
        {
            canvas[y1][x1] = '*';
        }

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy)
        {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx)
        {
            err += dx;
            y1 += sy;
        }
    }
}

/* Draw Triangle */
void drawTriangle(int x1, int y1,
                  int x2, int y2,
                  int x3, int y3)
{
    drawLine(x1, y1, x2, y2);
    drawLine(x2, y2, x3, y3);
    drawLine(x3, y3, x1, y1);
}

void drawCircle(int cx, int cy, int r)
{
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLS; x++)
        {
            double dx = x - cx;
            double dy = (y - cy) * 2.0;

            double dist = sqrt(dx * dx + dy * dy);

            if(fabs(dist - r) < 0.6)
            {
                canvas[y][x] = '*';
            }
        }
    }
}

int main()
{
    initializeCanvas();

    printf("\n===== INITIAL CANVAS =====\n\n");
    displayCanvas();

    drawRectangle(2, 2, 8, 4);

    drawLine(18, 2, 18, 16);

    drawTriangle(28, 11, 42, 11, 35, 4);

    drawCircle(35, 16, 4);

    printf("\n===== AFTER DRAWING ALL SHAPES =====\n\n");
    displayCanvas();

    return 0;
}
