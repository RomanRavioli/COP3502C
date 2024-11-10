#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 80

void printFormattedInput(const char *text, int length) {
    for (int i = 0; i < length; i++) {
        printf("%c", text[i]);
        if ((i + 1) % MAX_LINE_LENGTH == 0) {
            printf("\n");
        }
    }
    if (length % MAX_LINE_LENGTH != 0) {
        printf("\n");
    }
}

unsigned long calculateChecksum(const char *text, int length, int checksumSize) {
    unsigned long checksum = 0;
    int paddingNeeded = 0;
    
    // Calculate padding needed
    if (checksumSize == 16) {
        paddingNeeded = (length % 2) ? 1 : 0;
    } else if (checksumSize == 32) {
        paddingNeeded = (4 - (length % 4)) % 4;
    }
    
    // Process text byte by byte
    for (int i = 0; i < length; i++) {
        if (checksumSize == 8) {
            checksum = (checksum + (unsigned char)text[i]) & 0xFF;
        } else if (checksumSize == 16) {
            checksum = (checksum << 8) | (unsigned char)text[i];
            if (i % 2 == 1) {
                checksum = checksum & 0xFFFF;
            }
        } else if (checksumSize == 32) {
            checksum = (checksum << 8) | (unsigned char)text[i];
            if (i % 4 == 3) {
                checksum = checksum & 0xFFFFFFFF;
            }
        }
    }
    
    // Handle padding
    for (int i = 0; i < paddingNeeded; i++) {
        if (checksumSize == 16) {
            checksum = (checksum << 8) | 'X';
            if ((length + i) % 2 == 1) {
                checksum = checksum & 0xFFFF;
            }
        } else if (checksumSize == 32) {
            checksum = (checksum << 8) | 'X';
            if ((length + i) % 4 == 3) {
                checksum = checksum & 0xFFFFFFFF;
            }
        }
    }
    
    // Final masking
    if (checksumSize == 8) {
        checksum = checksum & 0xFF;
    } else if (checksumSize == 16) {
        checksum = checksum & 0xFFFF;
    } else if (checksumSize == 32) {
        checksum = checksum & 0xFFFFFFFF;
    }
    
    return checksum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input_file> <checksum_size>\n", argv[0]);
        return 1;
    }
    
    int checksumSize = atoi(argv[2]);
    if (checksumSize != 8 && checksumSize != 16 && checksumSize != 32) {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 1;
    }
    
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    
    char *buffer = NULL;
    size_t bufferSize = 0;
    int characterCnt = 0;
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        if (characterCnt >= bufferSize) {
            bufferSize = bufferSize ? bufferSize * 2 : 1024;
            buffer = realloc(buffer, bufferSize);
            if (!buffer) {
                fprintf(stderr, "Memory allocation failed\n");
                fclose(file);
                return 1;
            }
        }
        buffer[characterCnt++] = (char)c;
    }
    
    fclose(file);
    printFormattedInput(buffer, characterCnt);
    
    unsigned long checksum = calculateChecksum(buffer, characterCnt, checksumSize);
    printf("%2d bit checksum is %8lx for all %4d chars\n", 
           checksumSize, checksum, characterCnt);
    
    free(buffer);
    return 0;
}