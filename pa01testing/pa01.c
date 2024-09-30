/*============================================================================
| Assignment: pa01 - Encrypting a plaintext file using the Hill cipher
|
| Author: Roman Manuel
| Language: c
| To Compile: javac pa01.java
| gcc -o pa01 pa01.c
| g++ -o pa01 pa01.cpp
| go build pa01.go
| rustc pa01.rs
| To Execute: java -> java pa01 kX.txt pX.txt
| or c++ -> ./pa01 kX.txt pX.txt
| or c -> ./pa01 kX.txt pX.txt
| or go -> ./pa01 kX.txt pX.txt
| or rust -> ./pa01 kX.txt pX.txt
| or python -> python3 pa01.py kX.txt pX.txt
| where kX.txt is the keytext file
| and pX.txt is plaintext file
| Note:
| All input files are simple 8 bit ASCII input
| All execute commands above have been tested on Eustis
|
| Class: CIS3360 - Security in Computing - Fall 2024
| Instructor: McAlpin
| Due Date: 9/29/2024
+===========================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 9
#define MAXTEXT 10000

// Prototyping
void readK(const char *filename, int *size, int key[MAX][MAX]);
void readP(const char *filename, char *plaintext);
void processP(char *plaintext, char *newText, int size);
void hillCipher(int size, int key[MAX][MAX], char *newText, char *encryptedtext);
void printResult(int size, int key[MAX][MAX], char *newText, char *encryptedtext);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Wrong Usage! Use it like this: %s <key_file> <plaintext_file>\n", argv[0]);
        return 1;
    }

    int size;
    int key[MAX][MAX];
    char plaintext[MAXTEXT];
    char newText[MAXTEXT];
    char encryptedtext[MAXTEXT];

    readK(argv[1], &size, key);
    readP(argv[2], plaintext);
    processP(plaintext, newText, size);
    hillCipher(size, key, newText, encryptedtext);
    printResult(size, key, newText, encryptedtext);

    // Error code 0
    return 0;
}

// This reads the key files that contain the key for Hill Cipher (ie. k0.txt)
void readK(const char *filename, int *size, int key[MAX][MAX]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Can't open. Something wrong with file");
        exit(1);
    }

    fscanf(file, "%d", size);
    for (int i = 0; i < *size; i++) {
        for (int j = 0; j < *size; j++) {
            fscanf(file, "%d", &key[i][j]);
        }
    }

    fclose(file);
}

// This reads the processed text files used before encrypting using the Hill Cipher
void readP(const char *filename, char *plaintext) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Can't open px.txt");
        exit(1);
    }

    int c, i = 0;
    while ((c = fgetc(file)) != EOF && i < MAXTEXT - 1) {
        plaintext[i++] = c;
    }
    plaintext[i] = '\0';

    fclose(file);
}

// This processes the p0.txt files so it can be used for encrypting
void processP(char *plaintext, char *newText, int size) {
    int i = 0, j = 0;
    while (plaintext[i] != '\0') {
        if (isalpha(plaintext[i])) {
            newText[j++] = tolower(plaintext[i]);
        }
        i++;
    }
    
    // 'x' padding'
    while (j % size != 0) {
        newText[j++] = 'x';
    }
    newText[j] = '\0';
}

// This begins decrypting the plaintext using HillCipher encryption
void hillCipher(int size, int key[MAX][MAX], char *newText, char *encryptedtext) {
    int textLen = strlen(newText);

    for (int i = 0; i < textLen; i += size) {
        int block[MAX] = {0};
        int result[MAX] = {0};

        // Changes letters to the ASCII version
        for (int j = 0; j < size; j++) {
            block[j] = newText[i + j] - 'a';
        }

        // Do matrix multiplication according to the PDF instructions
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                result[j] += key[j][k] * block[k];
            }
            result[j] %= 26;  // Mods by 26 to keep it within the alphabet
        }

        // Changes numbers back to letters
        for (int j = 0; j < size; j++) {
            encryptedtext[i + j] = result[j] + 'a';
        }
    }
    encryptedtext[textLen] = '\0';
}

// Prints out the results after encryption/decryption
void printResult(int size, int key[MAX][MAX], char *newText, char *encryptedtext) {
    printf("Key matrix:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%4d", key[i][j]);
        }
        printf("\n");
    }

    printf("\nPlaintext:\n");
    int len = strlen(newText);
    for (int i = 0; i < len; i++) {
        printf("%c", newText[i]);
        if ((i + 1) % 80 == 0) {
            printf("\n");
        }
    }
    if (len % 80 != 0) {
        printf("\n");
    }

    printf("\nCiphertext:\n");
    len = strlen(encryptedtext);
    for (int i = 0; i < len; i++) {
        printf("%c", encryptedtext[i]);
        if ((i + 1) % 80 == 0) {
            printf("\n");
        }
    }
    if (len % 80 != 0) {
        printf("\n");
    }
}
/*=============================================================================
| I Roman Manuel (ro851159) affirm that this program is
| entirely my own work and that I have neither developed my code together with
| any another person, nor copied any code from any other person, nor permitted
| my code to be copied or otherwise used by any other person, nor have I
| copied, modified, or otherwise used programs created by others. I acknowledge
| that any violation of the above terms will be treated as academic dishonesty.
+=============================================================================*/