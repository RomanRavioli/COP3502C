#include <stdio.h>
#include <stdlib.h>

// Define structures for Node and Queue
typedef struct Node Node;
typedef struct Queue Queue;

// Circular linked list node structure
struct Node {
  int value;        // stores the value for each node
  Node *next;       // pointer to the next node in the circular linked list
};

// Queue structure, implemented using a circular linked list
struct Queue {
  Node *tail;       // pointer to the tail node of the circular linked list
};

// Function prototypes for the linked list
Node *createNode(int value);     // Create a new node
Node *addTail(Node *tail, int value);  // Add a node to the tail of the circular list
Node *removeHead(Node *tail);    // Remove the head node from the circular list

// Function prototypes for queue operations
void enqueue(Queue *q, int value);  // Add an element to the queue
void dequeue(Queue *q);             // Remove an element from the queue
int front(Queue *q);                // Get the front element from the queue

// Linked List Functions

// Function to create a new node with a given value
Node *createNode(int value) {
  Node *res = (Node *)malloc(sizeof(Node));  // Allocate memory for a new node
  res->value = value;        // Set the node's value
  res->next = res;           // Set the next pointer to itself (circular list with one node)
  return res;                // Return the newly created node
}

// Function to add a node with a given value to the tail of the circular list
Node *addTail(Node *tail, int value) {
  Node *newTail = createNode(value);  // Create a new node

  // Check if the list is empty (0 nodes)
  if (tail == NULL)
    return newTail;         // If empty, the new node becomes the tail

  newTail->next = tail->next; // Set the new node's next pointer to the head of the list
  tail->next = newTail;       // Set the current tail's next to the new node (new tail)
  return newTail;             // Return the new tail of the list
}

// Function to remove the head of the circular linked list
// This keeps the circular nature intact while removing the first element
Node *removeHead(Node *tail) {
  // Check if the list is empty (0 nodes)
  if (tail == NULL)
    return NULL;           // Return NULL since there's nothing to remove

  // Check if the list has only one node
  if (tail == tail->next) {
    free(tail);            // Free the memory of the single node
    return NULL;           // The list becomes empty
  }

  // If there are more than one node, remove the head
  Node *head = tail->next;    // Head is the node next to the tail
  tail->next = head->next;    // Tail now points to the new head (second node)
  free(head);                 // Free the memory of the old head
  return tail;                // Return the updated tail
}

// Queue Functions

// Function to add an element to the queue
// This is done by adding a new element to the tail of the circular linked list
void enqueue(Queue *q, int value) { 
  q->tail = addTail(q->tail, value);  // Add the new element to the queue's tail
}

// Function to remove an element from the queue (dequeue)
// This is done by removing the head of the circular linked list
void dequeue(Queue *q) { 
  q->tail = removeHead(q->tail);  // Remove the head of the circular list (first element)
}

// Function to return the front element of the queue (the head of the list)
int front(Queue *q) {
  Node *head = q->tail->next;   // The front element is the node next to the tail (head)
  return head->value;           // Return the value of the front element
}

// Constants to define the grid dimensions (rows and columns)
#define COL 5
#define ROW 6

// Arrays representing the 8 possible movement directions in a grid
// dx and dy represent the changes in the x (column) and y (row) coordinates
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

// Main function to run the flood fill algorithm
int main() {
  // Hardcoded grid to represent obstacles ('x') and free spaces (' ')
  char map[ROW][COL + 1] = {
    " x x ", 
    "xxxx ", 
    "    x",
    "xxx  ", 
    "  x  ", 
    "  x  "
  };

  // Starting location (row 0, column 4)
  int r1 = 0;
  int c1 = 4;

  // Target location to check if it gets flooded (row 0, column 0)
  int r2 = 0;
  int c2 = 0;

  // Initialize an empty queue
  Queue q;
  q.tail = NULL;

  // Create a 2D array to track visited cells
  int visited[ROW][COL];
  // Initialize all cells as not visited (0)
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      visited[i][j] = 0;
    }
  }

  // Enqueue the starting location (row 1, column 4)
  enqueue(&q, r1);  // Enqueue row
  enqueue(&q, c1);  // Enqueue column

  // Mark the starting location as visited
  visited[r1][c1] = 1;

  // Loop until the queue is empty (no more locations to process)
  while (q.tail != NULL) {
    // Dequeue the current row and column
    int curRow = front(&q);  // Get the current row
    dequeue(&q);             // Remove it from the queue
    int curCol = front(&q);  // Get the current column
    dequeue(&q);             // Remove it from the queue

    // Try all 8 possible movement directions from the current location
    for (int dir = 0; dir < 8; dir++) {
      // Calculate the next row and column based on the current direction
      int nxtRow = curRow + dy[dir];
      int nxtCol = curCol + dx[dir];

      // Boundary checks to ensure the next position is within the grid
      if (nxtRow >= ROW || nxtRow < 0 || nxtCol >= COL || nxtCol < 0)
        continue;  // If out of bounds, skip this direction

      // Check if the next cell is blocked ('x') or already visited
      if (map[nxtRow][nxtCol] == 'x' || visited[nxtRow][nxtCol])
        continue;  // Skip blocked or visited cells

      // Mark the new location as visited
      visited[nxtRow][nxtCol] = 1;

      // Enqueue the valid next location
      enqueue(&q, nxtRow);
      enqueue(&q, nxtCol);
    }
  }

  // Check if the target location (r2, c2) was flooded
  if (visited[r2][c2]) {
    printf("FLOODED!!!\n");  // If visited, it was flooded
  } else {
    printf("Safe!\n");       // Otherwise, it's safe
  }

  return 0;  // End the program
}
/*
Explanation:

	1.	Circular Linked List:
	•	This part of the program demonstrates how to create a circular linked list, where the last node points back to the first, forming a loop.
	•	Important functions include:
	•	createNode: Creates a new node.
	•	addTail: Adds a node to the end of the list (updating the tail).
	•	removeHead: Removes the head node from the list while keeping it circular.
	2.	Queue Implementation:
	•	The program implements a queue using the circular linked list. A queue is a data structure where elements are added to the rear (enqueue) and removed from the front (dequeue).
	•	Functions like enqueue, dequeue, and front are provided to manage the queue.
	3.	dx/dy Arrays:
	•	These arrays are used to represent the 8 possible directions of movement in a grid. Each pair of dx[i] and dy[i] gives the change in row and column for that direction.
	4.	Flood Fill Algorithm:
	•	The flood fill algorithm starts at a specific point and spreads to all neighboring open cells, simulating the process of filling a connected area.
	•	The queue is used to manage which cells to process next. When a new cell is “visited,” it is marked, and its neighbors are added to the queue.
	•	This algorithm is important in grid-based problems such as pathfinding or filling areas in images.
	5.	Grid and Obstacles:
	•	The grid is represented as a 2D array where 'x' represents obstacles that block the flood from spreading.
	•	The algorithm checks whether a specific target location gets flooded, demonstrating how the flood fill spreads across a grid.
*/