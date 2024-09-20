#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Queue Functions
// n-1 + 8*(n-1) - 1 + 8*(n-2) - 1 .. + 7 = 4*n*(n+1) = 4*10*11 = 440

void enqueue Queue * que, int value) {
    push (&(que->stk), value);
}
void dequeue Queue * que) {
    Stack tmp;
    tmp. head = NULL;
    flip (&tmp, &(que->stk));
    pop (&tmp) ;
    flip (&(que>stk), &tmp);
}
int front (Queue * que) {
    Stack tmp;
    tmp. head = NULL;
    flip (&tmp, &(que->stk));
    int rel = top (&tmp) ;
    flip(&(que->stk), &tmp);
    return res;
}

// The main function
int main () {

}