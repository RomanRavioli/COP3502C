// This program demonstrates,
//  * How to make a circular linked list
//  * How to implement a Queue using a circular linked list
//  * How to use a dx/dy array for grid problems
//  * How to flood fill from a single point using a queue

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Queue Queue;

// Circular linked list
struct Node {
  int value;
  Node *next;
};

struct Queue {
  Node *tail; // circular linked list
};

// Linked List Prototypes
Node *createNode(int value);
Node *addTail(Node *tail, int value);
Node *removeHead(Node *tail);

// Queue Prototypes
void enqueue(Queue *q, int value);
void dequeue(Queue *q);
int front(Queue *q);

// Linked List Functions
// Function to create a node
Node *createNode(int value) {
  Node *res = (Node *)malloc(sizeof(Node));
  res->value = value;
  res->next = res; // circular
  return res;
}
// Return the resulting tail of the linked list
Node *addTail(Node *tail, int value) {
  Node *newTail = createNode(value);

  // 0 node check
  if (tail == NULL)
    return newTail;

  newTail->next = tail->next; // Point to head
  tail->next = newTail;       // The new tail comes after
  return newTail;             // Return resulting tail
}

// Function that removes the head of a circular linked list
// Returns the tail
Node *removeHead(Node *tail) {
  // 0 node check
  if (tail == NULL)
    return NULL; // list is empty
  // 1 node check
  if (tail == tail->next) {
    free(tail);
    return NULL;
  }
  Node *head = tail->next;
  tail->next = head->next; // cuts the head out of list
  free(head);              // remove excess memory
  return tail;             // Return the resulting tail
}

// Queue Functions
void enqueue(Queue *q, int value) { 
  q->tail = addTail(q->tail, value); 
}
void dequeue(Queue *q) { 
  q->tail = removeHead(q->tail); 
}
int front(Queue *q) {
  Node *head = q->tail->next;
  return head->value;
}

// The dimensions of the grid
#define COL 5
#define ROW 6

// Store the differenct movement directions as an array of
// x and y changes
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};

// The entry point of the program
int main() {
  // Hard code a grid
  char map[ROW][COL + 1] = {
    " x x ", 
    "xxxx ", 
    "    x",
    "xxx  ", 
    "  x  ", 
    "  x  "
  };

  // Start location
  int r1 = 0;
  int c1 = 4;

  // End location
  int r2 = 0;
  int c2 = 0;

  // Make an empty queue
  Queue q;
  q.tail = NULL;

  // Track visited areas
  int visited[ROW][COL];
  for (int i = 0; i < ROW; i++) {
    for (int j = 0; j < COL; j++) {
      visited[i][j] = 0;
    }
  }

  // Set the initial flooding point of the queue
  enqueue(&q, r1);
  enqueue(&q, c1);

  // Visit the starting location
  visited[r1][c1] = 1;

  // Remove locations from the queue until empty
  while (q.tail != NULL) {
    // Get a current location
    int curRow = front(&q);
    dequeue(&q);
    int curCol = front(&q);
    dequeue(&q);

    for (int dir = 0; dir < 8; dir++) {
      // Find the location to flood from our current position
      int nxtRow = curRow + dy[dir];
      int nxtCol = curCol + dx[dir];

      // Can we flood here pleas?
      if (nxtRow >= ROW)
        continue; // you bad
      if (nxtCol >= COL)
        continue; // you bad
      if (nxtCol < 0)
        continue; // you bad
      if (nxtRow < 0)
        continue; // you bad

      // Is this blocked
      if (map[nxtRow][nxtCol] == 'x')
        continue;

      // IS this location previously visited
      if (visited[nxtRow][nxtCol])
        continue;

      // We have a valid location
      visited[nxtRow][nxtCol] = 1;

      // Add to queue
      enqueue(&q, nxtRow);
      enqueue(&q, nxtCol);
    }
  }

  // Check if point 2 was visited
  if (visited[r2][c2]) {
    printf("FLOODED!!!\n");
  } else {
    printf("Safe!\n");
  }

  // Exit the program
  return 0;
}