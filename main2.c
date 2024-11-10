/* COP 3502C Assignment 5
// This program is written by: Roman Manuel */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 26

// BST node
typedef struct Node
{
    char name[MAX_NAME_LENGTH];
    int fine;
    struct Node *left;
    struct Node *right;
} Node;

// Function prototypes
Node *createNode(const char *name, int fine);
Node *insert(Node *root, const char *name, int fine, int *depth);
Node *search(Node *root, const char *name, int *depth, int *fine);
Node *findMax(Node *root);
Node *delete(Node *root, const char *name);
int height(Node *root);
double calcAvg(Node *root, int *count, double *sum);
int calcBelow(Node *root, const char *name);
void freeTree(Node *root);

// Creates node
Node *createNode(const char *name, int fine)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->fine = fine;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Inserts node
Node *insert(Node *root, const char *name, int fine, int *depth)
{
    if (root == NULL)
    {
        return createNode(name, fine);
    }

    int compare = strcmp(name, root->name);
    if (compare < 0)
    {
        (*depth)++;
        root->left = insert(root->left, name, fine, depth);
    }
    else if (compare > 0)
    {
        (*depth)++;
        root->right = insert(root->right, name, fine, depth);
    }
    else
    {
        root->fine += fine;
    }
    return root;
}

// Search a node
Node *search(Node *root, const char *name, int *depth, int *fine)
{
    if (root == NULL)
    {
        return NULL;
    }

    int compare = strcmp(name, root->name);
    if (compare == 0)
    {
        *fine = root->fine;
        return root;
    }

    (*depth)++;
    if (compare < 0)
    {
        return search(root->left, name, depth, fine);
    }
    return search(root->right, name, depth, fine);
}

// Finds max
Node *findMax(Node *root)
{
    if (root == NULL || root->right == NULL)
    {
        return root;
    }
    return findMax(root->right);
}

// Deletes node
Node *delete(Node *root, const char *name)
{
    if (root == NULL)
    {
        return NULL;
    }

    int compare = strcmp(name, root->name);
    if (compare < 0)
    {
        root->left = delete (root->left, name);
    }
    else if (compare > 0)
    {
        root->right = delete (root->right, name);
    }
    else
    {
        // One child or no child
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // Two children: Get max from left subtree
        Node *temp = findMax(root->left);
        strcpy(root->name, temp->name);
        root->fine = temp->fine;
        root->left = delete (root->left, temp->name);
    }
    return root;
}

// Calculates height
int height(Node *root)
{
    if (root == NULL)
    {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Get avg fine
double calcAvg(Node *root, int *count, double *sum)
{
    if (root == NULL)
    {
        return 0;
    }
    (*count)++;
    *sum += root->fine;
    calcAvg(root->left, count, sum);
    calcAvg(root->right, count, sum);
    return *sum / *count;
}

// Gets sum of fines
int calcBelow(Node *root, const char *name)
{
    if (root == NULL)
    {
        return 0;
    }

    int sum = 0;
    int compare = strcmp(name, root->name);

    if (compare >= 0)
    {
        sum += root->fine;
        sum += calcBelow(root->left, name);
        sum += calcBelow(root->right, name);
    }
    else
    {
        sum += calcBelow(root->left, name);
    }

    return sum;
}

// Free memory
void freeTree(Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// The main function
int main()
{
    Node *root = NULL;
    int n;
    scanf("%d", &n);

    char command[20], name[MAX_NAME_LENGTH];
    int fine, depth;

    while (n--)
    {
        scanf("%s", command);

        if (strcmp(command, "add") == 0)
        {
            scanf("%s %d", name, &fine);
            depth = 0;
            root = insert(root, name, fine, &depth);
            int currentFine = 0;
            search(root, name, &depth, &currentFine);
            printf("%s %d %d\n", name, currentFine, depth);
        }
        else if (strcmp(command, "deduct") == 0)
        {
            scanf("%s %d", name, &fine);
            depth = 0;
            int currentFine = 0;
            Node *found = search(root, name, &depth, &currentFine);

            if (found != NULL)
            {
                if (currentFine <= fine)
                {
                    root = delete (root, name);
                    printf("%s removed\n", name);
                }
                else
                {
                    found->fine -= fine;
                    printf("%s %d %d\n", name, found->fine, depth);
                }
            }
            else
            {
                printf("%s not found\n", name);
            }
        }
        else if (strcmp(command, "search") == 0)
        {
            scanf("%s", name);
            depth = 0;
            int currentFine = 0;
            Node *found = search(root, name, &depth, &currentFine);

            if (found != NULL)
            {
                printf("%s %d %d\n", name, currentFine, depth);
            }
            else
            {
                printf("%s not found\n", name);
            }
        }
        else if (strcmp(command, "average") == 0)
        {
            int count = 0;
            double sum = 0;
            if (root != NULL)
            {
                calcAvg(root, &count, &sum);
                printf("%.2f\n", sum / count);
            }
        }
        else if (strcmp(command, "height_balance") == 0)
        {
            int leftHeight = root ? height(root->left) : -1;
            int rightHeight = root ? height(root->right) : -1;
            printf("left height = %d right height = %d %s\n",
                   leftHeight, rightHeight,
                   leftHeight == rightHeight ? "balanced" : "not balanced");
        }
        else if (strcmp(command, "calc_below") == 0)
        {
            scanf("%s", name);
            int total = calcBelow(root, name);
            printf("%d\n", total);
        }
    }

    freeTree(root);

    // Exits the program
    return 0;
}