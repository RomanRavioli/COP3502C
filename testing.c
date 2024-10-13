#include <stdio.h> // Standard Input/Output Library

// Aliases:
typedef struct Point Point; // Alias struct Poinnt to Point

// Structs:
struct Point // Struct definition
{
    int x, y; // Both members defined in the same line
};

// The print function
void printPoint(Point p)
{
    printf("(%d,", p.x);
    printf(" %d)\n", p.y);
}

// The modify function
// This function can modify point outside the function
void modify(Point * p)
{
    (*p).x += 1; // Dereference Point p to modify value
    (*p).y = 0; // Dereference Point p to modify value
    // Can also use p->x += 1;
    // Can also use p->y = 0;
}

// The modify function (that doesn't work)
// This function canot modify the point outside the function
void noModify(Point p)
{
    p.x += 1; // Only changes the copy
    p.y = 0; // Only changes the copy
}

// The add function
Point add(Point lhs, Point rsh) // Returns a Point
{
    Point result; // Instantiates a point called "result"

    // Store the sum of the x's from the 2 given points together in the result's x. Same with the y's.
    result.x = lhs.x + rsh.x;
    result.y = lhs.y + rsh.y;

    return result;
}

// The main function
int main()
{
    Point p; // Instantiation

    p.x = 1; // Initialize the x-coordinate
    p.y = 2; // Initialize the y-coordinate

    printPoint(p);
    modify(&p);
    printPoint(p); // Calls the printPoint() function
    
    return 0; // Exit program
}