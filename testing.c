#include <stdio.h> // Standard Input/Output Library
#include <stdlib.h> //  For the rand() function
#include <time.h> // To randomize using time

// Definitions:
#define SIZE 20
#define WORD "Strawberry"


// Aliases:
typedef struct Point Point; // Alias struct Poinnt to Point


// Structs:
struct Point // Struct definition
{
    int x, y; // Both members defined in the same line
};


// Arrays
int array[10]; // Instantiate an array of 10 values
// The values, however, are not yet initialized.
// The values in the array are garbage.
// Garbage values could be 0s or some random number.
int array_zeroes[10] = {0}; // Ensures array is filled with 0s


// The print function
void printPoint(Point p)
{
    printf("(%d,", p.x);
    printf(" %d)\n", p.y);
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


// The array argument can be specified using open close brackets
void makeRandomArray(int array[], int length) // Function to populate an array with random values
{
    for (int i = 0; i < length; i++)
    {
        array[i] = rand() % 100; // Make the value random value in the range of 0 to 99 inclusive
    }
}


// The array argument can be specified using the array pointer
int sumArray(int * array, int length) // Function to sum the values of the array
{
    int result = 0; // Instantiate and initialize a result to 0
    for (int i = 0; i < length; i++) // Loop through the values of the array
    {
        result = result + array[i]; // Add the value of the array to the result
    }
    return result; // Return the sum of all the values
}

// You should read the following code and try to determine what will be printed.
void whatDoIDo(int array[], int length)
{
    int array2[length];
    for (int i = 0; i < length; i++)
    {
        array2[i] = i;
    }
    array = array2;
    // For debugging and code tracing
    /*
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", array2[i]);
    }
    printf("\n");
    */
}


void swap(int * a, int * b)
{
    int tmp = *a; // Move a's value into tmp (a temporary variable)
    *a = *b; // Overwrite a with the value in b
    *b = tmp; // Overwrite b with the value in the tmp variable
}


// The main function
int main()
{

    // STRUCTURE STUFF
    Point p; // Instantiation
    p.x = 1; // Initialize the x-coordinate
    p.y = 2; // Initialize the y-coordinate
    printf("Coordinate 1: ");
    printPoint(p);
    modify(&p);
    printf("Coordinate 2: ");
    printPoint(p); // Calls the printPoint() function
    

    // ARRAY STUFF
    int arr[10]; // Instantiate an array of 10 values
    makeRandomArray(arr, 10); // (Purposefully) fill the array with random numbers
    int sum = sumArray(arr, 10); // Get the sum of the array
    printf("The array sum was %d.\n", sum); // Print the result
    // Mystery Function?
    whatDoIDo(arr, 10);
    // The following lines of code are all equivalent
    arr[7] = 0;
    *(arr + 7) = 0;
    *(7 + arr) = 0;
    7[arr] = 0;


    // POINTER STUFF
    int x = 5; // Create an integer x with value of 5
    int y = 7; // Create an integer y with value of 7
    swap(&x, &y); // Swap the values of x and y
    printf("x is %d\ty is %d\n", x, y); // Print the values stored in x and y


    // DYNAMIC MEMORY STUFF
    // malloc - Creates a section of dynamic memory in the heap
    // calloc - Creates a section of dynamic memory in the heap and innitialized to bytewise 0
    // realloc - Changes the size of a section of dynamic memory that was in the heap
    // free - Relinquishes a sectionn of memory that was given by a dnynamic memory back to the system


    // STRING STUFF
    char word[SIZE + 1]; // +1 is used to ensure there's room for the NULL Terminator
    word[0] = 'A';
    word[1] = 'p';
    word[2] = 'p';
    word[3] = 'l';
    word[4] = 'e';
    word[5] = '\0'; // NULL terminates the string
    printf("The hardcoded string was %s\n", word); // Prints the string using %s
    // char word[SIZE + 1] = WORD; - This would not compile due to "redefinition" of "word" (a string literal)
    char word_2[SIZE + 1] = WORD;
    printf("The word is originally %s\n", word_2);

    return 0; // Exit the program
}