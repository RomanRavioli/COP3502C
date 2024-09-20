# Import deque for efficient queue operations (not used in this implementation, but commonly used for queues)
from collections import deque

# Define a Node class for our linked list
class Node:
    def __init__(self, value):
        self.value = value  # Store the value of the node
        self.next = None    # Reference to the next node, initially None

# Define a Queue class using a circular linked list
class Queue:
    def __init__(self):
        self.tail = None  # Initialize the queue with no elements

    def enqueue(self, value):
        new_node = Node(value)  # Create a new node with the given value
        if not self.tail:  # If the queue is empty
            new_node.next = new_node  # Make the new node point to itself
            self.tail = new_node  # Set the tail to the new node
        else:  # If the queue is not empty
            new_node.next = self.tail.next  # New node points to the head
            self.tail.next = new_node  # The old tail points to the new node
            self.tail = new_node  # Update the tail to the new node

    def dequeue(self):
        if not self.tail:  # If the queue is empty
            return None  # Return None as there's nothing to dequeue
        if self.tail.next == self.tail:  # If there's only one element
            value = self.tail.value  # Get the value
            self.tail = None  # Set the tail to None (empty queue)
            return value  # Return the value
        value = self.tail.next.value  # Get the value of the head
        self.tail.next = self.tail.next.next  # Remove the head from the list
        return value  # Return the value

    def front(self):
        if not self.tail:  # If the queue is empty
            return None  # Return None as there's no front element
        return self.tail.next.value  # Return the value of the head

    def is_empty(self):
        return self.tail is None  # True if the queue is empty, False otherwise

# Define the dimensions of the grid
COL, ROW = 5, 6

# Define movement directions (8 directions: N, NE, E, SE, S, SW, W, NW)
dx = [0, 1, 1, 1, 0, -1, -1, -1]  # Change in x-coordinate for each direction
dy = [1, 1, 0, -1, -1, -1, 0, 1]  # Change in y-coordinate for each direction

def main():
    # Define the grid map
    map_grid = [
        " x x ",
        "xxxx ",
        "    x",
        "xxx  ",
        "  x  ",
        "  x  "
    ]

    # Define start and end locations
    r1, c1 = 0, 4  # Start location (row, column)
    r2, c2 = 0, 0  # End location (row, column)

    # Create an empty queue
    q = Queue()

    # Create a 2D list to track visited cells
    visited = [[False for _ in range(COL)] for _ in range(ROW)]

    # Enqueue the starting point
    q.enqueue(r1)
    q.enqueue(c1)

    # Mark the starting point as visited
    visited[r1][c1] = True

    # Continue until the queue is empty
    while not q.is_empty():
        # Get the current location from the queue
        cur_row = q.dequeue()
        cur_col = q.dequeue()

        # Check all 8 directions
        for dir in range(8):
            # Calculate the next cell coordinates
            nxt_row = cur_row + dy[dir]
            nxt_col = cur_col + dx[dir]

            # Check if the next cell is within the grid
            if nxt_row < 0 or nxt_row >= ROW or nxt_col < 0 or nxt_col >= COL:
                continue  # Skip if out of bounds

            # Check if the next cell is blocked
            if map_grid[nxt_row][nxt_col] == 'x':
                continue  # Skip if blocked

            # Check if the next cell has been visited
            if visited[nxt_row][nxt_col]:
                continue  # Skip if already visited

            # Mark the next cell as visited
            visited[nxt_row][nxt_col] = True

            # Enqueue the next cell
            q.enqueue(nxt_row)
            q.enqueue(nxt_col)

    # Check if the end point was visited
    if visited[r2][c2]:
        print("FLOODED!!!")  # Path exists between start and end
    else:
        print("Safe!")  # No path exists between start and end

# Run the main function if this script is executed
if __name__ == "__main__":
    main()