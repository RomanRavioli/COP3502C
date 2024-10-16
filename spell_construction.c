#include <stdio.h>
#include <string.h>


// variable definitions:
#define total 11
#define length 101


// variable declarations
char sequence[total][length];
char shortest[total * length];
int included[total];
int count, max_length;


// function prototypes:
int overlap(const char *a, const char *b);
void finder(char *current, int iteration);


// The main function
int main()
{
    // Ask user for input
    scanf("%d %d", &count, &max_length);
    // Initialize array
    for (int i = 0; i < count; i++)
        scanf("%s", sequence[i]);

    for (int i = 0; i < count; i++)
        included[i] = 0;

    // Creates the end of string for the shortest one
    shortest[0] = '\0';

    // Starts the recursion
    char start[total * length] = "";
    finder(start, 0);

    // Prints the shortest and best
    printf("%s\n", shortest);
    return 0;
}


// The overlap function - Finds how many characters at the end of string a match the beginning string b
int overlap(const char *a, const char *b)
{
    int len = strlen(a);
    // Start from longest overlap
    for (int i = len - 1; i >= 0; i--)
    {
        int match = 1;
        // Checks for match
        for (int j = 0; j < i; j++)
        {
            if (a[len - i + j] != b[j])
            {
                match = 0;
                break;
            }
        }
        // Matched all characters up to i, so we've found the max overlap
        if (match)
            return i;
    }
    return 0;
}


// The finder function - Finds the shortest iteration
void finder(char *current, int iteration)
{
    // Base case: Checks for shortest iteration
    if (iteration == count)
    {
        if (strlen(current) < strlen(shortest) || strlen(shortest) == 0)
            strcpy(shortest, current);
        return;
    }

    // Add to incantation
    for (int i = 0; i < count; i++)
    {
        if (!included[i])
        {
            included[i] = 1; // This means it's used
            char temp[total * length];
            strcpy(temp, current);
            // Finds a match between current and new
            int size = 0;
            if (strlen(temp) > 0)
                size = overlap(temp, sequence[i]);

            int current_len = strlen(temp);
            int incantation_length = strlen(sequence[i]);
            for (int j = size; j < incantation_length && (current_len + j - size) < total * length - 1; j++)
                temp[current_len + j - size] = sequence[i][j];
            temp[current_len + incantation_length - size] = '\0';

            finder(temp, iteration + 1); // Recursive function
            included[i] = 0; // This means it's unused
        }
    }
}