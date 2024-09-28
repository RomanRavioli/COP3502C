#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_KEY_SIZE 9
#define MAX_TEXT_SIZE 10000

// Function prototypes
void readKeyFile(const char *filename, int *keySize, int key[MAX_KEY_SIZE][MAX_KEY_SIZE]);
void readPlainTextFile(const char *filename, char *plaintext);
void processPlaintext(char *plaintext, char *processedText);
void encryptHill(int keySize, int key[MAX_KEY_SIZE][MAX_KEY_SIZE], char *processedText, char *ciphertext);
void printOutput(int keySize, int key[MAX_KEY_SIZE][MAX_KEY_SIZE], char *plaintext, char *ciphertext);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <key_file> <plaintext_file>\n", argv[0]);
        return 1;
    }

    int keySize;
    int key[MAX_KEY_SIZE][MAX_KEY_SIZE];
    char plaintext[MAX_TEXT_SIZE];
    char processedText[MAX_TEXT_SIZE];
    char ciphertext[MAX_TEXT_SIZE];

    readKeyFile(argv[1], &keySize, key);
    readPlainTextFile(argv[2], plaintext);
    processPlaintext(plaintext, processedText);
    encryptHill(keySize, key, processedText, ciphertext);
    printOutput(keySize, key, processedText, ciphertext);

    return 0;
}

void readKeyFile(const char *filename, int *keySize, int key[MAX_KEY_SIZE][MAX_KEY_SIZE]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening key file");
        exit(1);
    }

    fscanf(file, "%d", keySize);
    for (int i = 0; i < *keySize; i++) {
        for (int j = 0; j < *keySize; j++) {
            fscanf(file, "%d", &key[i][j]);
        }
    }

    fclose(file);
}

void readPlainTextFile(const char *filename, char *plaintext) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening plaintext file");
        exit(1);
    }

    int c, i = 0;
    while ((c = fgetc(file)) != EOF && i < MAX_TEXT_SIZE - 1) {
        plaintext[i++] = c;
    }
    plaintext[i] = '\0';

    fclose(file);
}

void processPlaintext(char *plaintext, char *processedText) {
    int i = 0, j = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            processedText[j++] = tolower(plaintext[i]);
        }
        i++;
    }
    processedText[j] = '\0';
}

void encryptHill(int keySize, int key[MAX_KEY_SIZE][MAX_KEY_SIZE], char *processedText, char *ciphertext) {
    int textLen = strlen(processedText);
    int paddedLen = ((textLen + keySize - 1) / keySize) * keySize;
    char paddedText[MAX_TEXT_SIZE];
    
    // Pad the text with 'x' if necessary
    strcpy(paddedText, processedText);
    for (int i = textLen; i < paddedLen; i++) {
        paddedText[i] = 'x';
    }
    paddedText[paddedLen] = '\0';

    // Encrypt the padded text
    for (int i = 0; i < paddedLen; i += keySize) {
        int block[MAX_KEY_SIZE] = {0};
        int result[MAX_KEY_SIZE] = {0};

        // Convert a block of letters to numbers (a=0, b=1, ...)
        for (int j = 0; j < keySize; j++) {
            block[j] = paddedText[i + j] - 'a';
        }

        // Perform matrix multiplication
        for (int j = 0; j < keySize; j++) {
            for (int k = 0; k < keySize; k++) {
                result[j] += key[j][k] * block[k];
            }
            result[j] %= 26;  // Modulo 26 to keep within alphabet range
        }

        // Convert numbers back to letters
        for (int j = 0; j < keySize; j++) {
            ciphertext[i + j] = result[j] + 'a';
        }
    }
    ciphertext[paddedLen] = '\0';
}

void printOutput(int keySize, int key[MAX_KEY_SIZE][MAX_KEY_SIZE], char *plaintext, char *ciphertext) {
    printf("Key matrix:\n");
    for (int i = 0; i < keySize; i++) {
        for (int j = 0; j < keySize; j++) {
            printf("%4d", key[i][j]);
        }
        printf("\n");
    }

    printf("\nPlaintext:\n%s\n", plaintext);

    printf("\nCiphertext:\n");
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        printf("%c", ciphertext[i]);
        if ((i + 1) % 80 == 0) {
            printf("\n");
        }
    }
    if (len % 80 != 0) {
        printf("\n");
    }
}