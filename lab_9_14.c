#include <stdio.h>

struct Node

Node * removeByValue(Node * head, int value) {
    if (head == NULL) return NULL; // Empty list case

    // Check if the head should be removed
    if (head->value == value) {
        Node * newHead = head->next;
        free(head);
        return newHead;
    }
}

// Return a value signalling whether a value was contained or not
int contains (Node * head, int value) [
// Iterate to the end
while (head ! = NULL) {
// Check if the head has the value now
if (head->value == value) 
    return 1;
｝
// Move to the next spot
head = head->next;
// Never stopped, so the result is o
return 0;
// Return the head of the resulting list
Node * removeByValue(Node * head, int value) ‹
if (head == NULL) return NULL; // Empty list case
// Check if the head should be removed
if
(head->value == value) {
Node * newHead = head->next;
free (head);
return newHead:

int main() {
    printf("Hello world\n");

    return 0;
}