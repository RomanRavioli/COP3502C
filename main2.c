/* COP 3502C Assignment 5 
// This program is written by: Roman Manuel */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 26

// BST node
typedef struct Node {
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
Node *createNode(const char *name, int fine) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->fine = fine;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Inserts node
Node *insert(Node *root, const char *name, int fine, int *depth) {
    if (root == NULL) {
        return createNode(name, fine);
    }

    int compare = strcmp(name, root->name);
    if (compare < 0) {
        *depth = *depth + 1;
        root->left = insert(root->left, name, fine, depth);
    }
    else if (compare > 0) {
        *depth = *depth + 1;
        root->right = insert(root->right, name, fine, depth);
    }
    else {
        root->fine = root->fine + fine;
    }
    return root;
}

// Searches node
Node *search(Node *root, const char *name, int *depth, int *fine) {
    if (root == NULL) {
        return NULL;
    }

    int compare = strcmp(name, root->name);
    if (compare == 0) {
        *fine = root->fine;
        return root;
    }

    *depth = *depth + 1;
    if (compare < 0) {
        return search(root->left, name, depth, fine);
    }
    return search(root->right, name, depth, fine);
}

// Finds max
Node *findMax(Node *root) {
    while (root != NULL && root->right != NULL) {
        root = root->right;
    }
    return root;
}

// The delete function
Node *delete(Node *root, const char *name) {
    if (root == NULL) {
        return NULL;
    }

    int compare = strcmp(name, root->name);
    
    if (compare < 0) {
        root->left = delete(root->left, name);
        return root;
    }
    if (compare > 0) {
        root->right = delete(root->right, name);
        return root;
    }
    
    // Leaf node
    if (root->left == NULL && root->right == NULL) {
        free(root);
        return NULL;
    }
    
    // One child
    if (root->left == NULL) {
        Node *temp = root->right;
        free(root);
        return temp;
    }
    if (root->right == NULL) {
        Node *temp = root->left;
        free(root);
        return temp;
    }
    
    // Two childs
    Node *maxNode = findMax(root->left);
    strcpy(root->name, maxNode->name);
    root->fine = maxNode->fine;
    root->left = delete(root->left, maxNode->name);
    
    return root;
}

// Calculates height
int height(Node *root) {
    if (root == NULL) {
        return -1;
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

// Calculate avg
double calcAvg(Node *root, int *count, double *sum) {
    if (root == NULL) {
        return 0;
    }
    *count = *count + 1;
    *sum = *sum + root->fine;
    calcAvg(root->left, count, sum);
    calcAvg(root->right, count, sum);
    return *sum / *count;
}

// Calculates fines below a certain name
int calcBelow(Node *root, const char *name) {
    if (root == NULL) {
        return 0;
    }

    int sum = 0;
    int compare = strcmp(name, root->name);

    if (compare >= 0) {
        sum = sum + root->fine;
        sum = sum + calcBelow(root->left, name);
        sum = sum + calcBelow(root->right, name);
    }
    else {
        sum = sum + calcBelow(root->left, name);
    }

    return sum;
}

// Frees memory
void freeTree(Node *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// The main function
int main() {
    Node *root = NULL;
    int n;
    scanf("%d", &n);

    char command[20], name[MAX_NAME_LENGTH];
    int fine, depth;

    while (n > 0) {
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf("%s %d", name, &fine);
            depth = 0;
            root = insert(root, name, fine, &depth);
            int currentFine = 0;
            depth = 0;
            search(root, name, &depth, &currentFine);
            printf("%s %d %d\n", name, currentFine, depth);
        }
        else if (strcmp(command, "deduct") == 0) {
            scanf("%s %d", name, &fine);
            depth = 0;
            int currentFine = 0;
            Node *found = search(root, name, &depth, &currentFine);

            if (found != NULL) {
                if (currentFine <= fine) {
                    root = delete(root, name);
                    printf("%s removed\n", name);
                }
                else {
                    found->fine = found->fine - fine;
                    printf("%s %d %d\n", name, found->fine, depth);
                }
            }
            else {
                printf("%s not found\n", name);
            }
        }
        else if (strcmp(command, "search") == 0) {
            scanf("%s", name);
            depth = 0;
            int currentFine = 0;
            Node *found = search(root, name, &depth, &currentFine);

            if (found != NULL) {
                printf("%s %d %d\n", name, currentFine, depth);
            }
            else {
                printf("%s not found\n", name);
            }
        }
        else if (strcmp(command, "average") == 0) {
            int count = 0;
            double sum = 0;
            if (root != NULL) {
                calcAvg(root, &count, &sum);
                printf("%.2f\n", sum / count);
            }
        }
        else if (strcmp(command, "height_balance") == 0) {
            int leftHeight;
            int rightHeight;
            if (root == NULL) {
                leftHeight = -1;
                rightHeight = -1;
            } else {
                leftHeight = height(root->left);
                rightHeight = height(root->right);
            }
            if (leftHeight == rightHeight) {
                printf("left height = %d right height = %d balanced\n", leftHeight, rightHeight);
            } else {
                printf("left height = %d right height = %d not balanced\n", leftHeight, rightHeight);
            }
        }
        else if (strcmp(command, "calc_below") == 0) {
            scanf("%s", name);
            int total = calcBelow(root, name);
            printf("%d\n", total);
        }
        n = n - 1;
    }

    // Calls the free memory function
    freeTree(root);

    // Exits the program
    return 0;
}