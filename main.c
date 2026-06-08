#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 20
#define COLS 50
#define MAX_SHAPES 100

char canvas[ROWS][COLS];

/* ================= SHAPE STRUCTURE ================= */

typedef struct
{
    int id;
    int type;   // 1 Rectangle, 2 Line, 3 Triangle, 4 Circle

    int x1, y1;
    int x2, y2;
    int x3, y3;

    int radius;

} Shape;

Shape shapes[MAX_SHAPES];
int shapeCount = 0;

/* ================= DAY 1 FUNCTIONS ================= */

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

void drawRectangle(int x, int y, int width, int height)
{
    for(int i = y; i < y + height; i++)
    {
        for(int j = x; j < x + width; j++)
        {
            if(i >= 0 && i < ROWS &&
               j >= 0 && j < COLS)
            {
                canvas[i][j] = '*';
            }
        }
    }
}

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

void drawTriangle(int x1,int y1,
                  int x2,int y2,
                  int x3,int y3)
{
    drawLine(x1,y1,x2,y2);
    drawLine(x2,y2,x3,y3);
    drawLine(x3,y3,x1,y1);
}

void drawCircle(int cx,int cy,int r)
{
    for(int y=0;y<ROWS;y++)
    {
        for(int x=0;x<COLS;x++)
        {
            double dx=x-cx;
            double dy=(y-cy)*2.0;

            double dist=sqrt(dx*dx+dy*dy);

            if(fabs(dist-r)<0.6)
            {
                canvas[y][x]='*';
            }
        }
    }
}

/* ================= OBJECT MANAGEMENT ================= */

int isIdExists(int id)
{
    for(int i=0;i<shapeCount;i++)
    {
        if(shapes[i].id==id)
        {
            return 1;
        }
    }

    return 0;
}
void addShape()
{
    if(shapeCount >= MAX_SHAPES)
    {
        printf("Shape Storage Full!\n");
        return;
    }

    Shape s;

    do
    {
        printf("Enter Shape ID: ");
        scanf("%d",&s.id);

        if(isIdExists(s.id))
        {
            printf("ID already exists. Enter a different ID.\n");
        }

    }while(isIdExists(s.id));

    printf("\nShape Types\n");
    printf("1 Rectangle\n");
    printf("2 Line\n");
    printf("3 Triangle\n");
    printf("4 Circle\n");

    printf("Enter Shape Type: ");
    scanf("%d",&s.type);

    while(s.type < 1 || s.type > 4)
    {
        printf("Invalid Type! Enter again: ");
        scanf("%d",&s.type);
    }

    switch(s.type)
    {
        case 1:
            printf("Enter x y width height: ");
            scanf("%d%d%d%d",
                  &s.x1,&s.y1,
                  &s.x2,&s.y2);
            break;

        case 2:
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d",
                  &s.x1,&s.y1,
                  &s.x2,&s.y2);
            break;

        case 3:
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d%d%d%d%d%d",
                  &s.x1,&s.y1,
                  &s.x2,&s.y2,
                  &s.x3,&s.y3);
            break;

        case 4:
            printf("Enter centerX centerY radius: ");
            scanf("%d%d%d",
                  &s.x1,&s.y1,
                  &s.radius);
            break;
    }

    shapes[shapeCount++] = s;

    printf("Shape Added Successfully!\n");
}

void deleteShape()
{
    int id;

    printf("Enter Shape ID to Delete: ");
    scanf("%d",&id);

    for(int i=0;i<shapeCount;i++)
    {
        if(shapes[i].id==id)
        {
            for(int j=i;j<shapeCount-1;j++)
            {
                shapes[j]=shapes[j+1];
            }

            shapeCount--;

            printf("Shape Deleted Successfully!\n");
            return;
        }
    }

    printf("Shape Not Found!\n");
}

void modifyShape()
{
    int id;

    printf("Enter Shape ID to Modify: ");
    scanf("%d",&id);

    for(int i=0;i<shapeCount;i++)
    {
        if(shapes[i].id==id)
        {
            printf("\nCurrent Type = %d\n",
                   shapes[i].type);

            printf("Enter New Shape Type: ");
            scanf("%d",&shapes[i].type);

            switch(shapes[i].type)
            {
                case 1:
                    printf("Enter x y width height: ");
                    scanf("%d%d%d%d",
                          &shapes[i].x1,
                          &shapes[i].y1,
                          &shapes[i].x2,
                          &shapes[i].y2);
                    break;

                case 2:
                    printf("Enter x1 y1 x2 y2: ");
                    scanf("%d%d%d%d",
                          &shapes[i].x1,
                          &shapes[i].y1,
                          &shapes[i].x2,
                          &shapes[i].y2);
                    break;

                case 3:
                    printf("Enter x1 y1 x2 y2 x3 y3: ");
                    scanf("%d%d%d%d%d%d",
                          &shapes[i].x1,
                          &shapes[i].y1,
                          &shapes[i].x2,
                          &shapes[i].y2,
                          &shapes[i].x3,
                          &shapes[i].y3);
                    break;

                case 4:
                    printf("Enter centerX centerY radius: ");
                    scanf("%d%d%d",
                          &shapes[i].x1,
                          &shapes[i].y1,
                          &shapes[i].radius);
                    break;
            }

            printf("Shape Modified Successfully!\n");
            return;
        }
    }

    printf("Shape Not Found!\n");
}

void displayShapeList()
{
    if(shapeCount==0)
    {
        printf("\nNo Shapes Available.\n");
        return;
    }

    printf("\n===== SHAPE LIST =====\n");

    for(int i=0;i<shapeCount;i++)
    {
        printf("\nShape %d\n",i+1);

        printf("ID   : %d\n",
               shapes[i].id);

        printf("Type : %d\n",
               shapes[i].type);
    }
}

/* ================= MAIN ================= */

int main()
{
    int choice;

    do
    {
        printf("\n===== DAY 2 : OBJECT MANAGEMENT =====\n");

        printf("1 Add Shape\n");
        printf("2 Delete Shape\n");
        printf("3 Modify Shape\n");
        printf("4 Display Shape List\n");
        printf("5 Exit\n");

        printf("Enter Choice: ");

        if(scanf("%d",&choice)!=1)
        {
            printf("Invalid Input!\n");
            return 0;
        }

        switch(choice)
        {
            case 1:
                addShape();
                break;

            case 2:
                deleteShape();
                break;

            case 3:
                modifyShape();
                break;

            case 4:
                displayShapeList();
                break;

            case 5:
                printf("Program Ended.\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    }while(choice!=5);

    return 0;
}
