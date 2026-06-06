#include <stdio.h>

#define MAX_SHAPES 100

typedef struct
{
    int id;
    int type;      // 1=Rectangle, 2=Line, 3=Triangle, 4=Circle
    int x;
    int y;
    int size;
} Shape;

Shape shapes[MAX_SHAPES];
int shapeCount = 0;

int isIdExists(int id)
{
    for(int i=0;i<shapeCount;i++)
    {
        if(shapes[i].id == id)
            return 1;
    }
    return 0;
}

char* getShapeName(int type)
{
    switch(type)
    {
        case 1: return "Rectangle";
        case 2: return "Line";
        case 3: return "Triangle";
        case 4: return "Circle";
        default: return "Unknown";
    }
}

void addShape()
{
    Shape s;

    printf("\nEnter Shape ID: ");
    scanf("%d",&s.id);

    if(isIdExists(s.id))
    {
        printf("Error! Shape ID already exists.\n");
        return;
    }

    printf("\nShape Types\n");
    printf("1 Rectangle\n");
    printf("2 Line\n");
    printf("3 Triangle\n");
    printf("4 Circle\n");

    printf("Enter Shape Type: ");
    scanf("%d",&s.type);

    if(s.type < 1 || s.type > 4)
    {
        printf("Invalid Shape Type!\n");
        return;
    }

    printf("Enter X Coordinate: ");
    scanf("%d",&s.x);

    printf("Enter Y Coordinate: ");
    scanf("%d",&s.y);

    printf("Enter Size: ");
    scanf("%d",&s.size);

    shapes[shapeCount++] = s;

    printf("Object Added Successfully!\n");
}

void deleteShape()
{
    int id;

    printf("\nEnter Shape ID to Delete: ");
    scanf("%d",&id);

    for(int i=0;i<shapeCount;i++)
    {
        if(shapes[i].id == id)
        {
            for(int j=i;j<shapeCount-1;j++)
            {
                shapes[j] = shapes[j+1];
            }

            shapeCount--;

            printf("Object Deleted Successfully!\n");
            return;
        }
    }

    printf("Shape Not Found!\n");
}

void modifyShape()
{
    int id;

    printf("\nEnter Shape ID to Modify: ");
    scanf("%d",&id);

    for(int i=0;i<shapeCount;i++)
    {
        if(shapes[i].id == id)
        {
            printf("\nCurrent Object Information\n");
            printf("Type : %s\n", getShapeName(shapes[i].type));
            printf("X    : %d\n", shapes[i].x);
            printf("Y    : %d\n", shapes[i].y);
            printf("Size : %d\n", shapes[i].size);

            printf("\nEnter New Shape Type: ");
            scanf("%d",&shapes[i].type);

            printf("Enter New X Coordinate: ");
            scanf("%d",&shapes[i].x);

            printf("Enter New Y Coordinate: ");
            scanf("%d",&shapes[i].y);

            printf("Enter New Size: ");
            scanf("%d",&shapes[i].size);

            printf("Object Modified Successfully!\n");
            return;
        }
    }

    printf("Shape Not Found!\n");
}

void displayShapes()
{
    if(shapeCount == 0)
    {
        printf("\nNo Objects Present.\n");
        return;
    }

    printf("\n========== OBJECT LIST ==========\n");

    for(int i=0;i<shapeCount;i++)
    {
        printf("\nObject %d\n", i+1);
        printf("ID   : %d\n", shapes[i].id);
        printf("Type : %s\n", getShapeName(shapes[i].type));
        printf("X    : %d\n", shapes[i].x);
        printf("Y    : %d\n", shapes[i].y);
        printf("Size : %d\n", shapes[i].size);
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n===== OBJECT MANAGEMENT MENU =====\n");
        printf("1. Add Object\n");
        printf("2. Delete Object\n");
        printf("3. Modify Object\n");
        printf("4. Display Objects\n");
        printf("5. Exit\n");

        printf("Enter Choice: ");
        scanf("%d",&choice);

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
                displayShapes();
                break;

            case 5:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 5);

    return 0;
}
