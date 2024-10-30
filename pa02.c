#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define OUTPUT_WIDTH 80

// Function to calculate checksum based on specified bit size
unsigned long calculate_checksum(const char *text, int length, int bit_size) {
    unsigned long checksum = 0;
    int padding = 0;
    
    // Calculate padding needed based on bit size
    if (bit_size == 16) {
        padding = length % 2;
    } else if (bit_size == 32) {
        padding = (4 - (length % 4)) % 4;
    }
    
    // Process each character
    for (int i = 0; i < length; i++) {
        checksum += (unsigned char)text[i];
    }
    
    // Add padding X's if needed
    for (int i = 0; i < padding; i++) {
        checksum += 'X';
    }
    
    // Mask the checksum based on bit size
    if (bit_size == 8) {
        checksum &= 0xFF;
    } else if (bit_size == 16) {
        checksum &= 0xFFFF;
    } else if (bit_size == 32) {
        checksum &= 0xFFFFFFFF;
    }
    
    return checksum;
}

int main(int argc, char *argv[]) {
    // Check command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <checksum_size>\n", argv[0]);
        return 1;
    }
    
    // Parse checksum size
    int checksum_size = atoi(argv[2]);
    if (checksum_size != 8 && checksum_size != 16 && checksum_size != 32) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }
    
    // Open input file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    
    // Read file content
    char content[MAX_LINE_LENGTH] = {0};
    int total_chars = 0;
    int c;
    
    while ((c = fgetc(file)) != EOF && total_chars < MAX_LINE_LENGTH - 1) {
        content[total_chars++] = (char)c;
        
        // Print characters in 80-character lines
        if (total_chars % OUTPUT_WIDTH == 0) {
            content[total_chars] = '\0';
            printf("%s", content);
            memset(content, 0, MAX_LINE_LENGTH);
            total_chars = 0;
        }
    }
    
    // Print remaining characters if any
    if (total_chars > 0) {
        content[total_chars] = '\0';
        printf("%s", content);
    }
    
    // Calculate and print checksum
    unsigned long checksum = calculate_checksum(content, total_chars, checksum_size);
    printf("%2d bit checksum is %8lx for all %4d chars\n", 
           checksum_size, checksum, total_chars);
    
    fclose(file);
    return 0;
}