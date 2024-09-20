#include <stdio.h>
#include <stdlib.h>

#define MAX 2000  // Maximum grid size

int R, C;  // Dimensions of the grid
char grid[MAX][MAX + 1];  // Grid to store the inscription
int region[MAX][MAX];  // To mark regions by flood fill
int region_size[MAX * MAX];  // To store the size of each region
int region_count = 0;  // Total number of regions
int dx[4] = {0, 1, 0, -1};  // x direction for 4 possible moves (right, down, left, up)
int dy[4] = {1, 0, -1, 0};  // y direction for 4 possible moves (right, down, left, up)

// Function to check if a point is within the grid
int in_bounds(int x, int y) {
    return x >= 0 && x < R && y >= 0 && y < C;
}

// Flood fill to identify regions of connected free points
void flood_fill(int x, int y) {
    // Create a queue for flood fill
    int queue[MAX * MAX][2];
    int front = 0, back = 0;

    queue[back][0] = x;
    queue[back++][1] = y;

    region[x][y] = region_count;
    region_size[region_count]++;

    // Process the queue
    while (front < back) {
        int curX = queue[front][0];
        int curY = queue[front++][1];

        // Explore 4 possible directions (up, down, left, right)
        for (int dir = 0; dir < 4; dir++) {
            int nx = curX + dx[dir];
            int ny = curY + dy[dir];

            // If the neighbor is in bounds and is a free point that hasn't been visited
            if (in_bounds(nx, ny) && grid[nx][ny] == '.' && region[nx][ny] == -1) {
                region[nx][ny] = region_count;
                region_size[region_count]++;
                queue[back][0] = nx;
                queue[back++][1] = ny;
            }
        }
    }
}

// Function to calculate the magic flow for a region size
long long calculate_magic(int n) {
    return (long long)n * (n + 1) / 2;  // Formula: n(n + 1) / 2
}

int main() {
    // Read the grid dimensions
    scanf("%d %d", &R, &C);

    // Read the grid itself
    for (int i = 0; i < R; i++) {
        scanf("%s", grid[i]);
    }

    // Initialize the region array with -1 (unvisited)
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            region[i][j] = -1;
        }
    }

    // Flood fill to identify connected regions of free points ('.')
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == '.' && region[i][j] == -1) {
                flood_fill(i, j);
                region_count++;
            }
        }
    }

    // Calculate the total initial magic flow
    long long total_magic = 0;
    for (int i = 0; i < region_count; i++) {
        total_magic += calculate_magic(region_size[i]);
    }

    // Now check each potential failure point ('X')
    long long max_magic = total_magic;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (grid[i][j] == 'X') {
                // We're testing a failure at this point (turn 'X' into '.')

                // Set to store unique regions adjacent to this 'X'
                int adjacent_regions[4] = {-1, -1, -1, -1};
                int new_region_size = 1;  // The point itself becomes a new free point

                for (int dir = 0; dir < 4; dir++) {
                    int ni = i + dx[dir];
                    int nj = j + dy[dir];

                    if (in_bounds(ni, nj) && grid[ni][nj] == '.' && region[ni][nj] != -1) {
                        int r = region[ni][nj];
                        int already_seen = 0;
                        for (int k = 0; k < 4; k++) {
                            if (adjacent_regions[k] == r) {
                                already_seen = 1;
                                break;
                            }
                        }
                        if (!already_seen) {
                            // Add this region's size to the new region size
                            new_region_size += region_size[r];
                            adjacent_regions[dir] = r;  // Mark this region as seen
                        }
                    }
                }

                // Calculate the new total magic flow after failure at (i, j)
                long long new_magic = total_magic;

                // Subtract magic of the regions we are merging
                for (int k = 0; k < 4; k++) {
                    if (adjacent_regions[k] != -1) {
                        new_magic -= calculate_magic(region_size[adjacent_regions[k]]);
                    }
                }

                // Add the new region's magic
                new_magic += calculate_magic(new_region_size);

                // Update the maximum magic flow found
                if (new_magic > max_magic) {
                    max_magic = new_magic;
                }
            }
        }
    }

    // Output the maximum magic flow
    printf("%lld\n", max_magic);

    return 0;
}